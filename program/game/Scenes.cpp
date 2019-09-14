#include "DxLib.h"
#include "../support/Support.h"
#include "Scenes.h"
#include "Collider.h"
#include "Character.h"
#include "RenderCamera.h"

#pragma region MainScene

int background_graph_handle = 0;
int background_floor_handle = 0;
int slim_floor_graph_handle = 0;
int mask_graph_handle = 0;
double mask_size = 1;
const int SLIM_FLOOR_COUNT = 3;

bool main_scene_init = false;

Character* player = new Character(0, 0);
Character* enemySample = new Character(-300, 280);
Collider* player_collider = nullptr;
Collider* enemy_collider = nullptr;
Collider* floor_colliders[SLIM_FLOOR_COUNT];
Collider* floor_collider = nullptr;
Collider* mini_floor_collider = nullptr;
Camera* main_camera = nullptr;


void MainScene() {
	if (!main_scene_init) {
		background_floor_handle = LoadGraph("graphics/bg_floor.png");
		slim_floor_graph_handle = LoadGraph("graphics/floor_slim01.png");
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
		floor_colliders[0] = new Collider(0, 400, f_width, f_height, FLOOR);
		// slim floors初期化
		int m_f_width, m_f_height;
		GetGraphSize(slim_floor_graph_handle, &m_f_width, &m_f_height);
		floor_colliders[1] = new Collider(100, 220, m_f_width, m_f_height, FLOOR);
		floor_colliders[2] = new Collider(600, 220, m_f_width, m_f_height, FLOOR);
		
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
	// 床判定
	for (Collider* c : floor_colliders)
	{
		if (player_collider->CheckType(c, FLOOR) && player_collider->CheckCollision(c))
		{
			player->SetState(false);
		}
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
	for (int i = 0; i < sizeof(floor_colliders) / sizeof(floor_colliders[0]); i++)
	{
		if(i == 0)
		{
			main_camera->Render(background_floor_handle, floor_colliders[i]->GetX(), floor_colliders[i]->GetY(), 0, 1);
		}else
		{
			main_camera->Render(slim_floor_graph_handle, floor_colliders[i]->GetX(), floor_colliders[i]->GetY(), 0, 1);
		}
	}
	enemySample->Render(main_camera, 2);
	// マスク以降にはプレイヤー以外のレンダリングをしない
	main_camera->Render(mask_graph_handle, player->GetX(), player->GetY(), 0, mask_size);
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