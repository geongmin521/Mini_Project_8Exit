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
        Cottage_door_open,                  //: ���θ� �� ���� �� ���  
        Merchant_chat,                      //: �������� ��ȭâ ���� �� ��� //clear
        New_Background_music,               //:   ���ο� �������.�ΰ��� ȭ�鿡�� ��� //clear
        Player_Walk,                        //: �÷��̾� �̵� �� ���, �� �� 1.5��� ��� //clear
        Scarecrow_drop_from_Web,            //: ����ƺ� �Ź��ٿ��� ������ �� ���(5����) //clear
        Snake_drop_from_Web,                //: 1�������� �Ź� ��� ���� ������ �� ���  //clear
        Snake_Bite,                         //: ���� �� �� ��� //clear
        Stage_Transition_with_correct,      //: �������� ��ȯ ��, ������ ��� ������ �� ��� //�Ʒ����ʹ� �������� Ʈ���������� ���� �߾˵�?
        Stage_Transition_with_wrong,        //: �������� ��ȯ ��, ������ ���� ��� ���
        Sunflower_Crying,                   //: �عٶ�� �������� ���
        Sunflower_Laughing,                 //: �عٶ�Ⱑ ���� �ִ� �̻� ��Ϳ��� ���
        When_the_wrong_picture_triggered_1, //: Ʋ�� �׸� ����� �߻��� ������Ʈ��, �÷��̾� ȭ�鿡 ������ ���, �� ���� �� �ϳ��� ��� (������ ������ �����ִ� �ý���)
        When_the_wrong_picture_triggered_2,
        Size
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