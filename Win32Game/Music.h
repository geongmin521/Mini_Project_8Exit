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
        Talk,
        Player,
        Size
    };

    enum class eSoundList
    {
        Attacked_by_Objects,                //clear
        Carriage_rush,                      //clear
        bonfire,
        Carriage_moving,
        Cottage_door_open,                  //: 오두막 문 열릴 때 재생  
        Merchant_chat,                      //: 마차상인 대화창 열릴 때 재생 //clear
        New_Background_music,               //:   새로운 배경음악.인게임 화면에서 재생 //clear
        Player_Walk,                        //: 플레이어 이동 시 재생, 뛸 때 1.5배속 재생 //clear
        Scarecrow_drop_from_Web,            //: 허수아비가 거미줄에서 떨어질 때 재생(5구역) //clear
        Snake_drop_from_Web,                //: 1구역에서 거미 대신 뱀이 떨어질 때 재생  //clear
        Snake_Bite,                         //: 뱀이 물 때 재생 //clear
        Stage_Transition_with_correct,      //: 스테이지 전환 시, 정답을 모두 맞췄을 때 재생 //아래부터는 세민이형 트리거족너을 좀더 잘알듯?
        Stage_Transition_with_wrong,        //: 스테이지 전환 시, 오답이 있을 경우 재생
        Sunflower_Crying,                   //: 해바라기 구역에서 재생
        Sunflower_Laughing,                 //: 해바라기가 웃고 있는 이상 기믹에서 재생
        When_the_wrong_picture_triggered_1, //: 틀린 그림 기믹이 발생한 오브젝트가, 플레이어 화면에 보여질 경우, 두 사운드 중 하나를 재생 (억지로 깨도록 도와주는 시스템)
        When_the_wrong_picture_triggered_2,
        Size
    };
    class SoundManager;  // 클래스 전방 선언
    extern SoundManager* soundManager;  // extern을 사용하여 외부에서 접근 가능하도록 선언

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