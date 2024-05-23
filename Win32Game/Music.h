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
#include "Vector3.h"
namespace Music
{
    enum class eSoundChannel
    {
        BGM,
        HorseCarRush,
        Effect,
        ChangeStageEffect,
        DoorOpenEffect,
        WrongEffect,
        Talk,
        Player,
        HorseCarMove,
        SnakeMove,
        Click,
        Fire,
        Size
    };

    enum class eSoundList
    {
        Attacked_by_Objects,                //clear
        Carriage_rush,                      //clear
        bonfire,                            // :��Ÿ�� ������Ʈ 
        Carriage_moving,                    //: ���� ������ �� ����ϴ� ȿ���� //clear
        Cottage_door_open,                  //: ���θ� �� ���� �� ���  
        Merchant_chat,                      //: �������� ��ȭâ ���� �� ��� //clear
        New_Background_music,               //: ���ο� �������.�ΰ��� ȭ�鿡�� ��� //clear
        Player_Walk,                        //: �÷��̾� �̵� �� ���, //clear
        Player_run,                         //: �� �� 1.5��� ��� //clear
        click,                              //: Ŭ���Ҷ� //clear
        Scarecrow_drop_from_Web,            //: ����ƺ� �Ź��ٿ��� ������ �� ���(5����) //clear
        Snake_drop_from_Web,                //: 1�������� �Ź� ��� ���� ������ �� ���  //clear
        Snake_Bite,                         //: ���� �� �� ��� //clear
        Snake_moving,                       //:: ���� ������ �� ����ϴ� ȿ���� //clear
        Stage_Transition_with_correct,      //: �������� ��ȯ ��, ������ ��� ������ �� ��� //clear
        Stage_Transition_with_wrong,        //: �������� ��ȯ ��, ������ ���� ��� ���//clear
        When_the_wrong_picture_triggered_1, //clear
        Size
    };
    class SoundManager;  // Ŭ���� ���� ����
    extern SoundManager* soundManager;  // extern�� ����Ͽ� �ܺο��� ���� �����ϵ��� ����

    class SoundManager final
    {
    public:
        static SoundManager* GetInstance();

        static void DestroyInstance();

        void Init();

        void LoadMusic(eSoundList soundlist, bool loopcheck, const std::string& path);

        void PlayMusic(eSoundList list, eSoundChannel channel);

        void StopMusic(eSoundChannel channel);

        void SetVolume(float volume, eSoundChannel chanel);

        void ManageMusic(const Vector3 Playerpos);
        void SetIsWrong(int index, bool ture) { IsWrong[index] = ture;}


    private:
        SoundManager();

        ~SoundManager();

    private:
        static SoundManager* mInstance;
        bool IsWrong[6] = { false, false, false, false, false, false };
        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };

}