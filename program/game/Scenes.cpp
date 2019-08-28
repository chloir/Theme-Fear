#include "DxLib.h"
#include "../support/Support.h"
#include "Scenes.h"
#include "Collider.h"
#include "Character.h"
#include "RenderCamera.h"

#pragma region MainScene

Character* player = new Character(0, 0);
Character* enemySample = new Character(0, 500);
Collider* player_collider = nullptr;
Collider* enemy_collider = nullptr;
Collider* floor_collider = nullptr;
Collider* floor_collider2 = nullptr;
Camera* main_camera = nullptr;

int background_graph_handle;
bool main_scene_init = false;

void MainScene() {
	if (!main_scene_init) {
		background_graph_handle = LoadGraph("graphics/bg_green.png");
		player->SetGraphHandle(LoadGraph("graphics/s_chr.png"));
		enemySample->SetGraphHandle(LoadGraph("graphics/frog.png"));
		int width, height;
		GetGraphSize(player->GetHandle(), &width, &height);
		player_collider = new Collider(player->GetX(), player->GetY(), width, height);
		int e_width, e_height;
		GetGraphSize(enemySample->GetHandle(), &e_width, &e_height);
		enemy_collider = new Collider(enemySample->GetX(), enemySample->GetY(), e_width, e_height);
		main_camera = new Camera(player->GetX(), player->GetY());
		floor_collider = new Collider(0, 300, 2000, 10);
		floor_collider2 = new Collider(100, 100, 300, 20);
		main_scene_init = true;
	}

	Update();
	Render();
}

// 位置の更新、当たり判定などのアップデート
void Update()
{
	player->Update();
	player_collider->Update(player->GetX(), player->GetY());
	player_collider->CheckCollision(floor_collider);
	player->SetX(player_collider->GetX());
	player->SetY(player_collider->GetY());
	//enemySample->Translate(0, -1);
	//enemy_collider->Update(enemySample->GetX(), enemySample->GetY());
}

// 描画
void Render()
{
	main_camera->LerpPosition(player->GetX(), player->GetY());
	main_camera->Render(background_graph_handle, 0, 0, 0);
	//enemySample->Render(main_camera);
	player->Render(main_camera);
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