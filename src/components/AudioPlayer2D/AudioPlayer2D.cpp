#include "AudioPlayer2D.h"

EXPORT(AudioPlayer2D, AudioName, AutoPlaying, Volume)

void AudioPlayer2D::OnCreate()
{
    if (AutoPlaying) Play();
}

void AudioPlayer2D::Play()
{
    // stop if is playing
    ///if (IsPlaying()) Stop();

    if (AudioID == CHUNK_NULL)
        AudioID = ResourceManager<Audio>::GetResourceId(AudioName);

    // get audio
    const auto& audio = ResourceManager<Audio>::Get(AudioID);
    
    // start playing 
    ChannelID = AudioEngine::Play(audio.GetData(), audio.GetSize(), Volume);
}
