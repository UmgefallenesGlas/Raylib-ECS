#pragma once
#include "Components.hpp"

class TransformComponent : public Component {

public:
	Vector2 position;
	Vector2 velocity;
	Rectangle rectangle;

	int height = 32;
	int width = 32;
	int scale = 1;
	int rotation = 0;

	//Sets Position automaticly to 0,0
	TransformComponent() {
		position = { 0,0 };
	}

	//Sets Scale, and sets position to 0,0
	TransformComponent(int sc) {
		position = { 0,0 };
		scale = sc;
	}

	//Set X and Y Position
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	//X Position, Y Position, Width, Height, Scale
	TransformComponent(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	//X Position, Y Position, Width, Height, Scale, Rotation
	TransformComponent(float x, float y, int w, int h, int sc, int rot) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
		rotation = rot;
	}

	void init() override {
		rectangle = {
		position.x - (width * scale) / 2,
		position.y - (height * scale) / 2,
		(float)width * scale,
		(float)height * scale
		};
		velocity = { 0,0 };
	}

	void update() override {
		rectangle = {
		position.x - (width * scale) / 2,
		position.y - (height * scale) / 2,
		(float)width * scale,
		(float)height * scale
		};

		position.x += velocity.x;
		position.y += velocity.y;
	}
};
