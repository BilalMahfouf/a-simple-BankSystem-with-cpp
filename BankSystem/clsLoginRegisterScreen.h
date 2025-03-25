#pragma once
#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>


class clsLoginRegisterScreen:protected clsScreen
{
private:
	 static void _PrintUserLoginRegisterLine(clsBankUsers User)
    {

        cout << "\t  | " << setw(30) << left << User.Date;
        cout << "| " << setw(15) << left << User.UserName;
        cout << "| " << setw(15) << left << User.Password;
        cout << "| " << setw(15) << left << User.Permission;


    }

public:
    static void ShowLoginRegister()
    {
        if (!CheckAccessRights(clsBankUsers::enPermissions::pLoginRegister))
        {
            return;
        }

        vector <clsBankUsers> vUsersLoginRegister = clsBankUsers::GetUserLoginRegisterList();

        string SubTitle = "     (" + to_string(vUsersLoginRegister.size()) + ") Record(s).";
        _DrawScreenHeader("\t  Login Register List Screen", SubTitle);

        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "\t  | " << left << setw(30) << "Date";
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(15) << "Permissions";

        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;

        

        if (vUsersLoginRegister.size() == 0)
            cout << "\t\t\t\tNo Users Login Register Available In the System!";
        else

            for (clsBankUsers &U : vUsersLoginRegister)
            {
                _PrintUserLoginRegisterLine(U);
                cout << endl;
            }


        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;
       
    }


};

