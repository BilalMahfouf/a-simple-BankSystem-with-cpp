
#pragma once
#include"clsSolution.h"
#include<iomanip>
#include <iostream>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsListCurrenciesScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRateScreen.h"
#include"clsCurrencyCalculatorScreen.h"

class clsCurrencyMainScreen :protected clsScreen
{
private:

    enum enCurrencyMenu {
        eListCurrencies = 1, eFindCurency = 2, eUpdateRate = 3, eCurrencyCalculator = 4
        , eMainMenu = 5

    };

    static void _ShowListCurrenciesScreen()
    {
     //   cout << "\n It Will be here /";

        clsListCurrenciesScreen::ListCurrencies();

    }

    static void _ShowFindCurrencyScreen()
    {
       // cout << "\n It Will be here /";

        clsFindCurrencyScreen::FindCurrency();

    }

    static void _ShowUpdateRateScreen()
    {
       // cout << "\n It Will be here /";

        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();

    }

    static void _ShowCurrencyCalculatorScreen()
    {
       // cout << "\n It Will be here /";

        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();

    }

    static void _PerformCurrencyOption(const enCurrencyMenu& Option)
    {


        switch (Option) {
        case enCurrencyMenu::eListCurrencies:
            system("CLS");

            _ShowListCurrenciesScreen();
            _ReturnToCurrencyMenu();

            break;

        case enCurrencyMenu::eFindCurency:
            system("CLS");

            _ShowFindCurrencyScreen();
            _ReturnToCurrencyMenu();


            break;

        case enCurrencyMenu::eUpdateRate:
            system("CLS");

            _ShowUpdateRateScreen();
            _ReturnToCurrencyMenu();

        case enCurrencyMenu::eCurrencyCalculator:
        {
            system("CLS");
            _ShowCurrencyCalculatorScreen();
            _ReturnToCurrencyMenu();
        }


        case enCurrencyMenu::eMainMenu:


            // do nothing 

            break;
        }

    }

    static  short _ReadCurrencyOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";

        short Option = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Option;
    }

    static void _ReturnToCurrencyMenu()
    {
        cout << "\n Press any key to return to currency menu...";

        system("pause>0");
        ShowCurrencyMenu();
    }


public:

    static void ShowCurrencyMenu() {
        system("CLS");
        /*if (!CheckAccessRights(clsBankUsers::pTranactions))
        {
            return;
        }*/

        _DrawScreenHeader("\t Currency Exchange Main Screen ");
        cout << "\t\t\t  =====================================================================\n";
        cout << "\t\t\t\t\t\t   Currency Exchange Menu\n";
        cout << "\t\t\t  =====================================================================\n";
        cout << "\t\t\t\t\t\t  [1] List Currencies\n";
        cout << "\t\t\t\t\t\t  [2] Find Currency \n";
        cout << "\t\t\t\t\t\t  [3] Update Rate \n";
        cout << "\t\t\t\t\t\t  [4] Currency Calculator\n";
        cout << "\t\t\t\t\t\t  [5] Main Menu\n";

        cout << "\t\t\t  =====================================================================\n";

        _PerformCurrencyOption((enCurrencyMenu)_ReadCurrencyOption());
    }








};

