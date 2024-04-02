#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtil.h"
#include "manageUsersClasses/clsListUsers.h"
#include "manageUsersClasses/addNewUserScreen.h"
#include "manageUsersClasses/clsDeleteUserScreen.h"
#include "manageUsersClasses/clsUpdateUserScreen.h"
#include "manageUsersClasses/clsFindUserScreen.h"
#include "clsUser.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private:
    enum enManageUsersMenueOptions
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenue = 6
    };

    static short ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 6]? ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _GoBackToManageUsersMenue()
    {

        clsUtil::systemPauseForLinux();
        ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen()
    {
        clsListUsers::showListUsers();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::showAddUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::showUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::showFindUserScreen();
    }

    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("clear");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eAddNewUser:
        {
            system("clear");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eDeleteUser:
        {
            system("clear");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eUpdateUser:
        {
            system("clear");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eFindUser:
        {
            system("clear");

            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        default:

            break;
        }
    }

public:
    static void ShowManageUsersMenue()
    {
        if (!doesUserHaveAccess(clsUser::enPermissions::pManageUsers))
            return;
        system("clear");
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t[1] List Users.\n";
        cout << setw(37) << left << ""
             << "\t[2] Add New User.\n";
        cout << setw(37) << left << ""
             << "\t[3] Delete User.\n";
        cout << setw(37) << left << ""
             << "\t[4] Update User.\n";
        cout << setw(37) << left << ""
             << "\t[5] Find User.\n";
        cout << setw(37) << left << ""
             << "\t[6] Main Menue.\n";
        cout << setw(37) << left << ""
             << "===========================================\n";

        _PerformManageUsersMenueOption((enManageUsersMenueOptions)ReadManageUsersMenueOption());
    }
};
