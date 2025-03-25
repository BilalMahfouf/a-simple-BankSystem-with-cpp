#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include"Global.h"

using namespace std;
class clsBankClient : public clsPerson
{
private:
    struct stTransferLogRegister;
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;


    string _AccountNumber;
    string _PinCode;
    double _AccountBalance;
    bool _MarkedForDelete = false;



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
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

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

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static stTransferLogRegister _ConvertLineToTransferLog(string Line, string Seperator = "#//#")
    {
        vector<string> vRegisterData;
        vRegisterData = clsString::Split(Line, Seperator);
        stTransferLogRegister Register;
        Register.Date = vRegisterData.at(0);
        Register.FromClientAccNum = vRegisterData.at(1);
        Register.ToClientAccNum = vRegisterData.at(2);
        Register.AmountTransferred = stod(vRegisterData.at(3));
        Register.FromClientBalance = stod(vRegisterData.at(4));
        Register.ToClientBalance = stod(vRegisterData.at(5));
        Register.UserName = vRegisterData.at(6);

        return Register;

    }

    static string _ConverClientObjectToLine(stTransferLogRegister LogRegister, string Seperator = "#//#")
    {

        string stRegisterRecord = "";
        stRegisterRecord += LogRegister.Date + Seperator;
        stRegisterRecord += LogRegister.FromClientAccNum + Seperator;
        stRegisterRecord += LogRegister.ToClientAccNum + Seperator;
        stRegisterRecord += to_string(LogRegister.AmountTransferred) + Seperator;
        stRegisterRecord += to_string(LogRegister.FromClientBalance) + Seperator;
        stRegisterRecord += to_string(LogRegister.ToClientBalance) + Seperator;
        stRegisterRecord += LogRegister.UserName;

        return stRegisterRecord;

    }

    static  vector <stTransferLogRegister> _LoadTransferLogDataFromFile()
    {

        vector <stTransferLogRegister> vTransferLog;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                stTransferLogRegister Register = _ConvertLineToTransferLog(Line);

                vTransferLog.push_back(Register);
            }

            MyFile.close();

        }

        return vTransferLog;

    }

    static  void _SaveTransferLogToFile(stTransferLogRegister Register)
    {
        string Line = "";
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::app | ios::out);
        if (MyFile.is_open())
        {
            Line = _ConverClientObjectToLine(Register);
            MyFile << Line << endl;
            MyFile.close();
        }
    }


public:


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

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

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
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
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;



    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

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

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }



    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    void Deposit(const double& Amount) {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(const double& Amount) {
        if (_AccountBalance < Amount)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();

        }

    }

    static double GetTotalBalances() {

        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();
        double TotalBalances = 0;
        for (clsBankClient& C : _vClients)
        {
            TotalBalances += C.AccountBalance;
        }
        return TotalBalances;
    }

    bool Transfer(const double& Amount, clsBankClient& Destination)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            Withdraw(Amount);
            Destination.Deposit(Amount);

            clsBankClient::stTransferLogRegister Register;
            Register = clsBankClient::GetTransferLogObject(clsDate::GetSystemDateTimeString()
                ,AccountNumber(), Destination.AccountNumber(), Amount,AccountBalance,
                Destination.AccountBalance, CurrentUser.UserName);

            clsBankClient::_SaveTransferLogToFile(Register);

            return true;
        }
    }

    struct stTransferLogRegister
    {
        string UserName;
        string Date;
        string FromClientAccNum;
        string ToClientAccNum;
       double AmountTransferred;
        double FromClientBalance;
        double ToClientBalance;
    };

    static stTransferLogRegister GetTransferLogObject(string Date,string FromClientAccNum, string ToClientAccNum,
        double AmountTransferred, double FromClientBalance, double ToClientBalance,string UserName)
    {
        stTransferLogRegister Register;
        Register.Date = Date;
        Register.FromClientAccNum = FromClientAccNum;
        Register.ToClientAccNum = ToClientAccNum;
        Register.AmountTransferred = AmountTransferred;
        Register.FromClientBalance = FromClientBalance;
        Register.ToClientBalance = ToClientBalance;
        Register.UserName = UserName;
        return Register;
    }

   static  vector<stTransferLogRegister> GetTransferLogList()
    {
        return _LoadTransferLogDataFromFile();
    }


};

