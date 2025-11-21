#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accNumber;
    char name[50];
    double balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "\nAccount Created Successfully!\n";
    }

    void showAccount() {
        cout << "\nAccount Number: " << accNumber;
        cout << "\nName: " << name;
        cout << "\nBalance: ₹" << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "\nAmount Deposited Successfully!\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
            return false;
        }
        balance -= amount;
        cout << "\nWithdrawal Successful!\n";
        return true;
    }

    int getAccNumber() {
        return accNumber;
    }

    double getBalance() {
        return balance;
    }

    void update() {
        fstream file("bankdata.txt", ios::in | ios::out | ios::binary);
        BankAccount temp;
        while(file.read(reinterpret_cast<char*>(&temp), sizeof(BankAccount))) {
            if(temp.getAccNumber() == accNumber) {
                file.seekp(-sizeof(BankAccount), ios::cur);
                file.write(reinterpret_cast<char*>(this), sizeof(BankAccount));
                break;
            }
        }
        file.close();
    }
};

void writeAccount(BankAccount &acc) {
    ofstream file("bankdata.txt", ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&acc), sizeof(acc));
    file.close();
}

bool readAccount(int accNum, BankAccount &acc) {
    ifstream file("bankdata.txt", ios::binary);
    while(file.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if(acc.getAccNumber() == accNum) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

int main() {
    BankAccount acc;
    int choice, accNum;
    double amount;

    while(true) {
        cout << "\n---- BANK MANAGEMENT SYSTEM ----";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Show Account Details";
        cout << "\n5. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

        case 1:
            acc.createAccount();
            writeAccount(acc);
            break;

        case 2:
            cout << "\nEnter Account Number: ";
            cin >> accNum;
            if(readAccount(accNum, acc)) {
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                acc.deposit(amount);
                acc.update();
            } else
                cout << "Account Not Found!\n";
            break;

        case 3:
            cout << "\nEnter Account Number: ";
            cin >> accNum;
            if(readAccount(accNum, acc)) {
                cout << "Enter Withdraw Amount: ";
                cin >> amount;
                if(acc.withdraw(amount))
                    acc.update();
            } else
                cout << "Account Not Found!\n";
            break;

        case 4:
            cout << "\nEnter Account Number: ";
            cin >> accNum;
            if(readAccount(accNum, acc))
                acc.showAccount();
            else
                cout << "Account Not Found!\n";
            break;

        case 5:
            cout << "Thank you for using Banking System!" << endl;
            return 0;

        default:
            cout << "Invalid Choice! Try Again.\n";
        }
    }
}
