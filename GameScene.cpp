#include "GameScene.h"

//SetMapChip�N���X��static�����o�ϐ��̏�����
int GameScene::SetMapChip::stage[STAGEMAX] = { 320 };
int GameScene::SetMapChip::Stage1Blocktexinfo[SEPARATEHEIGHT][320]{
	//stage1ver
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,			-1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,							  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,			   -1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,					-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};
float GameScene::SetMapChip::CameraCoord = SCREEN_WIDTH;

//Player�N���X��static�����o�ϐ��̏�����
D3DVECTOR GameScene::Player::m_playerPosition = { 500,300,0 };



// GameScene�̃R���X�g���N�^
GameScene::GameScene()
{
}

// GameScene�̃f�X�g���N�^
GameScene::~GameScene()
{
}

// GameScene�̏�����
void GameScene::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl) {
	game.Init(pHWND, device, tex, pcl);				// �w�i
	mapchip.InitMapchip(pHWND, device, tex, pcl);	//�}�b�v�`�b�v
	player.Init(pHWND, device, tex, pcl);			//�v���C���[
}

// GameScene�̕`��
void GameScene::Draw(LPDIRECT3DDEVICE9 *device)
{
	game.Draw(device);	  // �w�i
	mapchip.DrawMapchip(device);	//�}�b�v�`�b�v
	player.Draw(device);
}

// GameScene�̍X�V
void GameScene::Update(int *scene)
{
	game.Update();		   // �w�i
	player.Update(scene);
}

// GameScene�̉��
void GameScene::Uninit(void)
{
	game.Uninit(); 	  // �w�i
	mapchip.Uninit();	//�}�b�v�`�b�v
	player.Uninit();
}

// �w�i�̃R���X�g���N�^
GameScene::Game::Game()
{
}

// �w�i�̃f�X�g���N�^
GameScene::Game::~Game()
{
}

// �w�i�̏�����
void GameScene::Game::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// �e�N�X�`���`��(�w�i)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/46.jpg", &m_game_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�w�i�̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

// �w�i�̕`��	
void GameScene::Game::Draw(LPDIRECT3DDEVICE9 *device)
{
	// �w�i
	VERTEX_2D game_vertex[4] = {
	{0,0,0,1,D3DCOLOR_ARGB(255,255,255,255),0,0},
	{SCREEN_WIDTH,0,0,1,D3DCOLOR_ARGB(255,255,255,255),1,0},
	{0,SCREEN_HEIGHT,0,1,D3DCOLOR_ARGB(255,255,255,255),0,1},
	{SCREEN_WIDTH,SCREEN_HEIGHT,0,1,D3DCOLOR_ARGB(255,255,255,255),1,1},
	};

	// �w�i�`��
	(*device)->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	(*device)->SetTexture(0, m_game_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&game_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

// �w�i�̍X�V
void GameScene::Game::Update()
{
	// ��
}

// �w�i�̏I������
void GameScene::Game::Uninit()
{
	// �e�N�X�`���̉��
	if (m_game_pD3DTexture != NULL)
	{
		m_game_pD3DTexture->Release();
		m_game_pD3DTexture = NULL;
	}
}

// �n�ʂ̃R���X�g���N�^

void GameScene::GameScene::SetMapChip::InitMapchip(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl) {
	// �e�N�X�`���`��(�n��)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/field002.jpg", &Blocktex[0])) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�n�ʂ̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}


void GameScene::SetMapChip::UpdateMapchip(int num) {		//�����F���[�h�������X�e�[�W�ԍ�	�X�e�[�W���ς��Ƃ��Ɏg�p!
	currentstagenum = num;							
	CameraCoord = SCREEN_WIDTH;						//�X�e�[�W���W������
}

void GameScene::SetMapChip::DrawMapchip(LPDIRECT3DDEVICE9 *device) {

	DrawBlock(*device);						//�u���b�N�`��

}

void GameScene::SetMapChip::Uninit() {
	for (int i = 0; i < STAGEMAX; i++) {
		if (Blocktex[i] != NULL)
		{
			Blocktex[i]->Release();
			Blocktex[i] = NULL;
		}
	}
}

void GameScene::SetMapChip::DrawBlock(LPDIRECT3DDEVICE9 device) {

	switch (currentstagenum)							
	{
	case 1:
		for (int x = 0; x < stage[0]; x++) {
			for (int y = 0; y < SEPARATEHEIGHT; y++) {

				StageBlock[0].x = x * BLOCK_WIDTH - CameraCoord;
				StageBlock[0].y = y * BLOCK_HEIGHT;
				StageBlock[0].z = 0.0f;

				StageBlock[1].x = x * BLOCK_WIDTH + BLOCK_WIDTH - CameraCoord;
				StageBlock[1].y = y * BLOCK_HEIGHT;
				StageBlock[1].z = 0.0f;

				StageBlock[2].x = x * BLOCK_WIDTH - CameraCoord;
				StageBlock[2].y = y * BLOCK_HEIGHT + BLOCK_HEIGHT;
				StageBlock[2].z = 0.0f;

				StageBlock[3].x = x * BLOCK_WIDTH + BLOCK_WIDTH - CameraCoord;
				StageBlock[3].y = y * BLOCK_HEIGHT + BLOCK_HEIGHT;
				StageBlock[3].z = 0.0f;

				for (int i = 0; i <= 3; i++) {
					// RHW�̒l
					StageBlock[i].rhw = 1.0f;
					// �f�B�t���[�Y�F�̐ݒ�
					StageBlock[i].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
				}
				// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
				StageBlock[0].u = 0.0f;
				StageBlock[0].v = 0.0f;
				StageBlock[1].u = 1.0f;
				StageBlock[1].v = 0.0f;
				StageBlock[2].u = 0.0f;
				StageBlock[2].v = 1.0f;
				StageBlock[3].u = 1.0f;
				StageBlock[3].v = 1.0f;

				// �`��								��ʏ�݂̂̕`�������
				(device)->SetFVF(FVF_VERTEX_2D);

				//if (StageBlock[0].x >= CameraCoord - SCREEN_WIDTH
				//					&& StageBlock[0].x <= CameraCoord) {			//�X�N���[�����Ƀu���b�N������Ȃ�
					if (Stage1Blocktexinfo[y][x] != MAPCHIP::NONE) {					//�����u���b�N������Ȃ�
						//�u���b�N�e�N�X�`���Z�b�g
						(device)->SetTexture(0, Blocktex[Stage1Blocktexinfo[y][x]]);
						// g_pD3DDevice->DrawPrimitiveUP���Ă�
						(device)->DrawPrimitiveUP(
							D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
							2,                   // �|���S���̐�
							&StageBlock[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
							sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
						);
					}
				/*}*/
			}
		}
		break;
	default:
		break;
	}
}

void GameScene::SetMapChip::UpdateStageCoord() {
	if (CameraCoord - Player::m_playerPosition.x <= CameraCoord - SCREEN_WIDTH / SEPARATESCROLLNUM) {
		CameraCoord += BLOCK_WIDTH;
		Player::m_playerPosition.x -= KYARA_SPEED_MAX;
	}
	if (CameraCoord - Player::m_playerPosition.x >= CameraCoord - SCREEN_WIDTH / 5) {
		CameraCoord -= BLOCK_WIDTH;
		Player::m_playerPosition.x += KYARA_SPEED_MAX;
	}

}

//void GameScene::SetMapChip::SetTriangleTex(float x1, float y1, float x2, float y2, float x3, float y3, int texnum, LPDIRECT3DDEVICE9 device) {
//
//
//	StageBlock[0].x = x1;
//	StageBlock[0].y = y1;
//	StageBlock[0].z = 0;
//
//	StageBlock[1].x = x2;
//	StageBlock[1].y = y2;
//	StageBlock[1].z = 0;
//
//	StageBlock[2].x = x3;
//	StageBlock[2].y = y3;
//	StageBlock[2].z = 0;
//
//	for (int i = 0; i <= 2; i++) {
//		// RHW�̒l
//		StageBlock[i].rhw = 1.0f;
//		// �f�B�t���[�Y�F�̐ݒ�
//		StageBlock[i].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
//	}
//	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
//	StageBlock[0].u = 0.0f;
//	StageBlock[0].v = 0.0f;
//	StageBlock[1].u = 1.0f;
//	StageBlock[1].v = 0.0f;
//	StageBlock[2].u = 0.0f;
//	StageBlock[2].v = 1.0f;
//	// �`��
//	(device)->SetFVF(FVF_VERTEX_2D);
//
//	//�m�[�}���u���b�N�e�N�X�`���Z�b�g
//	if (texnum == MAPCHIP::BLOCK) {
//		(device)->SetTexture(0, m_NormalBlocktex);
//		// g_pD3DDevice->DrawPrimitiveUP���Ă�
//		(device)->DrawPrimitiveUP(
//			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
//			2,                   // �|���S���̐�
//			&StageBlock[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
//			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
//		);
//	}
//}

// �O�p�`�̃}�b�v�`�b�v
void GameScene::SetMapChip::DrawDiagonalMapchip(LPDIRECT3DDEVICE9 device) {


}

// Player�̃R���X�g���N�^
GameScene::Player::Player()
{
	
}

// Player�̃f�X�g���N�^
GameScene::Player::~Player()
{

}

// Player�`��̏�����
void GameScene::Player::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// Player�`��(player)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/5.png", &m_player_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "player�̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	// Player�`��(shield)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/5.png", &m_shield_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "shield�̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	// Player
	player_vertex[0].x = m_playerPosition.x;
	player_vertex[0].y = m_playerPosition.y;
	player_vertex[0].z = m_playerPosition.z;

	player_vertex[1].x = m_playerPosition.x + PLAYER_XSIZE;
	player_vertex[1].y = m_playerPosition.y;
	player_vertex[1].z = m_playerPosition.z;

	player_vertex[2].x = m_playerPosition.x;
	player_vertex[2].y = m_playerPosition.y + PLAYER_YSIZE;
	player_vertex[2].z = m_playerPosition.z;

	player_vertex[3].x = m_playerPosition.x + PLAYER_XSIZE;
	player_vertex[3].y = m_playerPosition.y + PLAYER_YSIZE;
	player_vertex[3].z = m_playerPosition.z;

	// RHW�̒l
	player_vertex[0].rhw = 1.0f;
	player_vertex[1].rhw = 1.0f;
	player_vertex[2].rhw = 1.0f;
	player_vertex[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	player_vertex[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	player_vertex[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	player_vertex[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	player_vertex[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(3���ɐ؂邽��)
	player_vertex[0].u = 0.0f;
	player_vertex[0].v = 0.0f;
	player_vertex[1].u = 0.33f;
	player_vertex[1].v = 0.0f;
	player_vertex[2].u = 0.0f;
	player_vertex[2].v = 0.25f;
	player_vertex[3].u = 0.33f;
	player_vertex[3].v = 0.25f;

	// Shield
	shield_vertex[0].x = m_shieldPosistion.x;
	shield_vertex[0].y = m_shieldPosistion.y;

	shield_vertex[1].x = m_shieldPosistion.x + SHIELD_THICKNESS;
	shield_vertex[1].y = m_shieldPosistion.y;

	shield_vertex[2].x = m_shieldPosistion.x;
	shield_vertex[2].y = m_shieldPosistion.y + SHIELD_WIDTH;

	shield_vertex[3].x = m_shieldPosistion.x + SHIELD_THICKNESS;
	shield_vertex[3].y = m_shieldPosistion.y + SHIELD_WIDTH;

	// RHW�̒l
	shield_vertex[0].rhw = 1.0f;
	shield_vertex[1].rhw = 1.0f;
	shield_vertex[2].rhw = 1.0f;
	shield_vertex[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	shield_vertex[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	shield_vertex[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	shield_vertex[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	shield_vertex[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(3���ɐ؂邽��)
	shield_vertex[0].u = 0.0f;
	shield_vertex[0].v = 0.0f;
	shield_vertex[1].u = 0.33f;
	shield_vertex[1].v = 0.0f;
	shield_vertex[2].u = 0.0f;
	shield_vertex[2].v = 0.25f;
	shield_vertex[3].u = 0.33f;
	shield_vertex[3].v = 0.25f;
}

// Player�̍X�V
void GameScene::Player::Update(int *scene)
{
	UpdateInput();
	//���x�{�����x
	PlayerSpeed.x += PlayerAddSpeed.x;
	PlayerSpeed.y += PlayerAddSpeed.y;

	//���ݍ��W�{���x
	m_playerPosition.x += PlayerSpeed.x;
	m_playerPosition.y += PlayerSpeed.y;


	// Player
	player_vertex[0].x = m_playerPosition.x;
	player_vertex[0].y = m_playerPosition.y;
	player_vertex[0].z = m_playerPosition.z;

	player_vertex[1].x = m_playerPosition.x + PLAYER_XSIZE;
	player_vertex[1].y = m_playerPosition.y;
	player_vertex[1].z = m_playerPosition.z;

	player_vertex[2].x = m_playerPosition.x;
	player_vertex[2].y = m_playerPosition.y + PLAYER_YSIZE;
	player_vertex[2].z = m_playerPosition.z;

	player_vertex[3].x = m_playerPosition.x + PLAYER_XSIZE;
	player_vertex[3].y = m_playerPosition.y + PLAYER_YSIZE;
	player_vertex[3].z = m_playerPosition.z;

	// Shield
	shield_vertex[0].x = m_shieldPosistion.x;
	shield_vertex[0].y = m_shieldPosistion.y;

	shield_vertex[1].x = m_shieldPosistion.x + SHIELD_THICKNESS;
	shield_vertex[1].y = m_shieldPosistion.y;

	shield_vertex[2].x = m_shieldPosistion.x;
	shield_vertex[2].y = m_shieldPosistion.y + SHIELD_WIDTH;

	shield_vertex[3].x = m_shieldPosistion.x + SHIELD_THICKNESS;
	shield_vertex[3].y = m_shieldPosistion.y + SHIELD_WIDTH;

	// XBOX
	//�ړ�����
	// �E(-255��1�̊Ԃ̎��͉E�֓���)
	if (GetXinputThumbLX(0) < 0)
	{
		now_playerPosition.x -= KYARA_SPEED_MAX;
	}
	// ��(1��255�̊Ԃ̎��͍��֓���)
	if (GetXinputThumbLX(0) > 0)
	{
		now_playerPosition.x += KYARA_SPEED_MAX;
	}
	// ��(1��255�̊Ԃ̎��͏�֓���)
	if (GetXinputThumbLY(0) < 0)
	{
		now_playerPosition.y += KYARA_SPEED_MAX;
	}
	// ��(-255��1�̎��͉��֓���)
	if (GetXinputThumbLY(0) > 0)
	{
		now_playerPosition.y -= KYARA_SPEED_MAX;
	}

	// �V�[���h�֐��Ăяo��
	DesideShieldPlace();

	// XBOX(�΂߈ړ�)
	float moveHorizontal = 0;
	float moveVertical = 0;

	moveHorizontal = GetXinputThumbLX(moveHorizontal);
	moveVertical = GetXinputThumbLY(moveVertical);

	CheckLand();			//LandFgupdate
	FreeFall();				//�d�͏���
	PlayerOperation();		//�v���C���[����
	

	//if (!isflg)
	//{
	//	if ((moveHorizontal >= 0.5 || moveVertical >= 0.5) && moveVertical <= 0)  // �E�ֈړ�
	//	{
	//		// �^��
	//		if (moveHorizontal == 0 && moveVertical == -1)
	//		{
	//			isflg = true;
	//		}
	//		// �E���ɒ��˂�
	//		else if (0.176 < moveVertical / moveHorizontal && moveVertical / moveHorizontal < 1.191) //10�`50
	//		{
	//			isflg = true;
	//		}
	//		// �E��ɒ��˂�
	//		else if (1.191 <= moveVertical / moveHorizontal) // 50�`90
	//		{
	//			isflg = true;
	//		}
	//		// �����ɒ��˂�
	//		else if (-0.176 > moveVertical / moveHorizontal && moveVertical / moveHorizontal > -1.191)
	//		{
	//			isflg = true;
	//		}
	//		// ����ɒ��˂�
	//		else if (-1.191 >= moveVertical / moveHorizontal)
	//		{
	//			isflg = true;
	//		}
	//	}
	//}

	// �V�[���J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		*scene = 3;
	}
}



// �V�[���h
void GameScene::Player::DesideShieldPlace() {										//�V�[���h�ʒu����

	
	if (GetXinputThumbRX(0) > 100 || GetXinputThumbRX(0) < -100 ||
		GetXinputThumbRY(0) > 100 || GetXinputThumbRX(0) < -100) {
		SHIELD_Fg = true;
	}
	else {
		SHIELD_Fg = false;
	}

	if (SHIELD_Fg == true) {
		//�E�A�i���O�X�e�B�b�N�̍��W�i�[
		m_shieldPosistion.x = m_playerPosition.x + GetXinputThumbRX(0);
		m_shieldPosistion.y = m_playerPosition.y + GetXinputThumbRY(0);

		//�V�[���h�ƃL�����Ƃ̑��΍��W�̎ΐ�
		float DiagonalLine = 0;
		DiagonalLine = D3DXVec2Length(&m_shieldPosistion);

		//PBETWEENS�Ƃ̔䗦
		float Diagonalratio = 0;
		Diagonalratio = PBETWEENS / DiagonalLine;


		//�V�[���h���W�i�[
		m_shieldPosistion.x *= Diagonalratio;
		m_shieldPosistion.y *= Diagonalratio;
	}
}

// Player�̕`��
void GameScene::Player::Draw(LPDIRECT3DDEVICE9 *device)
{
	// player�̕`��
	(*device)->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	(*device)->SetTexture(0, m_player_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&player_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// sheild�̕`��
	if (SHIELD_Fg == true)
	{
		(*device)->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		(*device)->SetTexture(0, m_shield_pD3DTexture);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		(*device)->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&shield_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);
	}
}

// Player�̏I������
void GameScene::Player::Uninit()
{
	// player�e�N�X�`���̉��
	if (m_player_pD3DTexture != NULL)
	{
		m_player_pD3DTexture->Release();
		m_player_pD3DTexture = NULL;
	}

	// shield�e�N�X�`���̉��
	if (m_shield_pD3DTexture != NULL)
	{
		m_shield_pD3DTexture->Release();
		m_shield_pD3DTexture = NULL;
	}
}

//�x�N�g���̈����Z
VERTEX_2D GameScene::Player::sub_vector(const VERTEX_2D& a, const VERTEX_2D& b)
{
	VERTEX_2D ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

// �߂�l    0:�O�p�`�̓����ɓ_������    1:�O�p�`�̊O���ɓ_������
// ����		A,B,C�͏��Ԃɓ���邱�ƁAP�͓����蔻����Ƃ肽���_
int	GameScene::Player::BetweenPointsCollision(VERTEX_2D A, VERTEX_2D B, VERTEX_2D C, VERTEX_2D P) {

	VERTEX_2D AB = sub_vector(B, A);
	VERTEX_2D BP = sub_vector(P, B);

	VERTEX_2D BC = sub_vector(C, B);
	VERTEX_2D CP = sub_vector(P, C);

	VERTEX_2D CA = sub_vector(A, C);
	VERTEX_2D AP = sub_vector(P, A);

	//�O��    Z���������v�Z����΂悢�ł�
	double c1 = AB.x * BP.y - AB.y * BP.x;
	double c2 = BC.x * CP.y - BC.y * CP.x;
	double c3 = CA.x * AP.y - CA.y * AP.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
		//�O�p�`�̓����ɓ_������
		return 0;
	}

	//�O�p�`�̊O���ɓ_������
	return 1;

}

void GameScene::Player:: FreeFall() {
	if (LandFg == false) {
		{
			PlayerAddSpeed.y += Gravity;
		}
	}
	else {
		PlayerAddSpeed.y = 0.0f;
		PlayerSpeed.y = 0.0f;
	}
};

void GameScene::Player::CheckLand() {


	if (m_playerPosition.y + PLAYER_YSIZE >= 500.0f) {
		LandFg = true;
		JumpFg = false;

	}
	else {
		LandFg = false;
	}

}

void GameScene::Player::PlayerOperation() {
	//�L�[����
	if (JumpFg == false
		&& LandFg == true) {
		if (GetXinputButton(0) == XBOX_A) {		//�W�����v
			PlayerSpeed.y += JumpASpeed;
			JumpFg = true;
		}
	}
	// XBOX
	//�ړ�����
	// ��(-255��1�̊Ԃ̎��͍��֓���)
	if (GetXinputThumbLX(0) < 0)
	{
		m_playerPosition.x -= KYARA_SPEED_MAX;
		GameScene::SetMapChip::UpdateStageCoord();

	}

	// �E(1��255�̊Ԃ̎��͉E�֓���)
	if (GetXinputThumbLX(0) > 0)
	{
		m_playerPosition.x += KYARA_SPEED_MAX;
		GameScene::SetMapChip::UpdateStageCoord();

	}

	// ��(1��255�̊Ԃ̎��͏�֓���)
	if (GetXinputThumbLY(0) < 0)
	{
		m_playerPosition.y += KYARA_SPEED_MAX;
	}

	// ��(-255��1�̎��͉��֓���)
	if (GetXinputThumbLY(0) > 0)
	{
		m_playerPosition.y -= KYARA_SPEED_MAX;
	}

};