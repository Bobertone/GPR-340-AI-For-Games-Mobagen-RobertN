#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  if(!neighborhood.empty())
  {
    Vector2f avgPos = Vector2f (0,0);
    for(int i = 0; i < neighborhood.size(); i++)
    {
      avgPos += neighborhood[i] -> getPosition();
    }
    // find center of mass
    avgPos = avgPos / neighborhood.size();
    auto directionVector = avgPos - boid -> getPosition();
    return Vector2f::normalized(directionVector);
  }
  return Vector2f::zero();
}