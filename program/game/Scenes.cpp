#include "DxLib.h"
#include "../support/Support.h"
#include "Scenes.h"
#include "Collider.h"
#include "Character.h"
#include "RenderCamera.h"

#pragma region TitleSceneVariables

bool title_scene_init = false;
int test = 0;

#pragma endregion

#pragma region MainSceneVariables

const int SLIM_FLOOR_COUNT = 12;
const int TORCH_COUNT = 2;

int background_graph_handle = 0;
int background_floor_handle = 0;
int slim_floor_graph_handle = 0;
int torch_graph_handle = 0;
int door_graph_handle = 0;
int mask_graph_handle = 0;
double mask_size = 1;
bool mask_is_wide = false;
const int TORCH_TIMER = 300;
int timer = 0;

bool main_scene_init = false;
bool player_is_alive = false;

Character* player = nullptr;
Character* enemySample = nullptr;
Collider* player_collider = nullptr;
Collider* enemy_collider = nullptr;
Collider* door_collider = nullptr;
Collider* floor_collider[SLIM_FLOOR_COUNT];
Collider* torch_collider[TORCH_COUNT];
Camera* main_camera = nullptr;

#pragma endregion

#pragma region EndSceneVariables

bool end_scene_init = false;
int bg_red, bg_green = 0, bg_blue = 0;
bool increment_red = true;

#pragma endregion

#pragma region SceneControlVariables

Scenes current_scene = TITLE_SCENE;

#pragma endregion

#pragma region TitleScene

void TitleScene()
{
	if (!title_scene_init)
	{
		// 初期化
		test = LoadGraph("graphics/chr.png");
		title_scene_init = true;
	}

	if (IsKeyDownTrigger(KEY_INPUT_SPACE))
	{
		title_scene_init = false;
		ChangeScene(MAIN_SCENE);
	}
	
	DrawGraph(150, 300, test, 1);
	SetFontSize(100);
	DrawString(700, 200, "Escape", GetColor(140, 0, 0));
	SetFontSize(50);
	DrawString(800, 600, "Push Space To Start", GetColor(140, 0, 0));
}

#pragma endregion

#pragma region MainScene

void MainScene() {
	if (!main_scene_init) {
		background_floor_handle = LoadGraph("graphics/bg_floor.png");
		slim_floor_graph_handle = LoadGraph("graphics/floor_slim01.png");
		torch_graph_handle = LoadGraph("graphics/torch.png");
		door_graph_handle = LoadGraph("graphics/door.png");
		mask_graph_handle = LoadGraph("graphics/Mask.png");
		// player初期化
		player = new Character(-200, 300);
		player->SetGraphHandle(LoadGraph("graphics/s_chr.png"));
		int width, height;
		GetGraphSize(player->GetHandle(), &width, &height);
		player_collider = new Collider(player->GetX(), player->GetY(), width, height, PLAYER);
		// enemy初期化
		enemySample = new Character(-600, 280);
		enemySample->SetGraphHandle(LoadGraph("graphics/frog.png"));
		int e_width, e_height;
		GetGraphSize(enemySample->GetHandle(), &e_width, &e_height);
		enemy_collider = new Collider(enemySample->GetX(), enemySample->GetY(), e_width, e_height, ENEMY);
		// floor初期化
		int f_width, f_height;
		GetGraphSize(background_floor_handle, &f_width, &f_height);
		floor_collider[0] = new Collider(0, 400, f_width, f_height, FLOOR);
		// slim floors初期化
		int m_f_width, m_f_height;
		GetGraphSize(slim_floor_graph_handle, &m_f_width, &m_f_height);
		floor_collider[1] = new Collider(100, 220, m_f_width, m_f_height, FLOOR);
		floor_collider[2] = new Collider(500, 220, m_f_width, m_f_height, FLOOR);
		floor_collider[3] = new Collider(850, 220, m_f_width, m_f_height, FLOOR);
		floor_collider[4] = new Collider(750, 70, m_f_width, m_f_height, FLOOR);
		floor_collider[5] = new Collider(1200, 220, m_f_width, m_f_height, FLOOR);
		floor_collider[6] = new Collider(1800, 220, m_f_width, m_f_height, FLOOR);
		floor_collider[7] = new Collider(1100, 70, m_f_width, m_f_height, FLOOR);
		floor_collider[8] = new Collider(2300, 220, m_f_width, m_f_height, FLOOR);
		floor_collider[9] = new Collider(1600, 70, m_f_width, m_f_height, FLOOR);
		floor_collider[10] = new Collider(1500, 220, m_f_width, m_f_height, FLOOR);
		floor_collider[11] = new Collider(2000, 70, m_f_width, m_f_height, FLOOR);
		// torch初期化
		int t_width, t_height;
		GetGraphSize(torch_graph_handle, &t_width, &t_height);
		torch_collider[0] = new Collider(200, 320, t_width, t_height, ITEM);
		torch_collider[1] = new Collider(1800, 320, t_width, t_height, ITEM);
		// door初期化
		int d_width, d_height;
		GetGraphSize(door_graph_handle, &d_width, &d_height);
		door_collider = new Collider(2300, 300, d_width, d_height, DOOR);
		
		main_camera = new Camera(player->GetX(), player->GetY());
		main_scene_init = true;
	}

	Update();
	Render();

	if (current_scene != MAIN_SCENE)
	{
		OnSceneExit();
	}
}

// 位置の更新、当たり判定などのアップデート
void Update()
{
	// player更新系
	player->Update();
	player_collider->Update(player->GetX(), player->GetY());
	
	// 床判定
	for (Collider* c : floor_collider)
	{
		if (c != nullptr)
		{
			if (player_collider->CheckCollision(c) && player_collider->CheckType(c, FLOOR))
			{
				player->SetState(false);
			}
		}
	}
	player->SetX(player_collider->GetX());
	player->SetY(player_collider->GetY());
	
	// 松明判定
	for (int i = 0; i < (sizeof(torch_collider) / sizeof(torch_collider[0])); i++)
	{
		if (torch_collider[i] != nullptr)
		{
			if (player_collider->CheckCollision(torch_collider[i]) && player_collider->CheckType(torch_collider[i], ITEM))
			{
				torch_collider[i] = nullptr;
				mask_size = 2;
				mask_is_wide = true;
			}
		}
	}
	if (mask_is_wide)
	{
		++timer;
		if (timer > TORCH_TIMER)
		{
			mask_size = 1;
			timer = 0;
			mask_is_wide = false;
		}
	}

	// ドア判定
	if (player_collider->CheckCollision(door_collider) && player_collider->CheckType(door_collider, DOOR))
	{
		player_is_alive = true;
		ChangeScene(END_SCENE);
	}
	
	// enemy更新系
	enemySample->Translate(2, 0);
	enemy_collider->Update(enemySample->GetX(), enemySample->GetY());

	// enemy判定
	if (player_collider->CheckCollision(enemy_collider))
	{
		player_is_alive = false;
		ChangeScene(END_SCENE);
	}
}

// 描画
void Render()
{
	main_camera->LerpPosition(player->GetX(), player->GetY());
	// 床描画
	for (int i = 0; i < sizeof(floor_collider) / sizeof(floor_collider[0]); i++)
	{
		if(i == 0)
		{
			main_camera->Render(background_floor_handle, floor_collider[i]->GetX(), floor_collider[i]->GetY(), 0, 1);
		}else
		{
			main_camera->Render(slim_floor_graph_handle, floor_collider[i]->GetX(), floor_collider[i]->GetY(), 0, 1);
		}
	}
	enemySample->Render(main_camera, 2);

	// たいまつ描画
	for (int i = 0; i < sizeof(torch_collider) / sizeof(torch_collider[0]); i++)
	{
		if (torch_collider[i] != nullptr)
		{
			main_camera->Render(torch_graph_handle, torch_collider[i]->GetX(), torch_collider[i]->GetY(), 0, 1);
		}
	}

	// ドア描画
	main_camera->Render(door_graph_handle, door_collider->GetX(), door_collider->GetY(), 0, 1);
	
	// マスク以降にはプレイヤー以外のレンダリングをしない
	main_camera->Render(mask_graph_handle, player->GetX(), player->GetY(), 0, mask_size);
	player->Render(main_camera, 1);
}

void OnSceneExit()
{
	// 変数初期化
	main_scene_init = false;
	player = nullptr;
	enemySample = nullptr;
	player_collider = nullptr;
	enemy_collider = nullptr;
	door_collider = nullptr;
	for (int i = 0; i < (sizeof(floor_collider) / sizeof(floor_collider[0])); i++)
	{
		floor_collider[i] = nullptr;
	}
	for (int i = 0; i < (sizeof(torch_collider) / sizeof(torch_collider[0])); i++)
	{
		torch_collider[i] = nullptr;
	}
	main_camera = nullptr;

	mask_is_wide = false;
	mask_size = 1;
	timer = 0;
}

#pragma endregion

#pragma region EndScene

void EndScene()
{
	if (!end_scene_init)
	{
		// 初期化
		end_scene_init = true;
	}

	if (IsKeyDownTrigger(KEY_INPUT_SPACE))
	{
		bg_red = 0;
		end_scene_init = false;
		ChangeScene(TITLE_SCENE);
	}

	if (player_is_alive)
	{
		SetFontSize(80);
		DrawString(480, 365, "Escape Success!", GetColor(0, 150, 255));
		SetFontSize(50);
		DrawString(455, 600, "Push Space To Return Title", GetColor(0, 80, 255));
	}

	if (!player_is_alive)
	{
		if (bg_red == 100)
		{
			increment_red = false;
		}
		if (bg_red == 0)
		{
			increment_red = true;
		}
		
		if (increment_red)
		{
			bg_red += 1;
		}
		if (!increment_red)
		{
			bg_red -= 1;
		}
		
		SetBackgroundColor(bg_red, bg_green, bg_blue);
		
		SetFontSize(80);
		DrawString(480, 365, "You Are Dead", GetColor(125, 0, 0));
		SetFontSize(50);
		DrawString(455, 600, "Push Space To Return Title", GetColor(125, 0, 0));
	}
}

#pragma endregion 

#pragma region SceneControl

Scenes GetCurrentScene()
{
	return current_scene;
}

void ChangeScene(Scenes scene) { current_scene = scene; }

#pragma endregion