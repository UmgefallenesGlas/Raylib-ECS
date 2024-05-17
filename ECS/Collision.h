#pragma once
#include <raylib.h>
#include <raymath.h>
#include "ECS.h"

class Collision
{
public:
	void PointNearestRectanglePoint(Rectangle rect, Vector2 point, Vector2* nearest, Vector2* normal);
	Vector2 MovingObjectCollision(Vector2 newPosOrigin, Entity& player);
};