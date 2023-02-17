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
         << " r      : Big rock." << endl
         << " p      : Pod laser." << endl
         << " <      : Arrow left." << endl
         << " >      : Arrow right." << endl
         << " ^      : Arrow up." << endl
         << " v      : Arrow down." << endl
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
    int getHealth()
    {
        return health;
    }
    int getAttack()
    {
        return attack;
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

    zombieAttribute()
    {
        int zombieHealth = 0;
        int zombieAttack = 0;
        int zombieRange = 0;
        int zombieCoorX = 0;
        int zombieCoorY = 0;
    }
    void getter(int x_axis, int y_axis)
    {
        zombieCoorX = rand() % x_axis;
        zombieCoorY = rand() % y_axis;
        zombieHealth = rand() % 51 + 50;
        zombieAttack = rand() % 21 + 10;
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
    vector<vector<string>> map_;
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
    void locateAlien(int x_axis, int y_axis);
    void generateZombie(int x_axis, int y_axis, int zombie);
    void init(int x_axis, int y_axis, int zombie);
    void display(int zombie, int characterTurn);
    void movePlayer(string direction, int zombie);
    void command(int x_axis, int y_axis, int zombie);
    void moveZombies(int x_axis, int y_axis, int zombie);
    void encounterItem(string direction, int zombie);
    void changeDirection(int x_axis, int y_axis);
    int winCheck(int zombie);
};

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
            for (int j = 0; j < i; j++)
            {
                if (z[j].zombieCoorX == zombieStatus.zombieCoorX && z[j].zombieCoorY == zombieStatus.zombieCoorY)
                {
                    validCoords = false;
                    break;
                }
            }
            if (alienStatus.coorX == zombieStatus.zombieCoorX && alienStatus.coorY == zombieStatus.zombieCoorY)
            {
                validCoords = false;
                break;
            }
            if (validCoords)
            {
                z.push_back(zombieStatus);
            }
        } while (z.size() < i + 1);
    }
}

void Board::init(int x_axis, int y_axis, int zombie)
{
    string objects[] = {"   ", "   ", " g ", " h ", " r ", " p ", " v ", " > ", " < ", " ^ "};
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
    map_[alienStatus.coorX][alienStatus.coorY] = " A ";
    // INITIALIZE COORDINATE ZOMBIES
    for (int i = 0; i < zombie; i++)
    {
        int j = i + 1;
        string k = to_string(j);
        k = " " + k + " ";
        map_[z[i].zombieCoorX][z[i].zombieCoorY] = k;
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
            cout << "|" << map_[i][j];
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

void Board::encounterItem(string direction, int zombie)
{
    // FINDS HEALTH PACK
    if (map_[alienStatus.coorX][alienStatus.coorY] == " h ")
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

        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS EMPTY SPACE
    else if (map_[alienStatus.coorX][alienStatus.coorY] == "   ")
    {
        cout << " Alien finds empty space. " << endl
             << " Alien continue to move. " << endl
             << endl;

        system("pause");
        cout << endl;

        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS POD
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " p ")
    {
        cout << " Alien finds pod. " << endl;
        // Calculate the distance from the zombie to the player
        int hitZombie;
        int totalDis = 10;
        for (int i = 0; i < zombie; i++)
        {
            int dx = alienStatus.coorX - z[i].zombieCoorX;
            int dy = alienStatus.coorY - z[i].zombieCoorY;

            // Move the zombie in the direction of the player
            if (abs(dx) + abs(dy) < totalDis)
            {
                totalDis = abs(dx) + abs(dy);
                hitZombie = i;
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
            map_[z[hitZombie].zombieCoorX][z[hitZombie].zombieCoorY] = "   ";
        }
        system("pause");
        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS RIGHT ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " > ")
    {
        alienStatus.addAttack(20);
        cout << " Alien finds right arrow. " << endl
             << " Alien's attack is increased by 20. " << endl
             << endl;

        system("pause");
        cout << endl;

        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        direction = "right";
        movePlayer(direction, zombie);
    }
    // FINDS LEFT ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " < ")
    {
        alienStatus.addAttack(20);
        cout << " Alien finds left arrow. " << endl
             << " Alien's attack is increased by 20. " << endl
             << endl;

        system("pause");
        cout << endl;

        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        direction = "left";
        movePlayer(direction, zombie);
    }
    // FINDS UP ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " ^ ")
    {
        alienStatus.addAttack(20);
        cout << " Alien finds up arrow. " << endl
             << " Alien's attack is increased by 20. " << endl
             << endl;

        system("pause");
        cout << endl;

        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        direction = "up";
        movePlayer(direction, zombie);
    }
    // FINDS DOWN ARROW
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " v ")
    {
        alienStatus.addAttack(20);
        cout << " Alien finds down arrow. " << endl
             << " Alien's attack is increased by 20. " << endl
             << endl;

        system("pause");
        cout << endl;

        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        direction = "down";
        movePlayer(direction, zombie);
    }
    // FIND GUN
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " g ")
    {
        int hitZombie;
        cout << " Alien finds gun. " << endl
             << " Choose which zombie to aim." << endl;
        cout << " ==> Zombie ";
        cin >> hitZombie;

        system("pause");
        cout << endl;

        if (hitZombie > zombie || hitZombie < 0 || z[hitZombie - 1].zombieHealth == 0)
        {
            display(zombie, characterTurn);
            cout << " There is no zombie " << hitZombie << " in the board. " << endl
                 << " Alien loss chance to use the gun." << endl
                 << endl;
            system("pause");
        }
        else
        {
            display(zombie, characterTurn);
            hitZombie -= 1;
            z[hitZombie].zombieHealth -= (alienStatus.getAttack() + 10);
            cout << " Zombie " << hitZombie + 1 << " got " << alienStatus.getAttack() + 10 << " damages. " << endl;
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
                map_[z[hitZombie].zombieCoorX][z[hitZombie].zombieCoorY] = "   ";
            }
            system("pause");
        }
        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        direction = "stop";
        movePlayer(direction, zombie);
    }
    // FINDS Rock
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " r ")
    {
        int objectUnderRock = rand() % 2 + 1;
        if (objectUnderRock == 1)
        {
            cout << " Alien stumbles upon a rock. " << endl
                 << " Alien discovers a pod beneath it. " << endl
                 << endl;
            map_[alienStatus.coorX][alienStatus.coorY] = " p ";
        }
        else if (objectUnderRock == 2)
        {
            cout << " Alien stumbles upon a rock. " << endl
                 << " Alien discovers a gun beneath it. " << endl
                 << endl;
            map_[alienStatus.coorX][alienStatus.coorY] = " g ";
        }
        system("pause");
        cout << endl;

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
        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        direction = "stop";
        movePlayer(direction, zombie);
    }
    // FINDS ALIEN TRAIL
    else if (map_[alienStatus.coorX][alienStatus.coorY] == " . ")
    {
        cout << " Alien finds its trail. " << endl
             << " Alien continues moving. " << endl
             << endl;
        system("pause");
        cout << endl;

        map_[alienStatus.coorX][alienStatus.coorY] = " A ";
        display(zombie, characterTurn);
        movePlayer(direction, zombie);
    }
    // FINDS ZOMBIES
    else
    {
        cout << " Alien hits a zombie. " << endl
             << " Zombie" << map_[alienStatus.coorX][alienStatus.coorY] << "accept " << alienStatus.getAttack() << " from the alien." << endl;

        int x = alienStatus.coorX;
        int y = alienStatus.coorY;
        int locZombie;
        for (int i = 0; i < zombie; i++)
        {
            if (z[i].zombieCoorX == x && z[i].zombieCoorY == y)
            {
                locZombie = i;
                break;
            }
        }

        z[locZombie].zombieHealth = z[locZombie].zombieHealth - alienStatus.attack;
        if (z[locZombie].zombieHealth <= 0)
        {
            z[locZombie].zombieHealth = 0;
            cout << " Zombie " << locZombie + 1 << " is dead." << endl
                 << endl;
            system("pause");
            map_[alienStatus.coorX][alienStatus.coorY] = " A ";
            display(zombie, characterTurn);
            movePlayer(direction, zombie);
        }
        else
        {
            cout << " Zombie " << locZombie + 1 << " is still alive." << endl
                 << endl;
            system("pause");
            locZombie += 1;
            string k = to_string(locZombie);
            k = " " + k + " ";
            map_[x][y] = k;
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
            map_[alienStatus.coorX][alienStatus.coorY] = " A ";
            display(zombie, characterTurn);
            direction = "stop";
            movePlayer(direction, zombie);
        }
    }
}

void Board::movePlayer(string direction, int zombie)
{
    // MOVE UP
    characterTurn = 0;
    if (direction == "up")
    {
        if (alienStatus.coorX > 0)
        {
            map_[alienStatus.coorX][alienStatus.coorY] = " . ";
            alienStatus.coorX--;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl
                 << endl;
            system("pause");

            map_[alienStatus.coorX][alienStatus.coorY] = " A ";

            string objects[] = {"   ", "   ", " g ", " h ", " r ", " p ", " v ", " > ", " < ", " ^ "};
            int noOfObjects = 10;

            for (int i = 0; i < dimX_; ++i)
            {
                for (int j = 0; j < dimY_; ++j)
                {
                    if (map_[i][j] == " . ")
                    {
                        int objNo = rand() % noOfObjects;
                        map_[i][j] = objects[objNo];
                    }
                }
            }
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl
                 << endl;
            system("pause");
        }
    }
    // MOVE DOWN
    else if (direction == "down")
    {
        if (alienStatus.coorX < (dimX_ - 1))
        {
            map_[alienStatus.coorX][alienStatus.coorY] = " . ";
            alienStatus.coorX++;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl
                 << endl;
            system("pause");

            map_[alienStatus.coorX][alienStatus.coorY] = " A ";

            string objects[] = {"   ", "   ", " g ", " h ", " r ", " p ", " v ", " > ", " < ", " ^ "};
            int noOfObjects = 10;

            for (int i = 0; i < dimX_; ++i)
            {
                for (int j = 0; j < dimY_; ++j)
                {
                    if (map_[i][j] == " . ")
                    {
                        int objNo = rand() % noOfObjects;
                        map_[i][j] = objects[objNo];
                    }
                }
            }
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl
                 << endl;
            system("pause");
        }
    }
    // MOVE LEFT
    else if (direction == "left")
    {
        if (alienStatus.coorY > 0)
        {
            map_[alienStatus.coorX][alienStatus.coorY] = " . ";
            alienStatus.coorY--;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl
                 << endl;
            system("pause");

            map_[alienStatus.coorX][alienStatus.coorY] = " A ";

            string objects[] = {"   ", "   ", " g ", " h ", " r ", " p ", " v ", " > ", " < ", " ^ "};
            int noOfObjects = 10;

            for (int i = 0; i < dimX_; ++i)
            {
                for (int j = 0; j < dimY_; ++j)
                {
                    if (map_[i][j] == " . ")
                    {
                        int objNo = rand() % noOfObjects;
                        map_[i][j] = objects[objNo];
                    }
                }
            }
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl
                 << endl;
            system("pause");
        }
    }
    // MOVE RIGHT
    else if (direction == "right")
    {
        if (alienStatus.coorY < (dimY_ - 1))
        {
            map_[alienStatus.coorX][alienStatus.coorY] = " . ";
            alienStatus.coorY++;
            encounterItem(direction, zombie);
        }
        else
        {
            cout << " Alien hit the border. " << endl
                 << " Alien stop moving. " << endl
                 << endl;
            system("pause");

            map_[alienStatus.coorX][alienStatus.coorY] = " A ";

            string objects[] = {"   ", "   ", " g ", " h ", " r ", " p ", " v ", " > ", " < ", " ^ "};
            int noOfObjects = 10;
            for (int i = 0; i < dimX_; ++i)
            {
                for (int j = 0; j < dimY_; ++j)
                {
                    if (map_[i][j] == " . ")
                    {
                        int objNo = rand() % noOfObjects;
                        map_[i][j] = objects[objNo];
                    }
                }
            }
            alienStatus.resetAttack(0);
            display(zombie, characterTurn);
            cout << " Alien turn ends. The trail is reset. " << endl
                 << endl;
            system("pause");
        }
    }
    // STOP
    else if (direction == "stop")
    {
        string objects[] = {"   ", "   ", " g ", " h ", " r ", " p ", " v ", " > ", " < ", " ^ "};
        int noOfObjects = 10;
        for (int i = 0; i < dimX_; ++i)
        {
            for (int j = 0; j < dimY_; ++j)
            {
                if (map_[i][j] == " . ")
                {
                    int objNo = rand() % noOfObjects;
                    map_[i][j] = objects[objNo];
                }
            }
        }
        alienStatus.resetAttack(0);
        display(zombie, characterTurn);
        cout << " Alien turn ends. The trail is reset. " << endl
             << endl;
        system("pause");
    }
}

void Board::moveZombies(int x_axis, int y_axis, int zombie)
{
    for (int i = 0; i < zombie; i++)
    {
        if (z[i].zombieHealth > 0)
        {
            characterTurn = i + 1;
            display(zombie, characterTurn);
            cout << " Zombie " << i + 1 << " turns. " << endl;
            cout << endl;
            system("pause");

            display(zombie, characterTurn);

            map_[z[i].zombieCoorX][z[i].zombieCoorY] = "   ";

            int j = i + 1;
            string k = to_string(j);
            k = " " + k + " ";

            srand(time(NULL));
            int stepZombies = 0;
            int counter = 0;
            bool repeat = false;
            bool occupied = false;
            do
            {
                int f = z[i].zombieCoorX;
                int g = z[i].zombieCoorY;
                std::vector<int> validMovement;
                if (f > 0)
                {
                    validMovement.push_back(1); // Up
                }
                if (f < (dimX_ - 1))
                {
                    validMovement.push_back(2); // Down
                }
                if (g > 0)
                {
                    validMovement.push_back(3); // Left
                }
                if (g < (dimY_ - 1))
                {
                    validMovement.push_back(4); // Right
                }

                // If there are no valid directions, the zombie is stuck
                if (validMovement.empty())
                {
                    break;
                }

                // Choose a random direction from the valid directions
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

                // check if the new coordinates are occupied by another zombie
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
                if (map_[f][g] == " r ")
                {
                    repeat = 1;
                }
                if (!repeat)
                {
                    z[i].zombieCoorX = f;
                    z[i].zombieCoorY = g;
                    counter++;
                }
            } while (repeat == 1);

            if (stepZombies == 1)
            {
                cout << " Zombie " << j << " move up." << endl;
                cout << endl;
                system("pause");
            }

            else if (stepZombies == 2) // MOVE DOWN
            {
                cout << " Zombie " << j << " move down." << endl;
                cout << endl;
                system("pause");
            }

            else if (stepZombies == 3) // MOVE LEFT
            {
                cout << " Zombie " << j << " move left." << endl;
                cout << endl;
                system("pause");
            }

            else if (stepZombies == 4) // MOVE RIGHT
            {
                cout << " Zombie " << j << " move right." << endl;
                cout << endl;
                system("pause");
            }
            else if (stepZombies == 0)
            {
                cout << " Zombie " << j << " is trapped." << endl;
                cout << endl;
                system("pause");
            }

            map_[z[i].zombieCoorX][z[i].zombieCoorY] = k;

            // Update the position of the zombie
            display(zombie, characterTurn);

            int dx = z[i].zombieCoorX - alienStatus.coorX;
            int dy = z[i].zombieCoorY - alienStatus.coorY;

            // ZOMBIE ATTACK ALIEN
            if ((abs(dx) <= z[i].zombieRange && abs(dy) == 0) || (abs(dy) <= z[i].zombieRange && abs(dx) == 0))
            {
                alienStatus.addHealth(-10);
                cout << " Zombie " << j << " attacked the alien. " << endl;
                cout << " Alien's health is " << alienStatus.health << endl;
                cout << endl;
                system("pause");
            }
            else
            {
                cout << " Zombie " << j << " cannot attack." << endl;
                cout << endl;
                system("pause");
            }
            display(zombie, characterTurn);
            cout << " Zombie " << j << " turn ends. " << endl
                 << endl;
            system("pause");
        }
    }
    characterTurn = 0;
}

void Board::changeDirection(int x_axis, int y_axis)
{
    int xArrow;
    int yArrow;
    string newArrow;
    cout << " Input row of arrow : ";
    cin >> xArrow;
    cout << " Input column of arrow: ";
    cin >> yArrow;
    cout << " Input arrow ' ^, v, >, < ' : ";
    cin >> newArrow;
    xArrow = xArrow - 1;
    yArrow = yArrow - 1;
    newArrow = " " + newArrow + " ";

    if (map_[xArrow][yArrow] == " ^ " || map_[xArrow][yArrow] == " v " || map_[xArrow][yArrow] == " > " || map_[xArrow][yArrow] == " < ")
    {
        map_[xArrow][yArrow] = newArrow;
        cout << " The arrow's changer is updated. " << endl;
    }
    else
    {
        cout << " There is no arrow in this coordinate. " << endl;
    }
    cout << endl;
    system("Pause");
}

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

void Board::command(int x_axis, int y_axis, int zombie)
{
    cout << "Command ==> ";
    string move;
    cin >> move;
    cout << endl;
    if (move == "help")
    {
        system("CLS");
        help();
        display(zombie, characterTurn);
        command(x_axis, y_axis, zombie);
    }
    else if (move == "arrow")
    {
        changeDirection(x_axis, y_axis);
        display(zombie, characterTurn);
        command(x_axis, y_axis, zombie);
    }
    else if (move == "exit")
    {
        cout << "Saving the game..." << endl;
        fstream myFile3;
        myFile3.open(usrtxt, ios::out);
        {
            myFile3 << x_axis << endl;
            myFile3 << y_axis << endl;
            for (int i = 0; i < x_axis; ++i)
            {
                myFile3 << "   ";
                for (int j = 0; j < y_axis; ++j)
                {
                    myFile3 << "+---";
                }
                myFile3 << "+" << endl;

                myFile3 << setw(2) << (i + 1) << " ";

                for (int j = 0; j < y_axis; ++j)
                {
                    myFile3 << "|" << map_[i][j];
                }
                myFile3 << "|" << endl;
            }

            myFile3 << "   ";
            for (int j = 0; j < y_axis; ++j)
            {
                myFile3 << "+---";
            }
            myFile3 << "+" << endl;

            myFile3 << "  ";
            for (int j = 0; j < y_axis; ++j)
            {
                int digit = (j + 1) / 10;
                myFile3 << "   ";
                if (digit == 0)
                    myFile3 << " ";
                else
                    myFile3 << digit;
            }
            myFile3 << endl;
            myFile3 << "C>";
            for (int j = 0; j < y_axis; ++j)
            {
                myFile3 << "   " << (j + 1) % 10;
            }
            myFile3 << endl;
            myFile3 << alienStatus.getHealth() << "," << alienStatus.getAttack() << endl;
            for (int i = 0; i < zombie; ++i)
            {
                myFile3 << z[i].zombieHealth << "," << z[i].zombieAttack << "," << z[i].zombieRange << endl;
            }
            cout << "See you again! " << endl;
            system("Pause");
            abort();
        }
    }
    else if (move == "right" || move == "left" || move == "up" || move == "down")
    {
        movePlayer(move, zombie);
    }
    else
    {
        cout << " Input wrong command!! " << endl;
        cout << " Enter 'help' for help. " << endl;
        command(x_axis, y_axis, zombie);
    }
    cout << endl;
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

void displayBoard(int x_axis, int y_axis, int zombie)
{
    Board board;
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