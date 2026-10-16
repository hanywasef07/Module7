//Name: Hany, Aleeza, and Thanh
// Date: 10/19/2026
// Description: Module 7 

#include <iostream>
#include "input.h"
#include "SimpleCalculator.h"

using namespace std;

// Function Prototypes
char menuOption();


int main()
{
    bool running = true;
    char option;

    while (running)
    {
        system("cls");

        option = menuOption();
        switch (option)
        {
        case '1':
        {
			system("cls");
            SimpleCalculator calculator;
           

            cout << "\n\t1> Simple Calculator";
            cout << "\n" << string(90, char(196));

            string expression = inputString("\n\tType a fully parenthesized arithmetic expression: \n\n", true);

            try
            {
                double result = calculator.evaluate(expression);

                cout << "\n\t\tIt evaluates to " << result << "\n";
            }
            catch (const exception& e)
            {
                cout << "\n\t\tERROR: " << e.what() << "\n";
            }
            cout << "\n\n";
            system("pause");
            break;
        }
        case '2':
      

            break;
        case '3':
     

            break;
        case '0':
            cout << "Exiting the program.\n";
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

	return 0;	
}

char menuOption()
{
    cout << "\t\t  CMPR131 Chapter 7: Applications using Stacks by Hany, Aleeza, and Thanh (10/19/2026)\n";
    cout << "\t\t" << string(90, char(205));
    cout << "\n\t\t  1> Simple Calculator (problem 9, pg 391)";
    cout << "\n\t\t  2> Translation of arithmetic expression (problem 10, pg 391)";
    cout << "\n\t\t  3> n-Queens Problem (problem 11, pg 391-292)\n";
    cout << "\t\t" << string(90, char(196));
    cout << "\n\t\t  0 > Exit\n";
    cout << "\t\t" << string(90, char(205));

    char option = toupper(inputChar("\n\t\t  option: ", static_cast<string>("1,2,3,0")));
    return option;
}