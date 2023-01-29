
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void loadGame()
{
    string usr;
    string usrtxt;
    fstream myFile;
    fstream myFile2;
    fstream myFile3;
    string line;
    string line2;

    cout << endl;
    cout << "Please enter username with correct letter case!" << endl;
    cout << "Enter Valid Username ==> ";
    cin >> usr;
    usrtxt = usr + ".txt";

    myFile2.open("Usr.txt", ios::in);
    {
        if (myFile2.is_open())
        {
            while (getline(myFile2, line))
            {
                if (line == usrtxt)
                {
                    myFile3.open(usrtxt, ios::in);
                    {
                        cout << endl;
                        while (getline(myFile3, line2))
                        {
                            cout << line2 << endl;
                        }
                        return;
                    }
                }
            }
        }
        if (line2 != usrtxt)
        {
            cout << "Username is not in the system, please enter correct username!  " << endl;
            loadGame();
        }
    }
}