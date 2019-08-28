#pragma once
enum Scenes
{
	TITLE_SCENE,
	MAIN_SCENE,
	END_SCENE
};

void MainScene();
void Update();
void Render();

void EndScene();

void LoadCurrentScene();
void ChangeScene(Scenes scene);