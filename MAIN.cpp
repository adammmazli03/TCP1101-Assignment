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
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

void displayBoard(int x_axis, int y_axis, int zombie);
void displayMainMenu(int x_axis, int y_axis, int zombie);

// HELP DISPLAY
void help()
{
    cout << " | How to Play ? | " << endl
         << endl
         << " 1. Coordinates for Alien, Zombies and Objects are read in rows then colomn " << endl
         << " 2. To change arrow's direction, input arrow in the command, state the coordinate of the arrow and the new arrow direction " << endl
         << " 3. This game is autosave when player exits " << endl
         << " 4. Alien must go to arrow in order to gain attack. Each arrow provides 20 attack " << endl
         << " 5. Health pack(h) provides Alien with 20 health " << endl
         << " 6. Alien's movement stops when stumble upon big rock(r). Under the rock has random objects " << endl
         << endl
         << endl
         << " | Movements & Objects | " << endl
         << endl
         << " h      : Health pack." << endl
         << " r      : Big rock. There are unique objects beneath it" << endl
         << " p      : Pod laser." << endl
         << " <      : Arrow left." << endl
         << " >      : Arrow right." << endl
         << " ^      : Arrow up." << endl
         << " v      : Arrow down." << endl
         << " g      : Gun. Choose which zombie to accept with the alien's accumulated attack." << endl
         << " up     : Alien to move up " << endl
         << " down   : Alien to move down " << endl
         << " left   : Alien to move left " << endl
         << " right  : Alien to move right " << endl
         << " arrow  : Switch the direction of an arrow object in the game board " << endl
         << " help   : Display commands that can use in the game " << endl
         << " exit   : Exit the game" << endl
         << endl;
    system("Pause");
    system("CLS");
}

// LOAD OBJECT
struct myObj
    {
        int objCoorX;
        int objCoorY;
        char objchar; 
    };
vector<myObj>objectlist;

// ALIEN ATTRIBUTES
class alienAttribute
{
public:
    int health;
    int attack;
    int coorX;
    int coorY;

    alienAttribute()
    {
        health = 100;
        attack = 0;
        coorX = 0;
        coorY = 0;
    }
    void getter(int x_axis, int y_axis)
    {
        coorX = (x_axis - 1) / 2;
        coorY = (y_axis - 1) / 2;
        health = 100;
        attack = 0;
    }
    int getHealth()
    {
        return health;
    }
    int getAttack()
    {
        return attack;
    }
    int getcoordinateX(){
        return coorX;
    }
    int getcoordinateY(){
        return coorY;
    }
    void attributeDisplay()
    {
        cout << "  Alien    :"
             << " Coordinate (" << setw(2) << coorX + 1 << "," << setw(2) << coorY + 1
             << ") Health: " << setw(3) << health << " , "
             << " Attack: " << setw(3) << attack
             << endl;
    }
    void addHealth(int h)
    {
        health += h;
        if (health > 100)
        {
            health = 100;
        }
    }
    void addAttack(int a)
    {
        attack += a;
    }
    void resetAttack(int null)
    {
        attack = null;
    }
};

// ZOMBIES ATTRIBUTES
class zombieAttribute
{
public:
    int zombieHealth, zombieAttack, zombieRange, zombieCoorX, zombieCoorY;

    void getter(int x_axis, int y_axis)
    {
        zombieCoorX = rand() % x_axis;
        zombieCoorY = rand() % y_axis;
        zombieHealth = rand() % 51 + 50;
        zombieAttack = rand() % 20 + 10;
        if (x_axis <= y_axis)
        {
            do
            {
                zombieRange = rand() % x_axis + 1;
            } while (zombieRange >= x_axis);
        }
        else
        {
            do
            {
                zombieRange = rand() % y_axis + 1;
            } while (zombieRange >= y_axis);
        }
    }
    void dispZombie()
    {
        cout << " Coordinate (" << setw(2) << zombieCoorX + 1 << "," << setw(2) << zombieCoorY + 1
             << ") Health: " << setw(3) << zombieHealth << " , "
             << " Attack: " << setw(3) << zombieAttack << " , "
             << "Range: " << setw(2) << zombieRange;
        cout << endl;
    }
};
vector<zombieAttribute> z;

string usrtxt;
class Board
{
public:
    vector<vector<char>> map_;
    alienAttribute alienStatus;
    zombieAttribute zombieStatus;
    int characterTurn = 0;
    int dimX_, dimY_;

    alienAttribute &getAlien()
    {
        return alienStatus;
    }
    zombieAttribute &getZombie()
    {
        return zombieStatus;
    }
    int winCheck(int zombie);    //    CHECK IF THERE IS ANY ZOMBIE ON THE BOARD
    void locateAlien(int x_axis, int y_axis);
    void generateZombie(int x_axis, int y_axis, int zombie);  //    GENERATE ATTRIBUTE OF THE ZOMBIES
    void generateObjects();                                   //    GENERATE OBJECTS AFTER THE TRAIL RESET 
    void init(int x_axis, int y_axis, int zombie);            //    INITIALIZE THE LOCATION OF ALIEN, ZOMBIES AND OBJECTS
    void display(int zombie, int characterTurn);              //    DISPLAY THE BOARD AND DASHBOARD
    void command(int x_axis, int y_axis, int zombie);         //    USER INPUT
    //      CHARACTER'S MOVEMENT
    void movePlayer(string direction, int zombie);
    void moveZombies(int x_axis, int y_axis, int zombie);
    void encounterItem(string direction, int zombie);
    void changeDirection(int x_axis, int y_axis);
    //      LOAD THE BOARD
    void initload(int x_axis, int y_axis, int zombie);
};

int Board::winCheck(int zombie)
{
    int winLose = 0;
    int loseWin = 0;
    for (int i = 0; i < zombie; i++)
    {
        if (z[i].zombieHealth == 0)
        {
            winLose = 0;
        }
        else
        {
            loseWin = 1;
        }
    }
    return winLose + loseWin;
}

// LOCATE ALIEN AT THE CENTRE
void Board::locateAlien(int a, int b)
{
    alienStatus.coorX = (a - 1) / 2;
    alienStatus.coorY = (b - 1) / 2;
}

void Board::generateZombie(int x_axis, int y_axis, int zombie)
{
    z.clear();
    for (int i = 0; i < zombie; i++)
    {
        do
        {
            zombieStatus.getter(x_axis, y_axis);
            bool validCoords = true;
            for (int j = 0; j < i; j++)  //     CHECK IF THE NEW LOCATION OCCUPIED WITH OTHER ZOMBIE
            {
                if (z[j].zombieCoorX == zombieStatus.zombieCoorX && z[j].zombieCoorY == zombieStatus.zombieCoorY)
                {
                    validCoords = false;
                    break;
                }
            }
            //     CHECK IF THE NEW LOCATION OCCUPIED WITH ALIEN
            if (alienStatus.coorX == zombieStatus.zombieCoorX && alienStatus.coorY == zombieStatus.zombieCoorY)
            {
                validCoords = false;
                break;
            }
            if (validCoords) // THE LOCATION IS GOOD
            {
                z.push_back(zombieStatus);
            }
        } while (z.size() < i + 1);
    }
}

void Board::generateObjects()
{
    char objects[] = {' ', ' ', ' ', 'h', 'r', 'p', 'v', '>', '<', '^'};
    int noOfObjects = 10;
    for (int i = 0; i < dimX_; ++i)
    {
        for (int j = 0; j < dimY_; ++j)
        {
            if (map_[i][j] == '.')
            {
                int objNo = rand() % noOfObjects;
                map_[i][j] = objects[objNo];
            }
        }
    }
}

void Board::init(int x_axis, int y_axis, int zombie)
{
    char objects[] = {' ', ' ', ' ', 'h', 'r', 'p', 'v', '>', '<', '^'};
    int noOfObjects = 10;

    dimX_ = x_axis;
    dimY_ = y_axis;

    map_.resize(dimX_);
    for (int i = 0; i < dimX_; ++i)
    {
        map_[i].resize(dimY_);
    }
    // INITIALIZE COORDINATE OBJECTS
    for (int i = 0; i < dimX_; ++i)
    {
        for (int j = 0; j < dimY_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
    // INITIALIZE COORDINATE ALIEN
    map_[alienStatus.coorX][alienStatus.coorY] = 'A';
    // INITIALIZE COORDINATE ZOMBIES
    for (int i = 0; i < zombie; i++)
    {
        char noZombie[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        map_[z[i].zombieCoorX][z[i].zombieCoorY] = noZombie[i];
    }
}

void Board::display(int zombie, int characterTurn)
{
    // DISPLAY BOARD
    cout << "   T+>>>>>>>>>>>>>>>[#]<<<<<<<<<<<<<<<+T" << endl;
    cout << "   ||>        ALIEN V/S ZOMBIE       <|| " << endl;
    cout << "   ||__^__^__^__^__^_*_^__^__^__^__^__|| " << endl;
    cout << endl;
    cout << "Rv" << endl;

    for (int i = 0; i < dimX_; ++i)
    {
        cout << "   ";
        for (int j = 0; j < dimY_; ++j)
        {
            cout << "+---";
        }
        cout << "+" << endl;

        cout << setw(2) << (i + 1) << " ";

        for (int j = 0; j < dimY_; ++j)
        {
            cout << "| " << map_[i][j] << " ";
        }
        cout << "|" << endl;
    }

    cout << "   ";
    for (int j = 0; j < dimY_; ++j)
    {
        cout << "+---";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < dimY_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << "   ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "C>";
    for (int j = 0; j < dimY_; ++j)
    {
        cout << "   " << (j + 1) % 10;
    }
    cout << endl
         << endl
         << endl;
    if (characterTurn == 0)
    {
        cout << "       <  <  <  <  <  <  < Alien is moving. >  >  >  >  >  >  >" << endl
             << endl;
    }
    else
    {
        cout << "     <  <  <  <  <  <  < Zombie " << characterTurn << "'s turn. >  >  >  >  >  >  >" << endl
             << endl;
    }
    // DISPLAY DASHBOARD
    alienStatus.attributeDisplay();
    cout << " ----------------------------------------------------------------------" << endl;
    for (int i = 0; i < zombie; i++)
    {
        cout << "  Zombie " << i + 1 << " :";
        z[i].dispZombie();
    }
    cout << endl;
}

void Board::command(int x_axis, int y_axis, int zombie)
{
    cout << "Command ==> ";
    string move;
    cin >> move;
    cout << endl;
    if (move == "help")  // SHOW HELP
    {
        system("CLS");
        help();
        display(zombie, characterTurn);
        command(x_axis, y_axis, zombie);
    }
    else if (move == "arrow") //    CHANGE ARROW
    {
        changeDirection(x_axis, y_axis);
        display(zombie, characterTurn);
        command(x_axis, y_axis, zombie);
    }
    else if (move == "exit") //       EXIT AND SAVE THE PROGRESS
    {
        string name;
        cout << "Saving the game..." << endl;
        fstream myFile;
        cout << "Enter Your Username: ";
        cin >> name;
        usrtxt = name + ".txt";
        myFile.open(usrtxt, ios::out);
        {
            myFile << x_axis << endl;
            myFile << y_axis << endl;
            myFile << zombie << endl;
            for (int i = 0; i < x_axis; ++i)
            {
                

                for (int j = 0; j < y_axis; ++j)
                {
                    myFile << "|" << map_[i][j];
                }
                myFile << "|" << endl;
            }
            
            myFile << endl;
            myFile << alienStatus.getHealth() << endl << alienStatus.getAttack() << endl << alienStatus.getcoordinateX() << endl << alienStatus.getcoordinateY() << endl; 
            for (int i = 0; i < zombie; ++i)
            {
                myFile << z[i].zombieHealth << endl << z[i].zombieAttack << endl << z[i].zombieRange << endl << z[i].zombieCoorX << endl << z[i].zombieCoorY << endl;
            }
            cout << "See you again! " << endl;
            system("Pause");
            abort();
        }
    }
    else if (move == "right" || move == "left" || move == "up" || move == "down") // PLAYER MOVEMENT
    {
        movePlayer(move, zombie);
    }
    else
    {
        cout << " Input wrong command!! " << endl;
        cout << " Enter 'help' for help. " << endl << endl;
        command(x_axis, y_axis, zombie);
    }
    cout << endl;
}

void Board::movePlayer(string direction, int zombie)
{
    // MOVE UP
    characterTurn = 0;
    if (direction == "up")
    {
        if (alienStatus.coorX > 0)
        {
            map_[alienStatus.coorX][alienStatus.coorY] = '.';
            alienStatus.coorX--;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl << endl;
            system("pause");
            system("cls");
            map_[alienStatus.coorX][alienStatus.coorY] = 'A';

            // GENERATE RANDOM OBJECTS ON TRAIL AND RESET THE ALIEN'S ATTACK
            generateObjects();
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl << endl;
            system("pause");
            system("cls");
        }
    }
    // MOVE DOWN
    else if (direction == "down")
    {
        if (alienStatus.coorX < (dimX_ - 1))
        {
            map_[alienStatus.coorX][alienStatus.coorY] = '.';
            alienStatus.coorX++;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl
                 << endl;
            system("pause");
            system("cls");
            map_[alienStatus.coorX][alienStatus.coorY] = 'A';
            generateObjects();
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl << endl;
            system("pause");
            system("cls");
        }
    }
    // MOVE LEFT
    else if (direction == "left")
    {
        if (alienStatus.coorY > 0)
        {
            map_[alienStatus.coorX][alienStatus.coorY] = '.';
            alienStatus.coorY--;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl
                 << endl;
            system("pause");
            system("cls");
            map_[alienStatus.coorX][alienStatus.coorY] = 'A';
            generateObjects();
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl << endl;
            system("pause");
            system("cls");
        }
    }
    // MOVE RIGHT
    else if (direction == "right")
    {
        if (alienStatus.coorY < (dimY_ - 1))
        {
            map_[alienStatus.coorX][alienStatus.coorY] = '.';
            alienStatus.coorY++;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl
                 << endl;
            system("pause");
            system("cls");
            map_[alienStatus.coorX][alienStatus.coorY] = 'A';
            generateObjects();
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl << endl;
            system("pause");
            system("cls");
        }
    }
    // STOP WHEN ENCOUNTER ROCK, GUN AND ALIVE ZOMBIES
    else if (direction == "stop")
    {
        generateObjects();
        alienStatus.resetAttack(0);
        display(zombie, characterTurn);
        cout << " Alien turn ends. The trail is reset. " << endl << endl;
        system("pause");
        system("cls");
    }
}

void Board::moveZombies(int x_axis, int y_axis, int zombie)
{
    for (int i = 0; i < zombie; i++)
    {
        if (z[i].zombieHealth > 0)     // ONLY ZOMBIES WITH HEALTH CAN MOVE
        {
            characterTurn = i + 1;
            display(zombie, characterTurn);
            cout << " Zombie " << i + 1 << " turns. " << endl;
            cout << endl;
            system("pause");
            system("cls");

            map_[z[i].zombieCoorX][z[i].zombieCoorY] = ' ';  // EMPTY SPACE THE OLD LOCATION OF ZOMBIE

            srand(time(NULL));
            int stepZombies = 0;
            int repeat;
            do
            {
                int f = z[i].zombieCoorX;
                int g = z[i].zombieCoorY;
                std::vector<int> validMovement;
                if (f > 0)   // IF THE ZOMBIE CAN MOVE UP
                {
                    validMovement.push_back(1); 
                }
                if (f < (dimX_ - 1))   // IF THE ZOMBIE CAN DOWN
                {
                    validMovement.push_back(2); 
                }
                if (g > 0)  // IF THE ZOMBIE CAN MOVE LEFT
                {
                    validMovement.push_back(3); 
                }
                if (g < (dimY_ - 1)) // IF THE ZOMBIE CAN MOVE RIGHT
                {
                    validMovement.push_back(4);
                }

                // IF THERE ARE NO VALID MOVEMENT, ZOMBIE ARE STUCK
                if (validMovement.empty())
                {
                    stepZombies = 0;
                    break;
                }

                // CHOOSE A RANDOM DIRECTION FROM VALID MOVEMENT
                stepZombies = validMovement[rand() % validMovement.size()];
                switch (stepZombies)
                {
                case 1: // MOVE UP
                    f--;
                    break;
                case 2: // MOVE DOWN
                    f++;
                    break;
                case 3: // MOVE LEFT
                    g--;
                    break;
                case 4: // MOVE RIGHT
                    g++;
                    break;
                }

                // CHECK IF THE NEW LOCATION OCCUPIED BY ZOMBIES, ALIEN AND ROCK
                repeat = 0;
                for (int j = 0; j < zombie; j++)
                {
                    if (j != i && z[j].zombieCoorX == f && z[j].zombieCoorY == g)
                    {
                        repeat = 1;
                        break;
                    }
                }
                if (alienStatus.coorX == f && alienStatus.coorY == g)
                {
                    repeat = 1;
                }
                if (map_[f][g] == 'r')
                {
                    repeat = 1;
                }
                if (!repeat)
                {
                    z[i].zombieCoorX = f;
                    z[i].zombieCoorY = g;
                }
            } while (repeat == 1);

            char noZombie[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
            map_[z[i].zombieCoorX][z[i].zombieCoorY] = noZombie[i];
            display(zombie, characterTurn);
            // SHOW WHICH DIRECTION ZOMBIE'S MOVE
            if (stepZombies == 1)
            {
                cout << " Zombie " << i+1 << " move up." << endl << endl;
            }
            else if (stepZombies == 2) // MOVE DOWN
            {
                cout << " Zombie " << i+1 << " move down." << endl << endl;
            }
            else if (stepZombies == 3) // MOVE LEFT
            {
                cout << " Zombie " << i+1 << " move left." << endl << endl;
            }
            else if (stepZombies == 4) // MOVE RIGHT
            {
                cout << " Zombie " << i+1 << " move right." << endl << endl;
            }
            else if (stepZombies == 0) // ZOMBIE STUCK
            {
                cout << " Zombie " << i+1 << " is trapped." << endl << endl;
            }
            system("pause");
            system("cls");

            map_[z[i].zombieCoorX][z[i].zombieCoorY] = noZombie[i];

            display(zombie, characterTurn);
            int dx = z[i].zombieCoorX - alienStatus.coorX;
            int dy = z[i].zombieCoorY - alienStatus.coorY;
            // ZOMBIE ATTACK ALIEN HORIZONTALLY AND VERTICALLY
            if ((abs(dx) <= z[i].zombieRange && abs(dy) == 0) || (abs(dy) <= z[i].zombieRange && abs(dx) == 0))
            {
                alienStatus.health -= z[i].zombieAttack;
                cout << " Zombie " << i+1 << " attacked the alien. " << endl;
                cout << " Alien's health is " << alienStatus.health << endl << endl;
            }
            else
            {
                cout << " Zombie " << i+1 << " cannot attack." << endl << endl;
            }
            system("pause");
            system("cls");
            display(zombie, characterTurn);
            cout << " Zombie " << i+1 << " turn ends. " << endl
                 << endl;
            system("pause");
            system("cls");
        }
    }
    characterTurn = 0;
}

void Board::encounterItem(string direction, int zombie)
{
    // FINDS HEALTH PACK
    if (map_[alienStatus.coorX][alienStatus.coorY] == 'h')
    {
        alienStatus.addHealth(20);
        cout << " Alien finds health pack. " << endl
             << " Alien's health add 20. " << endl;
        if (alienStatus.health >= 100)
        {
            cout << " Max alien's health is 100. " << endl;
        }
        cout << endl;
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS EMPTY SPACE
    else if (map_[alienStatus.coorX][alienStatus.coorY] == ' ')
    {
        cout << " Alien finds empty space. " << endl
             << " Alien continue to move. " << endl << endl;
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS POD
    else if (map_[alienStatus.coorX][alienStatus.coorY] == 'p')
    {
        cout << " Alien finds pod. " << endl;
        // Calculate the distance from the zombie to the player
        int hitZombie;
        int totalDis = 10;
        for (int i = 0; i < zombie; i++)
        {
            int dx = alienStatus.coorX - z[i].zombieCoorX;
            int dy = alienStatus.coorY - z[i].zombieCoorY;
            if (z[i].zombieHealth > 0)
            {
                if (abs(dx) + abs(dy) == totalDis)
                {
                    int olddx = alienStatus.coorX - z[hitZombie].zombieCoorX;
                    int olddy = alienStatus.coorY - z[hitZombie].zombieCoorY;
                    if (abs(olddx) > abs(dy) || abs(olddy) > abs(dy))
                    {
                        totalDis = abs(dx) + abs(dy);
                        hitZombie = i;
                    }
                }

                if (abs(dx) + abs(dy) < totalDis)
                {
                    totalDis = abs(dx) + abs(dy);
                    hitZombie = i;
                }
            }
        }
        z[hitZombie].zombieHealth -= 10;
        cout << " Zombie " << hitZombie + 1 << " got 10 damages. " << endl;
        if (z[hitZombie].zombieHealth > 0)
        {
            cout << " Zombie " << hitZombie + 1 << " still alive. " << endl
                 << endl;
        }
        else
        {
            cout << " Zombie " << hitZombie + 1 << " is dead. " << endl
                 << endl;
            z[hitZombie].zombieHealth = 0;
            map_[z[hitZombie].zombieCoorX][z[hitZombie].zombieCoorY] = ' ';
        }
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS RIGHT ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == '>')
    {
        alienStatus.addAttack(20);
        cout << " Alien finds right arrow. " << endl
             << " Alien's attack is increased by 20. " << endl << endl;
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer("right", zombie);
    }
    // FINDS LEFT ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == '<')
    {
        alienStatus.addAttack(20);
        cout << " Alien finds left arrow. " << endl
             << " Alien's attack is increased by 20. " << endl << endl;
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer("left", zombie);
    }
    // FINDS UP ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == '^')
    {
        alienStatus.addAttack(20);
        cout << " Alien finds up arrow. " << endl
             << " Alien's attack is increased by 20. " << endl << endl;
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer("up", zombie);
    }
    // FINDS DOWN ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == 'v')
    {
        alienStatus.addAttack(20);
        cout << " Alien finds down arrow. " << endl
             << " Alien's attack is increased by 20. " << endl << endl;
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer("down", zombie);
    }
    // FIND GUN
    else if (map_[alienStatus.coorX][alienStatus.coorY] == 'g')
    {
        int hitZombie;
        cout << " Alien finds gun. " << endl
             << " Choose which zombie to aim." << endl;
        cout << " ==> Zombie ";
        cin >> hitZombie;
        cout << endl;
        system("pause");
        system("cls");
        // SEARCH IF THE ZOMBIE STILL ALIVE IN THE BOARD
        if (hitZombie > zombie || hitZombie < 0 || z[hitZombie - 1].zombieHealth == 0)
        {
            map_[alienStatus.coorX][alienStatus.coorY] = 'A';
            display(zombie, characterTurn);
            cout << " There is no zombie " << hitZombie << " in the board. " << endl
                 << " Alien loss chance to use the gun." << endl << endl;
            system("pause");
            system("cls");
        }
        else
        {
            display(zombie, characterTurn);
            hitZombie -= 1;
            z[hitZombie].zombieHealth -= (alienStatus.getAttack() + 10);             // ZOMBIE HEALTH MINUS TOTAL ACCUMULATED ALIEN'S ATTACK PLUS 10
            cout << " Zombie " << hitZombie + 1 << " got " << alienStatus.getAttack() + 10 << " damages. " << endl;
            if (z[hitZombie].zombieHealth > 0)
            {
                cout << " Zombie " << hitZombie + 1 << " still alive. " << endl << endl;
            }
            else
            {
                cout << " Zombie " << hitZombie + 1 << " is dead. " << endl << endl;
                z[hitZombie].zombieHealth = 0;
                map_[z[hitZombie].zombieCoorX][z[hitZombie].zombieCoorY] = ' ';
            }
            system("pause");
            system("cls");
        }
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer("stop", zombie);
    }
    // FINDS Rock
    else if (map_[alienStatus.coorX][alienStatus.coorY] == 'r')
    {
        int objectUnderRock = rand() % 2 + 1;     // RANDOMIZE OBJECTS UNDER ROCK
        if (objectUnderRock == 1)
        {
            cout << " Alien stumbles upon a rock. " << endl
                 << " Alien discovers a pod beneath it. " << endl << endl;
            map_[alienStatus.coorX][alienStatus.coorY] = 'p';
        }
        else if (objectUnderRock == 2)
        {
            cout << " Alien stumbles upon a rock. " << endl
                 << " Alien discovers a gun beneath it. " << endl << endl;
            map_[alienStatus.coorX][alienStatus.coorY] = 'g';
        }
        system("pause");
        system("cls");
        if (direction == "up")
        {
            alienStatus.coorX++;
        }
        else if (direction == "down")
        {
            alienStatus.coorX--;
        }
        else if (direction == "right")
        {
            alienStatus.coorY--;
        }
        else if (direction == "left")
        {
            alienStatus.coorY++;
        }
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer("stop", zombie);
    }
    // FINDS ALIEN TRAIL
    else if (map_[alienStatus.coorX][alienStatus.coorY] == '.')
    {
        cout << " Alien finds its trail. " << endl
             << " Alien continues moving. " << endl << endl;
        system("pause");
        system("cls");
        map_[alienStatus.coorX][alienStatus.coorY] = 'A';
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS ZOMBIES
    else
    {
        cout << " Alien hits a zombie. " << endl
             << " Zombie " << map_[alienStatus.coorX][alienStatus.coorY] << " accept " << alienStatus.getAttack() << " from the alien." << endl;
        
        // FIND THE ZOMBIE NUMBER
        int locZombie = map_[alienStatus.coorX][alienStatus.coorY] - '1';          
        z[locZombie].zombieHealth = z[locZombie].zombieHealth - alienStatus.attack;

        // DETERMINE THE ZOMBIE'S HEALTH
        if (z[locZombie].zombieHealth <= 0)
        {
            z[locZombie].zombieHealth = 0;
            cout << " Zombie " << locZombie + 1 << " is dead." << endl << endl;
            system("pause");
            system("cls"); 
            map_[alienStatus.coorX][alienStatus.coorY] = 'A'; // ALIEN CONTINUE TO MOVE 
            display(zombie, characterTurn);
            movePlayer(direction, zombie);
        }
        else
        {
            cout << " Zombie " << locZombie + 1 << " is still alive." << endl << endl;
            system("pause");
            system("cls");
            char noZombie[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
            map_[alienStatus.coorX][alienStatus.coorY] = noZombie[locZombie];
            // PUSH BACK THE ALIEN'S COORDINATE
            if (direction == "up")
            {
                alienStatus.coorX++;
            }
            else if (direction == "down")
            {
                alienStatus.coorX--;
            }
            else if (direction == "right")
            {
                alienStatus.coorY--;
            }
            else if (direction == "left")
            {
                alienStatus.coorY++;
            }
            map_[alienStatus.coorX][alienStatus.coorY] = 'A';
            movePlayer("stop", zombie);
        }
    }
}

void Board::changeDirection(int x_axis, int y_axis)
{
    int xArrow;
    int yArrow;
    char newArrow;
    cout << " Input row of arrow : ";
    cin >> xArrow;
    cout << " Input column of arrow: ";
    cin >> yArrow;
    cout << " Input arrow ' ^, v, >, < ' : ";
    cin >> newArrow;
    xArrow -= 1;
    yArrow -= 1;
    // CHECK IF THERE IS A ARROW BASED ON THE USER INPUT'S COLUMN AND ROW
    if (map_[xArrow][yArrow] == '^' || map_[xArrow][yArrow] == 'v' || map_[xArrow][yArrow] == '>' || map_[xArrow][yArrow] == '<')
    {
        map_[xArrow][yArrow] = newArrow;
        cout << " The arrow's changer is updated. " << endl;
    }
    else
    {
        cout << " There is no arrow in this coordinate. " << endl;
    }
    cout << endl;
    system("pause");
    system("cls");
}

void Board::initload(int x_axis, int y_axis, int zombie)
{
    dimX_ = x_axis;
    dimY_ = y_axis;

    map_.resize(dimX_);
    for (int i = 0; i < dimX_; ++i)
    {
        map_[i].resize(dimY_);
    }

    for(int i = 0; i < objectlist.size(); i++)
    {
        map_[objectlist[i].objCoorX][objectlist[i].objCoorY] = objectlist[i].objchar;
    }
}

void playAgain(int x_axis, int y_axis, int zombie)
{
    char answer;
    cout << " You win!!" << endl;
    cout << " Do you want to play again? (y/n)" << endl;
    cin >> answer;
    if (answer == 'y')
    {
        system("CLS");
        displayMainMenu(x_axis, y_axis, zombie);
    }
    else if (answer == 'n')
    {
        abort();
    }
    else
    {
        cout << " Wrong input" << endl;
        playAgain(x_axis, y_axis, zombie);
    }
}

void alienDie(int x_axis, int y_axis, int zombie)
{
    char answer;
    cout << " You lose!!" << endl;
    cout << " Do you want to play again? (y/n)" << endl;
    cin >> answer;
    if (answer == 'y')
    {
        system("CLS");
        displayMainMenu(x_axis, y_axis, zombie);
    }
    else if (answer == 'n')
    {
        abort();
    }
    else
    {
        cout << " Wrong input" << endl;
        playAgain(x_axis, y_axis, zombie);
    }
}

Board board;
//      DISPLAY NEW BOARD
void displayBoard(int x_axis, int y_axis, int zombie)
{
    
    alienAttribute alienStatus;

    board.locateAlien(x_axis, y_axis);
    board.generateZombie(x_axis, y_axis, zombie);
    board.init(x_axis, y_axis, zombie);

    while (board.getAlien().health > 0)
    {
        board.display(zombie, board.characterTurn);
        board.command(x_axis, y_axis, zombie);
        if (board.winCheck(zombie) == 0)
        {
            playAgain(x_axis, y_axis, zombie);
        }
        board.moveZombies(x_axis, y_axis, zombie);
    }
    alienDie(x_axis, y_axis, zombie);
}

//      DISPLAY LOAD BOARD
void displayloadBoard(int x_axis, int y_axis, int zombie)
{
    alienAttribute alienStatus;
    board.locateAlien(x_axis, y_axis);
    board.initload(x_axis, y_axis, zombie);

    while (true)
    {
        board.display(zombie, board.characterTurn);
        board.command(x_axis, y_axis, zombie);
        if (board.winCheck(zombie) == 0)
        {
            playAgain(x_axis, y_axis, zombie);
        }
        board.moveZombies(x_axis, y_axis, zombie);
    }
    alienDie(x_axis, y_axis, zombie);
}

//      CHANGE SETTING PART
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

// LOAD THE ALIEN'S ATTRIBUTE
void ResetAlien(alienAttribute& alienStatus, int a, int b, int c, int d){
    alienStatus.health = a;
    alienStatus.attack = b;
    alienStatus.coorX = c;
    alienStatus.coorY = d;
}

//  CREATE AND LOAD PART
void loadGame()
{
    string usr;
    string usrtxt;
    fstream myFile;
    fstream myFile2;
    fstream myFile3;
    string line;
    string line2;
    string line3;
    int num = 0;
    int x_axis;
    int y_axis;
    int zombie;
    char object;
    int A_health;
    int A_Attack;
    int A_coorX;
    int A_coorY;
    int Z_health;
    int Z_Attack;
    int Z_Range;
    int Z_coorX;
    int Z_coorY;
    alienAttribute alienStatus;
    zombieAttribute zombieStatus;
    cout << endl;
    cout << "Please enter username with correct letter case!" << endl;
    cout << "Enter Valid Username ==> ";
    cin >> usr;
    usrtxt = usr + ".txt";
    bool exist = false;
    
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
                            if(num == 0){
                                x_axis = stoi(line2);
                            }
                            else if(num == 1){
                                y_axis = stoi(line2);
                            }
                            else if(num == 2){
                                zombie = stoi(line2);
                                break;
                            }
                            num = num + 1; 
                        }
                        //      LOAD THE COORDINATE OF EACH OBJECTS IN THE BOARD
                        num = 0;
                        while(getline(myFile3, line2)){
                            if (num == y_axis){
                                    break;
                            }
                            for(int i =  0; i < line2.length(); i++){
                                if(line2[i] != '|'){
                                    myObj obj = {num, i/2, line2[i]};
                                    objectlist.push_back(obj);
                                }
                            }
                            num++;
                        }
                    //      LOAD ALIEN'S ATTRIBUTE
                    num = 0;
                    while (getline(myFile3, line2)){
                        if (num == 0){
                            A_health = stoi(line2);
                        }
                        else if(num == 1){
                            A_Attack = stoi(line2);
                        }
                        else if(num ==  2){
                            A_coorX = stoi (line2);
                        }
                        else if(num == 3){
                            A_coorY = stoi(line2);
                            break;
                        }
                        num++;
                        }
                    //      LOAD THE ZOMBIES' ATTRIBUTE 
                    for(int j = 0; j < zombie;j++){
                        num = 0;
                        while (getline(myFile3, line2)){
                            if (num == 0){
                                Z_health = stoi(line2);
                            }
                            if (num == 1){
                                Z_Attack = stoi(line2);
                            }
                            if (num == 2){
                                Z_Range = stoi(line2);
                            }
                            if (num == 3){
                                Z_coorX = stoi(line2);
                            }
                            if (num == 4){
                                Z_coorY = stoi(line2);
                                break;
                            }
                        num = num + 1;
                        }

                    zombieAttribute zombieStatus = {Z_health, Z_Attack, Z_Range, Z_coorX, Z_coorY };
                    z.push_back(zombieStatus);
                    }

                  ResetAlien(alienStatus, A_health, A_Attack, A_coorX, A_coorY); } 
                }
            }
        myFile.open("Usr.txt", ios:: in);{
            if(myFile.is_open()){
                int number = 0;
                while (getline(myFile, line3)){
                    if (line3 == usrtxt){
                        number = number + 1;
                        break;
                    }
                }
                if (number == 0){
                    loadGame();
                }
            }
        }
        myFile.close();
            displayloadBoard(x_axis,y_axis,zombie);
        }    
    }
}

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

//  MAIN MENU
void startGame()
{
    string mainMenu_option;

    cout << endl;
    cout << endl;
    cout << "  AA  L    III EEEE N   N   V     V  SSS   ZZZZZ  OOO  M   M  BBBB  III EEEE " << endl;
    cout << " A  A L     I  E    NN  N   V     V S         Z  O   O MM MM  B   B  I  E    " << endl;
    cout << " AAAA L     I  EEE  N N N    V   V   SSS     Z   O   O M M M  BBBB   I  EEE  " << endl;
    cout << " A  A L     I  E    N  NN     V V       S   Z    O   O M   M  B   B  I  E    " << endl;
    cout << " A  A LLLL III EEEE N   N      V    SSSS   ZZZZZ  OOO  M   M  BBBB  III EEEE " << endl;
    cout << endl;
    cout << endl;
    cout << "                       ___________________________________                   " << endl;
    cout << "                      |                                   |                  " << endl;
    cout << "                      |                                   |                  " << endl;
    cout << "                      |             WELCOME!!             |                  " << endl;
    cout << "                      |                                   |                  " << endl;
    cout << "                      |                                   |                  " << endl;
    cout << "                      |                                   |                  " << endl;
    cout << "                      |             > START <             |                  " << endl;
    cout << "                      |             > LOAD  <             |                  " << endl;
    cout << "                      |             > EXIT  <             |                  " << endl;
    cout << "                      |                                   |                  " << endl;
    cout << "                      |___________________________________|                  " << endl;
    cout << endl;
    cout << endl;
    cout << " select ==> ";
    cin >> mainMenu_option;
    cout << endl;

    int x_axis;
    int y_axis;
    int zombie;

    for (int i = 0; i < mainMenu_option.length(); i++)
    {
        mainMenu_option[i] = toupper(mainMenu_option[i]);
    }

    // START OPTION
    if (mainMenu_option == "START")
    {
        newGame();
    }

    // LOAD OPTION
    else if (mainMenu_option == "LOAD")
    {
        loadGame();
    }

    // EXIT OPTION
    else if (mainMenu_option == "EXIT")
    {
        string exit;
        cout << "Are you sure? (YES/NO)" << endl;
        cin >> exit;
        cout << endl;
        for (int j = 0; j < exit.length(); j++)
        {
            exit[j] = toupper(exit[j]);
        }

        if (exit == "YES")
        {
            cout << endl;
            cout << "Thank You, see you next time!" << endl;
            system("pause");
        }

        else if (exit == "NO")
        {
            cout << endl;
            system("CLS");
            system("clear");
            startGame();
        }

        else
        {
            cout << "Input Error!!" << endl;
            cout << endl;
            startGame();
        }
    }

    else
    {
        cout << "Input Error!!" << endl;
        cout << endl;
        startGame();
    }
}

// main.cpp
int main()
{
    srand(time(NULL));
    startGame();
}
