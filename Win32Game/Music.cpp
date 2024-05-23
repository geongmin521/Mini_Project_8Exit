#include "Music.h"
#include "globalheader.h"
namespace Music
{
    SoundManager* SoundManager::mInstance = nullptr;
    SoundManager* soundManager = SoundManager::GetInstance();  // 초기화  

    SoundManager* SoundManager::GetInstance() //일단 파일만 갖다놨고 추가하고싶은데.. 
    {
        if (mInstance == nullptr)
            mInstance = new SoundManager();  

        return mInstance;
    }

    void SoundManager::DestroyInstance()
    {
        delete mInstance;
        mInstance = nullptr;
    }

    void SoundManager::Init()
    {
        System_Create(&mSystem);
        mSystem->init(20, FMOD_INIT_NORMAL, 0);
    }


    void SoundManager::LoadMusic(eSoundList soundlist, bool loopcheck, const std::string& path)
    {

        std::string filepath = "data\\" + path;
 
        if (loopcheck)
            mSystem->createSound(filepath.c_str(), FMOD_LOOP_NORMAL, 0, &mSoundList[static_cast<int>(soundlist)]);
        else
            mSystem->createSound(filepath.c_str(), FMOD_LOOP_OFF, 0, &mSoundList[static_cast<int>(soundlist)]);
    }

    void SoundManager::PlayMusic(eSoundList soundlist, eSoundChannel channel)
    {
        mChannel[static_cast<int>(channel)]->stop();
        mSystem->playSound(mSoundList[static_cast<int>(soundlist)], nullptr, 0, &mChannel[static_cast<int>(channel)]);
        //mChannel[static_cast<int>(channel)]->setVolume(mVolume);
    }

    void SoundManager::StopMusic(eSoundChannel channel)
    {
        mChannel[static_cast<int>(channel)]->stop();
    }

    void SoundManager::SetVolume(float volume, eSoundChannel chanel)
    {
        //mVolume = volume;
        mChannel[(int)chanel]->setVolume(volume);
    }

    void SoundManager::ManageMusic(const Vector3 Playerpos)
    {
        int index = int(Playerpos._x) / 3840;
        if (IsWrong[index] == true)
        {
            IsWrong[index] = false;
            mInstance->PlayMusic(eSoundList::When_the_wrong_picture_triggered_1,eSoundChannel::WrongEffect);
        }  
    }

    SoundManager::SoundManager(): mSystem(), mChannel{}, mSoundList{}, mVolume(0.5f)
    {
    }

    SoundManager::~SoundManager()
    {
        mSystem->release();
        mSystem->close();
    }
};