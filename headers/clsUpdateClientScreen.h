#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void ReadClientInfo(clsBankClient &Client)

    {
        char answer;
        answer = clsInputValidate::readChar("Do you want to Update First Name: ");

        if ((answer == 'Y') || (answer == 'y'))
        {
            cout
                << "\nEnter FirstName: ";
            Client.SetFirstName(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update Last Name: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter LastName: ";
            Client.SetLastName(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update Email: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter Email: ";
            Client.SetEmail(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update Phone: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter Phone: ";
            Client.SetPhone(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update PinCode: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter PinCode: ";
            Client.SetPinCode(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update Account Balance: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter Account Balance: ";
            Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
        }
    }
    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1
    };

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
    static void UpdateClient()
    {
        if (!doesUserHaveAccess(clsUser::enPermissions::pUpdateClients))
            return;
        _DrawScreenHeader("Update Client Info");
        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber, "Clients.txt"))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber, "Clients.txt");
        _PrintClient(Client1);
        cout
            << "\n\nUpdate Client Info:";
        cout << "\n____________________\n";

        ReadClientInfo(Client1);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = Client1.Save("Clients.txt");

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(Client1);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        }
    }
};