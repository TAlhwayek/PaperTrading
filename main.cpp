#include "account.h"
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

bool leave = false;

account user1;

// Infinite timer
void timer() {
    while (!leave) {
        // I should randomize the sleep time
        sleep(10);
        // Let stock market update
        user1.updateMarket();
    }
}

void askInput(account user) {
    string input;

    while (!leave) {
        cout << "Buy? (B/b)" << endl;
        cout << "Sell? (S/s)" << endl;
        cout << "View portfolio? (V/v)" << endl;
        cin >> input;

        // Buying
        if (input == "B" || input == "b") {
            cout << "\nCurrent market prices: " << endl;
            user.printMarket();

            cout << "\nEnter stock symbol to purchase, or E/e to go back: ";
            cin >> input;

            if (input == "E" || input == "e") {
                continue;
            } else {
                // Check if ticket exists in market
                if (user.checkIfTickerExists(input)) {
                    user.buyStock(input);
                } else {
                    cout << "\nInvalid stock symbol. Transaction has been cancelled.\n" << endl;
                }
            }
        }
            // Selling
        else if (input == "S" || input == "s") {
            cout << "Which stock do you want to sell?" << endl;
            cout << "Enter ticker symbol, or E/e to go back: ";
            cin >> input;

            if (input == "E" || input == "e") {
                continue;
            } else {
                // Check if ticker exists in portfolio
                if(user.checkIfUserOwnsTicker(input)) {
                    user.sellStock(input);
                } else {
                    cout << "Invalid stock symbol. Transaction has been cancelled.\n" << endl;
                }
            }

        } // View portfolio
        else if (input == "V" || input == "v") {
            user.printStocks();
        } // Exit
        else if (input == "E" || input == "e" || input == "Exit" || input == "exit") {
            cout << "\nTerminating program";
            exit(0);
        } // Handle invalid input
        else {
            cout << "\nInvalid input. Please try again.\n" << endl;
        }
    }
}

int main() {
    srand(104931);


    thread timerThread(timer);
    thread inputThread(askInput, user1);

    timerThread.join();
    inputThread.join();
}
