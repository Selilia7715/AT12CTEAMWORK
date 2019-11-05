//=============================================================================
//
// DX21
// DirectX���^���� [main.h]
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "d3dx9.h"						// �`�揈���ɕK�v
#include "XAudio2.h"
#include "Input.h"


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"��
// �Ώۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")		// �`�揈���ɕK�v
#pragma comment (lib, "d3dx9.lib")		// [d3d9.lib]�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")		// DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")      // ���ݎ����擾���ɕK�v

#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1200)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(600)			// �E�C���h�E�̍���
#define VERTEX_MAX  (4)                 // ���_�̐�
#define COLOR_MAX  (255)                // �f�B�t���[�Y�F�̍ő�
#define KYARA_SPEED_MAX (6.0f)          // �L�����̃X�s�[�h
#define KYARA_FPS (15)                  // �L������FPS
#define PLAYERBULLET_SPEED (20)         // player�̒e�̑��x
#define PLAYERROLL_SPEED (20)           // ���L�����̉�]���x
#define ANGLE (90.0f)                      // �e�̊p�x
#define ROLL_MAX  (100)


enum SCENE
{
	TITLE = 1,
	GAME,
	RESULT
};

SCENE scene = TITLE;
#endif