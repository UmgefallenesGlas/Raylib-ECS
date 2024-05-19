#pragma once
#include "Components.hpp"


class SpriteComponent : public Component {
private:
	TransformComponent *transform;
	Texture texture;
	Rectangle srcRect, destRect;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
	~SpriteComponent() {
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
		srcRect.width = transform->width-EPSILON/1;
		srcRect.height = transform->height-EPSILON/1;
	}

	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.width = transform->width * transform->scale;
		destRect.height = transform->height * transform->scale;
	}

	void draw() override{
		DrawTexturePro(texture, srcRect, destRect, Vector2{ destRect.width / 2, destRect.height / 2 }, transform->rotation, WHITE);
	}
};
