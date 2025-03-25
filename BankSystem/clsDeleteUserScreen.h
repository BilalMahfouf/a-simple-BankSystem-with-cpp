#pragma once
#include <iostream>
#include "clsBankUsers.h"
#include <iomanip>
#include "clsScreen.h"
#include"clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
{

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

public:
    static void ShowDeleteUserScreen() {

        _DrawScreenHeader("\t Delete User Screen");

        vector<clsBankUsers> vUsers = clsBankUsers::GetUsersList();

        cout << "\nEnter User Name ";
        string UserName = clsInputValidate::ReadString();
        while (!clsBankUsers::IsUserExist(UserName)) {
            cout << "\nUser name [" << UserName << "] don't exist,enter an other one ";
            UserName = clsInputValidate::ReadString();
        }
        clsBankUsers User = clsBankUsers::Find(UserName);

        _PrintUser(User);

        cout << "\nAre you sure you want to delete this user y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {


            if (User.Delete1())
            {
                cout << "\nUser Deleted Successfully :-)\n";

                _PrintUser(User);

            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }



};


