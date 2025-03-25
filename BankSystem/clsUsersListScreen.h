#pragma once

#include <iostream>
#include "clsBankUsers.h"
#include <iomanip>
#include "clsScreen.h"


class clsUsersListScreen :protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsBankUsers User)
    {

        cout << "\t  | " << setw(15) << left << User.UserName;
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permission;

    }


public:

    static void ShowClientsList()
    {

        vector <clsBankUsers> vUsers = clsBankUsers::GetUsersList();
        string Title = "\t  Users List Screen";
        string SubTitle = "\t   (" + to_string(vUsers.size()) + ") Users(s).";
        _DrawScreenHeader(Title, SubTitle);

        //cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "\t  | " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Pemission";
        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsBankUsers U : vUsers)
            {

                _PrintUserRecordLine(U);
                cout << endl;
            }

        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

