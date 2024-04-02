#pragma once
#include <iostream>
#include "../clsScreen.h"
#include "../clsPerson.h"
#include "../clsUser.h"
#include "../clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
{

private:
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
        cout << "\nShow Log Register file? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pShowLoginREgister;
        }

        return Permissions;
    }
    static void UpdateUserInfo(clsUser &User)

    {
        char answer;
        answer = clsInputValidate::readChar("Do you want to Update First Name: ");

        if ((answer == 'Y') || (answer == 'y'))
        {
            cout
                << "\nEnter FirstName: ";
            User.SetFirstName(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update Last Name: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter LastName: ";
            User.SetLastName(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update Email: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter Email: ";
            User.SetEmail(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update Phone: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter Phone: ";
            User.SetPhone(clsInputValidate::ReadString());
        }
        answer = clsInputValidate::readChar("Do you want to Update PinCode: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nEnter PinCode: ";
            User.SetPassword(clsSecurity::encryptString(clsInputValidate::ReadString(), superSecretKey));
        }
        answer = clsInputValidate::readChar("Do you want to Update Permissions: ");
        if ((answer == 'Y') || (answer == 'y'))
        {
            cout << "\nSelect new Permissions: ";
            User.SetPermissions(ReadPermissions());
        }
    }
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
    static void showUpdateUserScreen()
    {
        _DrawScreenHeader("Update User Screen");
        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        UpdateUserInfo(User);
        User.Save();
    }
};