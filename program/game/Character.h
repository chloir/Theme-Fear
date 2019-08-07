#pragma once
#include "RenderCamera.h"
#include "Collider.h"

const int MOVEMENT_SPEED = 10;

class Character {
public:
	Character() {}
	Character(int x, int y) {
		position_x_ = x;
		position_y_ = y;
	}
	~Character() {}

	void SetGraphHandle(int handle);
	void Update();
	void Render(Camera* main_camera);
	int GetX();
	int GetY();
	int GetHandle();

private:
	int position_x_;
	int position_y_;
	int graph_handle_;
	int direction_flag_; // 0:ç∂ 1:âE
};