#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.GetFirstName();
        cout << "\nLastName    : " << client.GetLastName();
        cout << "\nEmail       : " << client.GetEmail();
        cout << "\nPhone       : " << client.GetPhone();
        cout << "\nAcc. Number : " << client.AccountNumber();
        cout << "\nBalance     : " << client.GetAccountBalance();
        cout << "\nPin Code     : " << client.GetPinCode();
        cout << "\n___________________\n";
    }

public:
    static void findClient()
    {
        if (!doesUserHaveAccess(clsUser::enPermissions::pFindClient))
            return;
        _DrawScreenHeader("Find Client Screen");
        cout
            << "Enter Account Number : ";
        string accountNumber = clsInputValidate::ReadString();
        clsBankClient client = clsBankClient::Find(accountNumber, "Clients.txt");
        if (!client.IsEmpty())
        {
            cout << "Client Found !!" << endl;
            _PrintClient(client);
        }

        cout << "Client Not Found" << endl;
    }
};