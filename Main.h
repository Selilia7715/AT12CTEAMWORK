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
#include "xinpututil.h"
#include <math.h>
#include <dshow.h>
#include <atlbase.h>

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
#define	CLASS_NAME		"�T���v��"				// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"DirectX���^����"	// �E�B���h�E�̖��O
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// FPS�ݒ�
#define FPS (60)

#define SCREEN_WIDTH	(1280)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)			// �E�C���h�E�̍���
#define VERTEX_MAX  (4)                 // ���_�̐�
#define COLOR_MAX  (255)                // �f�B�t���[�Y�F�̍ő�
#define KYARA_SPEED_MAX (5.0f*2)          // �L�����̃X�s�[�h
#define KYARA_FPS (15)                  // �L������FPS
#define CURSOR_X  (80)                  // �J�[�\����X���W
#define CURSOR_Y  (80)					// �J�[�\����Y���W
#define PLAYER_XSIZE  40.0f             // �v���C���[�̑傫��
#define PLAYER_YSIZE  80.0f

#define SHIELD_THICKNESS	5				//�V�[���h�̌���
#define SHIELD_WIDTH		30				//�V�[���h�̕�
#define PBETWEENS			50				//�L�����ƃV�[���h�̊Ԃ̋���
#define SEPARATEANGLE		16				//�V�[���h�̊p�x�̕�����

#define BUTTON_SIZE_X (220)					// �{�^���̑傫��X
#define BUTTON_SIZE_Y (100)					// �{�^���̑傫��Y
#define BUTTON_SIZEUP_X (15)				// �{�^���̃T�C�Y�A�b�vX
#define BUTTON_SIZEUP_Y (15)				// �{�^���̃T�C�Y�A�b�vY

#define XBOX_A (4096)                       // XBOX��A�{�^��
#define XBOX_B (8192)                       // XBOX��B�{�^��
#define XBOX_X (16384)                      // XBOX��X�{�^��
#define XBOX_Y (32768)                      // XBOX��Y�{�^��
#define XBOX_START (16)                     // XBOX��START�{�^��
#define XBOX_BACK (32)                      // XBOX��BACK�{�^��
#define XBOX_UP (1)                         // XBOX��UP�{�^��
#define XBOX_DOWN (2)                       // XBOX��DOWN�{�^��
#define XBOX_LEFT (4)                       // XBOX��LEFT�{�^��
#define XBOX_RIGHT (8)                      // XBOX��RIGHT�{�^��
#define XBOX_LB (256)                       // XBOX��LB�{�^��
#define XBOX_RB (512)                       // XBOX��RB�{�^��
#define XBOX_RSTICK_PUSH (128)              // XBOX�̉E�X�e�B�b�N��������
#define XBOX_LSTICK_PUSH (64)               // XBOX�̍��X�e�B�b�N��������
#define XBOX_LSTICK_X (32768)			    // XBOX�̍��X�e�B�b�N�̒l
#define XBOX_LSTICK_Y (32768)			    // XBOX�̍��X�e�B�b�N�̒l

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct VERTEX_2D {
	float x, y, z;
	float rhw;
	DWORD col;
	float u, v;  // �e�N�X�`�����W
}VERTEX_2D;

enum SCENE {
	TITLE,
	GAME,
	RESULT
};

#endif