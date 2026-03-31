#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

enum Menu { Check = 1, Withdraw = 2, Deposit = 3, Exit = 4 };
enum MenuForStart { logining = 1, CreatNewAccount, Exit };

struct accounts {
    string Name;
    string Password;
    double Amount = 0;
};

// update vector from file
void SaveAllAccounts(const vector<accounts>& accountList) {
    ofstream file("accounts.txt");

    if (file.is_open()) {
        for (size_t i = 0; i < accountList.size(); i++){ 
            file << accountList[i].Name << " "
                << accountList[i].Password << " "
                << accountList[i].Amount <<endl;
        }

        file.close();
    }
}

vector<accounts> LoadAccount() {
    vector<accounts> accountList;
    ifstream file("accounts.txt");
    accounts acc;

    if (!file) return accountList;

    while (file >> acc.Name >> acc.Password >> acc.Amount) {
        accountList.push_back(acc);
    }
    file.close();
    return accountList;
}



void CreatAccount(vector<accounts>& accountList) {
    accounts acc;
    cout << "\n====== CREATE NEW ACCOUNT =====\n";

    cout << "Enter Your name: ";
    cin >> acc.Name;
    cout << "Enter Your PIN: ";
    cin >> acc.Password;



    for (size_t i = 0; i < accountList.size(); i++)
    {
        if (accountList[i].Name == acc.Name)
        {
            cout << "\nName Alredy Exists!\n";
            return;
        };

        if (acc.Password.length() < 4)
        {
            cout << "\nPin Must be at least 4 digits! \n";
            return;
        }
        
    }


    

    acc.Amount = 100;

    accountList.push_back(acc);
    SaveAllAccounts(accountList); // Save update
    cout << "Account created successfully!\n";
}

int login(const vector<accounts>& accountList) {
    string name, pin;
    cout << "\n====== LOGIN ====== \n";
    cout <<endl;
    cout << "Name: "; cin >> name;
    cout << "PIN: "; cin >> pin;

    for (size_t i = 0; i < accountList.size(); i++) {
        if (accountList[i].Name == name && accountList[i].Password == pin) {
            return (int)i;
        }
    }
    return -1;
}

// ... (MainMenu, showAmount, GetWithdraw, getDeposit - nfs l-logic dyalk mzyan)

int main() {
    vector<accounts> accountList = LoadAccount();
    int loggedInIndex = -1;

    bool appRunning = true;
    while (appRunning) {
        // Iila kano mam-loginich
        if (loggedInIndex == -1) {
            int startChoice;
            cout << "\n1. Login: \n2. Create Account: \n3. Exit: " << endl;
            cout << "Your Choice: ";
            cin >> startChoice;

            if (startChoice == 1) {
                loggedInIndex = login(accountList);
                if (loggedInIndex == -1) cout << "Login failed!\n";
            } else if (startChoice == 2) {
                CreatAccount(accountList);
            } else {
                appRunning = false;
            }
        } 
        // Ila dkhlo (ATM Mode)
        else {
            int atmChoice;
            cout << "\n1. Balance: \n2. Withdraw: \n3. Deposit: \n4. Logout: ";
            cin >> atmChoice;

            if (atmChoice == 1) {
                cout << "Balance: " << accountList[(size_t) loggedInIndex].Amount << " DH\n";
            } else if (atmChoice == 2) {
                double amount; cout << "Amount: "; cin >> amount;

                if (amount <= accountList[(size_t)  loggedInIndex].Amount) {
                    accountList[(size_t)  loggedInIndex].Amount -= amount;
                    SaveAllAccounts(accountList);
                    cout << "Done!\n";
                } 
                else cout << "No money!\n";

            } else if (atmChoice == 3) {
                double amount; cout << "Amount: "; cin >> amount;
                if(amount > 0){
                    accountList[(size_t)  loggedInIndex].Amount += amount;
                    SaveAllAccounts(accountList);
                    cout << "Done!\n";
                }
                else cout << "Invalid amount! \n";
                
            } else {
                cout << "logged out succsfully! \n";
                loggedInIndex = -1; // Logout
            }
        }
    }
    return 0;
}