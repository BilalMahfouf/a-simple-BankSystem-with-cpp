#pragma once
#include"clsSolution.h"

#include <iostream>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTransferScreen.h"



class clsTransactionsScreen:protected clsScreen
{
private:

    enum enTransactionMenu {
        DepositM = 1, WithDrawM = 2, ShowBalancesScreen = 3, Transfer = 4
        , TransferLog = 5, ReturnToMainMenu = 6
        
  };


    static  void _ShowDepositScreen() {
      //  cout << "Deposit screen will be here";

        clsDepositScreen::ShowDepositScreen();

}

    static  void _ShowWithdrawScreen() {
        //cout << "Withdraw screen will be here";
        clsWithdrawScreen::ShowWithdrawScreen();

    }

    static  void _ShowTotalBalancesScreen() {
      //  cout << "TotslBalances screen will be here";

        clsTotalBalancesScreen::ShowTotalBalances();


    }

    static void _PerformTransactionsOption(const enTransactionMenu &Option)
    {
       

        switch (Option) {
        case enTransactionMenu::DepositM:
            system("CLS");

            _ShowDepositScreen();
            _ReturnToTransactionMenu();

            break;

        case enTransactionMenu::WithDrawM:
            system("CLS");

            _ShowWithdrawScreen();
            _ReturnToTransactionMenu();


            break;

        case enTransactionMenu::ShowBalancesScreen:
            system("CLS");

            _ShowTotalBalancesScreen();
            _ReturnToTransactionMenu();

        case enTransactionMenu::Transfer:
        {
            system("CLS");
            _ShowTransferScreen();
            _ReturnToTransactionMenu();
        }

        case enTransactionMenu::TransferLog:
        {
            system("CLS");
            _ShowTransferLogScreen();
            _ReturnToTransactionMenu();
        }

        case enTransactionMenu::ReturnToMainMenu:

            
           // do nothing 

            break;
        }

    }

    static  short _ReadTransactionOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";

        short Option = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 5? ");
        return Option;
    }

    static void _ReturnToTransactionMenu()
    {
        cout << "\n Press any key to return to transaction menu...";
        
        system("pause>0");
        ShowTransactionsMenu();
    }

    static void _ShowTransferScreen()
    {
       // cout << "\nTransfer Screen will be here";

        clsTransferScreen::ShowTransferScreen();

    }

    static void _ShowTransferLogScreen()
    {
        //cout << "\nTransfer Log Screen Will Be Here";

        clsTransferLogScreen::ShowTransferLogScreen();

    }

public:

    static void ShowTransactionsMenu() {
        system("CLS");
        if (!CheckAccessRights(clsBankUsers::pTranactions))
        {
            return;
        }

        _DrawScreenHeader("\t Transaction Screen");
        cout << "\t\t\t  =====================================================================\n";
        cout << "\t\t\t\t\t\t   Transaction Menu\n";
        cout << "\t\t\t  =====================================================================\n";
        cout <<"\t\t\t\t\t\t  [1] Deposit\n";
        cout <<"\t\t\t\t\t\t  [2] Withdraw \n";
        cout <<"\t\t\t\t\t\t  [3] Total Balances\n";
        cout <<"\t\t\t\t\t\t  [4] Transfer\n";
        cout <<"\t\t\t\t\t\t  [5] Transfer Log\n";
        cout <<"\t\t\t\t\t\t  [6] Main Menu\n";


        cout << "\t\t\t  =====================================================================\n";
       
           _PerformTransactionsOption((enTransactionMenu)_ReadTransactionOption());
    }








};

