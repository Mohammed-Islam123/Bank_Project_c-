#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
class clsBankClient : public clsPerson
{

private:
    struct stMaxLengths
    {
        int accountNumberLength = 0, nameLength = 0, phoneLength = 0, email = 0, pin_codeLength = 0;
    };
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNew = 2,
    };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    static string _repeat(char c, int n)
    {
        string s = "";
        for (int i = 0; i < n; i++)
        {
            s += c;
        }
        return s;
    }
    void _getMaxLengths(stMaxLengths lengths, vector<clsBankClient> clients)
    {
        for (clsBankClient &c : clients)
        {
            lengths.accountNumberLength = c.AccountNumber().length() > lengths.accountNumberLength ? c.AccountNumber().length() : lengths.accountNumberLength;
            lengths.email = c.GetEmail().length() > lengths.email ? c.AccountNumber().length() : lengths.email;
            lengths.nameLength = c.FullName().length() > lengths.nameLength ? c.FullName().length() : lengths.nameLength;
            lengths.phoneLength = c.GetPhone().length() > lengths.phoneLength ? c.GetPhone().length() : lengths.phoneLength;
            lengths.pin_codeLength = c.GetPinCode().length() > lengths.pin_codeLength ? c.GetPinCode().length() : lengths.pin_codeLength;
        }
    }

    static void PrintClientRecordLine(clsBankClient Client, stMaxLengths lengths)
    {

        cout << "| " << setw(lengths.accountNumberLength) << left << Client.AccountNumber();
        cout << "| " << setw(lengths.nameLength) << left << Client.FullName();
        cout << "| " << setw(lengths.phoneLength) << left << Client.GetPhone();
        cout << "| " << setw(lengths.email) << left << Client.GetEmail();
        cout << "| " << setw(lengths.pin_codeLength) << left << Client.GetPinCode();
        cout << "| " << setw(12) << left << Client.GetAccountBalance();
    }
    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                             vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client._FirstName + Seperator;
        stClientRecord += Client._LastName + Seperator;
        stClientRecord += Client._Email + Seperator;
        stClientRecord += Client._Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client._PinCode + Seperator;
        stClientRecord += to_string(Client._AccountBalance);

        return stClientRecord;
    }

    static vector<clsBankClient> _LoadClientsDataFromFile(string fileName)
    {

        vector<clsBankClient> vClients;

        fstream MyFile;
        MyFile.open(fileName, ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();
        }

        return vClients;
    }

    static void _SaveCleintsDataToFile(vector<clsBankClient> vClients, string fileName)
    {

        fstream MyFile;
        MyFile.open(fileName, ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                DataLine = _ConverClientObjectToLine(C);
                MyFile << DataLine << endl;
            }

            MyFile.close();
        }
    }

    void _Update(string fileName)
    {
        vector<clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile(fileName);

        for (clsBankClient &C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients, fileName);
    }

    void _AddDataLineToFile(string stDataLine, string fileName)
    {
        fstream MyFile;
        MyFile.open(fileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine;

            MyFile.close();
        }
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    void _AddNew(string fileName)
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this), "Clients.txt");
    }

public:
    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double srcBalanceAfter;
        double destBalanceAfter;
        string UserName;
    };
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        vector<string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;
    }
    clsBankClient(enMode Mode, string FirstName, string LastName,
                  string Email, string Phone, string AccountNumber, string PinCode,
                  float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        _Update("Clients.txt");
    }
    bool Withdraw(double Amount)
    {
        if (Amount <= _AccountBalance)
        {
            _AccountBalance -= Amount;
            _Update("Clients.txt");
            return true;
        }
        return false;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    // __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    // __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static clsBankClient getAddNewClientObject(string accountNumber)
    {
        return clsBankClient(enMode::AddNew, "", "", "", "", accountNumber, "", 0);
    }

    static clsBankClient Find(string AccountNumber, string fileName = "Clients.txt")
    {

        fstream MyFile;
        MyFile.open(fileName, ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode, string fileName)
    {

        fstream MyFile;
        MyFile.open(fileName, ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client._PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1
    };

    enSaveResults Save(string fileName = "Clients.txt")
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {

            _Update(fileName);

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::AddNew:
            _AddNew("Clients.txt");
            _Mode = enMode::UpdateMode;
            return enSaveResults::svSucceeded;
            break;
        }
    }

    bool Delete(string fileName = "Clients.txt")
    {
        fstream file;
        file.open(fileName, ios::in);
        vector<clsBankClient> clients;
        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                if (!(_ConvertLinetoClientObject(line).AccountNumber() == _AccountNumber))
                {
                    clients.push_back(_ConvertLinetoClientObject(line));
                }
            }
            _SaveCleintsDataToFile(clients, "Clients.txt");
            *this = _GetEmptyClientObject();
            return true;
        }
        return false;
    }

    static bool IsClientExist(string AccountNumber, string fileName = "Clients.txt")
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber, fileName);

        return (!Client1.IsEmpty());
    }

    static void showCLeintsList(string fileName = "Clients.txt")
    {
        stMaxLengths lengths;
        vector<clsBankClient> vClients = _LoadClientsDataFromFile(fileName);
        int size = vClients.size();
        cout << "\n\t\t\tClient List (" << size << ") Client(s)" << endl;
        cout << _repeat('_', 50) << endl;
        cout << "| " << left << setw(lengths.accountNumberLength) << "Account Number "
             << "| " << left << setw(lengths.nameLength) << "Client Name"
             << "| " << left << setw(lengths.phoneLength) << "| " << setw(lengths.email) << "Email"
             << "| " << left << setw(lengths.pin_codeLength) << "| " << left << setw(12) << "Account Balance" << endl
             << endl;
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                clsBankClient::PrintClientRecordLine(Client, lengths);
                cout << endl;
            }

        cout << _repeat('_', 50) << endl;
    }
    static vector<clsBankClient> GetClientsList(string fileName = "Clients.txt")
    {
        return _LoadClientsDataFromFile(fileName);
    }
    static float GetTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList("Clients.txt");

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.GetAccountBalance();
        }

        return TotalBalances;
    }
    static vector<stTrnsferLogRecord> GetTransfersLogList()
    {
        vector<stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTrnsferLogRecord TransferRecord;

            while (getline(MyFile, Line))
            {

                TransferRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);
            }

            MyFile.close();
        }

        return vTransferLogRecord;
    }
}

;
