//
//  rec03.cpp
//  rec03
//  Helal Chowdhury

//  Created by Helal Chowdhury on 2/15/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Creates struct of an Account
struct Account{
    string accountName;
    int accountNumber;
};

// Creates Account Class that has Transaction class within. Can Deposit and Withdraw
class AccountsClass {
    friend ostream& operator<<(ostream& os, const vector<AccountsClass>& accountVector);
public:
    AccountsClass(const string& name, int number): accName(name), accNumber(number){}
    
    string getName() const {return accName;}
    int getNumber() const {return accNumber;}
    
    void deposit(int amount) {
        Transaction trans("Deposit", amount);
        balance += amount;
        transactions.push_back(trans);
        
    }

//    Checks if there is sufficient balance and sends error message
    void withdraw(int amount) {
        if (balance - amount < 0){
            cerr << "Insufficient Balance, cannot withdraw" << endl;
        }
        else{
            Transaction trans("Withdraw", amount);
            balance -= amount;
            transactions.push_back(trans);
        }
    }
    
private:
//    Transaction class only contains the type(deposit or withraw) and the amount
    class Transaction {
        friend ostream& operator<<(ostream& os, const vector<AccountsClass>& accountVector);
    public:
        Transaction(const string& type, int amount): type(type), amount(amount) {}
    private:
        string type;
        int amount;
    };
    string accName;
    int accNumber;
    int balance = 0;
    vector<Transaction> transactions;
};

//  Prints out the account name, number, transaction history and the final balance
ostream& operator<<(ostream& os, const vector<AccountsClass>& accountVector) {
    for(size_t i=0; i<accountVector.size(); i++) {
//      os << "Account " << i+1 << ": " << accountVector[i].getName() << ", " << accountVector[i].getNumber() << ".";
        os << "Account " << i+1 << ": " << accountVector[i].accName << ", " << accountVector[i].accNumber << ".";
        os << " Transaction History: ";
        for(int j=0; j < accountVector[i].transactions.size(); j++) {
            os << accountVector[i].transactions[j].type << " " << accountVector[i].transactions[j].amount << " ";
        }
        os << "Balanace: " << accountVector[i].balance<<endl;
    }
    return os;
}

void fillAccountVector1(vector<Account>& accountVector, ifstream& text);
void fillAccountVector2(vector<AccountsClass>& accountVector, ifstream& text);
void fillAccountVector3(vector<AccountsClass>& accountVector, ifstream& transactionText);


int main() {
    ifstream text("account.txt");
    if(!text){
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    
    ifstream transaction("transaction.txt");
    if(!transaction){
        cerr << "transaction file could not be opened" << endl;
        exit(1);
    }
    
    vector<Account> accountVector;
    vector<AccountsClass> accountClassVector;
    vector<AccountsClass> newAccountClassVector;
    
    fillAccountVector1(accountVector, text);
    fillAccountVector2(accountClassVector, text);
    fillAccountVector3(newAccountClassVector, transaction);

}


//  Reads file and calls functions for step 1 of recitation
void fillAccountVector1(vector<Account>& accountVector, ifstream& text) {
    
    string name;
    int number;
    while(text >> name >> number) {
        Account currAccount;
        currAccount.accountName = name;
        currAccount.accountNumber = number;
        accountVector.push_back(currAccount);
    }
    text.close();
    
    cout << "First Print" << endl;
    for(int i=0; i<accountVector.size(); i++) {
        cout << "Account " << i+1 << ": " << accountVector[i].accountName << ", " << accountVector[i].accountNumber << endl;
    }
    cout << endl;
    
    accountVector = {};
    
    text.open("account.txt");
    if(!text){
        cerr << "File could not be opened" << endl;
    }
    while(text >> name >> number) {
        Account currAccount{name, number};
        accountVector.push_back(currAccount);
    }
    text.close();
    cout << "Second Print" << endl;
    for(int i=0; i<accountVector.size(); i++) {
        cout << "Account " << i+1 << ": " << accountVector[i].accountName << ", " << accountVector[i].accountNumber << endl;
    }
    
}


//  Reads file and calls functions for step 2 of recitation
void fillAccountVector2(vector<AccountsClass>& accountVector, ifstream& text) {
    text.open("account.txt");
    if(!text){
        cerr << "File could not be opened" << endl;
    }
    
    string name;
    int number;
    while(text >> name >> number) {
        accountVector.emplace_back(AccountsClass(name, number));
    }
    text.close();
    
    cout << "--------------------" << endl;
    cout << endl;
    cout << "First Print" << endl;
    for(int i=0; i<accountVector.size(); i++) {
        cout << "Account " << i+1 << ": " << accountVector[i].getName() << ", " << accountVector[i].getNumber() << endl;
    }
    cout << endl;
    
    cout << "Second Print" << endl;
    cout << accountVector;
    cout << endl << "--------------------" << endl;
}

//  Reads file and calls functions for step 3 of recitation
void fillAccountVector3(vector<AccountsClass>& accountVector, ifstream& transactionText) {
    string command;
    while(transactionText >> command) {
        if (command == "Account") {
            string name;
            int number;
            transactionText >> name >> number;
            accountVector.emplace_back(AccountsClass(name, number));
        }
        else if(command == "Deposit"){
            int number;
            int amount;
            int index;
            transactionText >> number >> amount;
            for(int i = 0; i<accountVector.size(); i++){
                if (accountVector[i].getNumber() == number){
                    index = i;
                    break;
                }
            }
            accountVector[index].deposit(amount);
        }
        else{
            int number;
            int amount;
            int index;
            transactionText >> number >> amount;
            for(int i = 0; i<accountVector.size(); i++){
                if (accountVector[i].getNumber() == number){
                    index = i;
                    break;
                }
                accountVector[i].withdraw(amount);
            }
        }
    }
    cout << accountVector << endl;
}
