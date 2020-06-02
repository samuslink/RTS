#include "sound.h"

//////////////////////////////////////////////////////////////
//					MP3PLAYER								//
//////////////////////////////////////////////////////////////

MP3::MP3()
{
	m_pGraphBuilder = NULL;
	m_pMediaControl = NULL;
	m_pMediaPosition = NULL;
	m_pBasicAudio = NULL;
}

MP3::~MP3()
{
	Release();
}

void MP3::Release()
{
	if(m_pBasicAudio)m_pBasicAudio->Release();
	if(m_pMediaPosition)m_pMediaPosition->Release();
	if(m_pMediaControl)m_pMediaControl->Release();
	if(m_pGraphBuilder)m_pGraphBuilder->Release();

	m_pGraphBuilder = NULL;
	m_pMediaControl = NULL;
	m_pMediaPosition = NULL;
	m_pBasicAudio = NULL;
}

void MP3::Init()
{
	Release();

	// Initialise COM
	CoInitialize(NULL);

	// Create the Filter Graph Manager
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
	 		         IID_IGraphBuilder, (void **)&m_pGraphBuilder);

	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl);
	m_pGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pMediaPosition);
	m_pGraphBuilder->QueryInterface(IID_IBasicAudio, (void **)&m_pBasicAudio);
}

void MP3::LoadSong(WCHAR fName[])
{
	//Init the DirectShow objects
	Init();		

	//Create standard graph
	m_pGraphBuilder->RenderFile(fName, NULL);
}

void MP3::Play()
{
	//rewind...
	m_pMediaPosition->put_CurrentPosition(0);

	//Play
	m_pMediaControl->Run();
}

void MP3::Stop()
{
	m_pMediaControl->Stop();
}

bool MP3::IsPlaying()
{
	REFTIME currentPos;
    REFTIME duration;

    m_pMediaPosition->get_CurrentPosition(&currentPos);
    m_pMediaPosition->get_Duration(&duration);
    
    if(currentPos < duration)
        return true;
    else return false;
}

void MP3::SetVolume(float volume)
{
	if(volume < 0.0f)volume = 0.0f;
	if(volume > 1.0f)volume = 1.0f;
	
    if(m_pBasicAudio)
    {
		long vol = (long)(-10000 * (1.0f - sqrt(volume)));
        m_pBasicAudio->put_Volume(vol);
    }
}

void MP3::SetBalance(float balance)
{
	if(balance < -1.0f)balance = -1.0f;
	if(balance > 1.0f)balance = 1.0f;

    if (m_pBasicAudio)
    {
		long bal = (long)(10000 * balance);
        m_pBasicAudio->put_Balance(bal);
    }
}
