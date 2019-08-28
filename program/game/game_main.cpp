#include "DxLib.h"
#include "game_main.h"
#include "../support/Support.h"
#include "Scenes.h"

bool init = false;

//=============================================================================
// name... game_main
// work... �Q�[���̃��C�����[�v
// arg.... none
// ret.... [ ����I�� : 0 ]
//=============================================================================
int game_main()
{
	if(!init)
	{
		SetBackgroundColor(250, 250, 250);
		ChangeScene(MAIN_SCENE);
		init = true;
	}

	LoadCurrentScene();

	return 0 ;

}

