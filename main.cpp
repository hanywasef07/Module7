//Name: Hany, Aleeza, and Thanh
// Date: 10/19/2026
// Description: Module 7 

#include <iostream>
#include "input.h"
#include "SimpleCalculator.h"
#include "nQueens.h"

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
        {
			system("cls");
            SimpleCalculator calculator2;

            cout << "\n\t2> Translation of Arithmetic Expression";
            cout << "\n" << string(90, char(196));

            string expression = inputString("\n\tEnter an infix expression: \n", true);
            try
            {
                string postfix = calculator2.infixToPostfix(expression);
                cout << "\n\tPostfix expression: " << postfix << "\n";
            }
            catch (const exception& e)
            {
                cout << "\n\t\tPostfix expression: ERROR: " << e.what() << "\n";
            }
			cout << "\n\n";
            system("pause");
            break;
        }
        case '3':
        {
            system("cls");
            cout << "\n\t\t3> n-Queens Problem";
            cout << "\n\t\t" << string(70, char(196));

            int n;
            int firstColumn;
            // Validate the number of queens.
            do
            {
                n = inputInteger("\n\t\tEnter a number(1..100) of queens: ", 1, 100);

            } while (n < 1 || n > 100);

            // Validate the starting column.
            firstColumn = inputInteger("\n\t\tEnter the column(1.." + to_string(n) + ") to place the first queen: ", 1, n);
            nQueens game(n);
   
            if (game.solve(firstColumn))
            {
                cout << "\n\t" << n << "-Queens solution";
                game.display();
            }
            else
            {
                cout << "\n\t\tNo solution\n";
            }
            cout << "\n\n";
            system("pause");
            break;
        }
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