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