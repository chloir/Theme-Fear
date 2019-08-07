#include "DxLib.h"
#include "../support/Support.h"
#include "Character.h"
#include "RenderCamera.h"

void Character::SetGraphHandle(int handle) {
	graph_handle_ = handle;
}

void Character::Update() {
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		position_x_ -= MOVEMENT_SPEED;
		direction_flag_ = 0;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		position_x_ += MOVEMENT_SPEED;
		direction_flag_ = 1;
	}
}

void Character::Render(Camera* main_camera) {
	main_camera->Render(graph_handle_, position_x_, position_y_, direction_flag_);
}

int Character::GetX() { return position_x_; }
int Character::GetY() { return position_y_; }
int Character::GetHandle() { return graph_handle_; }