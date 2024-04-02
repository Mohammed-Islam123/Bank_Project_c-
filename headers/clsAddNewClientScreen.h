#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1
    };
    static void ReadClientInfo(clsBankClient &Client)

    {

        cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
    }
    static void addNewClient()
    {
        cout << "Enter a Account Number: ";
        string tempAccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(tempAccountNumber, "Clients.txt"))
        {
            cout << "Account Already exist pls try another number: ";
            string tempAccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient newCLient = clsBankClient::getAddNewClientObject(tempAccountNumber);
        ReadClientInfo(newCLient);
        if (newCLient.Save("Clients.txt") == enSaveResults::svSucceeded)
        {
            cout << "Client Added Successfully !!" << endl;
            _PrintClient(newCLient);
        }
        else
        {
            cout << "An error occured while adding Client!!" << endl;
        }
    }
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
    static void ShowAddNewClient()
    {
        if (!clsScreen::doesUserHaveAccess(clsUser::enPermissions::pAddNewClient))
            return;
        _DrawScreenHeader("Add New Client Screen !!");
        addNewClient();
    }
};