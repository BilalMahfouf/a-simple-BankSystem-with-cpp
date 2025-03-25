#pragma once
#include"clsSolution.h"
#include<iomanip>
#include <iostream>
#include"clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include<string>
class clsFindCurrencyScreen :protected clsScreen
{
private:

	enum enFindCurrencyChoice { eCode = 1, eCountry = 2 };

	static enFindCurrencyChoice _ReadChoice()
	{
		cout << "\n Find By:[1] Code or [2] Country ? ";
		int Choice = 0;
		Choice = clsInputValidate::ReadIntNumberBetween(1, 2);

		return (enFindCurrencyChoice)Choice;
	}

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n Currency card: ";
		cout << "\n________________________________";
		cout << "\nCountry	: " << Currency.Country();
		cout << "\nCode	: " << Currency.CurrencyCode();
		cout << "\nName	: " << Currency.CurrencyName();
		cout << "\nRate($)	: " << Currency.Rate();
		cout << "\n________________________________";

	}

public:

	static void FindCurrency()
	{
		_DrawScreenHeader("\tFind Currency Screen");

		enFindCurrencyChoice Choice = _ReadChoice();
		clsCurrency Currency = clsCurrency::GetEmptyCurrencyObject();
		

		switch (Choice)
		{
		case enFindCurrencyChoice::eCode:
		{
			string CurrencyCode = "";
			cout << "\n Enter Currency Code ";
			cin >> CurrencyCode;
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			if (!Currency.IsEmpty())
			{
				cout << "\n Currency found :-)";
				_PrintCurrencyCard(Currency);
			}
			else cout << "\n Currency not found :-)";
			break;
		}
		case enFindCurrencyChoice::eCountry:
		{
			string CurrencyCountry = "";
			cout << "\n Enter Currency Country ";
			cin >> CurrencyCountry;
			clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCountry);
			if (!Currency.IsEmpty())
			{
				cout << "\n Currency found :-)";
				_PrintCurrencyCard(Currency);
			}
			else cout << "\n Currency not found :-)";
			break;
		}

		}


	}



};



