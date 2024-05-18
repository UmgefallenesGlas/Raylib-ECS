#pragma once
#include <raylib.h>
#include <raymath.h>
#include "ECS.h"
#include "Components.h"
class Collision
{
public:
	void PointNearestRectanglePoint(Rectangle rect, Vector2 point, Vector2* nearest, Vector2* normal);

	//The New Position, The group of all your Collidable Objects, The Manager, The Entity that collides with it
	void MovingObjectCollision(Vector2 *newPosOrigin, Group collisionGroup, Manager& manager, Entity& obj);
};