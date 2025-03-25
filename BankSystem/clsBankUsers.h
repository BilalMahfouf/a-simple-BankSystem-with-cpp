#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include"clsDate.h"
#include <vector>
#include <fstream>
#include"clsPerson.h"
#include"clsUtil.h"

class clsBankUsers:public clsPerson
{
private:
	string _UserName;
	string _Password;
    int _Permission;
	bool _MarkForDeleted = false;
    string _Date;
   

    

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    static clsBankUsers _ConvertLineToUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

       

        return clsBankUsers(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5], 5)
            , stoi(vUserData[6]));

    }

    static string _ConvertClientObjectToLine(clsBankUsers User, string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password,5) + Seperator;
        UserRecord += to_string(User.Permission);

        return UserRecord;

    }

    static  vector <clsBankUsers> _LoadUsersDataFromFile()
    {

        vector <clsBankUsers> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            
            string Line;


            while (getline(MyFile, Line))
            {

                clsBankUsers Client = _ConvertLineToUserObject(Line);

                vUsers.push_back(Client);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsBankUsers> &vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankUsers U : vUsers)
            {
                if (U.MarkForDeleted == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConvertClientObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

     void _Update() {
        vector<clsBankUsers> vUsers = _LoadUsersDataFromFile();

        for (clsBankUsers& U : vUsers) {
            if (U.UserName == GetUserName()) {
                U = *this;
                break;
            }
        }
        _SaveUsersDataToFile(vUsers);
    }

     void _AddNew() {
         _AddDataLineToFile(_ConvertClientObjectToLine(*this));
     }

     static clsBankUsers _GetEmptyUserObject()
    {
        return clsBankUsers(enMode::EmptyMode, "", "", "", "", "", "",0);
    }

     static string _ConvertUserLoginObjectToLine(clsBankUsers User ,string Separator="#//#")
     {
         string Result = "";
        
         Result += clsDate::GetSystemDateTimeString() + Separator;
         Result += User.UserName + Separator;
         Result += clsUtil::EncryptText(User.Password,10) + Separator;
         Result += to_string(User.Permission);
         return Result;
     }

     static clsBankUsers _ConvertLineToUserLoginObject(string Line, string Separator = "#//#")
     {
         vector<string> User = clsString::Split(Line,Separator);
         return clsBankUsers(enMode::UpdateMode, "", "", "", "", User[1], clsUtil::DecryptText(User[2], 10)
             , stoi(User[3]),User[0]);

        
     }

     static  void _SaveUserLoginToFile(clsBankUsers UserLoginRegister)
     {
         string Line = "";
         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::app | ios::out);
         if (MyFile.is_open())
         {
             Line = _ConvertUserLoginObjectToLine(UserLoginRegister);
             MyFile << Line << endl;
             MyFile.close();
         }
     }

     static vector<clsBankUsers> _LoadUsersLoginRegisterFromFile()
     {
         vector <clsBankUsers> vUsersLoginRegister;

         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::in);//read Mode

         if (MyFile.is_open())
         {

             string Line;


             while (getline(MyFile, Line))
             {

                 clsBankUsers UserLoginRegister = _ConvertLineToUserLoginObject(Line);

                 vUsersLoginRegister.push_back(UserLoginRegister);
             }

             MyFile.close();

         }

         return vUsersLoginRegister;

     }

    

public:

    

    clsBankUsers(const enMode& Mode, const string& FirstName, const string& LastName,
        const string& Email, const string& Phone ,const string &UserName,const string& Password,
        const int &Permission,string Date="") :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _UserName = UserName;
        _Password = Password;
        _Mode = Mode;
        _Permission = Permission;
        _Date = Date;
    }
    
    void SetUserName(const string& UserName)
    {
        _UserName = UserName;
    }
    string GetUserName() {
        return _UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(const string& Password)
    {
        _Password = Password;
    }
    string GetPassword() {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetMarkForDeleted(const bool& MarkForDeleted)
    {
        _MarkForDeleted = MarkForDeleted;
    }
    bool GetMarkForDeleted() {
        return _MarkForDeleted;
    }
    __declspec(property(get = GetMarkForDeleted, put = SetMarkForDeleted)) bool MarkForDeleted;


    void SetPermission(const int& Permission) {
        _Permission = Permission;
    }
    int GetPermission()
    {
        return _Permission;
    }
    __declspec(property(get = GetPermission, put = SetPermission)) int Permission;

    void SetDate(const string& Date)
    {
        _Date = Date;
    }
    string GetDate() {
        return _Date;
    }
    __declspec(property(get = GetDate, put = SetDate)) string Date;




    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            return svFaildEmptyObject;
        }
        case enMode::UpdateMode:
        {
            _Update();
            return svSucceeded;
        }
        case enMode::AddNewMode:
        {
            if (IsUserExist(_UserName))
            {
                return svFaildEmptyObject;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return svSucceeded;
            }
            break;
        }

        }
    }

   static  clsBankUsers Find(const string& UserName)
    {
        vector<clsBankUsers> vUsers = _LoadUsersDataFromFile();
        for (clsBankUsers& U : vUsers) {
            if (U.UserName == UserName)
            {
                return U;
            }
        }

        return _GetEmptyUserObject();
    }

   static  clsBankUsers Find(const string& UserName,const string &Password)
   {
       vector<clsBankUsers> vUsers = _LoadUsersDataFromFile();
       for (clsBankUsers& U : vUsers) {
           if (U.UserName == UserName && U.Password==Password)
           {
               return U;
           }
       }

       return _GetEmptyUserObject();
   }

   static  bool IsUserExist(const string& UserName)
    {
        clsBankUsers User = clsBankUsers::Find(UserName);
        return (!User.IsEmpty());
    }

   static vector<clsBankUsers> GetUsersList() {
       return _LoadUsersDataFromFile();
   }

   bool Delete1()
   {
       vector <clsBankUsers> _vUsers;
       _vUsers = _LoadUsersDataFromFile();

       for (clsBankUsers& U : _vUsers)
       {
           if (U.UserName == _UserName)
           {
               U._MarkForDeleted = true;
               break;
           }

       }

       _SaveUsersDataToFile(_vUsers);

       *this = _GetEmptyUserObject();

       return true;

   }

   static clsBankUsers GetAddNewClientObject(const string &UserName)
   {
       return clsBankUsers(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
   }

   enum enPermissions {
       eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
       pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128
   };
   bool CheckAccessPermission(enPermissions Permission)
   {
       if (this->Permission == enPermissions::eAll)
           return true;

       if ((Permission & this->Permission) == Permission)
           return true;
       else
           return false;

   }

 
   void SaveUserLoginRegister()
   {
       _SaveUserLoginToFile(*this);
   }

   static vector<clsBankUsers> GetUserLoginRegisterList()
   {
       return _LoadUsersLoginRegisterFromFile();
   }

  

};

