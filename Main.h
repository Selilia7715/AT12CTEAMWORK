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

#define SCREEN_WIDTH	(1200)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(600)			// �E�C���h�E�̍���
#define VERTEX_MAX  (4)                 // ���_�̐�
#define COLOR_MAX  (255)                // �f�B�t���[�Y�F�̍ő�
#define KYARA_SPEED_MAX (20.0f)          // �L�����̃X�s�[�h
#define KYARA_FPS (15)                  // �L������FPS
#define CURSOR_X  (80)                  // �J�[�\����X���W
#define CURSOR_Y  (80)					// �J�[�\����Y���W
#define PLAYER_SIZE (80.0f)             // �v���C���[�̑傫��

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

#endif