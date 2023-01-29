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
    string usrtxt;
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
            myFile3.open(usrtxt, ios::out);
            {
                changeSettings(x_axis, y_axis, zombie);
                displayMainMenu(x_axis, y_axis, zombie);
                myFile3 << " No of rows: " << x_axis << endl;
                myFile3 << " No of colomn: " << y_axis << endl;
                myFile3 << endl;
                return;
            }
        }
    }
    myFile2.close();
}
