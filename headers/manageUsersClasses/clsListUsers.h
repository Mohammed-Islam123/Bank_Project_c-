#include <iostream>
#include <iomanip>
#include <string>
#include "../clsUser.h"
#include "../clsScreen.h"
#include "../clsSecurity.h"
#include "../Global.h"

using namespace std;

class clsListUsers : protected clsScreen
{

private:
    static void _PrintClientRecordLine(clsUser Client, bool printUserName, bool printFullName, bool printPhone, bool printEmail, bool printPassword, bool printPermission)
    {
        if (printUserName)
            cout << setw(8) << left << ""
                 << "| " << setw(15) << left << Client.GetUserName();
        if (printFullName)
            cout
                << "| " << setw(20) << left << Client.GetFullName();
        if (printPhone)
            cout
                << "| " << setw(12) << left << Client.GetPhone();
        if (printEmail)
            cout
                << "| " << setw(20) << left << Client.GetEmail();
        if (printPassword)
            cout
                << "| " << setw(10) << left << clsSecurity::decryptString(Client.GetPassword(), superSecretKey);
        if (printPermission)
            cout
                << "| " << setw(12) << left << Client.GetPermissions();
    }

public:
    static void showListUsers()
    {

        vector<clsUser> vUsers = clsUser::GetClientsList("Users.txt");
        _DrawScreenHeader("\t  Users List Screen", "\t    (" + to_string(vUsers.size()) + ") Users(s).");

        cout << setw(8) << left << ""
             << "| " << left << setw(15) << "User Name";
        cout
            << "| " << left << setw(20) << "Full Name";
        cout
            << "| " << left << setw(12) << "Phone";
        cout
            << "| " << left << setw(20) << "Email";
        cout
            << "| " << left << setw(10) << "Password";
        cout
            << "| " << left << setw(12) << "Permissions";
        cout << endl
             << setw(8) << left << ""
             << "________________________________________________________________________________________________\n"
             << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!" << endl;
        else

            for (clsUser User : vUsers)
            {

                clsListUsers::_PrintClientRecordLine(User, true, true, true, true, true, true);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "________________________________________________________________________________________________\n"
             << endl;
    }
};