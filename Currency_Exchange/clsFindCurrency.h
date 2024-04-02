#pragma once
#include <iostream>
#include "../headers/clsScreen.h"
#include "../headers/clsString.h"
#include "../headers/clsInputValidate.h"
#include "clsCurrency.h"
class clsFindCurrency : public clsScreen
{

private:
    static void _printCurrencyCard(clsCurrency currency)
    {
        cout << "\nCurrency Card: \n";
        cout << "____________________________" << endl;
        cout << "\nCountry: " << currency.Country();
        cout << "\nCode: " << currency.CurrencyCode();
        cout << "\nName: " << currency.CurrencyName();
        cout << "\nRate(1$): " << currency.Rate();
        cout << "\n____________________________" << endl;
    }
    static void _showSearchResult(clsCurrency currency)
    {
        if (currency.IsEmpty())
        {
            cout << "Currency not Found\n";
        }
        else
        {
            cout << "Currency Found! !!!!" << endl;
            _printCurrencyCard(currency);
        }
    }
    static void _findCurrency()
    {
        cout << "Find By : [1] Code   [2]Country: ";
        int choice = clsInputValidate::ReadIntNumberBetween(1, 2);
        string code = "", country = "";
        if (choice == 1)
        {

            cout << "Enter the Code: ";
            code = clsInputValidate::ReadString();
            clsCurrency currency = clsCurrency::FindByCode(code);
            _showSearchResult(currency);
        } // Initialize the variable inside the case

        else
        {
            cout << "Enter the Country: ";
            country = clsInputValidate::ReadString();
            clsCurrency currency = clsCurrency::FindByCountry(country);
            _showSearchResult(currency);
        }
        // Initialize the variable inside the case
    }

public:
    static void
    showFindCurrencyScreen()
    {
        _DrawScreenHeader("Find Currency Screen");
        _findCurrency();
    }
};

/*
the user choose the operation
    if 1
        get curr
        find currency
        print card
    if 2
        get country
        find country
        print card
    else
        not found


*/