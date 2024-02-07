#include<iostream>


void SatrtMenue() ;
int MapSize() ;
void GenerateSpace() ;
void Map(int& size , char** space ) ;

//to hold our spaceship horizontal and vertical location and it's heal
struct Spaceship{
    int x ;
    int y ;
    int heal ;
};




int main(){

GenerateSpace() ;

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
    //NewGame() ;
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



int MapSize(){

std::cout<<"enter the size of map(n x n) :" ;
int size ;
std::cin>>size ;
return size ;

}



void GenerateSpace(){
int size = MapSize() ;
 char** space = new char*[size] ;
for(int i = 0 ; i<size ; i++){
    for(int j = 0 ; j<size ; j++){
        space[i][j] = ' ' ;
    }
}

//Space() ;
Map(size , space) ;

}




// to make map
void Map (int& size , char** space ){



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


