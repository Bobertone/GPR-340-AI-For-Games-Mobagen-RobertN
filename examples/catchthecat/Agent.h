#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <queue>

class World;

struct node
{
  node();
  Point2D thisPos;
  Point2D fromPos;
  bool isOpen;
  int distance;
};

class Agent {
public:
  // dynamic queue of points
  std::queue<Point2D> frontier;
  // give current point, get visited
  std::unordered_map<Point2D, bool> visited;
  // give current point, get from point
  std::unordered_map<Point2D, Point2D> cameFrom;
//  //give current point, get distance from cat
  std::unordered_map<Point2D, int> distance;
  Point2D nearestEdge;

  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);

public:
  void ResetData();
  Point2D BreadthFirstSearch(World* world);
  Point2D FindExit(World* world);
  Point2D RandDir(World* world);
  std::vector<Point2D>  FindPath(World* world, Point2D goal);
  void GetOpenNeighbors(World* world);
  void CheckPoint(World* world, Point2D point);
};

#endif  // AGENT_H
