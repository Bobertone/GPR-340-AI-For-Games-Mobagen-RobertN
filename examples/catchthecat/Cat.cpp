#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <unordered_map>
#include <queue>
#include <iostream>

// dynamic queue of points
std::queue<Point2D> frontier;

//std::vector<Point2D> points;
// give current point, get visited
std::unordered_map<Point2D, bool> visited;
// give current point, get from point
std::unordered_map<Point2D, Point2D> fromPath;
//give current point, get distance from cat
std::unordered_map<Point2D, int> distance;
Point2D nearestEdge;

Point2D Cat::Move(World* world)
{
  Agent::ResetData();
  Point2D const END_GOAL = Agent::BreadthFirstSearch(world);
  std::vector<Point2D> const PATH = Agent::FindPath(world,END_GOAL);
  return PATH[PATH.size()-1];
}