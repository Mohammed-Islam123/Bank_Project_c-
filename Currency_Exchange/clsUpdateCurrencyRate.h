#pragma once
#include <iostream>
#include "../headers/clsScreen.h"
#include "clsCurrency.h"
#include <limits>
#include "../headers/clsInputValidate.h"

class clsUpdateCurrencyRate : public clsScreen
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

public:
    static void showUpdateCurrencyScreen()
    {
        _DrawScreenHeader("Update Currency Rate");
        cout << "Enter Currency Code: ";
        string code = clsInputValidate::ReadString();
        clsCurrency currency = clsCurrency::FindByCode(code);
        while (currency.IsEmpty())
        {
            cout << "\nCurrency Not Found, Try Again: ";
            code = clsInputValidate::ReadString();
            currency = clsCurrency::FindByCode(code);
        }
        _printCurrencyCard(currency);
        cout << "Enter New Rate : ";
        float newRate = clsInputValidate::ReadFloatNumberBetween(0, numeric_limits<streamsize>::max(), "Enter Positive number: ");
        currency.UpdateRate(newRate);
        cout << "Update Infos: \n";
        _printCurrencyCard(currency);
    }
};

/*

read curr code
    search until found
    print card
    read new rate
    update the record
    save


*/
