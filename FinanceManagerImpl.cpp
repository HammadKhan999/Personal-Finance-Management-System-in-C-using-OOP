// FinanceManagerImpl.cpp

#include "FinanceManagerImpl.h"
#include "Income.h"
#include "Expense.h"
#include "Debt.h"
#include "Asset.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void FinanceManagerImpl::addDebt(double amount, const string& description,const string& date) {
    debts.push_back(new Debt(amount, description, date));
    cout << "Debt added successfully." << endl;
    saveTransaction(debts.back());
}

void FinanceManagerImpl::removeDebt(int index) {
    if (index >= 0 && index < debts.size()) {
        delete debts[index];
        debts.erase(debts.begin() + index);
        cout << "Debt removed successfully." << endl;
    } else {
        cout << "Invalid debt index." << endl;
    }
}

void FinanceManagerImpl::addAsset(double amount, const string& description, const string& date) {
    assets.push_back(new Asset(amount, description, date));
    cout << "Asset added successfully." << endl;
    saveTransaction(assets.back());
}

void FinanceManagerImpl::removeAsset(int index) {
    if (index >= 0 && index < assets.size()) {
        delete assets[index];
        assets.erase(assets.begin() + index);
        cout << "Asset removed successfully." << endl;
    } else {
        cout << "Invalid asset index." << endl;
    }
}

void FinanceManagerImpl::addIncome(double amount, const string& type, const string& description, const string& date) {
    transactions.push_back(new Income(amount, type, description, date));
    cout << "Income added successfully." << endl;
    saveTransaction(transactions.back());
}

void FinanceManagerImpl::addExpense(double amount, const string& category, const string& description, const string& date) {
    transactions.push_back(new Expense(amount, category, description, date));
    cout << "Expense added successfully." << endl;
    saveTransaction(transactions.back());
}

void FinanceManagerImpl::displaySummary() const {
    cout << "================================================================================" << endl;
    cout << "Date" << setw(10) << "Type" << setw(10) << "Amount" << setw(20) << "Category/Type" << setw(20) << "Description" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    double totalDebt = 0.0;
    double totalAsset = 0.0;

    for (const Transaction* transaction : transactions) {
        transaction->displayTransaction();
        if (const Income* income = dynamic_cast<const Income*>(transaction)) {
            totalIncome += income->getAmount();
        } else if (const Expense* expense = dynamic_cast<const Expense*>(transaction)) {
            totalExpense += expense->getAmount();
        }
    }

    cout << "================================================================================" << endl;
    cout << "Total Income: $" << totalIncome << endl;
    cout << "Total Expense: $" << totalExpense << endl;
    cout << "Net Balance: $" << totalIncome - totalExpense << endl;
    cout << "================================================================================" << endl;
    cout << "================================================================================" << endl;
    
	cout << "Debts:" << endl;
    for (const Transaction* debt : debts) {
        debt->displayTransaction();
        if (const Debt* d = dynamic_cast<const Debt*>(debt)) {
            totalDebt += d->getAmount();
        }
    }
    cout << "--------------------------------------------------------------------------------" << endl;
    
	cout << "Assets:" << endl;
    for (const Transaction* asset : assets) {
        asset->displayTransaction();
        if (const Asset* a = dynamic_cast<const Asset*>(asset)) {
            totalAsset += a->getAmount();
        }
    }
    
    cout << "================================================================================" << endl;
	cout << "Net Debt: $" << totalDebt << endl;
    cout << "Net Asset Value: $" << totalAsset << endl;
}

void FinanceManagerImpl::saveTransaction(const Transaction* transaction) const {
    ofstream file("transactions.csv", ios::app);
    if (file.is_open()) {
    	 if (file.tellp() == 0) {
            file << "Date,Amount,Description,Type,Category" << endl;
        
        file << transaction->getDate() << "," << transaction->getAmount() << "," << transaction->getDescription() << ",";

        if (const Income* income = dynamic_cast<const Income*>(transaction)) {
            file << "Income," << income->getType();
        } else if (const Expense* expense = dynamic_cast<const Expense*>(transaction)) {
            file << "Expense," << expense->getCategory();
        } else if (dynamic_cast<const Debt*>(transaction)) {
            file << "Debt,";
        } else if (dynamic_cast<const Asset*>(transaction)) {
            file << "Asset,";
        }
    }

        file << endl;

        file.close();
    }
}

