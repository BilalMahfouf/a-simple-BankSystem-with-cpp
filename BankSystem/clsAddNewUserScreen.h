#pragma once
#include <iostream>
#include "clsBankUsers.h"
#include <iomanip>
#include "clsScreen.h"
#include"clsInputValidate.h"

class clsAddNewUserScreen:protected clsScreen
{
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
	static void ShowAddNewUserScreen() {

        _DrawScreenHeader("\t Add New User Screen");

		vector<clsBankUsers> vUsers = clsBankUsers::GetUsersList();

		cout << "\nEnter User Name ";
		string UserName = clsInputValidate::ReadString();
		while (clsBankUsers::IsUserExist(UserName)) {
			cout << "\nUser name [" << UserName << "] already exist,enter an other one ";
			UserName = clsInputValidate::ReadString();
		}
		clsBankUsers User = clsBankUsers::GetAddNewClientObject(UserName);
        _ReadUserInfo(User);
        
        

   
        clsBankUsers::enSaveResults SaveResult = User.Save();
        switch (SaveResult) {
        case clsBankUsers::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(User);
            break;
        }
        case clsBankUsers::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankUsers::enSaveResults::svFaildUserNameExists:
        {
            cout << "\nError account was not saved because UserName is used!\n";
            break;

        }
        }


	}
};

