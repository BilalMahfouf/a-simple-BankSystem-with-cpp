#pragma once
#include"clsSolution.h"
#include<iomanip>
#include <iostream>
#include"clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include<string>

class clsListCurrenciesScreen:protected clsScreen
{
private:

	static void _PrintCurrencyData( clsCurrency& Currency)
	{
		cout << "\t| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(10) << left << Currency.CurrencyCode();
		cout << "| " << setw(35) << left << Currency.CurrencyName();
		cout << "| " << setw(15) << left << Currency.Rate();

	}

public:

	static void ListCurrencies()
	{
		string Title = "\tCurrencies List Screen";
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string SubTitle = "\t   (" + to_string(vCurrencies.size()) + ") Currency.";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t| " << left << setw(30) << "Country";
		cout << "| " << left << setw(10) << "Code";
		cout << "| " << left << setw(35) << "Name";
		cout << "| " << left << setw(15) << "Rate/(1$)";

		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		for (clsCurrency& C : vCurrencies)
		{
			_PrintCurrencyData(C);
			cout << endl;
		}
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;


	}

		

};

