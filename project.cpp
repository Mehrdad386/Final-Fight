#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include <thread>
#include <chrono>
#include<fstream>
#include<sstream>

//the colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"



//to hold our spaceship horizontal and vertical location and it's heal
struct Spaceship{
    int x ;
    int y ;
    int heal ;
};

//to hold map's information
struct MapInfo{
    int size ;
    int point ;
} ;


struct Enemy{
std::string name ;
int heal ; 
int point ;
int x ;
int y ;
bool ltr ;
};




void SatrtMenue() ; //to make start menue
void Puase() ; //to show pause menue
void Guidence() ; //to guide user to play
void ExitGame() ; //to exit game
MapInfo MapSize() ; //to take map size and point from user
void GenerateGame() ; //to generate game
void RunGame(MapInfo& mapInfo , Spaceship& spaceship , Enemy& enemy , int& CurrentPoint ,std::vector<std::vector<char>>& space) ; //to run game
void Space (int& size , std::vector<std::vector<char>>& space ,Spaceship& spaceship ,Enemy& enemy) ; //to give the first position to spaceships
void Map(MapInfo mapInfo, std::vector<std::vector<char>>& space, int& heal , int& CurrentPoint) ; //to generate map
int Dart(int& size, std::vector<std::vector<char>>& space , Enemy& enemy) ; //to make Dart spaceship and return its y
int Striker(int& size, std::vector<std::vector<char>>& space, Enemy& enemy) ; //to make Striker spaceship and return its y
int Wraith(int& size, std::vector<std::vector<char>>& space, Enemy& enemy) ; //to make Wraith spaceship and return its y
int Banshee(int& size, std::vector<std::vector<char>>& space, Enemy& enemy) ; //to make Banshee spaceship and return its y
void Mover(Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo , int& CurrentPoint ) ; //to move spaceships
void MoveEnemy (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo) ; //to move enemy
void Attack (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo , int& CurrentPoint) ; //to do attack action
void Right (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo, int& CurrentPoint) ; //to do right action
void Left (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo, int& CurrentPoint) ; //to dp left action
void DestroyEnemy(std::vector<std::vector<char>>& space , MapInfo& mapInfo ) ; // to destroy enemy
void InsertEnemy(int& size , std::vector<std::vector<char>>& space ,Spaceship& spaceship ,Enemy& enemy) ; // to insert enemy in map
void Damage(Spaceship& spaceship , std::vector<std::vector<char>>& space , Enemy& enemy , MapInfo& mapInfo ) ; //to decrease our heal when the spaceships are in collision
void SaveGame(std::vector<std::vector<char>>& space , Spaceship& spaceship , Enemy& enemy , int& CurrentPoint , MapInfo& mapInfo) ; //to save game in a textfile
void LoadGame(std::vector<std::vector<char>>& space , Spaceship& spaceship , Enemy& enemy , int& CurrentPoint , MapInfo& mapInfo) ; //to load game from aa textfile

int main(){

SatrtMenue() ;

return 0 ;

}

//to show the menue to user and  ask how he wants to play
void SatrtMenue(){
system ("CLS") ;
std::cout<<"1- Start game"<<'\n' ;
std::cout<<"2- Load game"<<'\n' ;
std::cout<<"3- Guidence"<<'\n' ;
std::cout<<"4- Exit game"<<'\n' ;
int choice ;
do{
std::cin>>choice ;
switch (choice)
{
case 1 :
    GenerateGame() ;
    break;
case 2 :
    //LoadGame() ;
    break ;
case 3 :
    Guidence() ;
    break;
case 4 :
    ExitGame() ;
    break ;

default:
std::cout<<"invalid choice"<<'\n' ;
    break;
}
}while(choice != 1 && choice != 2 && choice != 3 && choice != 4 ) ;

}



//to save game in a text file
void SaveGame(std::vector<std::vector<char>>& space , Spaceship& spaceship , Enemy& enemy , int& CurrentPoint , MapInfo& mapInfo){

std::ofstream Save ;

Save.open("GameInfo.txt" ,  std::ios::out) ;

if(Save.is_open()){
Save<<spaceship.heal<<' '<<spaceship.x<<' '<<spaceship.y<<'\n' ;

Save<<enemy.name<<' '<<enemy.point<<' '<<enemy.heal<<' '<<enemy.ltr<<' '<<enemy.x<<' '<<enemy.y<<'\n' ;

Save<<mapInfo.size<<' '<<mapInfo.point<<'\n' ;

Save<<CurrentPoint<<'\n' ;

// for(int i = 0 ; i<mapInfo.size ; i++){
//     for(int j = 0 ; j<mapInfo.size ; j++){
//         Save<<space[i][j]<<' ' ;
//     }
// }

}
else{
    std::cerr<<"cant open the file\n" ;
}



}



// to load game from textfile
void LoadGame(std::vector<std::vector<char>>& space , Spaceship& spaceship , Enemy& enemy , int& CurrentPoint , MapInfo& mapInfo){

std::ifstream Load ;
Load.open("GameInfo.txt" , std::ios::out) ;
std::ofstream file("GameInfo.txt");



}







//to show puase menue
void Puase(MapInfo& mapInfo , Spaceship& spaceship , Enemy& enemy , int& CurrentPoint ,std::vector<std::vector<char>>& space){
    system ("CLs") ;
    std::cout<<"1- Resume game"<<'\n' ;
    std::cout<<"2 - Save and Leave game"<<'\n' ;
    int option ;
    do{
    std::cin>>option ;
    switch (option)
    {
    case 1 :
    Map(mapInfo , space, spaceship.heal , CurrentPoint);
    RunGame(mapInfo , spaceship , enemy , CurrentPoint , space) ;
        break;
    case 2 :
    SaveGame (space , spaceship , enemy , CurrentPoint , mapInfo) ;
    SatrtMenue() ;
        break;
    default:
    std::cerr<<"invalid input"<<'\n' ;
        break;
    }
    }while(option != 1 && option != 2) ;
}


//to guide user to play
void Guidence(){

std::cout<<"W : shoot straight"<<'\n' ;
std::cout<<"D : move rigth and shoot"<<'\n' ;
std::cout<<"A : move left and shoot\n" ;
std::cout<<"P : puse game"<<'\n' ;
int leave ;
do{
std::cout<<"enter 0 to leave\n" ;
std::cin>>leave ;
if(leave == 0)
    SatrtMenue() ;
else
    std::cout<<"invalid input\n" ;
}while (leave !=0) ;



}



//to exit game
void ExitGame(){
system("cls") ;
std::cout<<"are you sure you want to exit(1 : yes , 0 : no )?" ;
int sure ;
std::cin>>sure ;
if(sure== 1)
    exit(0) ;  
else if(sure == 0)
    SatrtMenue() ;
else
    std::cout<<"invalid input"<<'\n' ;

}








//to take size of the map from user
MapInfo MapSize(){

MapInfo mapInfo ;
do{
std::cout<<"enter the size of map(n x n) :"<<'\n' ;
std::cout<<"enter 0 if you want to leave"<<'\n' ;
std::cin>>mapInfo.size ;
    if(mapInfo.size<15 && mapInfo.size != 0){
        std::cout<<"the size of the map at least is 15"<<'\n' ;
    }
    else if(mapInfo.size == 0){
        SatrtMenue() ;
        break;
    }
    else if(mapInfo.size>=15){
        std::cout<<"how many points you want to achive"<<'\n' ;
        std::cin>>mapInfo.point ;
        break;
    }
}while(mapInfo.size<15) ;

return mapInfo ;

}


// to run the game
void GenerateGame(){

MapInfo mapInfo = MapSize() ; //size of the map

Spaceship spaceship ;
spaceship.heal = 3 ;

std::vector<std::vector<char>> space(mapInfo.size, std::vector<char>(mapInfo.size, ' ')); //to create empty spaces in map

Enemy enemy ;

int CurrentPoint ;

SaveGame (space , spaceship , enemy , CurrentPoint , mapInfo) ;

Space(mapInfo.size , space , spaceship , enemy) ;

Map(mapInfo , space, spaceship.heal , CurrentPoint) ;

RunGame(mapInfo , spaceship , enemy , CurrentPoint , space) ;

}



//to run game
void RunGame(MapInfo& mapInfo , Spaceship& spaceship , Enemy& enemy , int& CurrentPoint ,std::vector<std::vector<char>>& space){


while(CurrentPoint<mapInfo.point){
    if(spaceship.heal <1){
        break;
    }
Mover(spaceship , enemy , space , mapInfo , CurrentPoint) ;
if(enemy.heal == 0){
    CurrentPoint += enemy.point ;
    DestroyEnemy(space , mapInfo) ;
    InsertEnemy(mapInfo.size , space , spaceship , enemy) ;
    Map(mapInfo , space, spaceship.heal , CurrentPoint);

}
}
if(spaceship.heal<1){
    system("CLS") ;
    std::cout<<"you faild\n" ;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    SatrtMenue() ;
}
else{
    system("CLS") ;
    std::cout<<"you won\n" ;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"do you want continue(1 : yes , 0 : no)?\n" ;
    int YN ;
    std::cin>>YN ;
    if(YN== 1){
         //LoadGame() ;
    }
    else if(YN==0){
         SatrtMenue() ;
}
}

}




//to give the first position to the spaceships
void Space (int& size , std::vector<std::vector<char>>& space ,Spaceship& spaceship ,Enemy& enemy){

spaceship.x = size -1 ;
spaceship.y = static_cast<int>(size/2) -1 ;
space[spaceship.x][spaceship.y] = '#';
InsertEnemy(size , space , spaceship , enemy) ;

}


//to create enemy
void InsertEnemy(int& size , std::vector<std::vector<char>>& space ,Spaceship& spaceship ,Enemy& enemy){

srand(time(0)) ;
int RandomEnemy = rand()%4;
switch (RandomEnemy)
{
case 0 :
   enemy.name = "Dart" ;
   enemy.point = 2 ;
   enemy.x = 0 ;
   enemy.y = Dart(size , space , enemy) ;
   enemy.heal = 1 ;
    break;
case 1 :
    enemy.name = "Striker" ;
    enemy.point = 8 ;
    enemy.x = 0 ;
    enemy.y = Striker(size , space , enemy) ;
    enemy.heal = 2 ;
    break;
case 2 :
    enemy.name = "Wraith" ;
    enemy.point = 18 ;
    enemy.x = 0 ;
    enemy.y = Wraith(size , space , enemy) ;
    enemy.heal = 4 ;
    break;
case 3 :
    enemy.name = "Banshee" ;
    enemy.point = 32 ;
    enemy.x = 0 ;
    enemy.y = Banshee(size , space , enemy) ;
    enemy.heal = 6 ;
    break;

}



}






// to make map
void Map(MapInfo mapInfo , std::vector<std::vector<char>>& space, int& heal , int& CurrentPoint){

system ("CLS"); //to clear the screen

if(mapInfo.size>=15){
std::cout<<"your heal : "<<heal<<'\t' ;
std::cout<<"size of the map : "<<mapInfo.size<<" x "<<mapInfo.size<<'\t' ;
std::cout<<"your current point : "<<CurrentPoint<<'\t' ;
std::cout<<"pause(enter p)"<<'\n' ;


for(int i =0 ;i<mapInfo.size ; i++){

 for(int j= 0 ;j<mapInfo.size ; j++){
     std::cout<<" ---";
 }
     std::cout<<'\n';
 for(int k =0; k<=mapInfo.size ; k++){
    if(k==mapInfo.size)
    std::cout<<"|" ;
    else
	std::cout<<"|"<<' '<<space[i][k]<<' ' ;
}

std::cout<<'\n' ;

}

for(int i = 0 ; i<mapInfo.size ; i++)
std::cout<<" ---";

std::cout<<'\n' ;

    
}
}
//to make Dart spaceship and return its position
int Dart(int& size, std::vector<std::vector<char>>& space, Enemy& enemy){

srand(time(0)) ;
int y = rand()%size ;
space[0][y] = '*' ;
enemy.ltr = true ;
return y ;

}




//to make Striker spaceship and return its position
int Striker(int& size, std::vector<std::vector<char>>& space, Enemy& enemy){

srand(time(0)) ;
int y = rand()%size ;
if(y==size-1){
space[0][y] = '*' ;
space[0][y-1] = '*' ;
space[1][y] = '*' ;
space[1][y-1] = '*' ;
enemy.ltr = false ;
}
else{
space[0][y] = '*' ;
space[0][y+1] = '*' ;
space[1][y] = '*' ;
space[1][y+1] = '*' ;
enemy.ltr = true ;

}

return y ;
}



//to make Wraith spaceship and return its position
int Wraith(int& size, std::vector<std::vector<char>>& space, Enemy& enemy){

srand(time(0)) ;
int y = rand()%size ;
if(y==size-1 || y==size-2){
space[0][y] = '*' ;
space[0][y-1] = '*' ;
space[0][y-2] = '*' ;
space[1][y] = '*' ;
space[1][y-1] = '*' ;
space[1][y-2] = '*' ;
space[2][y] = '*' ;
space[2][y-1] = '*' ;
space[2][y-2] = '*' ;
enemy.ltr = false ;
}
else{
space[0][y] = '*' ;
space[0][y+1] = '*' ;
space[0][y+2] = '*' ;
space[1][y] = '*' ;
space[1][y+1] = '*' ;
space[1][y+2] = '*' ;
space[2][y] = '*' ;
space[2][y+1] = '*' ;
space[2][y+2] = '*' ;
enemy.ltr = true ;

}
return y ;

}

//to make Banshee spaceship and return its position
int Banshee(int& size, std::vector<std::vector<char>>& space, Enemy& enemy){


srand(time(0)) ;
int y = rand()%size ;
if(y==size-1 || y==size-2 || y==size-3){
space[0][y] = '*' ;
space[0][y-1] = '*' ;
space[0][y-2] = '*' ;
space[0][y-3] = '*' ;
space[1][y] = '*' ;
space[1][y-1] = '*' ;
space[1][y-2] = '*' ;
space[1][y-3] = '*' ;
space[2][y] = '*' ;
space[2][y-1] = '*' ;
space[2][y-2] = '*' ;
space[2][y-3] = '*' ;
space[3][y] = '*' ;
space[3][y-1] = '*' ;
space[3][y-2] = '*' ;
space[3][y-3] = '*' ;
enemy.ltr = false ;
}
else{
space[0][y] = '*' ;
space[0][y+1] = '*' ;
space[0][y+2] = '*' ;
space[0][y+3] = '*' ;
space[1][y] = '*' ;
space[1][y+1] = '*' ;
space[1][y+2] = '*' ;
space[1][y+3] = '*' ;
space[2][y] = '*' ;
space[2][y+1] = '*' ;
space[2][y+2] = '*' ;
space[2][y+3] = '*' ;
space[3][y] = '*' ;
space[3][y+1] = '*' ;
space[3][y+2] = '*' ;
space[3][y+3] = '*' ;
enemy.ltr = true ;
}
return y ;

}



//to move  spaceships
void Mover(Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo , int& CurrentPoint){
char move ;
std::cin>>move ;
switch (move)
{
case 'w' :
    Attack(spaceship , enemy , space , mapInfo , CurrentPoint) ;
    break;
case 'd':
    Right(spaceship , enemy , space , mapInfo , CurrentPoint) ;
    break;
case 'a' :
    Left(spaceship , enemy , space , mapInfo , CurrentPoint) ;
    break;
case 'p' :
    Puase(mapInfo , spaceship , enemy , CurrentPoint , space) ;
    break;

default:
    std::cerr<<"invalid input"<<'\n' ;
    break;
}

}



//to move enemy
void MoveEnemy (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo){


if(enemy.name == "Dart"){
    if(enemy.x < mapInfo.size - 2){
        space[enemy.x][enemy.y] = ' ' ;
        enemy.x++ ;
        space[enemy.x][enemy.y] = '*' ;
    }
    else if(enemy.x == mapInfo.size-2){
        Damage(spaceship , space , enemy , mapInfo ) ;
    }
    else if (enemy.x == mapInfo.size-1){
        DestroyEnemy(space , mapInfo) ;
        InsertEnemy(mapInfo.size , space , spaceship , enemy) ;
        //Map(mapInfo , space, spaceship.heal , CurrentPoint);
    }
}



if(enemy.name =="Striker"){
    if(enemy.x < mapInfo.size - 3){
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+2][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
    else if(enemy.x == mapInfo.size-3){
        Damage(spaceship , space , enemy , mapInfo ) ;
    }
        else if (enemy.x == mapInfo.size-2){
        DestroyEnemy(space , mapInfo) ;
        InsertEnemy(mapInfo.size , space , spaceship , enemy) ;
        //Map(mapInfo , space, spaceship.heal , CurrentPoint);
    }

}



if(enemy.name =="Wraith"){
    if(enemy.x < mapInfo.size - 4){
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+3][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
    else if(enemy.x == mapInfo.size-4){
        Damage(spaceship , space , enemy , mapInfo ) ;
    }
        else if (enemy.x == mapInfo.size-3){
        DestroyEnemy(space , mapInfo) ;
        InsertEnemy(mapInfo.size , space , spaceship , enemy) ;
        //Map(mapInfo , space, spaceship.heal , CurrentPoint);
    }
}



if(enemy.name =="Banshee"){
    if(enemy.x < mapInfo.size - 5){
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+4][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
    else if(enemy.x == mapInfo.size-5){
        Damage(spaceship , space , enemy , mapInfo ) ;
    }
        else if (enemy.x == mapInfo.size-4){
        DestroyEnemy(space , mapInfo) ;
        InsertEnemy(mapInfo.size , space , spaceship , enemy) ;
        //Map(mapInfo , space, spaceship.heal , CurrentPoint);
    }
}


}

//to do attack action
void Attack (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo , int& CurrentPoint){

for(int i = 1; i<mapInfo.size ; i++){
        if(space[spaceship.x-i][spaceship.y]==' '){
            space[spaceship.x-i][spaceship.y] ='^' ;
            Map(mapInfo, space, spaceship.heal , CurrentPoint) ;
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
            space[spaceship.x-i][spaceship.y] =' ' ;
        }

        if(space[spaceship.x-i][spaceship.y]=='*'){
            enemy.heal-- ;
            space[spaceship.x-i-1][spaceship.y]==' ' ;
            std::cout<<enemy.heal ;
            break ;
        }       
    }

    MoveEnemy(spaceship , enemy , space , mapInfo) ;
    Map(mapInfo, space, spaceship.heal , CurrentPoint) ;

}




//to do right action
void Right (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo , int& CurrentPoint){

if(spaceship.y != mapInfo.size-1){
space[spaceship.x][spaceship.y]= ' ' ;
spaceship.y++ ;
space[spaceship.x][spaceship.y]= '#' ;
Attack(spaceship , enemy , space , mapInfo , CurrentPoint) ;

}
}



//to do left action
void Left (Spaceship& spaceship , Enemy& enemy ,std::vector<std::vector<char>>& space , MapInfo& mapInfo , int& CurrentPoint){
if(spaceship.y != 0 ){
space[spaceship.x][spaceship.y]= ' ' ;
spaceship.y-- ;
space[spaceship.x][spaceship.y]= '#' ;
Attack(spaceship , enemy , space , mapInfo , CurrentPoint) ;
}

}

//to destroy enemy
void DestroyEnemy(std::vector<std::vector<char>>& space , MapInfo& mapInfo){

for(int i = 0 ; i<mapInfo.size ; i++){
    for(int j = 0 ; j<mapInfo.size ; j++){
        if(space[i][j] == '*')
             space[i][j] = ' ' ;
    }
}

}




//to decrease our heal when the spaceships are in collision
void Damage(Spaceship& spaceship , std::vector<std::vector<char>>& space , Enemy& enemy , MapInfo& mapInfo ){
enemy.x++ ;
if(enemy.name == "Dart"){
    if(enemy.x == spaceship.x && enemy.y == spaceship.y){
        spaceship.heal-- ;
        enemy.x--;

    }else{
        enemy.x-- ;
        space[enemy.x][enemy.y] = ' ' ;
        enemy.x++ ;
        space[enemy.x][enemy.y] = '*' ;
    }

}

if(enemy.name == "Striker" && enemy.ltr){
    if(enemy.x + 1 == spaceship.x && (enemy.y==spaceship.y|| enemy.y +1 == spaceship.y)){
        spaceship.heal-- ;
        enemy.x--;

    }else{
        enemy.x--;
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+2][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
}

if(enemy.name == "Striker" && !enemy.ltr){
    if(enemy.x + 1 == spaceship.x && (enemy.y==spaceship.y|| enemy.y -1 == spaceship.y)){
        std::cout<<"efjiefjeif" ;
        spaceship.heal-- ;
        enemy.x--;

    }else{
        enemy.x--;
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+2][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
}

if(enemy.name == "Wraith" && enemy.ltr){
    if(enemy.x + 2 == spaceship.x && (enemy.y==spaceship.y|| enemy.y +1 == spaceship.y || enemy.y +2 == spaceship.y)){
            spaceship.heal-- ;
            enemy.x--;
    }else{
    enemy.x--;
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+3][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
}

if(enemy.name == "Wraith" && !enemy.ltr){
    if(enemy.x + 2 == spaceship.x && (enemy.y==spaceship.y|| enemy.y -1 == spaceship.y || enemy.y -2 == spaceship.y)){
            spaceship.heal-- ;
            enemy.x--;
    }else{
    enemy.x--;
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+3][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
}


if(enemy.name == "Banshee" && enemy.ltr){
    if(enemy.x + 3 == spaceship.x && (enemy.y==spaceship.y|| enemy.y +1 == spaceship.y || enemy.y +2 == spaceship.y || enemy.y + 3 == spaceship.y)){
        spaceship.heal-- ;
        enemy.x--;
    }else{
    enemy.x--;
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+4][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
}

if(enemy.name == "Banshee" && !enemy.ltr){
    if(enemy.x + 3 == spaceship.x && (enemy.y==spaceship.y|| enemy.y -1 == spaceship.y || enemy.y -2 == spaceship.y || enemy.y - 3 == spaceship.y)){
        spaceship.heal-- ;
        enemy.x--;
    }else{
    enemy.x--;
    for(int i = 0 ; i<mapInfo.size ; i++){
        
    if(space[enemy.x][i] =='*'){
        space[enemy.x+4][i] ='*' ;
        space[enemy.x][i] = ' ' ;
    }

    }
    enemy.x++ ;
    }
}


}


