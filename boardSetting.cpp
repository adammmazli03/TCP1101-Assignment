// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T10L, Group 5
// Names: MUHAMMAD ADAM BIN MAZLI ZAKUAN | AHMAD NUR IKHWAN BIN HAMID | MUHAMMAD AL-AMIN BIN MOHD NORMARZUKI
// IDs: 1211101073 | 1211103140 | 1211103201
// Emails: 1211101073@student.mmu.edu.my | 1211103140@student.mmu.edu.my | 1211103201@student.mmu.edu.my
// Phones: 019-729-5420 | 011-5890-0328 | 011-2704-8621
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "boardDisplay.cpp"
using namespace std;

void oddNumbers(int &a)
{
    do
    {
        cin >> a;
        if (a & 2 != 0 && a != 1)
        {
            break;
        }
        else
        {
            cout << endl;
            cout << " Please enter ODD number only except 1! => ";
        }
    } while (a % 2 == 0 || a == 1);
    return;
}

void zombieLimits(int &b)
{
    do
    {
        cin >> b;
        if (b > 0 && b < 10)
        {
            break;
        }

        else if (b <= 0)
        {
            cout << endl;
            cout << " Number of zombie cannot be less than 1! => ";
        }

        else
        {
            cout << endl;
            cout << " Maximum number of zombie is 9! => ";
        }
    } while (b <= 0 || b > 9);
    return;
}

void changeSettings(int &x_axis, int &y_axis, int &zombie)
{
    cout << " _________________________________________ " << endl;
    cout << "|              Board Settings             |" << endl;
    cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
    cout << endl;
    cout << " Please enter odd numbers only except 1. " << endl;
    cout << " Enter number of board rows     =>  ";
    oddNumbers(x_axis);
    cout << endl;
    cout << " Enter number of board columns  =>  ";
    oddNumbers(y_axis);

    cout << " _________________________________________ " << endl;
    cout << "|             Zombies Settings            |" << endl;
    cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
    cout << " You can enter up to 9 zombies only! " << endl;
    cout << " Enter number of zombies        =>  ";
    zombieLimits(zombie);
    cout << endl;
    cout << " Settings Updated." << endl;
    system("pause");
}

void displayMainMenu(int x_axis, int y_axis, int zombie)
{
    char answer;
    cout << " __________________________________________ " << endl;
    cout << "|           Default Game Settings          |" << endl;
    cout << "|__________________________________________|" << endl;
    cout << "|                                          |" << endl;
    cout << "|   Number of Board Rows     =>  " << x_axis << "         |" << endl;
    cout << "|   Number of Board Columns  =>  " << y_axis << "         |" << endl;
    cout << "|   Number of Zombies        =>  " << zombie << "         |" << endl;
    cout << "|__________________________________________|" << endl;
    cout << endl;
    cout << " Do you want to change the settings? (y/n) => ";
    cin >> answer;
    cout << endl;
    answer = toupper(answer);
    if (answer == 'Y')
    {
        changeSettings(x_axis, y_axis, zombie);
        displayMainMenu(x_axis, y_axis, zombie);
    }
    else if (answer == 'N')
    {
        system("CLS");
        help();
        displayBoard(x_axis, y_axis, zombie);
    }
    else
    {
        cout << "Input Error!" << endl;
        cout << endl;
        displayMainMenu(x_axis, y_axis, zombie);
    }
}