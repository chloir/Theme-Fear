#pragma once

class Collider {
public:
	Collider() {}
	Collider(int x, int y, int width, int height) {
		position_x_ = x;
		position_y_ = y;
		width_ = width;
		height_ = height;
	}
	~Collider() {}

	void Update(int x, int y);
	bool CheckCollision(Collider* target);
	int GetHorizontal();
	int GetVertical();
	int GetX();
	int GetY();

private:
	int position_x_;
	int position_y_;
	int width_;
	int height_;
	int horizontal_ = width_ / 2;
	int vertical_ = height_ / 2;
};