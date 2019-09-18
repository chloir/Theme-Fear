#pragma once
#include "Character.h"

enum ColliderType
{
	FLOOR,
	ENEMY,
	PLAYER,
	ITEM,
	DOOR
};

class Collider {
public:
	Collider() {}
	Collider(int x, int y, int width, int height, ColliderType type) {
		tag = type;
		position_x_ = x;
		position_y_ = y;
		width_ = width;
		height_ = height;
		horizontal_ = width_ / 2;
		vertical_ = height_ / 2;
	}
	~Collider() {}

	void Update(int x, int y);
	// void UpdateWithCharacter(Character* cptr);
	bool CheckCollision(Collider* target);
	bool CheckType(Collider* target, ColliderType type);
	int GetHorizontal();
	int GetVertical();
	int GetX();
	int GetY();
	ColliderType GetTag();

private:
	ColliderType tag;
	int position_x_;
	int position_y_;
	int width_;
	int height_;
	int horizontal_;
	int vertical_;
};