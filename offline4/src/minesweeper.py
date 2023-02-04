import itertools
import random


class Minesweeper():
    """
    Minesweeper game representation
    """

    def __init__(self, height=8, width=8, mines=8):

        # Set initial width, height, and number of mines
        self.height = height
        self.width = width
        self.mines: set[tuple[int, int]] = set()

        # Initialize an empty field with no mines
        self.board: list[list[bool]] = []
        for i in range(self.height):
            row = []
            for j in range(self.width):
                row.append(False)
            self.board.append(row)

        # Add mines randomly
        while len(self.mines) != mines:
            i = random.randrange(height)
            j = random.randrange(width)
            if not self.board[i][j]:
                self.mines.add((i, j))
                self.board[i][j] = True

        # At first, player has found no mines
        self.mines_found: set[tuple[int, int]] = set()

    def print(self):
        """
        Prints a text-based representation
        of where mines are located.
        """
        for i in range(self.height):
            print("--" * self.width + "-")
            for j in range(self.width):
                if self.board[i][j]:
                    print("|X", end="")
                else:
                    print("| ", end="")
            print("|")
        print("--" * self.width + "-")

    def is_mine(self, cell: tuple[int, int]):
        i, j = cell
        return self.board[i][j]

    def nearby_mines(self, cell: tuple[int, int]):
        """
        Returns the number of mines that are
        within one row and column of a given cell,
        not including the cell itself.
        """

        # Keep count of nearby mines
        count = 0

        # Loop over all cells within one row and column
        for i in range(cell[0] - 1, cell[0] + 2):
            for j in range(cell[1] - 1, cell[1] + 2):

                # Ignore the cell itself
                if (i, j) == cell:
                    continue

                # Update count if cell in bounds and is mine
                if 0 <= i < self.height and 0 <= j < self.width:
                    if self.board[i][j]:
                        count += 1

        return count

    def won(self):
        """
        Checks if all mines have been flagged.
        """
        return self.mines_found == self.mines


class Sentence():
    """
    Logical statement about a Minesweeper game
    A sentence consists of a set of board cells,
    and a count of the number of those cells which are mines.
    """

    def __init__(self, cells: list[tuple[int, int]], count: int):
        self.cells = set(cells)
        self.count = count

    def __eq__(self, other: "Sentence"):
        return self.cells == other.cells and self.count == other.count

    def __str__(self):
        return f"{self.cells} = {self.count}"

    def known_mines(self) -> set[tuple[int, int]]:
        """
        Returns the set of all cells in self.cells known to be mines.
        """
        return self.cells.copy() if self.count == len(self.cells) else set()

    def known_safes(self) -> set[tuple[int, int]]:
        """
        Returns the set of all cells in self.cells known to be safe.
        """
        return self.cells.copy() if self.count == 0 else set()

    def mark_mine(self, cell: tuple[int, int]):
        """
        Updates internal knowledge representation given the fact that
        a cell is known to be a mine.
        """
        if cell in self.cells:
            self.cells.remove(cell)
            self.count -= 1  # TODO: assuming this will execute only if count is greater than zero

    def mark_safe(self, cell: tuple[int, int]):
        """
        Updates internal knowledge representation given the fact that
        a cell is known to be safe.
        """
        # TODO: assuming if discarding cell makes sentence empty, count cannot be nonzero
        self.cells.discard(cell)


class MinesweeperAI():
    """
    Minesweeper game player
    """

    def __init__(self, height=8, width=8):

        # Set initial height and width
        self.height = height
        self.width = width

        # Keep track of which cells have been clicked on
        self.moves_made: set[tuple[int, int]] = set()

        # Keep track of cells known to be safe or mines
        self.mines: set[tuple[int, int]] = set()
        self.safes: set[tuple[int, int]] = set()

        # List of sentences about the game known to be true
        self.knowledge: list[Sentence] = []

        # set of all cells
        self.all_cells = set(itertools.product(
            set(range(self.height)), set(range(self.width))))

    def mark_mine(self, cell: tuple[int, int]):
        """
        Marks a cell as a mine, and updates all knowledge
        to mark that cell as a mine as well.
        """
        self.mines.add(cell)
        for sentence in self.knowledge:
            sentence.mark_mine(cell)

    def mark_safe(self, cell: tuple[int, int]):
        """
        Marks a cell as safe, and updates all knowledge
        to mark that cell as safe as well.
        """
        self.safes.add(cell)
        for sentence in self.knowledge:
            sentence.mark_safe(cell)

    def add_knowledge(self, cell: tuple[int, int], count: int):
        """
        Called when the Minesweeper board tells us, for a given
        safe cell, how many neighboring cells have mines in them.

        This function should:
            1) mark the cell as a move that has been made
            2) mark the cell as safe
            3) add a new sentence to the AI's knowledge base
               based on the value of `cell` and `count`
            4) mark any additional cells as safe or as mines
               if it can be concluded based on the AI's knowledge base
            5) add any new sentences to the AI's knowledge base
               if they can be inferred from existing knowledge
        """
        self.moves_made.add(cell)
        self.mark_safe(cell)

        # diagonals are not neighbors
        neighbors = list(
            filter(
                lambda cell: cell[0] >= 0 and cell[1] >= 0 and cell[0] < self.height and cell[1] < self.width,
                [
                    (cell[0]-1, cell[1]),
                    (cell[0], cell[1]-1),
                    (cell[0]+1, cell[1]),
                    (cell[0], cell[1]+1)
                ]
            )
        )

        neighbor_sentence = Sentence(neighbors, count)
        self.knowledge.append(neighbor_sentence)

        for i, sentence1 in enumerate(self.knowledge):
            for sentence2 in self.knowledge[i+1:]:
                # sentence2 is the bigger sentence
                if len(sentence1.cells) > len(sentence2.cells):
                    s = sentence1
                    sentence1 = sentence2
                    sentence2 = s

                if sentence1.cells.issubset(sentence2.cells):
                    sentence2.cells.difference_update(sentence1.cells)
                    sentence2.count -= sentence1.count

        for sentence in self.knowledge:
            for safe_cell in sentence.known_safes():
                self.mark_safe(safe_cell)
            for mine_cell in sentence.known_mines():
                self.mark_mine(mine_cell)

    def make_safe_move(self) -> tuple[int, int] | None:
        """
        Returns a safe cell to choose on the Minesweeper board.
        The move must be known to be safe, and not already a move
        that has been made.

        This function may use the knowledge in self.mines, self.safes
        and self.moves_made, but should not modify any of those values.
        """
        return next(iter(self.safes.difference(self.moves_made)), None)

    def make_random_move(self) -> tuple[int, int] | None:
        """
        Returns a move to make on the Minesweeper board.
        Should choose randomly among cells that:
            1) have not already been chosen, and
            2) are not known to be mines
        """
        return next(iter(self.all_cells.difference(self.moves_made.union(self.mines))), None)
