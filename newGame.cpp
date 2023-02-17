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
#include <fstream>
#include <string>
#include "boardSetting.cpp"
using namespace std;

void newGame()
{
    fstream myFile;
    fstream myFile2;
    fstream myFile3;
    string usr;
    string line;
    int x_axis;
    int y_axis;
    int zombie;

    cout << " Welcome new user! Please enter your name!" << endl;
    cout << " (Do remember the spelling and cases!) " << endl;
    cout << " ==> ";
    cin >> usr;

    usrtxt = usr + ".txt";

    myFile.open("Usr.txt", ios::in);
    {
        if (myFile.is_open())
        {
            while (getline(myFile, line))
            {
                if (line == usrtxt)
                {
                    cout << " This Username has already been taken. Please enter a new one. " << endl;
                    cout << endl;
                    newGame();
                }
            }
        }
    }
    myFile.close();

    myFile2.open("Usr.txt", ios::app);
    {
        if (myFile2.is_open())
        {
            myFile2 << usrtxt << endl;
        }
    }
    myFile2.close();
    changeSettings(x_axis, y_axis, zombie);
    displayMainMenu(x_axis, y_axis, zombie);
}
