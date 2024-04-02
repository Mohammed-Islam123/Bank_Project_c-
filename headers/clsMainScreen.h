#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindclientScreen.h"
#include "clsTransactions.h"
#include "clsManageUsers.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "../Currency_Exchange/clsCurrencyExchangeMainScreen.h"
#include "clsLog.h"
#include "Global.h"
#include <csignal>
#include <termios.h>
#include <unistd.h>
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    static string _repeat(char c, int n)
    {
        string s = "";
        for (int i = 0; i < n; i++)
        {
            s += c;
        }
        return s;
    }

    enum enMainMenueOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eShowLog = 8,
        eCurrencyExchage = 9,
        eExit = 10
    };
    clsUser _user;
    static bool _checkPermission(int userPermission, clsUser::enPermissions categPermission)
    {
        if (userPermission == -1)
            return true;
        return (userPermission & (int)categPermission) == (int)categPermission;
    }
    static void _showAcessDeniedScreen()
    {
        system("clear");
        cout << "Permission Denied, Contact your Admin ..";
    }
    static int _ReadMainMenueOption()
    {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 10]? ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }

    static void _GoBackToMainMenue()
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

        showMainMenu();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList("Clients.txt");
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClient();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::showDeleteClient();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::UpdateClient();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::findClient();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _ShowLog()
    {
        clsLog::showLogScreen();
    }
    static void _Logout()
    {
        Current_User = clsUser::Find("");
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("clear");
            if (_checkPermission(Current_User.GetPermissions(), clsUser::enPermissions::pListClients))
                _ShowAllClientsScreen();
            else
                _showAcessDeniedScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("clear");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("clear");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("clear");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("clear");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("clear");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("clear");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        case enMainMenueOptions::eShowLog:
            system("clear");
            _ShowLog();
            _GoBackToMainMenue();
            break;
        case enMainMenueOptions::eCurrencyExchage:
            system("clear");
            clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
            _GoBackToMainMenue();
            break;
        case enMainMenueOptions::eExit:
            system("clear");
            _Logout();
            break;
        }
    }

public:
    static void showMainMenu()
    {
        system("clear");
        _DrawScreenHeader("Main Screen");
        cout << setw(37) << left << ""
             << clsMainScreen::_repeat('=', 37) << endl;
        cout << setw(29) << left << ""
             << "\t\t\tMain Menue\n";
        cout << setw(37) << left << ""
             << clsMainScreen::_repeat('=', 37) << endl;
        cout << setw(37) << left << ""
             << "\t[1] Show Client List.\n";
        cout << setw(37) << left << ""
             << "\t[2] Add New Client.\n";
        cout << setw(37) << left << ""
             << "\t[3] Delete Client.\n";
        cout << setw(37) << left << ""
             << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << ""
             << "\t[5] Find Client.\n";
        cout << setw(37) << left << ""
             << "\t[6] Transactions.\n";
        cout << setw(37) << left << ""
             << "\t[7] Manage Users.\n";
        cout << setw(37) << left << ""
             << "\t[8] Login Register.\n";
        cout << setw(37) << left << ""
             << "\t[9] Currency Exchage.\n";
        cout << setw(37) << left << ""
             << "\t[10] Logout.\n";
        cout << setw(37) << left << ""
             << clsMainScreen::_repeat('=', 37) << endl;
        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    };
};
