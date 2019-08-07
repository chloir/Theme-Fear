#include "DxLib.h"
#include "../support/Support.h"
#include "RenderCamera.h"

void Camera::Render(int graph_handle, int target_x, int target_y, int direction_flag) {
	int x = (1024 / 2) - position_x_ + target_x;
	int y = (768 / 2) - position_y_ + target_y;
	DrawRotaGraph(x, y, 1, 0, graph_handle, true, direction_flag);
}

void Camera::LerpPosition(int target_x, int target_y) {
	position_x_ += (target_x - position_x_) * 0.1f;
	position_y_ += (target_y - position_y_) * 0.1f;
}