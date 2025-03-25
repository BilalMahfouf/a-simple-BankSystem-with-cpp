#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsBankUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"



class clsFindUserScreen :protected clsScreen
{
private:
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
    static void ShowFindUserScreen() {
        _DrawScreenHeader("\tFind Client Screen");

        string UserName;
        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();
        while (!clsBankUsers::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsBankUsers User = clsBankUsers::Find(UserName);

        if (!User.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User);


    }
};

