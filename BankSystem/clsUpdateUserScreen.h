#pragma once
#pragma once
#include <iostream>
#include "clsBankUsers.h"
#include <iomanip>
#include "clsScreen.h"
#include"clsInputValidate.h"

class clsUpdateUserScreen:protected clsScreen
{
private:
    static void _ReadUserInfo(clsBankUsers& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permission = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsBankUsers User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permission;
        cout << "\n___________________\n";

    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
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


            Permissions += clsBankUsers::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsBankUsers::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsBankUsers::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsBankUsers::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsBankUsers::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsBankUsers::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsBankUsers::enPermissions::pManageUsers;
        }
        cout << "\nLogin Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsBankUsers::enPermissions::pLoginRegister;
        }


        return Permissions;

    }

    public:

        static void ShowUpdateUserScreen()
        {
            _DrawScreenHeader("\t Update User Screen");

            vector<clsBankUsers> vUsers = clsBankUsers::GetUsersList();

            cout << "\nEnter User Name ";
            string UserName = clsInputValidate::ReadString();
            while (!clsBankUsers::IsUserExist(UserName)) {
                cout << "\nUser name [" << UserName << "] don't exist,enter an other one ";
                UserName = clsInputValidate::ReadString();
            }
            clsBankUsers User = clsBankUsers::Find(UserName);
            _PrintUser(User);

            cout << "\nAre you sure you want to Update this user y/n? ";

            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {
                _ReadUserInfo(User);
                
                switch(User.Save())
                {
                case clsBankUsers::enSaveResults::svSucceeded:
                {
                    cout << "\nUser updated successfully";
                    _PrintUser(User);
                    break;
                }
                
                case clsBankUsers::enSaveResults::svFaildEmptyObject:
                {
                    cout << "\nError account was not saved because it's Empty";
                    break;

                }
                }
            

               
            }
        }
           
 };



