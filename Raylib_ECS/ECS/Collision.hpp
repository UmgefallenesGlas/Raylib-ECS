#pragma once
#include <raylib.h>
#include <raymath.h>
#include "ECS.hpp"
#include "Components.hpp"
class Collision
{
public:
	void PointNearestRectanglePoint(Rectangle rect, Vector2 point, Vector2* nearest, Vector2* normal);

	//The New Position, The group of all your Collidable Objects, The Manager, The Entity that collides with it
	void MovingObjectCollision(Vector2 *newPosOrigin, Group collisionGroup, Manager& manager, Entity& obj);
};

class MovingObjectComponent: public Component
{
public:
	MovingObjectComponent() = default;
	void MovePosition(Vector2 velocity, Group collisionGroup, Manager& manager);
	~MovingObjectComponent();

private:

};
