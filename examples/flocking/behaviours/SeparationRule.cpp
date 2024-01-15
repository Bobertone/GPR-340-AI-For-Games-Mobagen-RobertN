#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();
  Vector2f diffVector = Vector2f::zero();
  Vector2f invVector = Vector2f::zero();
  Vector2f sumVector = Vector2f::zero();
  float closeCount = 0;
  float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  if(!neighborhood.empty())
  {
    for(int i = 0; i < neighborhood.size(); i++)
    {
      //if in radius
      diffVector = boid -> getPosition() - neighborhood[i] -> getPosition();
      auto distance = diffVector.getMagnitude();
      if(distance < desiredDistance)
      {
        closeCount++;
        separatingForce = (diffVector/diffVector.getMagnitude());
        //Vector2f hat = (diffVector/diffVector.getMagnitude())/(diffVector.getMagnitude()/desiredDistance);
        //auto oppositeDir = diffVector.normalized();
        //invVector = Vector2f (1,1)/(diffVector);
        //accVector += oppositeDir/distance;
        //accVector += distance/(abs(distance));
        sumVector += separatingForce;
      }
    }
//    if(closeCount>0)
//    {
//      accVector /= closeCount;
//    }
  }
  //accVector = Vector2f::normalized(accVector);

  return sumVector;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
