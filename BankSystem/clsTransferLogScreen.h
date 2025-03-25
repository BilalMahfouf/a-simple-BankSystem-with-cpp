#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include"clsBankClient.h"

class clsTransferLogScreen :protected clsScreen
{
private:
    static void _PrintTransferLogLine(clsBankClient::stTransferLogRegister Register)
    {

        cout << "\t  | " << setw(22) << left << Register.Date;
        cout << "| " << setw(8) << left << Register.FromClientAccNum;
        cout << "| " << setw(8) << left << Register.ToClientAccNum;
        cout << "| " << setw(11) << left << Register.AmountTransferred;
        cout << "| " << setw(11) << left << Register.FromClientBalance;
        cout << "| " << setw(11) << left << Register.ToClientBalance;
        cout << "| " << setw(12) << left << Register.UserName;

    }

public:
    static void ShowTransferLogScreen()
    {
        

        vector <clsBankClient::stTransferLogRegister> vTransfersLogRegister;
        vTransfersLogRegister = clsBankClient::GetTransferLogList();

        string SubTitle = "     (" + to_string(vTransfersLogRegister.size()) + ") Record(s).";
        _DrawScreenHeader("\t  Transfer Log List Screen", SubTitle);

        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "\t  | " << left << setw(22) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d,Acct";
        cout << "| " << left << setw(11) << "Amount";
        cout << "| " << left << setw(11) << "s.Balance";
        cout << "| " << left << setw(11) << "d.Balance";
        cout << "| " << left << setw(12) << "User";


        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;



        if (vTransfersLogRegister.size() == 0)
            cout << "\t\t\t\tNo Transfer Log Register Available In the System!";
        else

            for (clsBankClient::stTransferLogRegister& U : vTransfersLogRegister)
            {
                _PrintTransferLogLine(U);
                cout << endl;
            }


        cout << "\n\t  _______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

