#include "DxLib.h"
#include "game_main.h"
#include "../support/Support.h"
#include "MainScene.h"
#include <time.h>
#include <math.h>
#include <string>

//=============================================================================
// name... game_main
// work... �Q�[���̃��C�����[�v
// arg.... none
// ret.... [ ����I�� : 0 ]
//=============================================================================
int game_main()
{
	SetBackgroundColor(250, 250, 250);

	MainScene();

	return 0 ;

}

