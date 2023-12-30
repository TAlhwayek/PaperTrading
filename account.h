//
// Created by Tony Alhwayek on 11/25/23.
//

#include <string>
#include <unordered_map>


using namespace std;

#ifndef PAPER_TRADING_ACCOUNT_H
#define PAPER_TRADING_ACCOUNT_H

class account {
    // Variables
    double cash;
    unordered_map<string, int> portfolio;
    unordered_map<string, double> market;
    unordered_map<string, vector<double>> portfolioBuyValues;

    // Profit
    float profitPercent;
    float profit;

    // Getters
    double getCash() const;
    void printPortfolio();
    void initializeMarket();
    double calculateChange(const string&);
    double calculateAveragePrice(const string&);

public:
    // Functions
    account();
    void printStocks();
    void buyStock(const string&);
    void sellStock(const string &);
    bool checkIfTickerExists(const string&);
    bool checkIfUserOwnsTicker(const string&);
    void printMarket();
    double generateChange();
    void updateMarket();
};

#endif // PAPER_TRADING_ACCOUNT_H
