#include <iostream>
#include "headers/clsBankClient.h"
#include "headers/clsInputValidate.h"
#include "headers/clsUtil.h"
#include "headers/clsMainScreen.h"
#include "headers/clsLoginScreen.h"
using namespace std;

void ReadClientInfo(clsBankClient &Client)
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

void addNewClient()
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
    newCLient.Save("Clients.txt");
}

void showTotalBalances(string fileName)
{

    vector<clsBankClient> vClients = clsBankClient::GetClientsList(fileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(20) << "Client Name";

    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (clsBankClient Client : vClients)
        {

            // PrintClientRecordLine(Client, true, true, false, false, false, true);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    float total = clsBankClient::GetTotalBalances();
    cout << "\t\t\t\tTotla Balances: " << total << endl;
    cout << "\t\t\t\t(" << clsUtil::NumberToText(total);
}

int main()
{
    // We Use The while loop to prevent cercular reference problem
    while (clsLoginScreen::showLoginScreen())
        ;
}
