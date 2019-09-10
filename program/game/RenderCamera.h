#pragma once

class Camera {
public:
	Camera();
	Camera(int x, int y)
	{
		position_x_ = x;
		position_y_ = y;
	}
	~Camera();

	void Render(int graph_handle, int target_x, int target_y, int direction_flag = 0, int extend_rate = 1);
	void LerpPosition(int target_x, int target_y);

private:
	int position_x_;
	int position_y_;
};