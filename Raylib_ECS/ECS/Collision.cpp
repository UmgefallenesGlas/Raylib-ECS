#include "Collision.h"
#include <iostream>

void Collision::PointNearestRectanglePoint(Rectangle rect, Vector2 point, Vector2* nearest, Vector2* normal) {
    // get the closest point on the vertical sides
    float hValue = rect.x;
    float hNormal = -1;
    if (point.x > rect.x + rect.width)
    {
        hValue = rect.x + rect.width;
        hNormal = 1;
    }

    Vector2 vecToPoint = Vector2Subtract(Vector2{hValue, rect.y }, point);
    // get the dot product between the ray and the vector to the point
    float dotForPoint = Vector2DotProduct(Vector2{ 0, -1 }, vecToPoint);
    Vector2 nearestPoint = { hValue,0 };

    if (dotForPoint < 0)
        nearestPoint.y = rect.y;
    else if (dotForPoint >= rect.height)
        nearestPoint.y = rect.y + rect.height;
    else
        nearestPoint.y = rect.y + dotForPoint;

    // get the closest point on the horizontal sides
    float vValue = rect.y;
    float vNormal = -1;
    if (point.y > rect.y + rect.height)
    {
        vValue = rect.y + rect.height;
        vNormal = 1;
    }

    vecToPoint = Vector2Subtract(Vector2{ rect.x, vValue }, point);
    // get the dot product between the ray and the vector to the point
    dotForPoint = Vector2DotProduct(Vector2{ -1, 0 }, vecToPoint);
    *nearest = Vector2{ 0,vValue };

    if (dotForPoint < 0)
        nearest->x = rect.x;
    else if (dotForPoint >= rect.width)
        nearest->x = rect.x + rect.width;
    else
        nearest->x = rect.x + dotForPoint;

    if (Vector2LengthSqr(Vector2Subtract(point, nearestPoint)) < Vector2LengthSqr(Vector2Subtract(point, *nearest)))
    {
        *nearest = nearestPoint;

        if (normal)
        {
            normal->x = hNormal;
            normal->y = 0;
        }
    }
    else
    {
        if (normal)
        {
            normal->y = vNormal;
            normal->x = 0;
        }
    }
}

void Collision::MovingObjectCollision(Vector2 *newPosOrigin,Group collisionGroup, Manager& manager, Entity& obj)
{
    Vector2 intersectPoint[2] = {{-100,-100},{-100,-100}};
    Vector2 tempNewPosOrigin = *newPosOrigin;
    bool collided = false;
    int collisionCount = 0;
    for (auto& e : manager.entities) {
        if (e->hasGroup(collisionGroup) && e->isActive() == 1) {
            
            Vector2 hitPoint = { 
                -(obj.getComponent<TransformComponent>().width * obj.getComponent<TransformComponent>().scale),
                -(obj.getComponent<TransformComponent>().height * obj.getComponent<TransformComponent>().scale) };
            Vector2 hitNormal = { 0,0 };
            //std::cout << hitPoint.x << hitPoint.y << '\n';
            //std::cout << Vector2{ hitPoint.x - tempNewPosOrigin.x, hitPoint.y - tempNewPosOrigin.y }.x << "|" << Vector2{ hitPoint.x - tempNewPosOrigin.x, hitPoint.y - tempNewPosOrigin.y }.y << "\n";
            PointNearestRectanglePoint(e->getComponent<TransformComponent>().rectangle, tempNewPosOrigin, &hitPoint, &hitNormal);
            Vector2 vectorToHit = Vector2{ hitPoint.x - tempNewPosOrigin.x, hitPoint.y - tempNewPosOrigin.y };

            bool inside = Vector2LengthSqr(vectorToHit) < obj.getComponent<TransformComponent>().width * obj.getComponent<TransformComponent>().width;

            if (inside)
            {
                collided = true;
                intersectPoint[collisionCount++] = hitPoint;
                // normalize
                //vectorToHit = Vector2Normalize(vectorToHit);

                // get point that is deepest into the rectangle
                Vector2 projectedPoint = Vector2Add(tempNewPosOrigin, Vector2Scale(vectorToHit, obj.getComponent<TransformComponent>().width));


                // shift it to nearest
                Vector2 delta = { 0,0 };

                if (hitNormal.x != 0) {
                    delta.x = hitPoint.x - projectedPoint.x;
                    std::cout << "HITNORMAL: " << delta.x << "|" << hitPoint.x << projectedPoint.x << '\n';
                }
                if (hitNormal.y != 0) {
                    delta.y = hitPoint.y - projectedPoint.y;
                    std::cout << "HITNORMAL: " << delta.y << "|" << hitPoint.y << projectedPoint.y << '\n';

                }

                delta = Vector2Divide(delta, Vector2{
                    obj.getComponent<TransformComponent>().width * obj.getComponent<TransformComponent>().scale * 10 * 2.f,
                    obj.getComponent<TransformComponent>().width* obj.getComponent<TransformComponent>().scale * 10 * 2.f});
                std::cout << delta.x << "|" << delta.y << '\n';
                // shift the new point by the delta to push us outside of the rectangle
                *newPosOrigin = Vector2Add(tempNewPosOrigin, delta);
            }
        }
    }
}


void MovingObjectComponent::MovePosition(Vector2 velocity, Group collisionGroup, Manager& manager)
{
    Collision collision;
    if (!entity->hasComponent<TransformComponent>()){
        std::cout << "NO TRANSFORM COMPONENT!";
        return;}
    
    Vector2 newPosOrigin = entity->getComponent<TransformComponent>().position;
    
    newPosOrigin = Vector2Add(newPosOrigin, velocity);

    collision.MovingObjectCollision(&newPosOrigin, collisionGroup, manager, *entity);
    
    entity->getComponent<TransformComponent>().position = newPosOrigin;
}

MovingObjectComponent::~MovingObjectComponent()
{
}
