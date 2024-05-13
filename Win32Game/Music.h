#pragma once
// FMOD
#ifndef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#ifdef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#include <string>
namespace Music
{
    enum class eSoundChannel
    {
        BGM,
        Effect,
        Size
    };

    enum class eSoundList
    {
        StartBGM,
        correct,
        wrong,
        hint,
        win,
        start,
        success,
        fail,
        Size,
    };
    class SoundManager;  // Ŭ���� ���� ����
    extern SoundManager* soundManager;  // extern�� ����Ͽ� �ܺο��� ���� �����ϵ��� ����

    class SoundManager final
    {
    public:
        static SoundManager* GetInstance();

        static void DestroyInstance();

        void LoadMusic(eSoundList soundlist, bool loopcheck, const std::string& path);

        void PlayMusic(eSoundList list, eSoundChannel channel);

        void StopMusic(eSoundChannel channel);

        void SetVolume(float volume);

    private:
        SoundManager();

        ~SoundManager();

    private:
        static SoundManager* mInstance;

        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };

}