#include <cmath>
#include "DxLib.h"
#include "../support/Support.h"
#include "Collider.h"

void Collider::Update(int x, int y) {
	position_x_ = x;
	position_y_ = y;
}

//void Collider::UpdateWithCharacter(Character* cptr)
//{
//	position_x_ = cptr->GetX();
//	position_y_ = cptr->GetY();
//}

bool Collider::CheckCollision(Collider* target) {
	int target_x = target->GetX();
	int target_width = target->GetHorizontal();

	bool horizontal_check = std::abs(position_x_ - target_x) < horizontal_ + target_width;

	int target_y = target->GetY();
	int target_height = target->GetVertical();

	bool vertical_check = std::abs(position_y_ - target_y) < vertical_ + target_height;

	bool hit = horizontal_check && vertical_check;

	if (hit)
	{
		//position_x_ += ((horizontal_ + target_width) - std::abs(position_x_ - target_x));
		if(position_y_ - target_y < 0)
		{
			position_y_ -= ((vertical_ + target_height) - std::abs(position_y_ - target_y));
		}
		if(position_y_ - target_y > 0)
		{
			position_y_ += ((vertical_ + target_height) - std::abs(position_y_ - target_y));
		}
	}

	return hit;
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