#include "Title.h"

Title::Title()
{
	// �X�^�[�g�{�^���̏����l
	StartButtonPosition.x = 500.0f;
	StartButtonPosition.y = 420.0f;

	// �I�v�V�����{�^���̏����l
	OptionButtonPosition.x = 500.0f;
	OptionButtonPosition.y = 600.0f;

	// BGM�̏����l
	BGMPosition.x = 500.0f;
	BGMPosition.y = 420.0f;

	// SE�̏����l
	SEPosition.x = 500.0f;
	SEPosition.y = 600.0f;

	// �t���O�̏�����
	StartFlag = false;
	OptionFlag = false;
	S_Push_Button = false; 
	OP_Push_Button = false;
	Button_Change = false; 
	OP_Change = false;
	OP_Button_Change = false;
}

Title::~Title()
{
}

void Title::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// �e�N�X�`���`��(�^�C�g��)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/4.png", &title_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�^�C�g���̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	// �e�N�X�`���`��(�X�^�[�g�{�^�������O)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/Start_P.png", &StartButton_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�X�^�[�g�{�^���̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	// �e�N�X�`���`��(�X�^�[�g�{�^�������ꂽ)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/Start.png", &StartButton_pD3DTexture2)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�X�^�[�g�{�^���̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	// �e�N�X�`���`��(�I�v�V�����{�^�������O)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/Option_P.png", &OptionButton_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�I�v�V�����{�^���̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	// �e�N�X�`���`��(�I�v�V�����{�^�������ꂽ)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/Option.png", &OptionButton_pD3DTexture2)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�I�v�V�����{�^���̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
	// �e�N�X�`���`��(BGM)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/BGM.png", &BGM_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "BGM�̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
	// �e�N�X�`���`��(SE)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/SE.png", &SE_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "SE�̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	// �^�C�g��
	title_vertex[0].x = 0.0f;
	title_vertex[0].y = 0.0f;
	title_vertex[0].z = 0.0f;
	title_vertex[1].x = SCREEN_WIDTH;
	title_vertex[1].y = 0.0f;
	title_vertex[1].z = 0.0f;
	title_vertex[2].x = 0.0f;
	title_vertex[2].y = SCREEN_HEIGHT;
	title_vertex[2].z = 0.0f;
	title_vertex[3].x = SCREEN_WIDTH;
	title_vertex[3].y = SCREEN_HEIGHT;
	title_vertex[3].z = 0.0f;

	// RHW�̒l
	title_vertex[0].rhw = 1.0f;
	title_vertex[1].rhw = 1.0f;
	title_vertex[2].rhw = 1.0f;
	title_vertex[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	title_vertex[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_vertex[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_vertex[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_vertex[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	title_vertex[0].u = 0.0f;
	title_vertex[0].v = 0.0f;
	title_vertex[1].u = 1.0f;
	title_vertex[1].v = 0.0f;
	title_vertex[2].u = 0.0f;
	title_vertex[2].v = 1.0f;
	title_vertex[3].u = 1.0f;
	title_vertex[3].v = 1.0f;

	// �X�^�[�g�{�^��
	title_StartButton[0].x = StartButtonPosition.x;
	title_StartButton[0].y = StartButtonPosition.y;
	title_StartButton[0].z = 0.0f;
	title_StartButton[1].x = StartButtonPosition.x + BUTTON_SIZE_X;
	title_StartButton[1].y = StartButtonPosition.y;
	title_StartButton[1].z = 0.0f;
	title_StartButton[2].x = StartButtonPosition.x;
	title_StartButton[2].y = StartButtonPosition.y + BUTTON_SIZE_Y;
	title_StartButton[2].z = 0.0f;
	title_StartButton[3].x = StartButtonPosition.x + BUTTON_SIZE_X;
	title_StartButton[3].y = StartButtonPosition.y + BUTTON_SIZE_Y;
	title_StartButton[3].z = 0.0f;

	// RHW�̒l
	title_StartButton[0].rhw = 1.0f;
	title_StartButton[1].rhw = 1.0f;
	title_StartButton[2].rhw = 1.0f;
	title_StartButton[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	title_StartButton[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_StartButton[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_StartButton[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_StartButton[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	title_StartButton[0].u = 0.0f;
	title_StartButton[0].v = 0.0f;
	title_StartButton[1].u = 1.0f;
	title_StartButton[1].v = 0.0f;
	title_StartButton[2].u = 0.0f;
	title_StartButton[2].v = 1.0f;
	title_StartButton[3].u = 1.0f;
	title_StartButton[3].v = 1.0f;

	// �I�v�V�����{�^��
	title_OptionButton[0].x = OptionButtonPosition.x;
	title_OptionButton[0].y = OptionButtonPosition.y;
	title_OptionButton[0].z = 0.0f;
	title_OptionButton[1].x = OptionButtonPosition.x + BUTTON_SIZE_X;
	title_OptionButton[1].y = OptionButtonPosition.y;
	title_OptionButton[1].z = 0.0f;
	title_OptionButton[2].x = OptionButtonPosition.x;
	title_OptionButton[2].y = OptionButtonPosition.y + BUTTON_SIZE_Y;
	title_OptionButton[2].z = 0.0f;
	title_OptionButton[3].x = OptionButtonPosition.x + BUTTON_SIZE_X;
	title_OptionButton[3].y = OptionButtonPosition.y + BUTTON_SIZE_Y;
	title_OptionButton[3].z = 0.0f;

	// RHW�̒l
	title_OptionButton[0].rhw = 1.0f;
	title_OptionButton[1].rhw = 1.0f;
	title_OptionButton[2].rhw = 1.0f;
	title_OptionButton[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	title_OptionButton[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_OptionButton[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_OptionButton[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	title_OptionButton[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	title_OptionButton[0].u = 0.0f;
	title_OptionButton[0].v = 0.0f;
	title_OptionButton[1].u = 1.0f;
	title_OptionButton[1].v = 0.0f;
	title_OptionButton[2].u = 0.0f;
	title_OptionButton[2].v = 1.0f;
	title_OptionButton[3].u = 1.0f;
	title_OptionButton[3].v = 1.0f;

	// Option
	Option[0].x = 0.0f;
	Option[0].y = 0.0f;
	Option[0].z = 0.0f;
	Option[1].x = SCREEN_WIDTH;
	Option[1].y = 0.0f;
	Option[1].z = 0.0f;
	Option[2].x = 0.0f;
	Option[2].y = SCREEN_HEIGHT;
	Option[2].z = 0.0f;
	Option[3].x = SCREEN_WIDTH;
	Option[3].y = SCREEN_HEIGHT;
	Option[3].z = 0.0f;

	// RHW�̒l
	Option[0].rhw = 1.0f;
	Option[1].rhw = 1.0f;
	Option[2].rhw = 1.0f;
	Option[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	Option[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, 0);
	Option[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, 0);
	Option[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, 0);
	Option[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, 0);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	Option[0].u = 0.0f;
	Option[0].v = 0.0f;
	Option[1].u = 1.0f;
	Option[1].v = 0.0f;
	Option[2].u = 0.0f;
	Option[2].v = 1.0f;
	Option[3].u = 1.0f;
	Option[3].v = 1.0f;

	// BGM
	BGM[0].x = BGMPosition.x;
	BGM[0].y = BGMPosition.y;
	BGM[0].z = 0.0f;
	BGM[1].x = BGMPosition.x;
	BGM[1].y = BGMPosition.y;
	BGM[1].z = 0.0f;
	BGM[2].x = BGMPosition.x;
	BGM[2].y = BGMPosition.y;
	BGM[2].z = 0.0f;
	BGM[3].x = BGMPosition.x;
	BGM[3].y = BGMPosition.y;
	BGM[3].z = 0.0f;

	// RHW�̒l
	BGM[0].rhw = 1.0f;
	BGM[1].rhw = 1.0f;
	BGM[2].rhw = 1.0f;
	BGM[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	BGM[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	BGM[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	BGM[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	BGM[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	BGM[0].u = 0.0f;
	BGM[0].v = 0.0f;
	BGM[1].u = 1.0f;
	BGM[1].v = 0.0f;
	BGM[2].u = 0.0f;
	BGM[2].v = 1.0f;
	BGM[3].u = 1.0f;
	BGM[3].v = 1.0f;
	
	// SE
	SE[0].x = SEPosition.x;
	SE[0].y = SEPosition.y;
	SE[0].z = 0.0f;
	SE[1].x = SEPosition.x;
	SE[1].y = SEPosition.y;
	SE[1].z = 0.0f;
	SE[2].x = SEPosition.x;
	SE[2].y = SEPosition.y;
	SE[2].z = 0.0f;
	SE[3].x = SEPosition.x;
	SE[3].y = SEPosition.y;
	SE[3].z = 0.0f;

	// RHW�̒l
	SE[0].rhw = 1.0f;
	SE[1].rhw = 1.0f;
	SE[2].rhw = 1.0f;
	SE[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	SE[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	SE[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	SE[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	SE[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	SE[0].u = 0.0f;
	SE[0].v = 0.0f;
	SE[1].u = 1.0f;
	SE[1].v = 0.0f;
	SE[2].u = 0.0f;
	SE[2].v = 1.0f;
	SE[3].u = 1.0f;
	SE[3].v = 1.0f;

}

void Title::Draw(LPDIRECT3DDEVICE9 *device)
{
	if (OP_Change == false) // �^�C�g���̏���
	{
		// �^�C�g���`��
		(*device)->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		(*device)->SetTexture(0, title_pD3DTexture);

		// (*device)->DrawPrimitiveUP���Ă�
		(*device)->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&title_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

		if (StartFlag == false)
		{
			// �X�^�[�g�{�^���`��
			(*device)->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`�����|���S���ɃZ�b�g
			(*device)->SetTexture(0, StartButton_pD3DTexture);

			// (*device)->DrawPrimitiveUP���Ă�
			(*device)->DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
				2,                   // �|���S���̐�
				&title_StartButton[0],// ���_�f�[�^�\���̂̐擪�A�h���X
				sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
			);
		}
		else if (StartFlag == true)
		{
			// �X�^�[�g�{�^���`��
			(*device)->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`�����|���S���ɃZ�b�g
			(*device)->SetTexture(0, StartButton_pD3DTexture2);

			// (*device)->DrawPrimitiveUP���Ă�
			(*device)->DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
				2,                   // �|���S���̐�
				&title_StartButton[0],// ���_�f�[�^�\���̂̐擪�A�h���X
				sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
			);

		}

		if (OptionFlag == false)
		{
			// �I�v�V�����{�^���`��
			(*device)->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`�����|���S���ɃZ�b�g
			(*device)->SetTexture(0, OptionButton_pD3DTexture);

			// (*device)->DrawPrimitiveUP���Ă�
			(*device)->DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
				2,                   // �|���S���̐�
				&title_OptionButton[0], // ���_�f�[�^�\���̂̐擪�A�h���X
				sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
			);
		}
		else if (OptionFlag == true)
		{
			// �I�v�V�����{�^���`��
			(*device)->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`�����|���S���ɃZ�b�g
			(*device)->SetTexture(0, OptionButton_pD3DTexture2);

			// (*device)->DrawPrimitiveUP���Ă�
			(*device)->DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
				2,                   // �|���S���̐�
				&title_OptionButton[0], // ���_�f�[�^�\���̂̐擪�A�h���X
				sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
			);
		}
	}
	else // �I�v�V�����̏���
	{
		// BGM�`��
		(*device)->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		(*device)->SetTexture(0, BGM_pD3DTexture);

		// (*device)->DrawPrimitiveUP���Ă�
		(*device)->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&BGM[0], // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

		// SE�`��
		(*device)->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		(*device)->SetTexture(0, SE_pD3DTexture);

		// (*device)->DrawPrimitiveUP���Ă�
		(*device)->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&SE[0], // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);
	}
}

void Title::Update(int *scene)
{
	UpdateInput();

	// XBOX�R���g���[���[�̒l
	int button = GetXinputButton(0);

	if (OP_Change == false)
	{
		// ���{�^��
		if (button == XBOX_DOWN)
		{
			Button_Change = true;
		}

		// ���{�^��
		if (button == XBOX_UP)
		{
			Button_Change = false;
		}

		// �{�^���؂�ւ�(�I�΂�Ă���{�^�����傫���Ȃ��Ă���)
		if (Button_Change == false)
		{
			// �X�^�[�g�{�^��
			title_StartButton[0].x = StartButtonPosition.x - BUTTON_SIZEUP_X;
			title_StartButton[0].y = StartButtonPosition.y - BUTTON_SIZEUP_Y;
			title_StartButton[0].z = 0.0f;
			title_StartButton[1].x = StartButtonPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			title_StartButton[1].y = StartButtonPosition.y - BUTTON_SIZEUP_Y;
			title_StartButton[1].z = 0.0f;
			title_StartButton[2].x = StartButtonPosition.x - BUTTON_SIZEUP_X;
			title_StartButton[2].y = StartButtonPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			title_StartButton[2].z = 0.0f;
			title_StartButton[3].x = StartButtonPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			title_StartButton[3].y = StartButtonPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			title_StartButton[3].z = 0.0f;

			// �I�v�V�����{�^��
			title_OptionButton[0].x = OptionButtonPosition.x;
			title_OptionButton[0].y = OptionButtonPosition.y;
			title_OptionButton[0].z = 0.0f;
			title_OptionButton[1].x = OptionButtonPosition.x + BUTTON_SIZE_X;
			title_OptionButton[1].y = OptionButtonPosition.y;
			title_OptionButton[1].z = 0.0f;
			title_OptionButton[2].x = OptionButtonPosition.x;
			title_OptionButton[2].y = OptionButtonPosition.y + BUTTON_SIZE_Y;
			title_OptionButton[2].z = 0.0f;
			title_OptionButton[3].x = OptionButtonPosition.x + BUTTON_SIZE_X;
			title_OptionButton[3].y = OptionButtonPosition.y + BUTTON_SIZE_Y;
			title_OptionButton[3].z = 0.0f;

			// A�{�^��
			if (button == XBOX_A)
			{
				S_Push_Button = true;
			}

		}
		else if (Button_Change == true)
		{
			// �X�^�[�g�{�^��
			title_StartButton[0].x = StartButtonPosition.x;
			title_StartButton[0].y = StartButtonPosition.y;
			title_StartButton[0].z = 0.0f;
			title_StartButton[1].x = StartButtonPosition.x + BUTTON_SIZE_X;
			title_StartButton[1].y = StartButtonPosition.y;
			title_StartButton[1].z = 0.0f;
			title_StartButton[2].x = StartButtonPosition.x;
			title_StartButton[2].y = StartButtonPosition.y + BUTTON_SIZE_Y;
			title_StartButton[2].z = 0.0f;
			title_StartButton[3].x = StartButtonPosition.x + BUTTON_SIZE_X;
			title_StartButton[3].y = StartButtonPosition.y + BUTTON_SIZE_Y;
			title_StartButton[3].z = 0.0f;

			// �I�v�V�����{�^��
			title_OptionButton[0].x = OptionButtonPosition.x - BUTTON_SIZEUP_X;
			title_OptionButton[0].y = OptionButtonPosition.y - BUTTON_SIZEUP_Y;
			title_OptionButton[0].z = 0.0f;
			title_OptionButton[1].x = OptionButtonPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			title_OptionButton[1].y = OptionButtonPosition.y - BUTTON_SIZEUP_Y;
			title_OptionButton[1].z = 0.0f;
			title_OptionButton[2].x = OptionButtonPosition.x - BUTTON_SIZEUP_X;
			title_OptionButton[2].y = OptionButtonPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			title_OptionButton[2].z = 0.0f;
			title_OptionButton[3].x = OptionButtonPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			title_OptionButton[3].y = OptionButtonPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			title_OptionButton[3].z = 0.0f;

			// A�{�^���őJ��
			if (button == XBOX_A)
			{
				OP_Change = true;
			}
		}

		// Start�{�^���������ꂽ�Ƃ�
		if (S_Push_Button == true)
		{
			if (cnt <= 50)
			{
				cnt++;
				StartFlag = true;
			}
			else if (cnt > 50)
			{
				*scene = 2;
				cnt = 0;
				S_Push_Button = false;
			}
		}

		// Option�{�^���������ꂽ�Ƃ�
		if (OP_Push_Button == true)
		{
			OptionFlag = true;
		}
	}
	else
	{
		// ���{�^��
		if (button == XBOX_DOWN)
		{
			OP_Button_Change = true;
		}

		// ���{�^��
		if (button == XBOX_UP)
		{
			OP_Button_Change = false;
		}

		// BGM
		if (OP_Button_Change == false)
		{
			// �X�^�[�g�{�^��
			BGM[0].x = BGMPosition.x - BUTTON_SIZEUP_X;
			BGM[0].y = BGMPosition.y - BUTTON_SIZEUP_Y;
			BGM[0].z = 0.0f;
			BGM[1].x = BGMPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			BGM[1].y = BGMPosition.y - BUTTON_SIZEUP_Y;
			BGM[1].z = 0.0f;
			BGM[2].x = BGMPosition.x - BUTTON_SIZEUP_X;
			BGM[2].y = BGMPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			BGM[2].z = 0.0f;
			BGM[3].x = BGMPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			BGM[3].y = BGMPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			BGM[3].z = 0.0f;

			// �I�v�V�����{�^��
			SE[0].x = SEPosition.x;
			SE[0].y = SEPosition.y;
			SE[0].z = 0.0f;
			SE[1].x = SEPosition.x + BUTTON_SIZE_X;
			SE[1].y = SEPosition.y;
			SE[1].z = 0.0f;
			SE[2].x = SEPosition.x;
			SE[2].y = SEPosition.y + BUTTON_SIZE_Y;
			SE[2].z = 0.0f;
			SE[3].x = SEPosition.x + BUTTON_SIZE_X;
			SE[3].y = SEPosition.y + BUTTON_SIZE_Y;
			SE[3].z = 0.0f;

			// A�{�^���őJ��
			if (button == XBOX_A)
			{
				OP_Change = false;
			}

		}
		else if(OP_Button_Change == true) // SE
		{
			// �X�^�[�g�{�^��
			BGM[0].x = BGMPosition.x;
			BGM[0].y = BGMPosition.y;
			BGM[0].z = 0.0f;
			BGM[1].x = BGMPosition.x + BUTTON_SIZE_X;
			BGM[1].y = BGMPosition.y;
			BGM[1].z = 0.0f;
			BGM[2].x = BGMPosition.x;
			BGM[2].y = BGMPosition.y + BUTTON_SIZE_Y;
			BGM[2].z = 0.0f;
			BGM[3].x = BGMPosition.x + BUTTON_SIZE_X;
			BGM[3].y = BGMPosition.y + BUTTON_SIZE_Y;
			BGM[3].z = 0.0f;

			// �I�v�V�����{�^��
			SE[0].x = SEPosition.x - BUTTON_SIZEUP_X;
			SE[0].y = SEPosition.y - BUTTON_SIZEUP_Y;
			SE[0].z = 0.0f;
			SE[1].x = SEPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			SE[1].y = SEPosition.y - BUTTON_SIZEUP_Y;
			SE[1].z = 0.0f;
			SE[2].x = SEPosition.x - BUTTON_SIZEUP_X;
			SE[2].y = SEPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			SE[2].z = 0.0f;
			SE[3].x = SEPosition.x + BUTTON_SIZE_X + BUTTON_SIZEUP_X;
			SE[3].y = SEPosition.y + BUTTON_SIZE_Y + BUTTON_SIZEUP_Y;
			SE[3].z = 0.0f;
		}
    }
}

void Title::Uninit()
{
	// �^�C�g���̉��
	if (title_pD3DTexture != NULL)
	{
		title_pD3DTexture->Release();
		title_pD3DTexture = NULL;
	}

	// �X�^�[�g�{�^���̉��
	if (StartButton_pD3DTexture != NULL)
	{
		StartButton_pD3DTexture->Release();
		StartButton_pD3DTexture = NULL;
	}

	// �X�^�[�g�{�^���̉��
	if (StartButton_pD3DTexture2 != NULL)
	{
		StartButton_pD3DTexture2->Release();
		StartButton_pD3DTexture2 = NULL;
	}

	// �I�v�V�����{�^���̉��
	if (OptionButton_pD3DTexture != NULL)
	{
		OptionButton_pD3DTexture->Release();
		OptionButton_pD3DTexture = NULL;
	}

	// �I�v�V�����{�^���̉��
	if (OptionButton_pD3DTexture2 != NULL)
	{
		OptionButton_pD3DTexture2->Release();
		OptionButton_pD3DTexture2 = NULL;
	}

	// BGM�̉��
	if (BGM_pD3DTexture != NULL)
	{	
		BGM_pD3DTexture->Release();
		BGM_pD3DTexture = NULL;
	}

	// SE�̉��
	if (SE_pD3DTexture != NULL)
	{	
		SE_pD3DTexture->Release();
		SE_pD3DTexture = NULL;
	}
}
