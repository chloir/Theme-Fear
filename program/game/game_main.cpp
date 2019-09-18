#include "DxLib.h"
#include "game_main.h"
#include "../support/Support.h"
#include "Scenes.h"

bool init = false;
Scenes scene;

//=============================================================================
// name... game_main
// work... ゲームのメインループ
// arg.... none
// ret.... [ 正常終了 : 0 ]
//=============================================================================
int game_main()
{
	
	scene = GetCurrentScene();
	
	switch(scene)
	{
	case TITLE_SCENE:
		TitleScene();
		break;
	case MAIN_SCENE:
		MainScene();
		break;
	case END_SCENE:
		EndScene();
		break;
	}

	return 0 ;

}

