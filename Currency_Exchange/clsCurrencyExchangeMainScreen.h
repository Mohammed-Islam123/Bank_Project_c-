#pragma once
#include <iostream>
#include "../headers/clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "../headers/clsInputValidate.h"
#include "clsUpdateCurrencyRate.h"
#include "clsExchangeCalculator.h"
#include "clsFindCurrency.h"
#include <iomanip>
#include <csignal>
#include <termios.h>
#include <unistd.h>

class clsCurrencyExchangeMainScreen : protected clsScreen
{

private:
    enum enCurrenciesMainMenueOptions
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4,
        eMainMenue = 5
    };

    static short ReadCurrenciesMainMenueOptions()
    {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 5]? ";
        short Choice = (short)clsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrenciesMenue()
    {
        cout << setw(37) << left << ""
             << "\n\tPress any key to go back to Main Menue...\n";
        struct termios old_tio, new_tio;
        unsigned char c;

        // get the terminal settings for stdin
        tcgetattr(STDIN_FILENO, &old_tio);

        // we want to keep the old setting to restore them at the end
        new_tio = old_tio;

        // disable canonical mode (buffered i/o) and local echo
        new_tio.c_lflag &= (~ICANON & ~ECHO);

        // set the new settings immediately
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

        while (true)
        {
            cin >> c;
            break;
        };

        // restore the former settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        ShowCurrenciesMenue();
    }

    static void _ShowCurrenciesListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrency::showFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyRate::showUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsExchangeCalculator::showExchangeCalculatorScreen();
    }

    static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrenciesMainMenueOptions)
    {

        switch (CurrenciesMainMenueOptions)
        {
        case enCurrenciesMainMenueOptions::eListCurrencies:
        {
            system("clear");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eFindCurrency:
        {
            system("clear");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eUpdateCurrencyRate:
        {
            system("clear");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eCurrencyCalculator:
        {
            char answer;
            do
            {

                system("clear");
                _ShowCurrencyCalculatorScreen();
                cout << "\nDo you want to perform another Operation: ";
                cin >> answer;
            } while (answer == 'Y' || answer == 'y');

            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eMainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void ShowCurrenciesMenue()
    {

        system("clear");
        _DrawScreenHeader("    Currancy Exhange Main Screen");

        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t\t  Currency Exhange Menue\n";
        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t[1] List Currencies.\n";
        cout << setw(37) << left << ""
             << "\t[2] Find Currency.\n";
        cout << setw(37) << left << ""
             << "\t[3] Update Rate.\n";
        cout << setw(37) << left << ""
             << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << ""
             << "\t[5] Main Menue.\n";
        cout << setw(37) << left << ""
             << "===========================================\n";

        _PerformCurrenciesMainMenueOptions((enCurrenciesMainMenueOptions)ReadCurrenciesMainMenueOptions());
    }
};
