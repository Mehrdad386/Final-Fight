#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>

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



void SatrtMenue() ; //to make start menue
MapInfo MapSize() ; //to take map size and point from user
void RunGame() ; //to run game
void Space (int& size , std::vector<std::vector<char>>& space , int& x , int& y , int& EnemyHeal , int& EnemyPosition) ; //to give the first position to spaceships
void Map(int& size, std::vector<std::vector<char>>& space, int& heal) ; //to generate map
int Dart(int& size, std::vector<std::vector<char>>& space) ; //to make Dart spaceship and return its y
int Striker(int& size, std::vector<std::vector<char>>& space) ; //to make Striker spaceship and return its y
int Wraith(int& size, std::vector<std::vector<char>>& space) ; //to make Wraith spaceship and return its y
int Banshee(int& size, std::vector<std::vector<char>>& space) ; //to make Banshee spaceship and return its y






int main(){

SatrtMenue() ;

return 0 ;

}

//to show the menue to user and  ask how he wants to play
void SatrtMenue(){
std::cout<<"1- start game"<<'\n' ;
std::cout<<"2- continue game"<<'\n' ;
std::cout<<"3- exit"<<'\n' ;
int choice ;
std::cin>>choice ;

switch (choice)
{
case 1 :
    RunGame() ;
    break;
case 2 :
    //LoadGame() ;
    break ;
case 3 :
    //ExitGame() ;
    break ;

default:
std::cout<<"invalid choice"<<'\n' ;
    break;
}

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
void RunGame(){
MapInfo mapInfo = MapSize() ; //size of the map
Spaceship spaceship ;
spaceship.heal = 3 ;
std::vector<std::vector<char>> space(mapInfo.size, std::vector<char>(mapInfo.size, ' '));
int EnemyHeal ;
int EnemyPosition ;

Space(mapInfo.size , space , spaceship.x , spaceship.y , EnemyHeal , EnemyPosition) ;
Map(mapInfo.size, space, spaceship.heal);


}


//to give the first position to the spaceships
void Space (int& size , std::vector<std::vector<char>>& space , int& x , int& y , int& EnemyHeal , int& EnemyPosition){

srand(time(0)) ;
int RandomEnemy = rand()%4;
x = size -1 ;
y = static_cast<int>(size/2) -1 ;
space[x][y] = '#';
switch (RandomEnemy)
{
case 0 :
   EnemyPosition = Dart(size , space) ;
   EnemyHeal = 1 ;
    break;
    case 1 :
   EnemyPosition = Striker(size , space) ;
   EnemyHeal = 2 ;
    break;
    case 2 :
   EnemyPosition = Wraith(size , space) ;
   EnemyHeal = 4 ;
    break;
    case 3 :
   EnemyPosition = Banshee(size , space) ;
   EnemyHeal = 6 ;
    break;

}


}




// to make map
void Map(int& size, std::vector<std::vector<char>>& space, int& heal){

if(size>=15){
std::cout<<"your heal : "<<heal<<'\t' ;
std::cout<<"size of the map : "<<size<<" x "<<size<<'\t' ;
std::cout<<"pause(enter p)"<<'\n' ;


for(int i =0 ;i<size ; i++){

 for(int j= 0 ;j<size ; j++){
     std::cout<<" ---";
 }
     std::cout<<'\n';
 for(int k =0; k<=size ; k++){
    if(k==size)
    std::cout<<"|" ;
    else
	std::cout<<"|"<<' '<<space[i][k]<<' ' ;
}

std::cout<<'\n' ;

}

for(int i = 0 ; i<size ; i++)
std::cout<<" ---";

std::cout<<'\n' ;

    
}
}
//to make Dart spaceship and return its position
int Dart(int& size, std::vector<std::vector<char>>& space){

srand(time(0)) ;
int y = rand()%size ;
space[0][y] = '*' ;

return y ;

}




//to make Striker spaceship and return its position
int Striker(int& size, std::vector<std::vector<char>>& space){

srand(time(0)) ;
int y = rand()%size ;
if(y==size-1){
space[0][y] = '*' ;
space[0][y-1] = '*' ;
space[1][y] = '*' ;
space[1][y-1] = '*' ;
}
else{
space[0][y] = '*' ;
space[0][y+1] = '*' ;
space[1][y] = '*' ;
space[1][y+1] = '*' ;

}

return y ;
}



//to make Wraith spaceship and return its position
int Wraith(int& size, std::vector<std::vector<char>>& space){

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

}
return y ;

}

//to make Banshee spaceship and return its position
int Banshee(int& size, std::vector<std::vector<char>>& space){


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
}
return y ;

}