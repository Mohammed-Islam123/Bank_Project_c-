#pragma once
#include <iostream>
#include <string>
#include "../clsScreen.h"
#include "../clsUser.h"
#include "../clsInputValidate.h"
#include "../clsSecurity.h"
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{

private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nUserName : " << User.GetUserName();
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nPassword     : " << User.GetPassword();
        cout << "\nPermissions     : " << User.GetPermissions();
        cout << "\n___________________\n";
    }
    static int ReadPermissions()
    {
        short Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return Permissions;
    }
    static void ReadUserInfo(clsUser &User)

    {

        cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.SetPassword(clsSecurity::encryptString(clsInputValidate::ReadString(), superSecretKey));

        cout << "\n Select Permissons: \n";
        User.SetPermissions(ReadPermissions());
    }

public:
    static void showAddUserScreen()
    {
        _DrawScreenHeader("Add New User");
        cout << "Enter Username: ";
        string userName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(userName))
        {
            cout << "User \"" + userName + "\" Already exist , Enter another username: ";
            userName = clsInputValidate::ReadString();
        }
        clsUser newUser = clsUser::getNewUser(userName);
        clsAddNewUserScreen::ReadUserInfo(newUser);
        cout << "Client Added Successfully: ";
        _PrintUser(newUser);
        newUser.Save();
    }
};

/*
Read UserName
    Find User Name
    If not Found
        read New User
        store new user
    else
        error
*/