#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankUsers.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include"clsShowUserNameAndDate.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        int LoginAttempt = 0;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                LoginAttempt++;
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "You have [" << 3 - LoginAttempt << "]chances\n";

            }
            if (LoginAttempt == 3)
            {
                cout << "\n You have been locked after 3 trailes";
                return false;
            }


            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsBankUsers::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        CurrentUser.SaveUserLoginRegister();

        clsMainScreen::ShowMainMenu();
        return true;

    }

public:

    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");

        return _Login();

    }

};

