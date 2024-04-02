#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsClientListScreen : public clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client, bool printAccNum, bool printFullName, bool printPhone, bool printEmail, bool printPinCode, bool printBalance)
    {
        if (printAccNum)
            cout << setw(8) << left << ""
                 << "| " << setw(15) << left << Client.AccountNumber();
        if (printFullName)
            cout
                << "| " << setw(20) << left << Client.FullName();
        if (printPhone)
            cout
                << "| " << setw(12) << left << Client.GetPhone();
        if (printEmail)
            cout
                << "| " << setw(20) << left << Client.GetEmail();
        if (printPinCode)
            cout
                << "| " << setw(10) << left << Client.GetPinCode();
        if (printBalance)
            cout
                << "| " << setw(12) << left << Client.GetAccountBalance();
    }

public:
    static void ShowClientsList(string fileName)
    {
        if (!doesUserHaveAccess(clsUser::enPermissions::pListClients))
            return;
        vector<clsBankClient> vClients = clsBankClient::GetClientsList(fileName);
        _DrawScreenHeader("\t  Client List Screen", "\t    (" + to_string(vClients.size()) + ") Client(s).");

        cout << setw(8) << left << ""
             << "| " << left << setw(15) << "Accout Number";
        cout
            << "| " << left << setw(20) << "Client Name";
        cout
            << "| " << left << setw(12) << "Phone";
        cout
            << "| " << left << setw(20) << "Email";
        cout
            << "| " << left << setw(10) << "Pin Code";
        cout
            << "| " << left << setw(12) << "Balance";
        cout << endl
             << setw(8) << left << ""
             << "________________________________________________________________________________________________\n"
             << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                clsClientListScreen::_PrintClientRecordLine(Client, true, true, true, true, true, true);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "________________________________________________________________________________________________\n"
             << endl;
    }
};
