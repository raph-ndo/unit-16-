import tkinter as tk

# Code to update the expression
class Calculator:
    def __init__(self, root):
        self.expression = ""
        self.equation = tk.StringVar()

        # Entry widget to display the current expression
        self.entry = tk.Entry(root, textvariable=self.equation, font=('Calibri', 20), justify='left')
        self.entry.grid(row=0, column=0, columnspan=4, ipadx=12, ipady=12, pady=15)

        # Layout for buttons
        buttons = [
            ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('/', 1, 3),
            ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('*', 2, 3),
            ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('-', 3, 3),
            ('C', 4, 0), ('0', 4, 1), ('=', 4, 2), ('+', 4, 3),
        ]

        for (text, row, col) in buttons:
            if text == '=':
                button = tk.Button(root, text=text, font=('Arial', 18), bg='yellow',
                                   command=self.calculate)  # Button to calculate the numbers inputted
            elif text == 'C':
                button = tk.Button(root, text=text, font=('Arial', 18), bg='grey',
                                   command=self.clear)  # Button to clear the display
            elif text in ['/', '*', '-', '+']:
                button = tk.Button(root, text=text, font=('Arial', 18), bg='orange',
                                   command=lambda t=text: self.press(t))
            else:
                button = tk.Button(root, text=text, font=('Arial', 18),
                                   command=lambda t=text: self.press(t))

            button.grid(row=row, column=col, ipadx=12, ipady=12, padx=5, pady=5)

    def press(self, key, alt_key=None):
        """Handle button press, with optional alternative key."""
        if alt_key is not None:
            self.expression += str(alt_key)
        else:
            self.expression += str(key)
        self.equation.set(self.expression)

    def calculate(self):
        """Evaluate and display the expression."""
        try:
            total = str(eval(self.expression))  # Evaluate the expression
            self.equation.set(total)
            self.expression = total  # Show the result of the inputted numbers
        except Exception:
            self.equation.set("Not do able")
            self.expression = ""

    def clear(self):
        """Clear the current expression."""
        self.expression = ""
        self.equation.set("")


# GUI code
root = tk.Tk()
root.title("Raph's GUI")
root.geometry("300x400")

calc = Calculator(root)  # Initialize the calculator with the root window

root.mainloop()
