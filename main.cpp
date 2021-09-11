#include "./models/quadTree.hpp"
#include <iostream>
#include <string>
using namespace std;

void setFirstChild(Rectangle *firstsChild,int Row,int Column){
  int subWidth = Column/2;
  int subHeight = Row/2;
  int x = 0;
  int y = 0;

  firstsChild[0] = *new Rectangle(x+subWidth,y,subWidth,subHeight);
  firstsChild[1] = *new Rectangle(x,y,subWidth,subHeight);
  firstsChild[2] = *new Rectangle(x,y+subHeight,subWidth,subHeight);
  firstsChild[3] = *new Rectangle(x+subWidth,y+subHeight,subWidth,subHeight);


}
void setMap(char **matriz,int row,int column){
  for(size_t i =0;i<row;i++){
    string mapLine;
    cin>>mapLine;
    for(size_t j=0;j<column;j++){
      matriz[i][j] = mapLine[j];
    }
  }
}

int main(){
  int iterationCounts=0,
      peopleVelocityX=0,
      peopleVelocityY=0,
      jellyFishVelocityX=0,
      jellyFishVelocityY=0,
      Column=0,
      Row=0;

  cin>>iterationCounts;
  cin>>Row;
  cin>>Column;
  cin>>peopleVelocityX;
  cin>>peopleVelocityY;
  cin>>jellyFishVelocityX;
  cin>>jellyFishVelocityY;

  if( !Row || // row is less than 1
      !Column|| //column is less than 1
      peopleVelocityX<-1|| //people velocityX invalid
      peopleVelocityX>1|| 
      peopleVelocityY<-1||//peopleVelocityY invalid
      peopleVelocityY>1||
      jellyFishVelocityX<-1|| //jellyFishVelocityX invalid
      jellyFishVelocityX>1||
      jellyFishVelocityY<-1|| //jellyFishVelocityY invalid
      jellyFishVelocityY>1
      ){
    cout<<"NO VALIDO";
    return  -1;
  }

  char **matrizMap = new char*[Row];
  for (int i = 0; i < Row; ++i)
    matrizMap[i] = new char[Column];

  setMap(matrizMap,Row,Column);



  Rectangle *myRectangle = new Rectangle(0,0,Column,Row);
  QuadTree *map = new QuadTree(0,myRectangle); 
  map->clear();
  Rectangle *firstsChild = new Rectangle[4];
  setFirstChild(firstsChild, Row, Column);

  for(size_t i = 0; i<4;i++)
    map->insert(firstsChild[i]);

  return 0;
}
