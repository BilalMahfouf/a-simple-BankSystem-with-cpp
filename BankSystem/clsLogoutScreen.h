#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankUsers.h"
#include "Global.h"
#include"clsLoginScreen.h"


class clsLogoutScreen :protected clsScreen
{

public:


    static void ShowLogoutScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Logout Screen");
        cout << "\nAre you sure you want to logout?";
        char C;
        cin >> C;
        if (toupper(C) == 'Y')
        {
            CurrentUser = clsBankUsers::Find("", "");
            clsLoginScreen::ShowLoginScreen();
        }

    }

};

