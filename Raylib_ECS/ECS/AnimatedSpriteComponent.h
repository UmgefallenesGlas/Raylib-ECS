#pragma once
#include <map>
#include "Components.hpp"
#include "Animation.hpp"

class AnimatedSpriteComponent : public Component
{
private:
	TransformComponent* transform;
	Texture texture;
	Rectangle srcRect, destRect;

	bool playing = false;
	float currentFrame = 0;
	int frames = 0;
	float speed = 100;

public:
	int  animIndex = 0;
	std::map<const char*, Animation> animations;

	AnimatedSpriteComponent() = default;
	AnimatedSpriteComponent(const char* file) {
		setTex(file);
	}
	~AnimatedSpriteComponent() {
		UnloadTexture(texture);
	}


	void setTex(const char* path) {
		Image tempImg = LoadImage(path);
		texture = LoadTextureFromImage(tempImg);
		UnloadImage(tempImg);

	}
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.width = transform->width;
		srcRect.height = transform->height;
	}

	void update() override {
		if (playing) {
			currentFrame += GetFrameTime() * 2;
			if (currentFrame > frames) {
				currentFrame = 0;
			}
			srcRect.x = srcRect.width * static_cast<int>((int)(currentFrame * speed) % frames);
		}
		
		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.width = transform->width * transform->scale;
		destRect.height = transform->height * transform->scale;
	}

	void draw() override {
		DrawTexturePro(texture, srcRect, destRect, Vector2{ destRect.width / 2, destRect.height / 2 }, transform->rotation, WHITE);
	}

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
		playing = true;
	}

	void Resume() {
		playing = true;
	}

	void Pause() {
		playing = false;
	}
};
