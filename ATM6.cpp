

#include <iostream>
#include <limits>

using namespace std;

class ATM {
private:
    string username;
    double balance;
    int pinCode; // Added member for PIN code

public:
    ATM(const string &name, double initialBalance, int pin) : username(name), balance(initialBalance), pinCode(pin) {}

    void askForATMCard() {
        cout << "Do you want to enter your ATM card? (yes/no): ";
        string answer;
        cin >> answer;

        if (answer == "no") {
            cout << "Thank you for considering our services. Have a nice day!" << endl;
            exit(0);
        }
    }

    void displayMenu();

    void checkBalance();

    void withdrawAmount();

    void transferCash(ATM &recipient);

    void displayAccountDetails();
};

void ATM::displayMenu() {
    const int CHECK_BALANCE = 1;
    const int WITHDRAW_AMOUNT = 2;
    const int TRANSFER_CASH = 3;
    const int ACCOUNT_DETAILS = 4;
    const int GO_BACK = 5;

    int choice;
    do {
        cout << "\n1. Check Balance" << endl;
        cout << "2. Withdraw Amount" << endl;
        cout << "3. Transfer Cash" << endl;
        cout << "4. Account Details" << endl;
        cout << "5. Go Back" << endl;
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case CHECK_BALANCE:
                checkBalance();
                break;
            case WITHDRAW_AMOUNT:
                withdrawAmount();
                break;
            case TRANSFER_CASH:
                transferCash(*this);  // Pass the current object as the sender
                break;
            case ACCOUNT_DETAILS:
                displayAccountDetails();
                break;
            case GO_BACK:
                cout << "Going back to the main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    } while (choice != GO_BACK);
}

void ATM::checkBalance() {
    cout << "Your current balance is: $" << balance << endl;
}

void ATM::withdrawAmount() {
    int enteredPin;
    cout << "Please enter your PIN code: ";
    while (!(cin >> enteredPin) || enteredPin != pinCode) {
        cout << "Incorrect PIN. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double amount;
    cout << "Enter the amount to withdraw: $";

    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid input. Please enter a positive numeric value." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (amount <= balance) {
        balance -= amount;
        cout << "Withdrawal successful. Remaining balance: $" << balance << endl;
    } else {
        cout << "Invalid amount or insufficient funds." << endl;
    }
}

void ATM::transferCash(ATM &recipient) {
    double transferAmount;
    cout << "Enter the amount to transfer: $";

    while (!(cin >> transferAmount) || transferAmount <= 0) {
        cout << "Invalid input. Please enter a positive numeric value." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (transferAmount <= balance) {
        balance -= transferAmount;
        recipient.balance += transferAmount;

        cout << "Transfer successful."  << endl;
        cout << "Transferred $" << transferAmount << " from " << recipient.username << "." << endl;
    } else {
        cout << "Invalid amount or insufficient funds." << endl;
    }
}

void ATM::displayAccountDetails() {
    cout << "\nAccount Details:" << endl;
    cout << "Username: " << username << endl;
    cout << "Balance: $" << balance << endl;
}

int main() {
    string username;
    do {
        cout << "Enter your username: ";
        getline(cin, username);
    } while (username.empty() || username.find_first_not_of(' ') == string::npos);

    ATM sender(username, 5000, 1234); // Assuming initial balance and PIN for demonstration

    sender.askForATMCard();

    cout << "\nWelcome, " << username << "!" << endl;

    sender.displayMenu();

    cout << "\nThank you for using the ATM. Have a nice day!" << endl;

    return 0;
}

