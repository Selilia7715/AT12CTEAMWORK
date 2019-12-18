#include <windows.h>
#include <xinput.h>
#include "xinpututil.h"

// ���C�u�����������N
#pragma comment(lib,"xinput.lib")

// XBOX�R���g���[�����i�l�`�w�S��j
CONTROLLER_STATE g_Controllers[MAX_CONTROLLERS];

// �s���Ȓl��␳
void XinputSetDeadZone(int idx) {
	// Zero value if thumbsticks are within the dead zone 
	if ((g_Controllers[idx].state.Gamepad.sThumbLX < INPUT_DEADZONE &&
		g_Controllers[idx].state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
		(g_Controllers[idx].state.Gamepad.sThumbLY < INPUT_DEADZONE &&
			g_Controllers[idx].state.Gamepad.sThumbLY > -INPUT_DEADZONE))
	{
		g_Controllers[idx].state.Gamepad.sThumbLX = 0;
		g_Controllers[idx].state.Gamepad.sThumbLY = 0;
	}

	if ((g_Controllers[idx].state.Gamepad.sThumbRX < INPUT_DEADZONE &&
		g_Controllers[idx].state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
		(g_Controllers[idx].state.Gamepad.sThumbRY < INPUT_DEADZONE &&
			g_Controllers[idx].state.Gamepad.sThumbRY > -INPUT_DEADZONE))
	{
		g_Controllers[idx].state.Gamepad.sThumbRX = 0;
		g_Controllers[idx].state.Gamepad.sThumbRY = 0;
	}
}

// idx�Ԗڂ̃{�^�����i�f�W�^���f�[�^�j���擾
WORD GetXinputButton(int idx) {
	return(g_Controllers[idx].state.Gamepad.wButtons);
}

// idx�Ԗڂ̂w�a�n�w�R���g���[�����ڑ�����Ă��邩���m�F
bool XinputConnected(int idx) {

	return g_Controllers[idx].bConnected;
}

// XINPUT������
void InitXinputState() {
	// Init state
	memset(g_Controllers, 0, sizeof(CONTROLLER_STATE) * MAX_CONTROLLERS);
}

// XINPUT�@�t�o�c�`�s�d
HRESULT UpdateXinputControllerState()
{
	unsigned int  dwResult;
	for (unsigned int i = 0; i < MAX_CONTROLLERS; i++)
	{
		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &g_Controllers[i].state);

		if (dwResult == ERROR_SUCCESS)
			g_Controllers[i].bConnected = true;
		else
			g_Controllers[i].bConnected = false;
	}

	return S_OK;
}

// �������Ԗڂ̍��g���K�[�l�i�A�i���O�O�|�Q�T�T�j���擾
int GetXinputLeftTrigger(int idx) {
	return g_Controllers[idx].state.Gamepad.bLeftTrigger;
}

// �������Ԗڂ̉E�g���K�[�l�i�A�i���O�O�|�Q�T�T�j���擾
int GetXinputRightTrigger(int idx) {
	return g_Controllers[idx].state.Gamepad.bRightTrigger;
}

// �������Ԗڂ̍��i�n�x�X�e�B�b�N�i�A�i���O�w�l�j���擾
int GetXinputThumbLX(int idx) {
	return g_Controllers[idx].state.Gamepad.sThumbLX;
}

// �������Ԗڂ̍��i�n�x�X�e�B�b�N�i�A�i���O�x�l�j���擾
int GetXinputThumbLY(int idx) {
	return g_Controllers[idx].state.Gamepad.sThumbLY;
}

// �������Ԗڂ̉E�i�n�x�X�e�B�b�N�i�A�i���O�w�l�j���擾
int GetXinputThumbRX(int idx) {
	return g_Controllers[idx].state.Gamepad.sThumbRX;
}

// �������Ԗڂ̉E�i�n�x�X�e�B�b�N�i�A�i���O�x�l�j���擾
int GetXinputThumbRY(int idx) {
	return g_Controllers[idx].state.Gamepad.sThumbRY;
}
