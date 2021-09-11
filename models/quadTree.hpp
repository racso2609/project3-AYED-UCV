#include <iostream>
#ifndef __list__hpp__
#include "./list.hpp"
#endif
#ifndef __node__hpp__
#include "./node.hpp"
#endif
using namespace std;


class Rectangle{ 
  private:        
    double height;     
    double width;     
    int x,y;

  public:         
    Rectangle()         { 
      width = 1.0;        
      height = 1.0;
      x=0;
      y=0
    } 
    Rectangle(int a_x,int a_y,double a_width, double a_height) {  
      width= a_width;
      height= a_height;
      x=a_x;
      y = a_y;
    } 

    double getHeight(){   
      return height;      // Returns the value of the class member "height"
    }
    int getX(){
      return x;
    }
    int getY(){
      return y;
    }

    /*get the Area .*/
    double getWidth(){
      return width;
    }
    double getArea() const 
    { 
      return height*width;
    } 
    double getPerimeter() const
    {                     
      return 2*(width+height); 
    } 
};

class QuadTree{
  private:
    int 
      //MAX_OBJECTS=1000000000,
      //MAX_LEVELS=10000000000,
      level;
    list<Rectangle> objects;
    Rectangle *bounds;
    QuadTree nodes[];

  public:

    QuadTree(int plevel,Rectangle *pBound){
      level = plevel;
      bounds = pBound;
      nodes = new QuadTree[4];
    }
    QuadTree(){
      //level = 0;
      //bounds = new Rectangle(0,0,0,0);
      //nodes = new QuadTree[4]
    }
    void clear() {
      objects.clear();

      for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] != NULL) {
          nodes[i].clear();
          nodes[i] = NULL;
        }
      }
    }
    void split(){
      int subWidth = (int)(bounds->getWidth()/2);
      int subHeight = (int)(bounds->getHeight()/2);


      int x = bounds->getX();
      int y = bounds->getY();

      Rectangle *pBound = new Rectangle(x + subWidth, y, subWidth, subHeight);
      nodes[0] = new QuadTree(level+1, pBound);
      pBound = new Rectangle(x, y, subWidth, subHeight);
      nodes[1] = new QuadTree(level+1, pBound);
      pBound = new Rectangle(x, y + subHeight, subWidth, subHeight);
      nodes[2] = new QuadTree(level+1, pBound);
      pBound = new Rectangle(x + subWidth, y + subHeight, subWidth, subHeight);
      nodes[3] = new QuadTree(level+1,pBound );
    }
    int getIndex(Rectangle pRect) {
      int index = -1;
      double verticalMidpoint = bounds->getX() + (bounds->getWidth() / 2);
      double horizontalMidpoint = bounds->getY() + (bounds->getHeight() / 2);


      // Object can completely fit within the top quadrants
      bool topQuadrant = (pRect.getY() < horizontalMidpoint && pRect.getY() + pRect.getHeight() < horizontalMidpoint);
      // Object can completely fit within the bottom quadrants
      bool bottomQuadrant = (pRect.getY() > horizontalMidpoint);

      // Object can completely fit within the left quadrants
      if (pRect.getX() < verticalMidpoint && pRect.getX() + pRect.getWidth() < verticalMidpoint) {
        if (topQuadrant) {
          index = 1;
        }
        else if (bottomQuadrant) {
          index = 2;
        }
      }
      // Object can completely fit within the right quadrants
      else if (pRect.getX() > verticalMidpoint) {
        if (topQuadrant) {
          index = 0;
        }
        else if (bottomQuadrant) {
          index = 3;
        }
      }

      return index;
    }
    void insert(Rectangle pRect) {
      if (nodes[0] != NULL) {
        int index = getIndex(pRect);

        if (index != -1) {
          nodes[index].insert(pRect);

          return;
        }
      }

      objects.insert(pRect,objects.last());

      //if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
      if (nodes[0] == NULL) { 
        split(); 
      }

      int i = 0;
      node<Rectangle> *pValueNode = objects.first();
      while (i < objects.size()) {
        Rectangle pValue = pValueNode->info;
        int index = getIndex(pValue);
        if (index != -1) {
          nodes[index].insert(objects.del(pValueNode));
        }
        else {
          pValueNode = pValueNode->next;
          i++;
        }
      }
      //}
    }
    list<Rectangle> retrieve(list<Rectangle> returnObjects, Rectangle pRect) {
      int index = getIndex(pRect);
      if (index != -1 && nodes[0] != NULL) {
        nodes[index].retrieve(returnObjects, pRect);
      }

      returnObjects.concat(objects);

      return returnObjects;
    }
};
