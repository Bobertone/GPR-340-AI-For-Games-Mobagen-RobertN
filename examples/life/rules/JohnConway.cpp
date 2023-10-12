#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world)
{
  for(int y = 0; y < world.SideSize(); y++)
  {
    for(int x = 0; x < world.SideSize(); x++)
    {
      bool isAlive = world.Get({x,y});
      int neighbors = CountNeighbors(world, {x,y});

      world.SetNext({x,y},isAlive);

      if(isAlive)
      {
        //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
        if(neighbors<2){ world.SetNext({x,y},false);}
        //Any live cell with two or three live neighbours lives on to the next generation.
        if(neighbors==2||neighbors==3){world.SetNext({x,y},true);}
        //if(neighbors==3){world.SetNext({x,y},true);}
        //Any live cell with more than three live neighbours dies, as if by overpopulation.
        if(neighbors>3){world.SetNext({x,y},false);}
      }
      else
      {
        //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        if(neighbors==3){world.SetNext({x,y},true);}
      }
    }
  }

}

int JohnConway::CountNeighbors(World& w, Point2D p)
{
  /*
  int neighbors = 0;
  for(int y=-1; y<=1; y++)
  {
    for(int x=-1; x<=1; x++)
    {
      if(x!=0&&y!=0)
      {
        if(w.Get({p.x+x,p.y+y})){
          neighbors++;
        }
      }
    }
  }
  return neighbors;
  */
  return w.Get(p.Up())+w.Get(p.Up().Left())+w.Get(p.Up().Right())         //top row
         +w.Get(p.Left())+w.Get(p.Right())                                      //middle row
         +w.Get(p.Down())+w.Get(p.Down().Left())+w.Get(p.Down().Right()); //bottom row
}
