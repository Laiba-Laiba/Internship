#include <iostream>
#include <string>
#include <fstream>
#include <cstdio> // For remove function

using namespace std;

// Customer class
class Customer 
{
public:
    string name;
    int customerID;
    string email;

    Customer(string name, int customerID, string email) : name(name), customerID(customerID), email(email) {}
    Customer() {} // Default constructor for file reading
};

// Transaction class
class Transaction 
{
public:
    string type; // Deposit, Withdrawal, Transfer
    double amount;
    string details;

    Transaction(string type, double amount, string details) : type(type), amount(amount), details(details) {}
    Transaction() {} // Default constructor for file reading
};

// Account class
class Account 
{
private:
    int transactionCount;
    static const int maxTransactions = 100;
    Transaction* transactions[maxTransactions];

public:
    int accountNumber;
    double balance;

    Account(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance), transactionCount(0) {}
    Account() {} // Default constructor for file reading

    void addTransaction(const string& type, double amount, const string& details) 
    {
        if (transactionCount < maxTransactions) 
        {
            transactions[transactionCount++] = new Transaction(type, amount, details);
        }
    }

    void deposit(double amount) 
    {
        balance += amount;
        addTransaction("Deposit", amount, "Deposited " + to_string(amount));
        cout << "\n\n\n\t\t\t\t\t\t\t\t\t\033[35mDeposit successful. New balance: $ \033[0m" << balance << endl << endl <<endl;
    }

    void withdraw(double amount) 
    {
        if (amount > balance) 
        {
            cout << "\n\t\t\t \033[31m Insufficient funds. \033[0m" << endl;
        } 
        else 
        {
            balance -= amount;
            addTransaction("Withdrawal", amount, "Withdrew " + to_string(amount));
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t\033[35mWithdrawal successful. New balance: $\033[0m" << balance << endl << endl << endl;
        }
    }

    void displayBalance() const 
    {
        cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\033[35m  Account balance: $ \033[0m" << balance << endl << endl;
    }

    void displayTransactions() const 
    {
        cout << "\n\n\n\t\t\t\t\t\t\t\t\t\033[35m Recent Transactions: \033[0m" << endl;
        for (int i = 0; i < transactionCount; ++i) 
        {
            cout << transactions[i]->type << " - $" << transactions[i]->amount << " (" << transactions[i]->details << ")" << endl;
        }
    }
};

// BankingSystem class
class BankingSystem 
{
private:
    Customer* customers[100];
    Account* accounts[100];
    int customerCount;
    int accountCount;

public:
    BankingSystem() : customerCount(0), accountCount(0) 
    {
        loadCustomers();
        loadAccounts();
    }

    ~BankingSystem() 
    {
        saveCustomers();
        saveAccounts();
    }

    void addCustomer(string name, int customerID, string email) 
    {
        if (customerCount < 100) 
        {
            customers[customerCount++] = new Customer(name, customerID, email);
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t\033[35m------Customer added successfully.-------\n\033[0m\n\n" << endl;
        } 
        else 
        {
            cout << "\n\n\n\t\t\t\t\033[35m------Customer limit reached.-------\n\033[0m" << endl;
        }
    }

    void createAccount(int accountNumber, double initialDeposit) 
    {
        if (accountCount < 100) 
        {
            accounts[accountCount++] = new Account(accountNumber, initialDeposit);
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t\033[35m------Account created successfully.-------\n\033[0m" << endl;
        } 
        else 
        {
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t\033[35m------Account limit reached.-------\n\033[0m" << endl;
        }
    }

    Account* getAccount(int accountNumber) 
    {
        for (int i = 0; i < accountCount; i++) 
        {
            if (accounts[i]->accountNumber == accountNumber) 
            {
                return accounts[i];
            }
        }
        return nullptr;
    }

    Customer* getCustomer(int customerID) 
    {
        for (int i = 0; i < customerCount; i++) 
        {
            if (customers[i]->customerID == customerID) 
            {
                return customers[i];
            }
        }
        return nullptr;
    }

    void displayCustomerInfo(int customerID) 
    {
        Customer* customer = getCustomer(customerID);
        if (customer != nullptr) 
        {
            cout << "\n\n\t\t\tCustomer ID: " << customer->customerID << endl ;
            cout << "\t\t\tName: " << customer->name << endl;
            cout << "\t\t\tEmail: " << customer->email << endl;
        } 
        else
        {
            cout << "\n\t\t\033[31m Customer not found.\033[0m" << endl;
        }
    }

    void transfer(int fromAccountNumber, int toAccountNumber, double amount) 
    {
        Account* fromAccount = getAccount(fromAccountNumber);
        Account* toAccount = getAccount(toAccountNumber);

        if (fromAccount == nullptr || toAccount == nullptr) 
        {
            cout << "\n\t\t\t\033[31m One or both accounts not found.\033[0m" << endl;
            return;
        }

        if (fromAccount->balance < amount) 
        {
            cout << "\n\t\t\t\033[31m Insufficient funds in the source account.\033[0m" << endl;
            return;
        }

        fromAccount->balance -= amount;
        toAccount->balance += amount;

        fromAccount->addTransaction("Transfer Out", amount, "Transferred to account " + to_string(toAccountNumber));
        toAccount->addTransaction("Transfer In", amount, "Received from account " + to_string(fromAccountNumber));

        cout << "\n\n\n\t\t\t\t\t\t\t\t\033[35m Transfer successful. New balance of account \033[0m" << fromAccountNumber << "\033[35m : $ \033[0m" << fromAccount->balance ;
        cout << "\n\n\n\t\t\t\t\t\t\t\t\t\033[35m New balance of account " << toAccountNumber << "\033[35m : $ \033[0m" << toAccount->balance << endl << endl << endl;
    }

    void saveCustomers() 
    {
        ofstream outFile("customers.txt");
        for (int i = 0; i < customerCount; i++) 
        {
            outFile << customers[i]->name << "," << customers[i]->customerID << "," << customers[i]->email << endl;
        }
        outFile.close();
    }

    void loadCustomers() 
    {
        ifstream inFile("customers.txt");
        if (!inFile) return;

        string line;
        while (getline(inFile, line)) 
        {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            string name = line.substr(0, pos1);
            int customerID = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            string email = line.substr(pos2 + 1);
            customers[customerCount++] = new Customer(name, customerID, email);
        }
        inFile.close();
    }

    void saveAccounts() 
    {
        ofstream outFile("accounts.txt");
        for (int i = 0; i < accountCount; i++) 
        {
            outFile << accounts[i]->accountNumber << "," << accounts[i]->balance << endl;
        }
        outFile.close();
    }

    void loadAccounts() 
    {
        ifstream inFile("accounts.txt");
        if (!inFile) return;

        string line;
        while (getline(inFile, line)) 
        {
            size_t pos = line.find(",");
            int accountNumber = stoi(line.substr(0, pos));
            double balance = stod(line.substr(pos + 1));
            accounts[accountCount++] = new Account(accountNumber, balance);
        }
        inFile.close();
    }

    void deleteDataFiles()
    {
        if (remove("customers.txt") != 0)
        {
            perror("Error deleting customers.txt");
        }
        else
        {
            cout << "\n\t\t\t \033[31m Customer data deleted successfully.\033[0m\n";
        }

        if (remove("accounts.txt") != 0)
        {
            perror("Error deleting accounts.txt");
        }
        else
        {
            cout << "\n\t\t\t\033[31m Account data deleted successfully.\033[0m\n";
        }
    }
};

int main() 
{
    BankingSystem bank;
    int choice;

    do 
    {
        cout << "\t\t\t\t\t\t\t\t\t\t\033[36m**********************\033[0m";
        cout << "\n\t\t\t\t\t\t\t\t\t\t\033[4m\033[36m*Banking System Menu:*\033[0m\n";
        cout << "\t\t\t\t\t\t\t\t\t\t\033[36m**********************\033[0m\n\n";
        
        cout << "\n\n\n\t\033[31m-----OPERTAIONS-----\033[0m\n\n";
        cout << "\t1. Add Customer\n";
        cout << "\t2. Create Account\n";
        cout << "\t3. Deposit\n";
        cout << "\t4. Withdraw\n";
        cout << "\t5. Transfer Money\n";
        cout << "\t6. Display Account Balance\n";
        cout << "\t7. Display Customer Information\n";
        cout << "\t8. Display Recent Transactions\n";
        cout << "\t9. Exit\n\n";
        cout << "\t Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                string name, email;
                int customerID;
                cout << "\n\t\033[36mEnter Customer ID: \033[0m";
                cin >> customerID;
                cout << "\n\t\033[36mEnter Customer Name: \033[0m";
                cin.ignore();
                getline(cin, name);
                cout << "\n\t\033[36mEnter Customer Email: \033[0m";
                getline(cin, email);
                bank.addCustomer(name, customerID, email);
                break;
            }
            case 2: 
            {
                int accountNumber;
                double initialDeposit;
                cout << "\n\t\033[36m Enter Account Number:  \033[0m";
                cin >> accountNumber;
                cout << "\n\t\033[36m Enter Initial Deposit:  \033[0m";
                cin >> initialDeposit;
                bank.createAccount(accountNumber, initialDeposit);
                break;
            }
            case 3: 
            {
                int accountNumber;
                double amount;
                cout << "\n\t\033[36mEnter Account Number: \033[0m";
                cin >> accountNumber;
                cout << "\n\t\033[36mEnter Deposit Amount: \033[0m";
                cin >> amount;
                Account* account = bank.getAccount(accountNumber);
                if (account != nullptr) 
                {
                    account->deposit(amount);
                } 
                else 
                {
                    cout << "\n\t\033[36m Account not found.\033[0m" << endl;
                }
                break;
            }
            case 4: 
            {
                int accountNumber;
                double amount;
                cout << "\n\t\033[36mEnter Account Number: \033[0m";
                cin >> accountNumber;
                cout << "\n\t\033[36mEnter Withdrawal Amount: \033[0m";
                cin >> amount;
                Account* account = bank.getAccount(accountNumber);
                if (account != nullptr) 
                {
                    account->withdraw(amount);
                } 
                else 
                {
                    cout << "\n\t\033[36m Account not found. \033[0m" << endl;
                }
                break;
            }
            case 5: 
            {
                int fromAccountNumber, toAccountNumber;
                double amount;
                cout << "\n\t\033[36mEnter Source Account Number: \033[0m";
                cin >> fromAccountNumber;
                cout << "\n\t\033[36mEnter Destination Account Number: \033[0m";
                cin >> toAccountNumber;
                cout << "\n\t\033[36mEnter Transfer Amount: \033[0m";
                cin >> amount;
                bank.transfer(fromAccountNumber, toAccountNumber, amount);
                break;
            }
            case 6: 
            {
                int accountNumber;
                cout << "\n\t\033[36m Enter Account Number: \033[0m";
                cin >> accountNumber;
                Account* account = bank.getAccount(accountNumber);
                if (account != nullptr) 
                {
                    account->displayBalance();
                } 
                else 
                {
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\033[31m   Account not found.\033[0m" << endl << endl;
                }
                break;
            }
            case 7: 
            {
                int customerID;
                cout << "\n\t\033[36m Enter Customer ID: \033[0m";
                cin >> customerID;
                bank.displayCustomerInfo(customerID);
                break;
            }
            case 8: 
            {
                int accountNumber;
                cout << "\n\t\033[36m Enter Account Number: \033[0m";
                cin >> accountNumber;
                Account* account = bank.getAccount(accountNumber);
                if (account != nullptr) 
                {
                    account->displayTransactions();
                } 
                else 
                {
                    cout << "\n\t\t\t\t\033[31m Account not found.\033[0m" << endl;
                }
                break;
            }
            case 9: 
            {
                bank.deleteDataFiles();
                cout << "\n\t\033[36m Exiting the system. Goodbye!\033[0m" << endl;
                break;
            }
            default: 
            {
                cout << "\n\t\033[31m Invalid choice. Please try again.\033[0m" << endl;
                break;
            }
        }
    } while (choice != 9);

    return 0;
}

