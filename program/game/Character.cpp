#include "DxLib.h"
#include "../support/Support.h"
#include "Character.h"
#include "RenderCamera.h"

void Character::SetGraphHandle(int handle) {
	graph_handle_ = handle;
}

void Character::Update() {
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) {
		position_x_ -= MOVEMENT_SPEED;
		direction_flag_ = 0;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
		position_x_ += MOVEMENT_SPEED;
		direction_flag_ = 1;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && !is_jumping)
	{
		is_jumping = true;
		target_temp = position_y_ - 1;
		velocity_temp = JUMP_VELOCITY;
		position_y_ -= velocity_temp;
	}
	if (is_jumping)
	{
		velocity_temp -= velocity_temp * 0.1f;
		position_y_ -= velocity_temp;
		if (position_y_ >= target_temp)
		{
			is_jumping = false;
		}
	}

	ApplyGravity();
	
}

void Character::ApplyGravity()
{
	position_y_ += GRAVITY_SCALE;
}

void Character::Translate(int x = NULL, int y = NULL)
{
	position_x_ += x;
	position_y_ += y;
}


void Character::Render(Camera* main_camera, int e_rate) {
	main_camera->Render(graph_handle_, position_x_, position_y_, direction_flag_, e_rate);
}

int Character::GetX() { return position_x_; }
void Character::SetX(int x) { position_x_ = x; }
int Character::GetY() { return position_y_; }
void Character::SetY(int y) { position_y_ = y; }
int Character::GetHandle() { return graph_handle_; }
void Character::SetState(bool state) { is_jumping = state; }
