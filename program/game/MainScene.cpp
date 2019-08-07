#include "DxLib.h"
#include "../support/Support.h"
#include "MainScene.h"
#include "Collider.h"
#include "Character.h"
#include "RenderCamera.h"

Character* player = new Character(200, 200);
Collider* player_collider = nullptr;
Camera* main_camera = nullptr;

int background_graph_handle;
bool main_scene_init = false;

void MainScene() {
	if (!main_scene_init) {
		background_graph_handle = LoadGraph("graphics/bg_green.png");
		player->SetGraphHandle(LoadGraph("graphics/s_chr.png"));
		int width, height;
		GetGraphSize(player->GetHandle(), &width, &height);
		player_collider = new Collider(player->GetX(), player->GetY(), width, height);
		main_camera = new Camera(player->GetX(), player->GetY());
		main_scene_init = true;
	}

	player->Update();
	main_camera->LerpPosition(player->GetX(), player->GetY());
	main_camera->Render(background_graph_handle, 0, 0, 0);
	player->Render(main_camera);
}

//bool main_scene_init = false;
//int player_x = 100, player_y = 100;
//int player_graph_size = 100;
//int player_sprite_handle = 0;
//int player_direction = 0;
//int movement_speed = 4;
//int jump_height = 300;
//int floor = 650;
//int gravity = 6;
//
//Collider* player_collider;
//
//bool jump = false;
//
//void MainScene() {
//	if (!main_scene_init) {
//		Initialize();
//		player_collider = new Collider(player_x, player_y, player_graph_size, player_graph_size);
//		main_scene_init = true;
//	}
//
//	Update();
//	DrawCharacter();
//
//}
//
//void Initialize() {
//	player_sprite_handle = LoadGraph("graphics/s_chr.png");
//}
//
//void DrawCharacter() {
//	if (player_direction == 0) {
//		DrawGraph(player_x, player_y, player_sprite_handle, true);
//	}
//	else {
//		DrawTurnGraph(player_x, player_y, player_sprite_handle, true);
//	}
//}
//
//void Update() {
//	if (CheckHitKey(KEY_INPUT_RIGHT)) {
//		player_x += movement_speed;
//		player_direction = 1;
//	}
//	if (CheckHitKey(KEY_INPUT_LEFT)) {
//		player_x -= movement_speed;
//		player_direction = 0;
//	}
//
//	if (player_y + player_graph_size > floor) {
//		player_y = floor - player_graph_size;
//	}
//
//	if (IsKeyDownTrigger(KEY_INPUT_SPACE)) {
//		Jump();
//	}
//
//	player_y += gravity;
//	
//}
//
//void Jump() {
//	if (!jump) {
//		jump = true;
//	}
//	else {
//		player_y -= 100;
//	}
//
//	if (player_y < jump_height) {
//		jump = false;
//	}
//}