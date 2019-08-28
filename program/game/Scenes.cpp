#include "DxLib.h"
#include "../support/Support.h"
#include "Scenes.h"
#include "Collider.h"
#include "Character.h"
#include "RenderCamera.h"

#pragma region MainScene

Character* player = new Character(0, 200);
Character* enemySample = new Character(0, 500);
Collider* player_collider = nullptr;
Collider* enemy_collider = nullptr;
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
		main_scene_init = true;
	}

	Update();
	Render();

	DrawStringEx(10, 10, 1, "Hit:%d", player_collider->CheckCollision(enemy_collider));
}

// 位置の更新、当たり判定などのアップデート
void Update()
{
	player->Update();
	player_collider->Update(player->GetX(), player->GetY());
 if (player->GetY() > 200)
 {
	 player->SetY(200);
 }
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