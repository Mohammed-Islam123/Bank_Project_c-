#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
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
        cout << "\n___________________\n";
    }

public:
    static void showDeleteClient()
    {
        if (!doesUserHaveAccess(clsUser::enPermissions::pDeleteClient))
            return;
        _DrawScreenHeader("\tDelete Client Screen");
        cout << "Enter a Account Number: ";
        string tempAccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(tempAccountNumber, "Clients.txt"))
        {
            cout << "Account not found, pls try another number: ";
            string tempAccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(tempAccountNumber, "Clients.txt");
        _PrintClient(client);
        char answer;
        cout << "Do you want to delete this client: Y/N??";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            if (client.Delete())
            {
                cout << "Client Deleted successfully !!" << endl;
            }
            else
            {
                cout << "Error while deleting Client";
            }
        }
    }
};