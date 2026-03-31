import random

class SavingsAccount:
    """Represents a bank savings account with basic ATM operations."""
    
    def __init__(self, account_number, pin, balance=0.0):
        """Initialize account with account number, PIN, and balance."""
        self.account_number = account_number
        self.pin = pin
        self.balance = balance

    def check_balance(self):
        """Returns the current account balance."""
        return f"Your balance is: ${self.balance:.2f}"

    def deposit(self, amount):
        """Deposits an amount into the account."""
        if amount > 0:
            self.balance += amount
            return f"Deposited: ${amount:.2f}\n{self.check_balance()}"
        return "Invalid deposit amount."

    def withdraw(self, amount):
        """Withdraws an amount from the account if funds are sufficient."""
        if amount > self.balance:
            return "Insufficient balance."
        elif amount > 0:
            self.balance -= amount
            return f"Withdrawn: ${amount:.2f}\n{self.check_balance()}"
        return "Invalid withdrawal amount."

class Bank:
    """Represents a bank that manages multiple savings accounts."""
    
    def __init__(self):
        """Initialize a bank with an empty dictionary of accounts."""
        self.accounts = {}

    def create_account(self, pin, initial_balance=0.0):
        """Creates a new account with a 12-digit account number."""
        account_number = str(random.randint(10**11, 10**12 - 1))  # Generates a 12-digit number
        self.accounts[account_number] = SavingsAccount(account_number, pin, initial_balance)
        return f"Account created successfully! Your Account Number: {account_number}"

    def login(self, account_number, pin):
        """Validates user login by checking account number and PIN."""
        account = self.accounts.get(account_number)
        if account and account.pin == pin:
            return account
        return None


def atm_simulation():
    """Simulates an ATM system allowing users to interact with their accounts."""
    bank = Bank()
    
    # Create some sample accounts for testing
    sample_acc1 = bank.create_account("1234", 500)
    sample_acc2 = bank.create_account("5678", 1000)
    print(sample_acc1)
    print(sample_acc2)

    while True:
        print("\nWelcome to the ATM!")
        account_number = input("Enter your 12-digit Account Number: ")
        pin = input("Enter your 4-digit PIN: ")
        
        user = bank.login(account_number, pin)

        if user:
            print("\nLogin successful!")
            while True:
                print("\n1. Check Balance\n2. Deposit Money\n3. Withdraw Money\n4. Exit")
                choice = input("Choose an option: ")

                if choice == "1":
                    print(user.check_balance())
                elif choice == "2":
                    amount = float(input("Enter deposit amount: "))
                    print(user.deposit(amount))
                elif choice == "3":
                    amount = float(input("Enter withdrawal amount: "))
                    print(user.withdraw(amount))
                elif choice == "4":
                    print("Thank you for using the ATM. Goodbye!")
                    break
                else:
                    print("Invalid option. Please try again.")
        else:
            print("Invalid Account Number or PIN. Please try again.")

# Run the ATM simulation
atm_simulation()
