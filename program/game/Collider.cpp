#include "DxLib.h"
#include "../support/Support.h"
#include "Collider.h"

void Collider::Update(int x, int y) {
	position_x_ = x;
	position_y_ = y;
}

bool Collider::CheckCollision(Collider* target) {
	int target_x = target->GetX();
	int target_width = target->GetHorizontal();

	bool horizontal_check = position_x_ - target_x < horizontal_ + target_width;

	int target_y = target->GetY();
	int target_height = target->GetVertical();

	bool vertical_check = position_y_ - target_y < vertical_ + target_height;

	return horizontal_check && vertical_check;
}

int Collider::GetHorizontal() {
	return horizontal_;
}

int Collider::GetVertical() {
	return vertical_;
}

int Collider::GetX() {
	return position_x_;
}

int Collider::GetY() {
	return position_y_;
}