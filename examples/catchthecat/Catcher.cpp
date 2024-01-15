#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  for (;;) {

    Agent::ResetData();
    Point2D const END_GOAL = Agent::BreadthFirstSearch(world);
    std::vector<Point2D> const PATH = Agent::FindPath(world,END_GOAL);
    return PATH[0];

//    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
//    auto cat = world->getCat();
//    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;


  }
}
