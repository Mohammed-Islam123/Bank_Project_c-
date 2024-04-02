#include <iostream>
#include "clsCurrency.h"
#include "../headers/clsScreen.h"
#include "../headers/clsInputValidate.h"
#include <limits>
class clsExchangeCalculator
{
private:
    static void _printCurrencyCard(clsCurrency currency, string header = "\nCurrency Card: \n")
    {
        cout << header;
        cout << "____________________________" << endl;
        cout << "\nCountry: " << currency.Country();
        cout << "\nCode: " << currency.CurrencyCode();
        cout << "\nName: " << currency.CurrencyName();
        cout << "\nRate(1$): " << currency.Rate();
        cout << "\n____________________________" << endl;
    }
    static clsCurrency _readCurrency(string message)
    {
        cout << message;
        string code = clsInputValidate::ReadString();
        clsCurrency currency = clsCurrency::FindByCode(code);
        while (currency.IsEmpty())
        {
            cout << "Currency Not Found , Try Again: ";
            code = clsInputValidate::ReadString();
            currency = clsCurrency::FindByCode(code);
        }
        return currency;
    }

public:
    static void showExchangeCalculatorScreen()
    {
        clsCurrency currencyFrom = _readCurrency("Enter Currency to exchange from: ");
        clsCurrency currencyTo = _readCurrency("Enter Currency to exchange to: ");
        cout << "Enter Amount to exchange: ";
        float amount = clsInputValidate::ReadFloatNumberBetween(0, numeric_limits<streamsize>::max(), "Enter positive Number: ");
        float resultOfConvertingToDollar = currencyFrom.convertToDollar(amount);
        _printCurrencyCard(currencyFrom, "\nConvert From: \n");
        cout << to_string(amount) + currencyFrom.CurrencyCode() << " = " << to_string(resultOfConvertingToDollar) + " USD" << endl;

        if (currencyTo.CurrencyCode() != "USD")
        {
            _printCurrencyCard(currencyTo, "\nConverting from USD to : \n");
            cout << to_string(amount) + currencyFrom.CurrencyCode() << " = " << to_string(currencyTo.convertFromDollar(resultOfConvertingToDollar)) + currencyTo.CurrencyCode() << endl;
        }
    }
};

/*
read curr from(until found)
read curr2 until found
call  curr1.transferToDollar(curr, amout) returns the result (float)
print curr1
show result
if (curr2 != $)
    prnt curr2
    call curr2.transferFromDollar(curr2, amountInDollar)
    show retult




*/