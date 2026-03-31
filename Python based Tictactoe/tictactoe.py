import os
import random
import gettext
import tkinter as tk
from tkinter import messagebox

# Set up gettext for translations
gettext.install("oxo_game", localedir="locales")
_ = gettext.gettext  # `_()` will be used for translation

class TicTacToeGUI:
    def __init__(self, root):
        """Initialize the Tic-Tac-Toe game with a GUI."""
        self.root = root
        self.root.title(_("Tic-Tac-Toe"))

        self.buttons = []
        self.board = [" "] * 9
        self.current_player = "X"

        self.create_widgets()

    def create_widgets(self):
        """Create buttons for the Tic-Tac-Toe grid."""
        for i in range(9):
            btn = tk.Button(self.root, text=" ", font=("Arial", 20), width=5, height=2,
                            command=lambda i=i: self.make_move(i))
            btn.grid(row=i//3, column=i%3)
            self.buttons.append(btn)

        self.reset_button = tk.Button(self.root, text=_("New Game"), command=self.reset_game)
        self.reset_button.grid(row=3, column=0, columnspan=3)

    def make_move(self, index):
        """Process user move."""
        if self.board[index] == " ":
            self.board[index] = self.current_player
            self.buttons[index].config(text=self.current_player)

            if self.check_winner():
                messagebox.showinfo(_("Game Over"), _("Winner is: ") + self.current_player)
                self.reset_game()
                return

            self.current_player = "O" if self.current_player == "X" else "X"

    def check_winner(self):
        """Check if the current board contains a winning move."""
        wins = [(0,1,2), (3,4,5), (6,7,8), (0,3,6), (1,4,7), (2,5,8), (0,4,8), (2,4,6)]
        for a, b, c in wins:
            if self.board[a] == self.board[b] == self.board[c] != " ":
                return True
        return False

    def reset_game(self):
        """Reset the game board."""
        self.board = [" "] * 9
        self.current_player = "X"
        for btn in self.buttons:
            btn.config(text=" ")

# Run the GUI
if __name__ == "__main__":
    root = tk.Tk()
    app = TicTacToeGUI(root)
    root.mainloop()
 