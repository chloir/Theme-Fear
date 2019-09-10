#include "DxLib.h"
#include "../support/Support.h"
#include "Scenes.h"
#include "Collider.h"
#include "Character.h"
#include "RenderCamera.h"

#pragma region MainScene

Character* player = new Character(0, 0);
Character* enemySample = new Character(-300, 280);
Collider* player_collider = nullptr;
Collider* enemy_collider = nullptr;
Collider* floor_collider = nullptr;
Camera* main_camera = nullptr;

int background_graph_handle = 0;
int background_floor_handle = 0;
int mask_graph_handle = 0;
float mask_size = 1;

bool main_scene_init = false;

void MainScene() {
	if (!main_scene_init) {
		background_graph_handle = LoadGraph("graphics/bg_green.png");
		background_floor_handle = LoadGraph("graphics/bg_floor.png");
		mask_graph_handle = LoadGraph("graphics/Mask.png");
		player->SetGraphHandle(LoadGraph("graphics/s_chr.png"));
		enemySample->SetGraphHandle(LoadGraph("graphics/frog.png"));
		// player初期化
		int width, height;
		GetGraphSize(player->GetHandle(), &width, &height);
		player_collider = new Collider(player->GetX(), player->GetY(), width, height, PLAYER);
		// enemy初期化
		int e_width, e_height;
		GetGraphSize(enemySample->GetHandle(), &e_width, &e_height);
		enemy_collider = new Collider(enemySample->GetX(), enemySample->GetY(), e_width, e_height, ENEMY);
		// floor初期化
		int f_width, f_height;
		GetGraphSize(background_floor_handle, &f_width, &f_height);
		floor_collider = new Collider(0, 400, f_width, f_height, FLOOR);
		
		main_camera = new Camera(player->GetX(), player->GetY());
		main_scene_init = true;
	}

	Update();
	Render();

}

// 位置の更新、当たり判定などのアップデート
void Update()
{
	// player更新系
	player->Update();
	player_collider->Update(player->GetX(), player->GetY());
	player_collider->CheckCollision(floor_collider);
	if (player_collider->CheckType(floor_collider, FLOOR))
	{
		player->SetState(false);
	}
	player->SetX(player_collider->GetX());
	player->SetY(player_collider->GetY());
	// enemy更新系
	enemySample->Translate(2, 0);
	enemy_collider->Update(enemySample->GetX(), enemySample->GetY());
}

// 描画
void Render()
{
	main_camera->LerpPosition(player->GetX(), player->GetY());
	main_camera->Render(background_graph_handle, 0, 0, 0, 1);
	main_camera->Render(background_floor_handle, floor_collider->GetX(), floor_collider->GetY(), 0, 1);
	//main_camera->Render(mask_graph_handle, player->GetX(), player->GetY(), 0, 1);
	enemySample->Render(main_camera, 2);
	player->Render(main_camera, 1);
}

#pragma endregion

#pragma region EndScene

bool end_scene_init = false;

void EndScene()
{
	if (!end_scene_init)
	{
		// 初期化
		SetFontSize(50);
		end_scene_init = true;
	}
	DrawStringEx(512, 365, 1, "End Scene");
}

#pragma endregion 

#pragma region SceneControl

Scenes current_scene;

void LoadCurrentScene()
{
	switch (current_scene)
	{
	case TITLE_SCENE:
		break;
	case MAIN_SCENE:
		MainScene();
		break;
	case END_SCENE:
		EndScene();
		break;
	}
}

void ChangeScene(Scenes scene) { current_scene = scene; }

#pragma endregion