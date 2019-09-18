#pragma once
enum Scenes
{
	TITLE_SCENE,
	MAIN_SCENE,
	END_SCENE
};

void TitleScene();

void MainScene();
void Update();
void Render();
void OnSceneExit();

void EndScene();

Scenes GetCurrentScene();
void ChangeScene(Scenes scene);