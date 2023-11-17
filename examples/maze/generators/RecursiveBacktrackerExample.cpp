#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <vector>
bool RecursiveBacktrackerExample::Step(World* w) {
  auto rStartp = randomStartPoint(w);
  if(stack.empty() && rStartp == Point2D{INT_MAX, INT_MAX} ){
    return false;
  }
  if(stack.empty())
  {
    stack.push_back(randomStartPoint(w));
    return true;
  }

  auto top = stack.back();
  std::vector<Point2D> neighbors;

  visited[top]  = true;
  w->SetNodeColor(top,Color::Red);

  neighbors = getVisitables(w,top);

  if(neighbors.empty())
  {
    stack.pop_back();
    w->SetNodeColor(top,Color::Black);
    return true;
  }else{
    auto neighbor = neighbors[Random::Range(0,neighbors.size()-1)];
    w->SetNodeColor(neighbor,Color::Green);
    auto lastPoint = top;
    stack.push_back(neighbor);
    top = stack.back();
    // TODO: break walls between neighbor and top
    if((top.x - lastPoint.x)>0){w->SetWest(top, false);}
    else if((top.x - lastPoint.x)<0){w->SetEast(top, false);}
    else if((top.y - lastPoint.y)<0){w->SetSouth(top, false);}
    else if((top.y - lastPoint.y)>0){w->SetNorth(top, false);}
  }

  //TODO: Choose random neighbor to visit and add it to the stack
//  if(neighbors.empty())
//    ; // backtrack
//  if()

  return true;
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
//might be bugged  Point2D()
  if(!visited[{p.x,p.y-1}]
      && p.y-1 >= -sideOver2)  {
    visitables.emplace_back(p.x,p.y-1);
  }
  if(!visited[{p.x+1,p.y}]
      && p.x+1 <= sideOver2)  {
    visitables.emplace_back(p.x+1,p.y);
  }
  if(!visited[{p.x,p.y+1}]
      && p.y+1 <= sideOver2)  {
    visitables.emplace_back(p.x,p.y+1);
  }
  if(!visited[{p.x-1,p.y}]
      && p.x-1 >= -sideOver2)  {
    visitables.emplace_back(p.x-1,p.y);
  }

  return visitables;
}


void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[Point2D(i,j)] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;
  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[{x,y}]) return {x, y};
  return {INT_MAX, INT_MAX};
}