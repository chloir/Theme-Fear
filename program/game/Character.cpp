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
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		position_y_ -= JUMP_VELOCITY;
	}
	ApplyGravity();
	//if(CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	//{
	//	position_y_ -= MOVEMENT_SPEED;
	//}
	//if(CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	//{
	//	position_y_ += MOVEMENT_SPEED;
	//}
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


void Character::Render(Camera* main_camera) {
	main_camera->Render(graph_handle_, position_x_, position_y_, direction_flag_);
}

int Character::GetX() { return position_x_; }
void Character::SetX(int x) { position_x_ = x; }
int Character::GetY() { return position_y_; }
void Character::SetY(int y) { position_y_ = y; }
int Character::GetHandle() { return graph_handle_; }