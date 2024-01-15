#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  // start the producer-consumer loop with the cat position
  frontier.emplace(catPos);

  // we are following the breadth first search
  while (!frontier.empty()) {
    // consume one element from the queue
    auto current = frontier.front(); // get the head of the queue
    frontier.pop(); // remove the head of the queue

    // todo: implement this below:
    // list all not visited neighbors, not the cat, and not blocked
    // iterate over the list
    // if one element is an exit, store in on the var borderExit and break the producer-consumer loop
    // else add it to the queue to be visited and store the current as the camefrom of the neighbor
    // tip: to check if it is border: if (the abs of x) or (abs of y) is w->getWorldSideSize()/2
  }

  // build the path
  if(borderExit!=Point2D::INFINITE){
    vector<Point2D> path;
    Point2D curr = borderExit;
    while(borderExit!=catPos) { // while we do not arrive at the cat
      path.push_back(borderExit); // fill the path
      borderExit = cameFrom[borderExit]; // iterate to the next camefrom
    }
    return path;
  }
  // todo: else return random movement
    vector<Point2D> path;
    path.push_back(RandDir(w));
    return path;
}

// get the current from frontier
// remove the current from frontierset
// mark current as visited
// getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
// iterate over the neighs:
// for every neighbor set the cameFrom
// enqueue the neighbors to frontier and frontierset
// do this up to find a visitable border and break the loop

// if the border is not infinity, build the path from border to the cat using the camefrom map
// if there isnt a reachable border, just return empty vector
// if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move

void Agent::ResetData()
{
  while (!frontier.empty())
  {
    frontier.pop();
  }
  visited.clear();
  cameFrom.clear();
  distance.clear();
  nearestEdge = Point2D(0,0);
}

Point2D Agent::BreadthFirstSearch(World* world)
{
  frontier.push(world->getCat());

  distance[world->getCat()] = 0;
  while(!frontier.empty())
  {
    GetOpenNeighbors(world);
    visited[frontier.front()] = true;
    //points.push_back(frontier.front());
    frontier.pop();
    if(nearestEdge != Point2D(0,0)){ return nearestEdge;}
  }
  return RandDir(world);
}

void Agent::GetOpenNeighbors(World* world)
{
  Point2D point = world->E(frontier.front());
  printf("E(%d,%d)\n",point.x,point.y);
  std::cout << "("<< point.x << ","<< point.y << ")"<< "\n";
  CheckPoint(world, point);
  point = world->SE(frontier.front());
  printf("SE(%d,%d)\n",point.x,point.y);
  std::cout << "("<< point.x << ","<< point.y << ")"<< "\n";
  CheckPoint(world, point);
  point = world->SW(frontier.front());
  printf("SW(%d,%d)\n",point.x,point.y);
  std::cout << "("<< point.x << ","<< point.y << ")"<< "\n";
  CheckPoint(world, point);
  point = world->W(frontier.front());
  printf("W(%d,%d)\n",point.x,point.y);
  std::cout << "("<< point.x << ","<< point.y << ")"<< "\n";
  CheckPoint(world, point);
  point = world->NW(frontier.front());
  printf("NW(%d,%d)\n",point.x,point.y);
  std::cout << "("<< point.x << ","<< point.y << ")"<< "\n";
  CheckPoint(world, point);
  point = world->NE(frontier.front());
  printf("NE(%d,%d)\n",point.x,point.y);
  std::cout << "("<< point.x << ","<< point.y << ")"<< "\n";
  CheckPoint(world, point);
}

void Agent::CheckPoint(World* world, Point2D point)
{
  if(!world->getContent(point)&&!visited[point])
  {
    cameFrom[point] = frontier.front();
    visited[point] = true;
    distance[point] = distance[frontier.front()] + 1;
    frontier.push(point);
    if(world->catWinsOnSpace(point)){ nearestEdge = point; }
    //printf("%d%d",fromPath[point].x,fromPath[point].y);
  }
}

std::vector<Point2D> Agent::FindPath(World* world, Point2D goal)
{
  Point2D temp = goal;
  std::vector<Point2D> path;
  while(temp!=world->getCat())
  {
    printf("(%d,%d)\n",temp.x,temp.y);
    path.push_back(temp);
    temp = cameFrom[temp];
  }
  return path;
}

Point2D Agent::RandDir(World* world)
{
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();

  switch (rand) {
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}