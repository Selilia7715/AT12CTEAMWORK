#pragma once
#include	<xinput.h>

#define MAX_CONTROLLERS 4  // ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Í‚l‚`‚w‚S‚Â‚Ü‚Å 
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

// XINPUT ƒRƒ“ƒgƒ[ƒ‰î•ñ
struct CONTROLLER_STATE
{
	XINPUT_STATE state;							// XINPUTƒRƒ“ƒgƒ[ƒ‰‚Ìó‘Ô
	bool bConnected;							// Ú‘±‚³‚ê‚Ä‚¢‚é‚©”Û‚©
};

void InitXinputState();							// XINPUT ‰Šú‰»;
HRESULT UpdateXinputControllerState();			// XINPUT UPDATE
WORD GetXinputButton(int i);					// ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Ìƒ{ƒ^ƒ“î•ñ‚ğ‚f‚d‚s
int  GetXinputLeftTrigger(int idx);				// ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Ì¶ƒgƒŠƒK[’li‚O|‚Q‚T‚Tj‚ğ‚f‚d‚s
int  GetXinputRightTrigger(int idx);		    // ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Ì‰EƒgƒŠƒK[’li‚O|‚Q‚T‚Tj‚ğ‚f‚d‚s
int  GetXinputThumbLX(int idx);					// ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Ì¶ƒAƒiƒƒOƒRƒ“ƒgƒ[ƒ‰‚w’l‚ğ‚f‚d‚s
int  GetXinputThumbLY(int idx);					// ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Ì¶ƒAƒiƒƒOƒRƒ“ƒgƒ[ƒ‰‚x’l‚ğ‚f‚d‚s
int  GetXinputThumbRX(int idx);					// ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Ì‰EƒAƒiƒƒOƒRƒ“ƒgƒ[ƒ‰‚w’l‚ğ‚f‚d‚s
int  GetXinputThumbRY(int idx);					// ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚Ì‰EƒAƒiƒƒOƒRƒ“ƒgƒ[ƒ‰‚x’l‚ğ‚f‚d‚s
void XinputSetDeadZone(int idx);				// •s³‚È’l•â³	
bool XinputConnected(int i);					// ‚w‚a‚n‚wƒRƒ“ƒgƒ[ƒ‰‚ªÚ‘±‚³‚ê‚Ä‚¢‚é‚©H

bool GetKeyboardTrigger(int idx);
