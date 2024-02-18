#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

// the colors
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// to hold our spaceship's location and it's heal
struct Spaceship
{
    int x;
    int y;
    int heal;
};

// to hold map's information
struct MapInfo
{
    int size;
    int point;
};

// to save enemy's informations
struct Enemy
{
    std::string name;
    int heal;
    int point;
    int x;
    int y;
    bool ltr;
};

// to save bullets location
struct Bullet
{

    int x;
    int y;
};

void SatrtMenu();                                                                                                                                           // to make start menue
void Puase(MapInfo &mapInfo, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, std::vector<std::vector<char>> &space, std::vector<Bullet> &bullet);    // to show pause menue
void Guidence();                                                                                                                                            // to guide user to play
void ExitGame();                                                                                                                                            // to exit game
MapInfo MapSize();                                                                                                                                          // to take map size and point from user
void GenerateGame(int choice);                                                                                                                              // to generate game
void RunGame(MapInfo &mapInfo, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, std::vector<std::vector<char>> &space, std::vector<Bullet> &bullet);  // to run game
void Space(int &size, std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, std::vector<Bullet> &bullet);                              // to give the first position to spaceships
void LoadSpace(int &size, std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, std::vector<Bullet> &bullet);                          // to load information on map
void Map(MapInfo mapInfo, std::vector<std::vector<char>> &space, int &heal, int &CurrentPoint, Enemy enemy);                                                // to generate map
void RandomEnemy(int &y, int &size);                                                                                                                        // to give random place to enemy
void Dart(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet);                                                     // to make Dart spaceship and return its y
void Striker(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet);                                                  // to make Striker spaceship and return its y
void Wraith(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet);                                                   // to make Wraith spaceship and return its y
void Banshee(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet);                                                  // to make Banshee spaceship and return its y
void Mover(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet);    // to move spaceships
void MoveEnemy(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, std::vector<Bullet> &bullet);                   // to move enemy
void Attack(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet);   // to do attack action
void Right(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet);    // to do right action
void Left(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet);     // to dp left action
void DestroyEnemy(std::vector<std::vector<char>> &space, MapInfo &mapInfo);                                                                                 // to destroy enemy
void InsertEnemy(int &size, std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, std::vector<Bullet> &bullet);                        // to insert enemy in map
void Damage(Spaceship &spaceship, std::vector<std::vector<char>> &space, Enemy &enemy, MapInfo &mapInfo);                                                   // to decrease our heal when the spaceships are in collision
void SaveGame(std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, MapInfo &mapInfo, std::vector<Bullet> &bullet); // to save game in a textfile
void LoadGame(Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, MapInfo &mapInfo, std::vector<Bullet> &bullet);                                        // to load game from aa textfile
int stringToInt(std::string txt);                                                                                                                           // to convert string to int
void Win(std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, MapInfo &mapInfo, std::vector<Bullet> &bullet);      // to show win popup
void Lose();                                                                                                                                                // to show lose popup

int main()
{

    SatrtMenu();

    return 0;
}

// to show the menue to user and  ask how he wants to play
void SatrtMenu()
{
    system("CLS");
    std::cout << R"( /\/\/\                            /  \
| \  / |                         /      \
|  \/  |                       /          \
|  /\  |----------------------|     /\     |
| /  \ |                      |    /  \    |
|/    \|                      |   /    \   |
|\    /|                      |  | (  ) |  |
| \  / |                      |  | (  ) |  |
|  \/  |                 /\   |  |      |  |   /\
|  /\  |                /  \  |  |      |  |  /  \
| /  \ |               |----| |  |      |  | |----|
|/    \|---------------|    | | /|   .  |\ | |    |
|\    /|               |    | /  |   .  |  \ |    |
| \  / |               |    /    |   .  |    \    |
|  \/  |               |  /      |   .  |      \  |
|  /\  |---------------|/        |   .  |        \|
| /  \ |              /   NASA   |   .  |  NASA    \
|/    \|              (          |      |           )
|/\/\/\|               |    | |--|      |--| |    |
------------------------/  \-----/  \/  \-----/  \--------
                        \\//     \\//\\//     \\//
                         \/       \/  \/       \/)"
              << '\n';
    std::cout << "-----------------------" << '\n';
    std::cout << "1- Start game" << '\n';
    std::cout << "2- Load game" << '\n';
    std::cout << "3- Guidence" << '\n';
    std::cout << "4- Exit game" << '\n';
    std::cout << "-----------------------" << '\n';
    int choice;
    do
    {
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            GenerateGame(1);
            break;
        case 2:
            GenerateGame(2);
            break;
        case 3:
            Guidence();
            break;
        case 4:
            ExitGame();
            break;

        default:
            std::cout << "invalid choice" << '\n';
            break;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
}

// to save game in a text file
void SaveGame(std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, MapInfo &mapInfo, std::vector<Bullet> &bullet)
{

    std::ofstream Save;

    Save.open("GameInfo.txt", std::ios::out);

    if (Save.is_open())
    {
        Save << spaceship.heal << ' ' << spaceship.x << ' ' << spaceship.y << '\n';

        Save << enemy.name << ' ' << enemy.point << ' ' << enemy.heal << ' ' << enemy.ltr << ' ' << enemy.x << ' ' << enemy.y << '\n';

        Save << mapInfo.size << ' ' << mapInfo.point << '\n';

        Save << CurrentPoint << '\n';

        for (int i = 0; i < bullet.size(); i++)
        {

            Save << bullet[i].x << ' ' << bullet[i].y << '\n';
        }
    }
    else
    {
        std::cerr << "cant open the file\n";
    }

    Save.close();
}

// to load game from textfile
void LoadGame(Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, MapInfo &mapInfo, std::vector<Bullet> &bullet)
{

    std::ifstream Load;
    Load.open("GameInfo.txt", std::ios::in);

    if (Load.is_open())
    {
        std::string line;

        int counter = 0;
        int counter1 = 0;
        int counter2 = 0;
        int counter3 = 0;
        int counter4 = 0;
        Bullet temp;

        while (std::getline(Load, line))
        {

            counter++;

            std::stringstream cutter(line);
            std::string word;

            switch (counter)
            {
            case 1:

                while (cutter >> word)
                {
                    counter1++;

                    switch (counter1)
                    {
                    case 1:
                        spaceship.heal = stringToInt(word);
                        break;

                    case 2:
                        spaceship.x = stringToInt(word);
                        break;

                    case 3:
                        spaceship.y = stringToInt(word);
                        break;
                    default:
                        break;
                    }
                }
                break;
            case 2:

                while (cutter >> word)
                {

                    counter2++;
                    switch (counter2)
                    {
                    case 1:
                        enemy.name = word;
                        break;

                    case 2:
                        enemy.point = stringToInt(word);
                        break;

                    case 3:
                        enemy.heal = stringToInt(word);
                        break;

                    case 4:
                        enemy.ltr = stringToInt(word);
                        break;

                    case 5:
                        enemy.x = stringToInt(word);
                        break;

                    case 6:
                        enemy.y = stringToInt(word);
                        break;
                    }
                }
                break;

            case 3:

                while (cutter >> word)
                {

                    counter3++;

                    switch (counter3)
                    {
                    case 1:
                        mapInfo.size = stringToInt(word);
                        break;
                    case 2:
                        mapInfo.point = stringToInt(word);
                        break;

                    default:
                        break;
                    }
                }

                break;
            case 4:
                while (cutter >> word)
                {
                    CurrentPoint = stringToInt(word);
                }

                break;

            default:

                counter4 = 0;

                while (cutter >> word)
                {
                    counter4++;
                    if (counter4 == 1)
                    {

                        temp.x = stringToInt(word);
                    }

                    if (counter4 == 2)
                    {

                        temp.y = stringToInt(word);
                    }
                }

                bullet.push_back(temp);

                break;
            }
        }
    }
    else
    {

        std::cerr << "can't open the file\n";
    }

    Load.close();
}

// to show puase menue
void Puase(MapInfo &mapInfo, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, std::vector<std::vector<char>> &space, std::vector<Bullet> &bullet)
{
    system("CLs");
    std::cout << "1- Resume game" << '\n';
    std::cout << "2- Save and Leave game" << '\n';
    int option;
    do
    {
        std::cin >> option;
        switch (option)
        {
        case 1:
            Map(mapInfo, space, spaceship.heal, CurrentPoint, enemy);
            RunGame(mapInfo, spaceship, enemy, CurrentPoint, space, bullet);
            break;
        case 2:
            SaveGame(space, spaceship, enemy, CurrentPoint, mapInfo, bullet);
            SatrtMenu();
            break;
        default:
            std::cerr << "invalid input" << '\n';
            break;
        }
    } while (option != 1 && option != 2);
}

// to guide user to play
void Guidence()
{
    system("CLS");
    std::cout << "W : shoot straight" << '\n';
    std::cout << "D : move rigth and shoot" << '\n';
    std::cout << "A : move left and shoot\n";
    std::cout << "P : puse game" << '\n';
    int leave;
    do
    {
        std::cout << "enter 0 to leave\n";
        std::cin >> leave;
        if (leave == 0)
            SatrtMenu();
        else
            std::cout << "invalid input\n";
    } while (leave != 0);
}

// to exit game
void ExitGame()
{
    system("cls");
    std::cout << "are you sure you want to exit(1 : yes , 0 : no )?";
    int sure;

    do
    {
        std::cin >> sure;
        if (sure == 1)
            exit(0);
        else if (sure == 0)
            SatrtMenu();
        else
            std::cout << "invalid input" << '\n';

    } while (sure != 1 && sure != 0);
}

// to take size of the map from user
MapInfo MapSize()
{

    MapInfo mapInfo;
    do
    {
        std::cout << "enter the size of map(n x n) :" << '\n';
        std::cout << "enter 0 if you want to leave" << '\n';
        std::cin >> mapInfo.size;
        if (mapInfo.size < 15 && mapInfo.size != 0)
        {
            std::cout << "the size of the map at least is 15" << '\n';
        }
        else if (mapInfo.size == 0)
        {
            SatrtMenu();
            break;
        }
        else if (mapInfo.size >= 15)
        {
            std::cout << "how many points you want to achive" << '\n';
            std::cin >> mapInfo.point;
            break;
        }
    } while (mapInfo.size < 15);

    return mapInfo;
}

// to run the game
void GenerateGame(int choice)
{

    Spaceship spaceship;

    MapInfo mapInfo;

    Enemy enemy;

    std::vector<Bullet> bullet;

    int CurrentPoint;
    if (choice == 1)
    {

        mapInfo = MapSize(); // size of the map

        std::vector<std::vector<char>> space(mapInfo.size, std::vector<char>(mapInfo.size, ' ')); // to create empty spaces in map

        spaceship.heal = 3;

        CurrentPoint = 0;

        Space(mapInfo.size, space, spaceship, enemy, bullet);

        Map(mapInfo, space, spaceship.heal, CurrentPoint, enemy);

        RunGame(mapInfo, spaceship, enemy, CurrentPoint, space, bullet);
    }
    if (choice == 2)
    {

        LoadGame(spaceship, enemy, CurrentPoint, mapInfo, bullet);

        std::vector<std::vector<char>> space(mapInfo.size, std::vector<char>(mapInfo.size, ' ')); // to create empty spaces in map

        LoadSpace(mapInfo.size, space, spaceship, enemy, bullet);

        Map(mapInfo, space, spaceship.heal, CurrentPoint, enemy);

        RunGame(mapInfo, spaceship, enemy, CurrentPoint, space, bullet);
    }
}

// to run game
void RunGame(MapInfo &mapInfo, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, std::vector<std::vector<char>> &space, std::vector<Bullet> &bullet)
{

    while (CurrentPoint < mapInfo.point)
    {

        if (spaceship.heal < 1)
        {
            break;
        }

        Mover(spaceship, enemy, space, mapInfo, CurrentPoint, bullet);
        MoveEnemy(spaceship, enemy, space, mapInfo, bullet);

        if (enemy.heal < 1)
        {
            CurrentPoint += enemy.point;
            DestroyEnemy(space, mapInfo);
            InsertEnemy(mapInfo.size, space, spaceship, enemy, bullet);
            // Map(mapInfo , space, spaceship.heal , CurrentPoint , enemy);
        }

        Map(mapInfo, space, spaceship.heal, CurrentPoint, enemy);

        SaveGame(space, spaceship, enemy, CurrentPoint, mapInfo, bullet);
    }

    if (spaceship.heal < 1)
    {
        Lose();
    }
    else
    {
        Win(space, spaceship, enemy, CurrentPoint, mapInfo, bullet);
    }
}

// to give the first position to the spaceships
void Space(int &size, std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, std::vector<Bullet> &bullet)
{

    spaceship.x = size - 1;
    spaceship.y = static_cast<int>(size / 2) - 1;
    space[spaceship.x][spaceship.y] = '#';
    InsertEnemy(size, space, spaceship, enemy, bullet);
}

// to give loaded value to space
void LoadSpace(int &size, std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, std::vector<Bullet> &bullet)
{

    space[spaceship.x][spaceship.y] = '#';

    if (enemy.name == "Dart")
    {

        Dart(size, space, enemy, bullet);
    }

    if (enemy.name == "Striker")
    {

        Striker(size, space, enemy, bullet);
    }

    if (enemy.name == "Wraith")
    {

        Wraith(size, space, enemy, bullet);
    }

    if (enemy.name == "Banshee")
    {

        Banshee(size, space, enemy, bullet);
    }

    for (int i = 0; i < bullet.size(); i++)
    {

        space[bullet[i].x][bullet[i].y] = '^';
    }
}

// to create enemy
void InsertEnemy(int &size, std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, std::vector<Bullet> &bullet)
{
    RandomEnemy(enemy.y, size);
    srand(time(0));
    int RandomEnemy = rand() % 4;
    switch (RandomEnemy)
    {
    case 0:
        enemy.name = "Dart";
        enemy.point = 2;
        enemy.x = 0;
        Dart(size, space, enemy, bullet);
        enemy.heal = 1;
        break;
    case 1:
        enemy.name = "Striker";
        enemy.point = 8;
        enemy.x = 0;
        Striker(size, space, enemy, bullet);
        enemy.heal = 2;
        break;
    case 2:
        enemy.name = "Wraith";
        enemy.point = 18;
        enemy.x = 0;
        Wraith(size, space, enemy, bullet);
        enemy.heal = 4;
        break;
    case 3:
        enemy.name = "Banshee";
        enemy.point = 32;
        enemy.x = 0;
        Banshee(size, space, enemy, bullet);
        enemy.heal = 6;
        break;
    }
}

// to make map
void Map(MapInfo mapInfo, std::vector<std::vector<char>> &space, int &heal, int &CurrentPoint, Enemy enemy)
{


    system("CLS"); // to clear the screen

    if (mapInfo.size >= 15)
    {
        std::cout << "your heal : ";
        for (int i = 0; i < heal; i++)
        {

            std::cout << '#';
        }
        std::cout << " | ";
        std::cout << "the enemy's heal : ";
        for (int i = 0; i < enemy.heal; i++)
        {

            std::cout << '*';
        }
        std::cout << " | ";
        std::cout << "size of the map : " << mapInfo.size << " x " << mapInfo.size << " | ";
        std::cout << "your current point : " << CurrentPoint << " | ";
        std::cout << "the total point : " << mapInfo.point << " | ";
        std::cout << "pause(enter p)" << '\n';

        for (int i = 0; i < mapInfo.size; i++)
        {

            for (int j = 0; j < mapInfo.size; j++)
            {
                std::cout << " ---";
            }
            std::cout << '\n';
            for (int k = 0; k <= mapInfo.size; k++)
            {
                if (k == mapInfo.size)
                    std::cout << "|";
                else{
                    if(space[i][k]== '*'){
                        if(enemy.name == "Dart")
                             std::cout << "|" << ' ' <<RED<< space[i][k]<<RESET << ' ';
                        if(enemy.name == "Striker")
                             std::cout << "|" << ' ' <<GREEN<< space[i][k]<<RESET << ' ';
                        if(enemy.name == "Wraith")
                             std::cout << "|" << ' ' <<YELLOW<< space[i][k]<<RESET << ' ';
                        if(enemy.name == "Banshee")
                             std::cout << "|" << ' ' <<BLUE<< space[i][k]<<RESET << ' ';
                    }
                    else if(space[i][k]== '#')
                         std::cout << "|" << ' ' <<CYAN<< space[i][k]<<RESET << ' ';
                    else
                        std::cout << "|" << ' ' << space[i][k] << ' ';
                            
            }
            }

            std::cout << '\n';
        }

        for (int i = 0; i < mapInfo.size; i++)
            std::cout << " ---";

        std::cout << '\n';
    }
}

// to give a random place to enemy
void RandomEnemy(int &y, int &size)
{

    srand(time(0));
    y = rand() % size;
}

// to make Dart spaceship and return its position
void Dart(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet)
{
    if (space[enemy.x][enemy.y] == '^')
    {

        enemy.heal--;
        for (int i = 0; i < bullet.size(); i++)
        {
            if (bullet[i].x == enemy.x && bullet[i].y == enemy.y)
            {

                bullet.erase(bullet.begin() + i);
                i--;
            }
        }
    }

    space[enemy.x][enemy.y] = '*';
    enemy.ltr = true;
}

// to make Striker spaceship and return its position
void Striker(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet)
{

    if (enemy.y == size - 1)
    {

        // if(space[enemy.x][enemy.y] == '^' ||space[enemy.x+1][enemy.y] == '^' ||space[enemy.x][enemy.y-1] == '^'||space[enemy.x+1][enemy.y-1] == '^'){

        //     enemy.heal-- ;
        //     for(int i = 0 ; i<bullet.size() ; i++){
        //         if(bullet[i].x == enemy.x && bullet[i].y == enemy.y){

        //                bullet.erase(bullet.begin() + i) ;
        //                i-- ;

        //         }
        //     }

        // }

        space[enemy.x][enemy.y] = '*';
        space[enemy.x][enemy.y - 1] = '*';
        space[enemy.x + 1][enemy.y] = '*';
        space[enemy.x + 1][enemy.y - 1] = '*';
        enemy.ltr = false;
    }
    else
    {

        // if(space[enemy.x][enemy.y] == '^' ||space[enemy.x+1][enemy.y] == '^' ||space[enemy.x][enemy.y+1] == '^'||space[enemy.x+1][enemy.y+1] == '^'){

        //     enemy.heal-- ;
        //     for(int i = 0 ; i<bullet.size() ; i++){
        //         if(bullet[i].x == enemy.x && bullet[i].y == enemy.y){

        //                bullet.erase(bullet.begin() + i) ;
        //                i-- ;

        //         }
        //     }

        // }

        space[enemy.x][enemy.y] = '*';
        space[enemy.x][enemy.y + 1] = '*';
        space[enemy.x + 1][enemy.y] = '*';
        space[enemy.x + 1][enemy.y + 1] = '*';
        enemy.ltr = true;
    }
}

// to make Wraith spaceship and return its position
void Wraith(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet)
{

    if (enemy.y == size - 1 || enemy.y == size - 2)
    {

        // if(space[enemy.x][enemy.y] == '^' ||space[enemy.x+1][enemy.y] == '^'||space[enemy.x+2][enemy.y] == '^'  ||space[enemy.x][enemy.y-1] == '^'||space[enemy.x+1][enemy.y-1] == '^'||space[enemy.x+2][enemy.y-1] == '^' || space[enemy.x][enemy.y-2] == '^'||space[enemy.x+1][enemy.y-2] == '^'||space[enemy.x+2][enemy.y-2] == '^'){

        //     enemy.heal-- ;
        //     for(int i = 0 ; i<bullet.size() ; i++){
        //         if(bullet[i].x == enemy.x && bullet[i].y == enemy.y){

        //                bullet.erase(bullet.begin() + i) ;
        //                i-- ;

        //         }
        //     }

        // }

        space[enemy.x][enemy.y] = '*';
        space[enemy.x][enemy.y - 1] = '*';
        space[enemy.x][enemy.y - 2] = '*';
        space[enemy.x + 1][enemy.y] = '*';
        space[enemy.x + 1][enemy.y - 1] = '*';
        space[enemy.x + 1][enemy.y - 2] = '*';
        space[enemy.x + 2][enemy.y] = '*';
        space[enemy.x + 2][enemy.y - 1] = '*';
        space[enemy.x + 2][enemy.y - 2] = '*';
        enemy.ltr = false;
    }
    else
    {

        // if(space[enemy.x][enemy.y] == '^' ||space[enemy.x+1][enemy.y] == '^'||space[enemy.x+2][enemy.y] == '^'  ||space[enemy.x][enemy.y+1] == '^'||space[enemy.x+1][enemy.y+1] == '^'||space[enemy.x+2][enemy.y+1] == '^' || space[enemy.x][enemy.y+2] == '^'||space[enemy.x+1][enemy.y+2] == '^'||space[enemy.x+2][enemy.y+2] == '^'){

        //     enemy.heal-- ;
        //     for(int i = 0 ; i<bullet.size() ; i++){
        //         if(bullet[i].x == enemy.x && bullet[i].y == enemy.y){

        //                bullet.erase(bullet.begin() + i) ;
        //                i-- ;

        //         }
        //     }

        // }

        space[enemy.x][enemy.y] = '*';
        space[enemy.x][enemy.y + 1] = '*';
        space[enemy.x][enemy.y + 2] = '*';
        space[enemy.x + 1][enemy.y] = '*';
        space[enemy.x + 1][enemy.y + 1] = '*';
        space[enemy.x + 1][enemy.y + 2] = '*';
        space[enemy.x + 2][enemy.y] = '*';
        space[enemy.x + 2][enemy.y + 1] = '*';
        space[enemy.x + 2][enemy.y + 2] = '*';
        enemy.ltr = true;
    }
}

// to make Banshee spaceship and return its position
void Banshee(int &size, std::vector<std::vector<char>> &space, Enemy &enemy, std::vector<Bullet> &bullet)
{

    if (enemy.y == size - 1 || enemy.y == size - 2 || enemy.y == size - 3)
    {

        // if(space[enemy.x][enemy.y] == '^' ||space[enemy.x+1][enemy.y] == '^'||space[enemy.x+2][enemy.y] == '^' ||space[enemy.x+3][enemy.y] == '^'  ||space[enemy.x][enemy.y-1] == '^'||space[enemy.x+1][enemy.y-1] == '^'||space[enemy.x+2][enemy.y-1] == '^' ||space[enemy.x+3][enemy.y-1] == '^' || space[enemy.x][enemy.y-2] == '^'||space[enemy.x+1][enemy.y-2] == '^'||space[enemy.x+2][enemy.y-2] == '^'||space[enemy.x+3][enemy.y-2] == '^' || space[enemy.x][enemy.y-3] == '^' ||space[enemy.x+1][enemy.y-3] == '^'||space[enemy.x+2][enemy.y-3] == '^' ||space[enemy.x+3][enemy.y-3] ){

        //     enemy.heal-- ;
        //     for(int i = 0 ; i<bullet.size() ; i++){
        //         if(bullet[i].x == enemy.x && bullet[i].y == enemy.y){

        //                bullet.erase(bullet.begin() + i) ;
        //                i-- ;

        //         }
        //     }

        // }

        space[enemy.x][enemy.y] = '*';
        space[enemy.x][enemy.y - 1] = '*';
        space[enemy.x][enemy.y - 2] = '*';
        space[enemy.x][enemy.y - 3] = '*';
        space[enemy.x + 1][enemy.y] = '*';
        space[enemy.x + 1][enemy.y - 1] = '*';
        space[enemy.x + 1][enemy.y - 2] = '*';
        space[enemy.x + 1][enemy.y - 3] = '*';
        space[enemy.x + 2][enemy.y] = '*';
        space[enemy.x + 2][enemy.y - 1] = '*';
        space[enemy.x + 2][enemy.y - 2] = '*';
        space[enemy.x + 2][enemy.y - 3] = '*';
        space[enemy.x + 3][enemy.y] = '*';
        space[enemy.x + 3][enemy.y - 1] = '*';
        space[enemy.x + 3][enemy.y - 2] = '*';
        space[enemy.x + 3][enemy.y - 3] = '*';
        enemy.ltr = false;
    }
    else
    {

        // if(space[enemy.x][enemy.y] == '^' ||space[enemy.x+1][enemy.y] == '^'||space[enemy.x+2][enemy.y] == '^' ||space[enemy.x+3][enemy.y] == '^'  ||space[enemy.x][enemy.y+1] == '^'||space[enemy.x+1][enemy.y+1] == '^'||space[enemy.x+2][enemy.y+1] == '^' ||space[enemy.x+3][enemy.y+1] == '^' || space[enemy.x][enemy.y+2] == '^'||space[enemy.x+1][enemy.y+2] == '^'||space[enemy.x+2][enemy.y+2] == '^'||space[enemy.x+3][enemy.y+2] == '^' || space[enemy.x][enemy.y+3] == '^' ||space[enemy.x+1][enemy.y+3] == '^'||space[enemy.x+2][enemy.y+3] == '^' ||space[enemy.x+3][enemy.y+3] ){

        //     enemy.heal-- ;
        //     for(int i = 0 ; i<bullet.size() ; i++){
        //         if(bullet[i].x == enemy.x && bullet[i].y == enemy.y){

        //                bullet.erase(bullet.begin() + i) ;
        //                i-- ;

        //         }
        //     }

        // }

        space[enemy.x][enemy.y] = '*';
        space[enemy.x][enemy.y + 1] = '*';
        space[enemy.x][enemy.y + 2] = '*';
        space[enemy.x][enemy.y + 3] = '*';
        space[enemy.x + 1][enemy.y] = '*';
        space[enemy.x + 1][enemy.y + 1] = '*';
        space[enemy.x + 1][enemy.y + 2] = '*';
        space[enemy.x + 1][enemy.y + 3] = '*';
        space[enemy.x + 2][enemy.y] = '*';
        space[enemy.x + 2][enemy.y + 1] = '*';
        space[enemy.x + 2][enemy.y + 2] = '*';
        space[enemy.x + 2][enemy.y + 3] = '*';
        space[enemy.x + 3][enemy.y] = '*';
        space[enemy.x + 3][enemy.y + 1] = '*';
        space[enemy.x + 3][enemy.y + 2] = '*';
        space[enemy.x + 3][enemy.y + 3] = '*';
        enemy.ltr = true;
    }
}

// to move  spaceships
void Mover(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet)
{
    char move;
    std::cin >> move;
    switch (move)
    {
    case 'w':
        Attack(spaceship, enemy, space, mapInfo, CurrentPoint, bullet);
        break;
    case 'd':
        Right(spaceship, enemy, space, mapInfo, CurrentPoint, bullet);
        break;
    case 'a':
        Left(spaceship, enemy, space, mapInfo, CurrentPoint, bullet);
        break;
    case 'p':
        Puase(mapInfo, spaceship, enemy, CurrentPoint, space, bullet);
        break;

    default:
        std::cerr << "invalid input" << '\n';
        break;
    }
}

// to move enemy
void MoveEnemy(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, std::vector<Bullet> &bullet)
{

    if (enemy.name == "Dart")
    {
        if (enemy.x < mapInfo.size - 2)
        {
            space[enemy.x][enemy.y] = ' ';
            enemy.x++;
            space[enemy.x][enemy.y] = '*';
        }
        else if (enemy.x == mapInfo.size - 2)
        {
            Damage(spaceship, space, enemy, mapInfo);
        }
        else if (enemy.x == mapInfo.size - 1)
        {
            spaceship.heal--;
            DestroyEnemy(space, mapInfo);
            InsertEnemy(mapInfo.size, space, spaceship, enemy, bullet);
        }
    }

    if (enemy.name == "Striker")
    {
        if (enemy.x < mapInfo.size - 3)
        {
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 2][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
        else if (enemy.x == mapInfo.size - 3)
        {
            Damage(spaceship, space, enemy, mapInfo);
        }
        else if (enemy.x == mapInfo.size - 2)
        {
            spaceship.heal--;
            DestroyEnemy(space, mapInfo);
            InsertEnemy(mapInfo.size, space, spaceship, enemy, bullet);
        }
    }

    if (enemy.name == "Wraith")
    {
        if (enemy.x < mapInfo.size - 4)
        {
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 3][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
        else if (enemy.x == mapInfo.size - 4)
        {
            Damage(spaceship, space, enemy, mapInfo);
        }
        else if (enemy.x == mapInfo.size - 3)
        {
            spaceship.heal--;
            DestroyEnemy(space, mapInfo);
            InsertEnemy(mapInfo.size, space, spaceship, enemy, bullet);
        }
    }

    if (enemy.name == "Banshee")
    {
        if (enemy.x < mapInfo.size - 5)
        {
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 4][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
        else if (enemy.x == mapInfo.size - 5)
        {
            Damage(spaceship, space, enemy, mapInfo);
        }
        else if (enemy.x == mapInfo.size - 4)
        {
            spaceship.heal--;
            DestroyEnemy(space, mapInfo);
            InsertEnemy(mapInfo.size, space, spaceship, enemy, bullet);
            // Map(mapInfo , space, spaceship.heal , CurrentPoint);
        }
    }
}

// to do attack action
void Attack(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet)
{

    // for(int i = 1; i<mapInfo.size ; i++){
    //         if(space[spaceship.x-i][spaceship.y]==' '){
    //             space[spaceship.x-i][spaceship.y] ='^' ;
    //             Map(mapInfo, space, spaceship.heal , CurrentPoint , enemy) ;
    //             std::this_thread::sleep_for(std::chrono::milliseconds(25));
    //             space[spaceship.x-i][spaceship.y] =' ' ;
    //         }

    //         if(space[spaceship.x-i][spaceship.y]=='*'){
    //             enemy.heal-- ;
    //             space[spaceship.x-i-1][spaceship.y]==' ' ;
    //             std::cout<<enemy.heal ;
    //             break ;
    //         }
    //     }

    Bullet b;
    b.x = spaceship.x - 1;
    b.y = spaceship.y;

    bullet.push_back(b);

    for (int i = 0; i < bullet.size(); i++)
    {

        if (bullet[i].x >= 0)
        {

            if (bullet[i].x > 0 && (space[bullet[i].x][bullet[i].y] == '*' || space[bullet[i].x - 1][bullet[i].y] == '*'))
            {

                enemy.heal--;

                if (space[bullet[i].x + 1][bullet[i].y] != '#' && space[bullet[i].x + 1][bullet[i].y] != '*')
                {

                    space[bullet[i].x + 1][bullet[i].y] = ' ';
                }

                bullet.erase(bullet.begin() + i);

                i--;
            }
            else
            {

                space[bullet[i].x][bullet[i].y] = '^';

                if (space[bullet[i].x + 1][bullet[i].y] != '#' && space[bullet[i].x + 1][bullet[i].y] != '*')
                {

                    space[bullet[i].x + 1][bullet[i].y] = ' ';
                }

                bullet[i].x--;
            }
        }
        else
        {
            if (space[bullet[i].x + 1][bullet[i].y] != '#' && space[bullet[i].x + 1][bullet[i].y] != '*')
            {
                space[bullet[i].x + 1][bullet[i].y] = ' ';
            }
            bullet.erase(bullet.begin() + i);
            i--;
        }
    }
}

// to do right action
void Right(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet)
{

    if (spaceship.y != mapInfo.size - 1)
    {
        space[spaceship.x][spaceship.y] = ' ';
        spaceship.y++;
        space[spaceship.x][spaceship.y] = '#';
        Attack(spaceship, enemy, space, mapInfo, CurrentPoint, bullet);
    }
}

// to do left action
void Left(Spaceship &spaceship, Enemy &enemy, std::vector<std::vector<char>> &space, MapInfo &mapInfo, int &CurrentPoint, std::vector<Bullet> &bullet)
{
    if (spaceship.y != 0)
    {
        space[spaceship.x][spaceship.y] = ' ';
        spaceship.y--;
        space[spaceship.x][spaceship.y] = '#';
        Attack(spaceship, enemy, space, mapInfo, CurrentPoint, bullet);
    }
}

// to destroy enemy
void DestroyEnemy(std::vector<std::vector<char>> &space, MapInfo &mapInfo)
{

    for (int i = 0; i < mapInfo.size; i++)
    {
        for (int j = 0; j < mapInfo.size; j++)
        {
            if (space[i][j] == '*')
                space[i][j] = ' ';
        }
    }
}

// to decrease our heal when the spaceships are in collision
void Damage(Spaceship &spaceship, std::vector<std::vector<char>> &space, Enemy &enemy, MapInfo &mapInfo)
{
    enemy.x++;
    if (enemy.name == "Dart")
    {
        if (enemy.x == spaceship.x && enemy.y == spaceship.y)
        {
            spaceship.heal--;
            enemy.x--;
        }
        else
        {
            enemy.x--;
            space[enemy.x][enemy.y] = ' ';
            enemy.x++;
            space[enemy.x][enemy.y] = '*';
        }
    }

    if (enemy.name == "Striker" && enemy.ltr)
    {
        if (enemy.x + 1 == spaceship.x && (enemy.y == spaceship.y || enemy.y + 1 == spaceship.y))
        {
            spaceship.heal--;
            enemy.x--;
        }
        else
        {
            enemy.x--;
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 2][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
    }

    if (enemy.name == "Striker" && !enemy.ltr)
    {
        if (enemy.x + 1 == spaceship.x && (enemy.y == spaceship.y || enemy.y - 1 == spaceship.y))
        {
            spaceship.heal--;
            enemy.x--;
        }
        else
        {
            enemy.x--;
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 2][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
    }

    if (enemy.name == "Wraith" && enemy.ltr)
    {
        if (enemy.x + 2 == spaceship.x && (enemy.y == spaceship.y || enemy.y + 1 == spaceship.y || enemy.y + 2 == spaceship.y))
        {
            spaceship.heal--;
            enemy.x--;
        }
        else
        {
            enemy.x--;
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 3][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
    }

    if (enemy.name == "Wraith" && !enemy.ltr)
    {
        if (enemy.x + 2 == spaceship.x && (enemy.y == spaceship.y || enemy.y - 1 == spaceship.y || enemy.y - 2 == spaceship.y))
        {
            spaceship.heal--;
            enemy.x--;
        }
        else
        {
            enemy.x--;
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 3][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
    }

    if (enemy.name == "Banshee" && enemy.ltr)
    {
        if (enemy.x + 3 == spaceship.x && (enemy.y == spaceship.y || enemy.y + 1 == spaceship.y || enemy.y + 2 == spaceship.y || enemy.y + 3 == spaceship.y))
        {
            spaceship.heal--;
            enemy.x--;
        }
        else
        {
            enemy.x--;
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 4][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
    }

    if (enemy.name == "Banshee" && !enemy.ltr)
    {
        if (enemy.x + 3 == spaceship.x && (enemy.y == spaceship.y || enemy.y - 1 == spaceship.y || enemy.y - 2 == spaceship.y || enemy.y - 3 == spaceship.y))
        {
            spaceship.heal--;
            enemy.x--;
        }
        else
        {
            enemy.x--;
            for (int i = 0; i < mapInfo.size; i++)
            {

                if (space[enemy.x][i] == '*')
                {
                    space[enemy.x + 4][i] = '*';
                    space[enemy.x][i] = ' ';
                }
            }
            enemy.x++;
        }
    }
}

int stringToInt(std::string txt)
{
    int num = 0;
    for (int i = 0; i < txt.size(); i++)
    {
        if (isdigit(txt[i]))
            num = num * 10 + (txt[i] - '0');
        else
        {
            std::cerr << "invalid";
            return 0;
        }
    }
    return num;
}

// to show win popup
void Win(std::vector<std::vector<char>> &space, Spaceship &spaceship, Enemy &enemy, int &CurrentPoint, MapInfo &mapInfo, std::vector<Bullet> &bullet)
{

    system("CLS");
    std::cout << R"( !
       !
       ^
      / \
     /___\
    |=   =|
    |     |
    |     |
    |     |
    |     |
    |     |
    |     |
    |     |
    |     |
    |     |
   /|##!##|\
  / |##!##| \
 /  |##!##|  \
|  / ^ | ^ \  |
| /  ( | )  \ |
|/   ( | )   \|
    ((   ))
   ((  :  ))
   ((  :  ))
    ((   ))
     (( ))
      ( )
       .
       .
       .)" << '\n';
    std::cout << "you won\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "do you want continue(1 : yes , 0 : no)?\n";
    int YN;
    do
    {
        std::cin >> YN;
        if (YN == 1)
        {

            std::cout << "enter a new total point  : ";
            std::cin >> mapInfo.point;
            SaveGame(space, spaceship, enemy, CurrentPoint, mapInfo, bullet);
            GenerateGame(2);
        }
        else if (YN == 0)
        {
            std::ofstream("GameInfo.txt");
            SatrtMenu();
        }
        else
        {
            std::cout << "invalid input" << '\n';
        }
    } while (YN != 1 && YN != 0);
}

// to show lose popup
void Lose()
{

    system("CLS");
    std::cout << "you faild\n";
    std::cout << '\n'
              << R"(     
    _.-^^---....,,--       
 _--                  --_  
<                        >)
|                         | 
 \._                   _./  
    ```--. . , ; .--'''       
          | |   |             
       .-=||  | |=-.   
       `-=#$%&%$#=-'   
          | ;  :|     
 _____.,-#%&$@%#&#~,._____)";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::ofstream("GameInfo.txt");
    SatrtMenu();
}
