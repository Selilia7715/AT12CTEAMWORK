#pragma once
#include	<xinput.h>

#define MAX_CONTROLLERS 4  // �w�a�n�w�R���g���[���͂l�`�w�S�܂� 
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

// XINPUT �R���g���[�����
struct CONTROLLER_STATE
{
	XINPUT_STATE state;							// XINPUT�R���g���[���̏��
	bool bConnected;							// �ڑ�����Ă��邩�ۂ�
};

void InitXinputState();							// XINPUT ������;
HRESULT UpdateXinputControllerState();			// XINPUT UPDATE
WORD GetXinputButton(int i);					// �w�a�n�w�R���g���[���̃{�^�������f�d�s
int  GetXinputLeftTrigger(int idx);				// �w�a�n�w�R���g���[���̍��g���K�[�l�i�O�|�Q�T�T�j���f�d�s
int  GetXinputRightTrigger(int idx);		    // �w�a�n�w�R���g���[���̉E�g���K�[�l�i�O�|�Q�T�T�j���f�d�s
int  GetXinputThumbLX(int idx);					// �w�a�n�w�R���g���[���̍��A�i���O�R���g���[���w�l���f�d�s
int  GetXinputThumbLY(int idx);					// �w�a�n�w�R���g���[���̍��A�i���O�R���g���[���x�l���f�d�s
int  GetXinputThumbRX(int idx);					// �w�a�n�w�R���g���[���̉E�A�i���O�R���g���[���w�l���f�d�s
int  GetXinputThumbRY(int idx);					// �w�a�n�w�R���g���[���̉E�A�i���O�R���g���[���x�l���f�d�s
void XinputSetDeadZone(int idx);				// �s���Ȓl�␳	
bool XinputConnected(int i);					// �w�a�n�w�R���g���[�����ڑ�����Ă��邩�H

bool GetKeyboardTrigger(int idx);
