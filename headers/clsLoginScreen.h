#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsUtil.h"
#include "clsLog.h"
#include "clsSecurity.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
        static void _readCredintials(string &username, string &password)
    {
        cout << "Enter Username: ";
        username = clsInputValidate::ReadString();
        cout << "Enter Password: ";
        password = clsInputValidate::ReadString();
    }
    static bool _Login()
    {

        int wrongAnsers = 0;

        string username,
            password;
        bool Login_Failed = false;
        do
        {
            _readCredintials(username, password);

            Current_User = clsUser::Find(username, clsSecurity::encryptString(password, superSecretKey));
            Login_Failed = Current_User.IsEmpty();

            if (Login_Failed)
            {
                wrongAnsers++;
                cout << "Invalid Username or Password!!" << endl;
                if (wrongAnsers < 3)
                    cout << "The system will be locked after " + to_string((3 - wrongAnsers)) + " tries: " << endl;
            }
        } while ((wrongAnsers < 3) && Login_Failed);

        return (wrongAnsers < 3);
    }

public:
    static bool showLoginScreen()
    {
        system("clear");
        _DrawScreenHeader("Login Screen");

        if (_Login())
        {
            clsLog::saveLog("LogFile.txt");
            clsMainScreen::showMainMenu();
            return true;
        }

        else
        {
            system("clear");
            cout << "Sorry But System is locked" << endl;
            clsUtil::systemPauseForLinux();
            return false;
        }
    }
};