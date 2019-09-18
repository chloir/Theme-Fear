#pragma once
#include "RenderCamera.h"
#include "Collider.h"

const int MOVEMENT_SPEED = 3;
const int GRAVITY_SCALE = 9;
const int JUMP_VELOCITY = 40;

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
	void Translate(int x, int y);
	void ApplyGravity();
	void Render(Camera* main_camera, int e_rate);
	int GetX();
	void SetX(int x);
	int GetY();
	void SetY(int y);
	int GetHandle();
	void SetState(bool state);

private:
	bool is_jumping = false;
	int target_temp = 0;
	float velocity_temp = 0;
	int position_x_;
	int position_y_;
	int graph_handle_;
	int direction_flag_; // 0:�� 1:�E
};