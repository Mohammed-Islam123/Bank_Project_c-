#pragma once
#include <iostream>
#include "../clsScreen.h"
#include "../clsPerson.h"
#include "../clsUser.h"
#include "../clsInputValidate.h"
using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";
    }

public:
    static void showFindUserScreen()
    {
        _DrawScreenHeader("Find User Screen");
        cout << "Enter UserName: ";
        string userName = clsInputValidate::ReadString();
        clsUser foundUser = clsUser::Find(userName);
        if (foundUser.IsEmpty())
        {
            cout << "User Not Found !! \n";
        }
        else
        {
            cout << "\nUser Found :)\n";
            _PrintUser(foundUser);
        }
    }
};