#include <iostream>
#include "../clsUser.h"
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "../clsBankClient.h"
#include "../Global.h"
using namespace std;

class clsTransfareScreen : protected clsScreen
{
private:
    static clsBankClient readClient(string message)
    {
        string accountNumber;

        cout << message;
        accountNumber = clsInputValidate::ReadString();
        clsBankClient client = clsBankClient::Find(accountNumber);
        while (client.IsEmpty())
        {
            cout << "Account Number does not found , try again: ";
            accountNumber = clsInputValidate::ReadString();
            client = clsBankClient::Find(accountNumber);
        }
        return client;
    }
    static void _PrintClient(clsBankClient client, string title)
    {
        cout << "\n" + title;
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.GetFirstName();
        cout << "\nLastName    : " << client.GetLastName();
        cout << "\nAcc. Number : " << client.AccountNumber();
        cout << "\nBalance     : " << client.GetAccountBalance();
        cout << "\n___________________\n";
    }

public:
    static void showTransferScreen()
    {
        _DrawScreenHeader("Transfer Screen");
        clsBankClient sender = readClient("Enter Sender Acc Number: ");
        _PrintClient(sender, "Sender Infos: ");
        clsBankClient receiver = readClient("\nEnter Receiver Acc Number: ");
        _PrintClient(receiver, "Receiver Infos: ");
        cout << "Enter Amount ";
        float amount = clsInputValidate::ReadFloatNumberBetween(0, sender.GetAccountBalance(), "Amount Exeeded The Sender Balance , try again: ");
        cout << "Are you sure you want to perform this operation: ";
        char answer;
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            sender.Withdraw(amount);
            receiver.Deposit(amount);
            cout << "\nUpdated Infos: ";
            _PrintClient(sender, "Sender Infos: ");
            _PrintClient(receiver, "Receiver Infos: ");
            Current_User.registerTransfer(sender, receiver, amount);
        }
    }
};