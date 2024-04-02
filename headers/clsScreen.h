#pragma once
#include <iostream>
#include "clsUser.h"
#include <ctime>
#include "clsDate.h"
#include "Global.h"
using namespace std;

class clsScreen
{
private:
    static string printDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        return to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_year + 1900);
    }

protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {

        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\t\tCurrent User: " + (Current_User.GetUserName() == "" ? "Not Signed In" : Current_User.GetUserName()) << endl;
        cout << "\t\t\t\t\t\t Date: " + printDate() << endl;
    }
    static bool doesUserHaveAccess(clsUser::enPermissions screenPerm)
    {
        if (!Current_User.checkPermission(screenPerm))
        {
            _DrawScreenHeader("Acess Denied Contact Your Admin\n");
            return false;
        }
        return true;
    }
};
