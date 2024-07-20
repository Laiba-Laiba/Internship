#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to check if a user exists
bool Existance(const string& username) 
{
    ifstream f1(username + ".txt");
    return f1.is_open();
}

// Function to register a user
void Register_User() 
{
    string User_name, Password;
    cout << "\nEnter username: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, User_name);

    // Check if the user already exists
    if (Existance(User_name)) 
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\033[4m\033[31mUser already exists. Try another username.\033[0m\n";
        return;
    }

    cout << "\nEnter password: ";
    getline(cin, Password);

    // Write username and password to a file
    ofstream f1(User_name + ".txt");
    if (f1.is_open()) 
    {
        f1 << User_name << endl;
        f1 << Password << endl;
        f1.close();
        cout << "\n\t\t\t\t\t\t\t\t\t\t\033[4m\033[36mRegistration successful.\033[0m\n";
    }
    else 
    {
        cout << "\n\t\t\033[31mError creating user file.\033[0m\n";
    }
}

// Function to login a user
void login_User() 
{
    string Username, Password, existingUsername, existingPassword;
    int attempts = 0; // initializing a variable for 3 attempts 
    const int allowed_attempts = 3; // total attempts allowed

    cout << "\nEnter username: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, Username);

    // Check if the user exists
    if (!Existance(Username))
    {
        cout << "\n\t\t\t\t\t\t\t\033[4m\033[31m\t\tUser does not exist. Please register first.\033[0m\n";
        return;
    }

    while (attempts < allowed_attempts) 
    {
        cout << "\nEnter password: ";
        getline(cin, Password);

        // Read stored username and password from file
        ifstream f1(Username + ".txt");
        if (f1.is_open()) 
        {
            getline(f1, existingUsername);
            getline(f1, existingPassword);
            f1.close();

            // Check if the entered password matches the stored password
            if (Username == existingUsername && Password == existingPassword) 
            {
                cout <<"\n\t\t\t\t\t\t\t\t\t\t\033[4m\033[36mLogin successful.\033[0m\n";
                return;
            } 
            else
            {
                attempts++;
                cout << "\n\t\t\t\t\t\t\t\t\t\033[4m\033[32mIncorrect password. Attempt " << attempts << " of " << allowed_attempts << ".\033[0m\n";
            }
        } 
        else 
        {
            cout << "\n\t\t\t\t\t\t\t\t\033[31mError reading user file.\033[0m\n";
            return;
        }
    }

    cout << "\n\n\n\n\t\t\t\t\t\t\t\t\033[4m\033[31mToo many failed login attempts. Please try again later.\033[0m\n";
}

int main() 
{
    int choicee;
    cout << " \t\t\t\t\t\t\t\t\t\033[36m**********************************************\033[0m\n";
    cout << " \t\t\t\t\t\t\t\t\t\033[36m*      LOGIN AND REGISTRATION SYSTEM         *\033[0m\n";
    cout << " \t\t\t\t\t\t\t\t\t\033[36m**********************************************\033[0m\n\n";
    while (true) 
    {
        cout << "\n\n\t1. REGISTER\n\t2. LOGIN\n\t3. EXIT\n\n\t\t\tChoose an option: ";
        cin >> choicee;
        switch (choicee) 
        {
            case 1:
                Register_User();
                break;
            case 2:
                login_User();
                break;
            case 3:
                cout << " \n\t\t\t\t\t\t\t\t\t\t\033[4m\033[36mEXITING...\033[0m\n";
                return 0;
            default:
                cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\033[4m\033[31mINVALID CHOICE. TRY AGAIN.\033[0m\n";
        }
    }
    return 0;
}
