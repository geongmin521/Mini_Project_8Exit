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
        bonfire,                            // :불타는 오브젝트 
        Carriage_moving,                    //: 뱀이 움직일 때 재생하는 효과음 //clear
        Cottage_door_open,                  //: 오두막 문 열릴 때 재생  
        Merchant_chat,                      //: 마차상인 대화창 열릴 때 재생 //clear
        New_Background_music,               //: 새로운 배경음악.인게임 화면에서 재생 //clear
        Player_Walk,                        //: 플레이어 이동 시 재생, //clear
        Player_run,                         //: 뛸 때 1.5배속 재생 //clear
        click,                              //: 클릭할때 //clear
        Scarecrow_drop_from_Web,            //: 허수아비가 거미줄에서 떨어질 때 재생(5구역) //clear
        Snake_drop_from_Web,                //: 1구역에서 거미 대신 뱀이 떨어질 때 재생  //clear
        Snake_Bite,                         //: 뱀이 물 때 재생 //clear
        Snake_moving,                       //:: 뱀이 움직일 때 재생하는 효과음 //clear
        Stage_Transition_with_correct,      //: 스테이지 전환 시, 정답을 모두 맞췄을 때 재생 //clear
        Stage_Transition_with_wrong,        //: 스테이지 전환 시, 오답이 있을 경우 재생//clear
        When_the_wrong_picture_triggered_1, //clear
        Size
    };
    class SoundManager;  // 클래스 전방 선언
    extern SoundManager* soundManager;  // extern을 사용하여 외부에서 접근 가능하도록 선언

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