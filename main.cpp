#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <conio.h> // Windows-specific library for changing console colors
#include <windows.h>
#include <chrono>  
#include <thread>  
#include "menu.h"   // Include the menu header file
#include "FinanceManagerImpl.h"

using namespace std;
int main() {
      bool isAuthenticated = false;
      string username, password;
      cout<<"************Welcome To Personal Finance Management System**************"<<endl;
      cout<<endl;
      cout<<"Please Enter your correct user name and password to access PFMS"<<endl;

    while (!isAuthenticated) {
        // Prompt the user for username and password
        cout <<endl<<"Enter your Username: ";
        cin >> username;
        cout<<endl;
        cout << "Enter your Password: ";
        char ch;
        password = "";
        while ((ch = _getch()) != '\r') { // Read characters until Enter is pressed
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    password.pop_back(); // Remove last character from password
                    cout << "\b \b"; // Move cursor back, print space, move cursor back again
                }
            } else {
                password.push_back(ch); // Append character to password
                cout << "*"; // Print asterisk instead of the actual character
            }
        }

        // Check username and password
        if (username == "hammad" && password == "191216") {
        	cout<<endl<<"Logged In successfully!!!!"<<endl;
        	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        	system("cls");
            isAuthenticated = true;
             HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        } else {
        	cout<<endl;
            cout << "Invalid username or password. Please try again." << endl;
        }
    }

    FinanceManagerImpl financeManager;
    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1: {
                double amount;
                string type, description, date;
                cout<<"        *******INCOME RECORD********       "<<endl;
                cout << "Enter the Date: ";
                cin.ignore();
                getline(cin, date);
                while (true) {
        		cout << "Enter the amount: $";
        		if (cin >> amount) {
            	// Valid amount entered, break the loop
            	break;
        		} else {
            		cout << "Invalid input. Amount must be a number. Please try again." << std::endl;
            		cin.clear();
           	 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
                cout << "Enter the type of income: ";
                cin.ignore();
                getline(cin, type);
                cout << "Enter a description: ";
                getline(cin, description);
                cout << endl;
                financeManager.addIncome(amount, type, description,date);
                cout << "Press Enter to return to the menu...";
                cin.get();
                system("cls");
                break;
            }
            case 2: {
                double amount;
                string category, description, date;
                cout<<"        *******EXPENSE RECORD********       "<<endl;
                cout << "Enter the Date: ";
                cin.ignore();
                getline(cin, date);
                while (true) {
        		cout << "Enter the amount: $";
        		if (cin >> amount) {
            	// Valid amount entered, break the loop
            	break;
        		} else {
            		cout << "Invalid input. Amount must be a number. Please try again." << std::endl;
            		cin.clear();
           	 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
                cout << "Enter the category of expense: ";
                cin.ignore();
                getline(cin, category);
                cout << "Enter a description: ";
                getline(cin, description);
                financeManager.addExpense(amount, category, description,date);
                cout << "Press Enter to return to the menu...";
             
                cin.get();
                system("cls");
                break;
            }
            
            case 3:{	
            double amount;
                string description, date;
                cout<<"        *******ADD DEBT********       "<<endl;
                cout << "Enter the Date: ";
                cin.ignore();
                getline(cin, date);
                while (true) {
        		cout << "Enter the amount: $";
        		if (cin >> amount) {
            	// Valid amount entered, break the loop
            	break;
        		} else {
            		cout << "Invalid input. Amount must be a number. Please try again." << std::endl;
            		cin.clear();
           	 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
                cout << "Enter a description: ";
                cin.ignore();
                getline(cin, description);
                financeManager.addDebt(amount, description,date);
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            
            case 4:{
                int index;
                cout<<"        *******REMMOVE DEBT********       "<<endl;
                
                    while (true) {
        		cout << "Enter the index of the debt to remove: ";
        		if (cin >> index) {
            	// Valid amount entered, break the loop
            	break;
        		} else {
            		cout << "Invalid input. index must be a number. Please try again." << std::endl;
            		cin.clear();
           	 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
                financeManager.removeDebt(index);
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            
			case 5:{
				double amount;
                string description, date;
                cout<<"        *******ADD ASSET********       "<<endl;
                cout << "Enter the Date: ";
                cin.ignore();
                getline(cin, date);
                 while (true) {
        		cout << "Enter the amount of Asset: $";
        		if (cin >> amount) {
            	// Valid amount entered, break the loop
            	break;
        		} else {
            		cout << "Invalid input. Amount must be a number. Please try again." << std::endl;
            		cin.clear();
           	 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
                cout << "Enter a description: ";
                cin.ignore();
                getline(cin, description);
                financeManager.addAsset(amount, description,date);
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                system("cls");
				break;
			}
			
			case 6: {
				int index;
				cout<<"        *******REMOVE ASSET********       "<<endl;
                
                 while (true) {
        		cout << "Enter the index of the asset to remove: ";
        		if (cin >> index) {
            	// Valid amount entered, break the loop
            	break;
        		} else {
            		cout << "Invalid input. Index must be a number. Please try again." << std::endl;
            		cin.clear();
           	 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
                financeManager.removeAsset(index);
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                system("cls");
				break;
			}
    
            case 7:
              financeManager.displaySummary();
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            	
            case 8:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }


    return 0;
}
