
//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include <assert.h>
#include <string.h>
#include <memory>
#include "EffekseerSoundAL.SoundImplemented.h"
#include "EffekseerSoundAL.SoundLoader.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerSound
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
SoundLoader::SoundLoader( ::Effekseer::FileInterface* fileInterface )
	: m_fileInterface( fileInterface )
{
	if( m_fileInterface == NULL )
	{ 
		m_fileInterface = &m_defaultFileInterface;
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
SoundLoader::~SoundLoader()
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void* SoundLoader::Load( const EFK_CHAR* path )
{
	assert( path != NULL );
	
	std::unique_ptr<Effekseer::FileReader> 
		reader( m_fileInterface->OpenRead( path ) );
	if( reader.get() == NULL ) return NULL;

	uint32_t chunkIdent, chunkSize;
	// RIFF�`�����N���`�F�b�N
	reader->Read(&chunkIdent, 4);
	reader->Read(&chunkSize, 4);
	if (memcmp(&chunkIdent, "RIFF", 4) != 0) {
		return NULL;
	}

	// WAVE�V���{�����`�F�b�N
	reader->Read(&chunkIdent, 4);
	if (memcmp(&chunkIdent, "WAVE", 4) != 0) {
		return NULL;
	}
	
	struct { 
		uint16_t	wFormatTag;
		uint16_t	nChannels;
		uint32_t	nSamplesPerSec;
		uint32_t	nAvgBytesPerSec;
		uint16_t	nBlockAlign;
		uint16_t	wBitsPerSample;
		uint16_t	cbSize;
	} wavefmt = {0}; 
	for (;;) {
		reader->Read(&chunkIdent, 4);
		reader->Read(&chunkSize, 4);

		if (memcmp(&chunkIdent, "fmt ", 4) == 0) {
			// �t�H�[�}�b�g�`�����N
			uint32_t size = (chunkSize < sizeof(wavefmt)) ? chunkSize : sizeof(wavefmt);
			reader->Read(&wavefmt, size);
			if (size < chunkSize) {
				reader->Seek(reader->GetPosition() + chunkSize - size);
			}
		} else if (memcmp(&chunkIdent, "data", 4) == 0) {
			// �f�[�^�`�����N
			break;
		} else {
			// �s���ȃ`�����N�̓X�L�b�v
			reader->Seek(reader->GetPosition() + chunkSize);
		}
	}
	
	// �t�H�[�}�b�g�`�F�b�N
	if (wavefmt.wFormatTag != 1 || wavefmt.nChannels > 2 || wavefmt.wBitsPerSample > 16) {
		return NULL;
	}

	uint8_t* buffer;
	uint32_t size;
	switch (wavefmt.wBitsPerSample) {
	case 8:
		// 16bitPCM�ɕϊ�
		size = chunkSize * 2;
		buffer = new uint8_t[size];
		reader->Read(&buffer[size / 2], chunkSize);
		{
			int16_t* dst = (int16_t*)&buffer[0];
			uint8_t* src = (uint8_t*)&buffer[size / 2];
			for (uint32_t i = 0; i < chunkSize; i++) {
				*dst++ = (int16_t)(((int32_t)*src++ - 128) << 8);
			}
		}
		break;
	case 16:
		// ���̂܂ܓǂݍ���
		buffer = new uint8_t[chunkSize];
		size = reader->Read(buffer, chunkSize);
		break;
	}

	ALenum format = (wavefmt.nChannels == 16) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;

	SoundData* soundData = new SoundData;
	memset(soundData, 0, sizeof(SoundData));
	soundData->channels = wavefmt.nChannels;
	soundData->sampleRate = wavefmt.nSamplesPerSec;
	alGenBuffers(1, &soundData->buffer);
	alBufferData(soundData->buffer, format, buffer, size, wavefmt.nSamplesPerSec);
	delete[] buffer;

	return soundData;
}
	
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void SoundLoader::Unload( void* data )
{
	SoundData* soundData = (SoundData*)data;
	if (soundData == NULL) {
		return;
	}
	alDeleteBuffers(1, &soundData->buffer);
	delete soundData;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
