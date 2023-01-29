#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Board
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_;

public:
    void init(int x_axis, int y_axis);
    void display() const;
    void setObject(int col, int row, char object);
};

void Board::init(int x_axis, int y_axis)
{
    dimX_ = x_axis;
    dimY_ = y_axis;
    char objects[] = {' ', ' ', ' ', 'h', 'r', 'p', '>', '<', '^', 'v'};
    char alien[] = {'A'};
    int noOfObjects = 10;

    map_.resize(dimX_);
    for (int i = 0; i < dimX_; ++i)
    {
        map_[i].resize(dimY_);
    }

    for (int i = 0; i < dimX_; ++i)
    {
        for (int j = 0; j < dimY_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }

    int m;
    int n;
    m = (dimX_ - 1) / 2;
    n = (dimY_ - 1) / 2;
    map_[m][n] = alien[0];
}

void Board::display() const
{
    cout << "   T+>>>>>>>>>>>>>>>[#]<<<<<<<<<<<<<<<+T" << endl;
    cout << "   ||>        ALIEN V/S ZOMBIE       <|| " << endl;
    cout << "   ||__^__^__^__^__^_*_^__^__^__^__^__|| " << endl; // row = 7, //colomn = 3
    cout << endl;

    for (int i = 0; i < dimX_; ++i)
    {
        cout << "  ";
        for (int j = 0; j < dimY_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << setw(2) << (i + 1);

        for (int j = 0; j < dimY_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    cout << "  ";
    for (int j = 0; j < dimY_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < dimY_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimY_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void displayBoard(int x_axis, int y_axis)
{
    Board board;
    board.init(x_axis, y_axis);
    board.display();
}