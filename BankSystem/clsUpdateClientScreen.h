#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsUpdateClientScreen :protected clsScreen
{
private:
    static void _PrintClientCard(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.FirstName;
        cout << "\nLastName    : " << client.LastName;
        cout << "\nFull Name   : " << client.FullName();
        cout << "\nEmail       : " << client.Email;
        cout << "\nPhone       : " << client.Phone;
        cout << "\nAcc. Number : " << client.AccountNumber();
        cout << "\nPassword    : " << client.PinCode;
        cout << "\nBalance     : " << client.AccountBalance;
        cout << "\n___________________\n";

    }

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

public:
    static void UpdateClient() {
        if (!CheckAccessRights(clsBankUsers::pUpdateClients))
        {
            return;
        }

        string Title = "\t  Update Client Screen";
        _DrawScreenHeader(Title);

        cout << "Enter Client Account Number? ";
        string AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "Client Doesn't Exist,Enter Valid Account Number? ";
            AccountNumber = clsInputValidate::ReadString();
        }
              
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        char Choice = 'n';
        cout << "\n Do you want to update this Client y/n ? ";
        cin >> Choice;

        if (toupper(Choice) == 'Y')
        {
         
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            _ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClientCard(Client);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;

            }
            }
        }

    }

};