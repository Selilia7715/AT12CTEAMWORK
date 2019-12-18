//=============================================================================
//
// サウンド処理 [XAudio2.cpp]
//
//=============================================================================

#include "XAudio2.h"

// パラメータ構造体
typedef struct
{
	LPCSTR filename;	// 音声ファイルまでのパスを設定
	bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
} PARAM;

PARAM g_param[SOUND_LABEL_MAX] =
{
	{"BGM/Everything_Everytime.wav", true},	// タイトルBGM（ループさせるのでtrue設定）
	{"BGM/karma.wav", true},	// ゲームBGM
	{"SE/bomb0.wav", false},		// サンプルSE（ループしないのでfalse設定）
	{"SE/defend0.wav", false},		// サンプルSE
	{"SE/defend1.wav", false},		// サンプルSE
	{"SE/hit0.wav", false},			// サンプルSE
	{"SE/laser0.wav", false},		// サンプルSE
	{"SE/lockon0.wav", false},		// サンプルSE
	{"SE/shot0.wav", false},		// サンプルSE
	{"SE/shot1.wav", false},		// サンプルSE
};

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif


//-----------------------------------------------------------------
//    グローバル変数
//-----------------------------------------------------------------
IXAudio2               *g_pXAudio2        = NULL;
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;
IXAudio2SourceVoice    *g_pSourceVoice[SOUND_LABEL_MAX];

WAVEFORMATEXTENSIBLE	wfx[SOUND_LABEL_MAX];			// WAVフォーマット
XAUDIO2_BUFFER			buffer[SOUND_LABEL_MAX];
BYTE					*pDataBuffer[SOUND_LABEL_MAX];

//-----------------------------------------------------------------
//    プロトタイプ宣言
//-----------------------------------------------------------------
HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
HRESULT ReadChunkData( HANDLE , void* , DWORD , DWORD );

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitSound()
{
	HRESULT      hr;
	
	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;
		
	CoInitializeEx( NULL , COINIT_MULTITHREADED );
	
	/**** Create XAudio2 ****/
	hr = XAudio2Create( &g_pXAudio2, 0/* , XAUDIO2_DEFAULT_PROCESSOR*/);
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if( FAILED( hr ) ){
		CoUninitialize();
		return -1;
	}
	
	/**** Create Mastering Voice ****/
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/);
	if( FAILED( hr ) ){
		if( g_pXAudio2 )	g_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	/**** Initalize Sound ****/
	for(int i=0; i<SOUND_LABEL_MAX; i++)
	{
		memset( &wfx[i] , 0 , sizeof( WAVEFORMATEXTENSIBLE ) );
		memset( &buffer[i] , 0 , sizeof( XAUDIO2_BUFFER ) );
	
		hFile = CreateFile( g_param[i].filename , GENERIC_READ , FILE_SHARE_READ , NULL ,
							OPEN_EXISTING , 0 , NULL );
		if ( hFile == INVALID_HANDLE_VALUE ){
			return HRESULT_FROM_WIN32( GetLastError() );
		}
		if ( SetFilePointer( hFile , 0 , NULL , FILE_BEGIN ) == INVALID_SET_FILE_POINTER ){
			return HRESULT_FROM_WIN32( GetLastError() );
		}

		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile,fourccRIFF,dwChunkSize, dwChunkPosition );
		ReadChunkData(hFile,&filetype,sizeof(DWORD),dwChunkPosition);
		if (filetype != fourccWAVE)		return S_FALSE;

		FindChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition );
		ReadChunkData(hFile, &wfx[i], dwChunkSize, dwChunkPosition );

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile,fourccDATA,dwChunkSize, dwChunkPosition );
		pDataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, pDataBuffer[i], dwChunkSize, dwChunkPosition);
		
		CloseHandle(hFile);

		// 	サブミットボイスで利用するサブミットバッファの設定
		buffer[i].AudioBytes = dwChunkSize;
		buffer[i].pAudioData = pDataBuffer[i];
		buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		if(g_param[i].bLoop)
			buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			buffer[i].LoopCount = 0;

		g_pXAudio2->CreateSourceVoice( &g_pSourceVoice[i] , &(wfx[i].Format) );
	}

	return hr;
}

//=============================================================================
// 開放処理
//=============================================================================
void UninitSound(void)
{
	for(int i=0; i<SOUND_LABEL_MAX; i++)
	{
		if(g_pSourceVoice[i])
		{
			g_pSourceVoice[i]->Stop( 0 );
			g_pSourceVoice[i]->FlushSourceBuffers();
			g_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  pDataBuffer[i];
		}
	}

	g_pMasteringVoice->DestroyVoice();
	
	if ( g_pXAudio2 ) g_pXAudio2->Release();
	
	CoUninitialize();
}

//=============================================================================
// 再生
//=============================================================================
void PlaySound(SOUND_LABEL label)
{
	// ソースボイス作成
	g_pXAudio2->CreateSourceVoice( &(g_pSourceVoice[(int)label]) , &(wfx[(int)label].Format) );
	g_pSourceVoice[(int)label]->SubmitSourceBuffer( &(buffer[(int)label]) );	// ボイスキューに新しいオーディオバッファーを追加

	// 再生
	g_pSourceVoice[(int)label]->Start( 0 );
	
}

//=============================================================================
// 停止
//=============================================================================
void StopSound(SOUND_LABEL label)
{
	if(g_pSourceVoice[(int)label] == NULL) return;

	XAUDIO2_VOICE_STATE xa2state;
	g_pSourceVoice[(int)label]->GetState( &xa2state );
	if(xa2state.BuffersQueued)
	{
		g_pSourceVoice[(int)label]->Stop( 0 );
	}
}

//=============================================================================
// 一時停止
//=============================================================================
void PauseSound(SOUND_LABEL label)
{
	// ごにょっとすれば可能。
}
//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );
		if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if( 0 == ReadFile( hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL ) )
				hr = HRESULT_FROM_WIN32( GetLastError() );
			break;
		default:
			if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
				return HRESULT_FROM_WIN32( GetLastError() );
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	DWORD dwRead;
	if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
		hr = HRESULT_FROM_WIN32( GetLastError() );
	return hr;
}
