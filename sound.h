#ifndef _RTS_SOUND_
#define _RTS_SOUND_

#include <vector>
#include <dshow.h>
#include <d3dx10.h>
#include <dsound.h>
#include "debug.h"

class MP3{
	public:
		MP3();
		~MP3();
		void Release();
		void Init();
		void LoadSong(WCHAR fName[]);
		void Play();
		void Stop();
		bool IsPlaying();
		void SetVolume(float volume);
		void SetBalance(float balance);

	private:

		IGraphBuilder *m_pGraphBuilder;
		IMediaControl *m_pMediaControl;
		IMediaPosition *m_pMediaPosition;
		IBasicAudio *m_pBasicAudio;
};

#endif
