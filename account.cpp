//
// Created by Tony Alhwayek on 11/25/23.
//

#include <iomanip>
#include <iostream>

#include "account.h"

using namespace std;

//////////////////////////
// Constructors
//      +
// Initializers
//////////////////////////
account::account() {
    cash = 10000.00;
    profit = 0.00;
    profitPercent = 0.00;
    initializeMarket();
}

void account::initializeMarket() {
    market["SMH"] = 500;
    market["AAPL"] = 900;
    market["FISH"] = 420;
}

//////////////////////////
// CHECK FUNCTIONS
//////////////////////////

// Check if ticker exists in market
bool account::checkIfTickerExists(const string& ticker) {
    return (market.find(ticker) != market.end());
}

// check if ticker exists in portfolio
bool account::checkIfUserOwnsTicker(const string& ticker) {
    return (portfolio.find(ticker) != portfolio.end());
}

//////////////////////////
// GETTERS
//////////////////////////

// Return user's amount of cash
double account::getCash() const {
    return cash;
}

// Calculates change in price between purchase price and current market price
double account::calculateChange(const string& ticker) {
    double changeTotal = 0;

        for(int i = 0; i < portfolioBuyValues[ticker].size(); i++) {
            changeTotal += market[ticker] - portfolioBuyValues[ticker].at(i);
    }
        return changeTotal;
}

// Returns average purchase price of stock
double account::calculateAveragePrice(const string& ticker) {
    double average = 0;
    int sizeOfVector = portfolioBuyValues[ticker].size();

    for(int i = 0; i < sizeOfVector; i++) {
        average += portfolioBuyValues[ticker].at(i);
    }
    return average / sizeOfVector;
}

//////////////////////////
// BUY AND SELL FUNCTIONS
//////////////////////////

void account::buyStock(const string& ticker) {
    // Check if user has enough funds
    if (market[ticker] > cash) {
        cout << "Insufficient funds to purchase " << ticker << "." << endl << endl;
    } else {
        // Add new stock to map
        portfolio[ticker]++;
        // Add purchase price to values map
        portfolioBuyValues[ticker].push_back(market[ticker]);
        cash -= market[ticker];
        cout << "\nYou've purchased 1 share of " << ticker << " for "
             << market[ticker] << " dollars." << endl;
        cout << "Remaining balance: $" << cash << endl << endl;
    }
}

void account::sellStock(const string &ticker) {
    if (portfolio[ticker]) {
        cash += market[ticker];
        if(portfolio[ticker] > 1) {
            portfolio[ticker]--;
        } else {
            portfolio.erase(ticker);
        }
        cout << "You've successfully sold " << ticker << " for $" << market[ticker]
             << "." << endl;
    }
}

//////////////////////////
// PRINT FUNCTIONS
//////////////////////////

// Print current market prices
void account::printMarket() {
    cout << "---------------------------" << endl;
    for (const auto &pair : market) {
        std::cout << "Ticker: " << pair.first << ", Value: $" << pair.second
                  << std::endl;
    }
}

// Print total portfolio
void account::printPortfolio() { //unordered_map<string, double> portfolio) {
    double sum = 0.00;
    double totalChange = 0.00;
    for (const auto &pair : portfolio) {
        string ticker = pair.first;
        double totalPerStock = 0.00;
        for(int i = 0; i < portfolioBuyValues[ticker].size(); i++) {
            totalPerStock += market[ticker];
        }

        std::cout << setw(7) << "Ticker: "
                  << left  << setw(6) << pair.first
                  << right << setw(8) << "Amount: "
                  << left  << setw(4) << pair.second
                  << right << setw(16) << "Average price: $"
                  << left  << setw(8) << calculateAveragePrice(pair.first)
                  << right << setw(8) << "Value: $"
                  << left  << setw(8) << totalPerStock
                  << right << setw(8) << "Change: $"
                  << left  << setw(5) << calculateChange(pair.first)
                  << std::endl;
        // Gather sum of all stocks in portfolio
        sum += totalPerStock;
        totalChange += calculateChange(pair.first);
    }

    // Add remaining balance to sum
    sum += getCash();

    cout << "---------------------------" << endl;
    cout << "Total portfolio value: $" << sum << endl;
    if(totalChange > 0) {
        cout << "Total gains: $" << totalChange << endl;
    } else if (totalChange < 0) {
        cout << "Total losses: $" << totalChange << endl;
    } else {
        cout << "You've broken even." << endl;
    }
    cout << "---------------------------" << endl << endl;
}

// Print entire portfolio
// Calls the above printPortfolio function (because that's private and this is
// public)
void account::printStocks() {
    cout << "\nPortfolio:" << endl;
    cout << "Available cash: $" << getCash() << endl;
    cout << "---------------------------" << endl;
    printPortfolio();
}

// Temp function to simulate market fluctuations
void account::changeValue(const string& ticker) {
    double f = (double)rand() / RAND_MAX;
    double sum = -2.00 + f * (2.00 - -2.00);
    cout << ticker <<  " CHANGED BY: " << fixed << setprecision(2) << sum << endl;
    market[ticker] += sum;
}
