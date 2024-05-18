#pragma once
#include <raylib.h>
#include <raymath.h>
#include "ECS.h"

class Collision
{
public:
	void PointNearestRectanglePoint(Rectangle rect, Vector2 point, Vector2* nearest, Vector2* normal);
	void MovingObjectCollision(Vector2 *newPosOrigin,Manager& manager , Entity& obj);
};