//Include Raylib
#include <raylib.h>

//Include all the Components
#include "ECS/Components.h"

//Add Manager
Manager manager;

//Add Collision (This approach i may change in the future)
Collision collision;

//Create Entitys

auto& wall_1 = manager.addEntity();
auto& wall_2 = manager.addEntity();

auto& player = manager.addEntity();

//Groups
enum groupLabels : std::size_t {
	groupCollider,
	groupMap,
	groupPlayer
};

//Look directions
enum lookDir { up, down, left, right };

//Player Directions
lookDir playerDir;

void HandlePlayer() {
	//The Walk Keys Pressed
	Vector2 inputKeys;
	
	//Player moving Speed
	float speed = 400.f;

	//New position is equals to the Original Player Position
	Vector2 newPosOrigin = player.getComponent<TransformComponent>().position;

#pragma region InputHandling
	//Keys Pressed
	inputKeys = { (float)(-IsKeyDown(KEY_A) + IsKeyDown(KEY_D)),
				(float)(-IsKeyDown(KEY_W) + IsKeyDown(KEY_S)) };


	//Change direction by Input Keys
	if (inputKeys.x > 0) {
		playerDir = lookDir(right);
	}
	else if (inputKeys.x < 0) {
		playerDir = lookDir(left);
	}
	else if (inputKeys.y > 0) {
		playerDir = lookDir(down);
	}
	else if (inputKeys.y < 0) {
		playerDir = lookDir(up);
	}

	//Play Animation
	switch (playerDir)
	{
	case up:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Up");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Up");
		}
		break;
	case down:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Down");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Down");
		}
		break;
	case left:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Left");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Left");
		}
		break;
	case right:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Right");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Right");
		}
		break;
	default:
		break;
	}
	
	//Change Position
	newPosOrigin = Vector2Add(newPosOrigin, Vector2Scale(inputKeys, speed * GetFrameTime()));
	
	//The Collision
	collision.MovingObjectCollision(&newPosOrigin, groupMap, manager, player);
#pragma endregion

	//Player Position is equals to the new Position
	player.getComponent<TransformComponent>().position = newPosOrigin;
}

int main() {
	//Create Window
	InitWindow(600, 600, "Example");
	//------Heres-Start-------//
	
	//Entitys also need to be Created at Start
#pragma region CreateEntitys

	//Adds Position
	wall_1.addComponent<TransformComponent>(96, 128, 32, 32, 2, 0);
	//Adds Texture
	wall_1.addComponent<SpriteComponent>("assets/water.png");
	//Adds Group
	wall_1.addGroup(groupMap);

	wall_2.addComponent<TransformComponent>(96 * 2, 128, 32, 32, 2, 0);
	wall_2.addComponent<SpriteComponent>("assets/water.png");
	wall_2.addGroup(groupMap);

	player.addComponent<TransformComponent>(300, 300, 32, 32, 2, 0);
	//Adds Animated Texture
	player.addComponent<AnimatedSpriteComponent>("assets/Char_Main_file.png");
	player.addGroup(groupPlayer);

#pragma endregion


	//Animations need to be Created at Start
#pragma region Animation

	//Create Animation coodinates
	Animation idle_down = Animation(0, 1, 5);
	Animation idle_up = Animation(1, 1, 5);
	Animation idle_left = Animation(2, 1, 5);
	Animation idle_right = Animation(3, 1, 5);

	Animation walk_down = Animation(0, 4, 5);
	Animation walk_up = Animation(1, 4, 5);
	Animation walk_left = Animation(2, 4, 5);
	Animation walk_right = Animation(3, 4, 5);

	
	//Set emplace of Animation
	
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Down", idle_down);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Up", idle_up);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Left", idle_left);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Right", idle_right);

	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Down", walk_down);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Up", walk_up);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Left", walk_left);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Right", walk_right);

	playerDir = lookDir(down);
#pragma endregion

	while (!WindowShouldClose())
	{
		//------Heres-Update------//
		
		//Updates Components
		manager.update();
		//Refreshes components (need this if your delete Entitys)
		manager.refresh();

		//Handle Player
		HandlePlayer();


		BeginDrawing();
		//------Heres-Drawing-----//
		//Draws in Components
		ClearBackground(WHITE);
		manager.draw();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}