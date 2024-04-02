#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
#include <ctime>
#include "Global.h"
#include <fstream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsSecurity.h"
#include <vector>
#include <iomanip>
using namespace std;

class clsLog : clsScreen
{
private:
    struct stData
    {
        string date;
        string time;
        string username;
        string password;
        int permissions;
    };
    static string getCurrentTime()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        return to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
    }
    static stData saveDataToRecord()

    {
        stData currentData;
        currentData.username = Current_User.GetUserName();
        currentData.permissions = Current_User.GetPermissions();
        currentData.password = clsSecurity::encryptString(Current_User.GetPassword(), superSecretKey);
        currentData.date = clsDate::DateToString(clsDate());
        currentData.time = getCurrentTime();
        return currentData;
    }
    static string convertRecordToString(stData currentData, string separator = "#//#")
    {
        return currentData.date + separator + currentData.time + separator + currentData.username + separator + currentData.password + separator + to_string(currentData.permissions);
    }
    static bool saveDatatoFile(string logFileName)
    {
        fstream file;
        file.open(logFileName, ios::app | ios::out);
        if (file.is_open())
        {
            file << convertRecordToString(saveDataToRecord()) << endl;
            file.close();
            return true;
        }
        file.close();
        return false;
    }

    static void printLogLine(vector<string> line)
    {
        cout << setw(8) << left << ""
             << "| " << left << setw(15) << line[0];
        cout
            << left << setw(32) << line[1];
        cout
            << left << setw(15) << line[2];
        cout
            << left << setw(20) << clsSecurity::decryptString(line[3], superSecretKey);
        cout
            << left << setw(10) << line[4];
        cout << endl;
    }
    // Return The number of lines
    static int printLines()
    {
        vector<string> vLine;
        fstream file;
        string line;
        int counter = 0;
        file.open("LogFile.txt", ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {
                vLine = clsString::Split(line, "#//#");
                printLogLine(vLine);
                counter++;
            }
        }
        return counter;
    }

public:
    static void saveLog(string logFileName)
    {
        saveDatatoFile(logFileName);
    }
    static void showLogScreen()
    {
        if (!doesUserHaveAccess(clsUser::pShowLoginREgister))
            return;
        _DrawScreenHeader("Log File");
        cout << endl;
        cout << endl
             << setw(8) << left << ""
             << "________________________________________________________________________________________________\n"
             << endl
             << endl;
        cout
            << setw(8) << left << ""
            << "| " << left << setw(15) << "Date";
        cout
            << "| " << left << setw(25) << "Time";
        cout
            << "| " << left << setw(15) << "UserName";
        cout
            << "| " << left << setw(20) << "Password";
        cout
            << "| " << left << setw(15) << "Permissions" << endl;
        if (printLines() == 0)
            cout
                << setw(8) << left << ""
                << "| " << left << setw(15) << "Log File Is empty";
        cout << endl
             << setw(8) << left << ""
             << "________________________________________________________________________________________________\n"
             << endl
             << endl;
    }
};