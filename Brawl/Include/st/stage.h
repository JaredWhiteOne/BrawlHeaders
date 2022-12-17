#pragma once

#include <GX/GXColor.h>
#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <gf/gf_task.h>
#include <gr/gr_yakumono.h>
#include <memory.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <snd/snd_3d_generator.h>
#include <snd/snd_id.h>
#include <st/st_positions.h>
#include <types.h>
#include <em/em_create.h>
#include <st/st_trigger.h>
#include <st/st_collision_attr_param.h>

namespace StSeUtil {
    class SeSeq {
    public:
        virtual ~SeSeq();

    public:
        char _1[0x10];                  // 0x00
        snd3DGenerator* m_sndGenerator; // 0x14
        char _2[0x8];                   // 0x18

    public:
        SeSeq(void* unk, int unk2, void* unk3, int unk4);
        void playFrame(float frame, u32 unk);
        void playFrame(float frame, float unk1, u32 unk2);
        void registId(SndID* ID, int unk1);
        void registSeq(int unk1, SndID* ID, int unk2, Heaps::HeapType heapType);

        STATIC_CHECK(sizeof(SeSeq) == 0x20)
    };
}

class StageParam {
public:
    u8 m_echo;
    u8 m_id1;
    u8 m_id2;
    char _3;
    float _4;
    float _8;
    float _12;
    float _16;
    u8 m_bgmVolume;
    u8 m_sfxVolume;
    char _22;
    char _23;
    float m_shadowPitch;
    float m_shadowYaw;
    char _26[8];
    float m_cameraFOV;
    float m_minZ;
    float m_maxZ;
    float m_minTilt;
    float m_maxTilt;
    float m_horizontalRotationFactor;
    float m_verticalRotationFactor;
    float m_characterBubbleBufferMultiplier;
    float _72;
    float m_cameraSpeed;
    float m_starKOCamTilt;
    float m_finalSmashCamTilt;
    float m_cameraRight;
    float m_cameraLeft;
    Vec3f m_pauseCamPos;
    float m_pauseCamAngle;
    float m_pauseCamZoomIn;
    float m_pauseCamZoomDefault;
    float m_pauseCamZoomOut;
    float m_pauseCamRotYMin;
    float m_pauseCamRotYMax;
    float m_pauseCamRotXMin;
    float m_pauseCamRotXMax;
    Vec3f m_fixedCamPos;
    float m_fixedCamFOV;
    float m_fixedHorizontalAngle;
    float m_fixedVerticalAngle;
    char _164[4];
    float m_olimarFinalCamAngle;
    Vec3f m_iceClimbersFinalPos;
    float m_iceClimbersFinalScaleX;
    float m_iceClimbersFinalScaleYl;
    float m_pitFinalPalutenaScaleX;
    float m_pitFinalPalutenaScaleY;
    u8 m_kirifudaModelType;
    bool m_characterWindEnabled;
    char _202[2];
    float m_windStrength;
    float m_horizontalWindRotation;
    float m_verticalWindRotation;
    float _216;
    GXColor _220;
    char _224[4];
    bool _228;
    bool _229;
    u8 m_effectVol;
    u8 m_reverbLPF;
    u8 m_reverbType;
    u8 m_reverbColoration;
    u8 m_reverbDamping;
    u8 m_reverbPreDelay;
    u8 m_reverbBalance;
    u8 m_delayFeedback;
    u8 m_delayOutput;
    char _239;
    s16 m_reverbTime;
    u16 m_delayTime;
    char _244[16];

    STATIC_CHECK(sizeof(StageParam) == 260)
};

class Stage : public gfTask {
public:
    class CameraParam {
        char _0[0x40];

        STATIC_CHECK(sizeof(CameraParam) == 0x40)
    };

    // 0
    char _spacer[0x04];
    // 4
    int m_stageID;
    // 8
    char _spacer1[0x10];
    // 18
    stRange m_deadRange;
    // 28
    stRange m_aiRange;
    // 38
    CameraParam* m_cameraParam1;
    // 3c
    char _3c[0x4];
    // 40
    CameraParam* m_cameraParam2;
    // 44
    char _spacer2[4];
    // 48
    Ground* m_headGround;
    // 4c
    void* m_collConv;
    // 50
    stPositions* m_stagePositions;
    // 54
    char _spacer3[4];
    // 58
    StageParam* m_stageParam;
    // 5C
    void* m_stageData;
    // 60
    stTriggerMng* m_triggerMng;
    // 64
    char _spacer4[0x18];
    // 7C
    u32 m_unk;
    // 80
    char _spacer5[0x38];
    // B8
    char collisionAttrs[0xC];
    // C4
    gfArchive m_archive;
    // 144
    bool m_unk2;
    // 145
    char _spacer6[3];
    // 148
    u32 m_unk3;
    // 14C
    float m_unk4;
    // 150
    float m_frameRuleTime;
    // 154
    char _spacer7[0xC];
    // TOTAL_SIZE == 0x160

    void testStageParamInit(gfArchive* archive, int fileIndex);
    void testStageDataInit(gfArchive* archive, int fileIndex, int unk2);
    void addGround(Ground* Ground);
    Ground* getGround(int index);
    grCollision* createCollision(gfArchive* archive, int index, Ground* ground);
    void createStagePositions();
    void createStagePositions(void* stgPosMdl);
    void loadStageAttrParam(gfArchive* filedata, int fileIndex);
    void registSceneAnim(void* scnData, int unk1);
    void initPosPokeTrainer(int unk1, int unk2);
    void setStageAttackData(grGimmickDamageFloor* attackData, u32 index);

    Stage(char* name, int stageID);
    virtual void processBegin();
    virtual void processAnim();
    virtual void processUpdate();
    virtual void processMapCorrection();
    virtual void processFixCamera();
    virtual  void processEnd();
    virtual void renderPre();
    virtual void renderDebug();
    virtual ~Stage();

    virtual void createObj();
    virtual void createObjPokeTrainer(gfArchive* filedata, int fileindex, const char* name, int unk1, int unk2);
    virtual int getPokeTrainerPointNum();
    virtual void getPokeTrainerPointData(int* unk1, int unk2);
    virtual float getPokeTrainerPositionZ();
    virtual int getPokeTrainerDrawLayer();
    virtual bool isAdventureStage();
    virtual void getItemPac(gfArchive** brres, gfArchive** param, int itemID, int variantID);
    virtual void getItemGenPac(gfArchive** archive);
    virtual void getItemPacEnemyFigure(); // TODO
    virtual void getEnemyPac(gfArchive **brres, gfArchive **param, gfArchive **enmCommon, gfArchive **primFaceBrres, EnemyID enemyID);
    virtual void getAdvRadarData(gfArchive**, gfArchive**);
    virtual void initializeStage();       // TODO
    virtual void closeStage();
    virtual void renderDebugPositions();
    virtual bool loading();
    virtual void process();
    virtual void updateStagePositions();
    virtual void debugCollision();
    virtual stRange* getAIRange();
    virtual int getDefaultLightSetIndex();
    virtual int getZoneLightSetIndex();
    virtual int getScrollDir(u32 unk1);
    virtual void clearCameraParam();
    virtual void initCameraParam();
    virtual void startLoadLocalData();
    virtual bool isLoadLocalData();
    virtual int entryLocalData();
    virtual void removeLocalData();
    virtual void appearanceFighterLocal();
    virtual void getFighterStartPos(Vec3f* startPos, int fighterIndex);
    virtual void getFighterReStartPos(Vec3f* startPos, int fighterIndex);
    virtual bool isReStartSamePoint();
    virtual void getPokeTrainerStartPos(int unk1, int unk2);      // TODO
    virtual int getItemPosCount();                                // TODO
    virtual void getItemPos(int unk1, int unk2, int unk3);        // TODO
    virtual void getRandItemPos(int unk1);                        // TODO
    virtual void getKirifudaPos(int unk1, int unk2);              // TODO
    virtual float getKirifudaAngle(int unk1);                     // TODO
    virtual float getKirifudaScale(int unk1, int unk2);           // TODO
    virtual int getKirifudaModelType(int unk1);                   // TODO
    virtual int getPokeTrainerPosCount();                         // TODO
    virtual void getPokeTrainerPos(int unk1, int unk2, int unk3); // TODO
    virtual float getFighterDeadEffectSizeRate();
    virtual float getEnemyDeadEffectSizeRate();
    virtual float getEnableZ();
    virtual int getBgmID();         // TODO
    virtual int getBgmIDOverload(); // TODO, overloaded
    virtual int getNowStepBgmID();
    virtual int getBgmOptionID();
    virtual bool isBgmChange();
    virtual void getBgmChangeID(u32 unk1, float unk2);         // TODO
    virtual void setBgmChange(float unk1, u32 unk2, u32 unk3); // TODO
    virtual float getBgmVolume();
    virtual float getBgmPlayOffsetFrame();
    virtual bool isNextStepBgmEqualNowStepBgmFromFlag(); // TODO
    virtual void setFrameRuleTime(float unk1);
    virtual float getFrameRuleTime();      // TODO
    virtual void notifyTimmingGameStart(); // TODO
    virtual bool isEnd();
    virtual bool isEventEnd();
    virtual void enableDevil();
    virtual void disableDevil();
    virtual bool isDevil();
    virtual void setDevilScrool(float unk1, float unk2);     // TODO
    virtual void getLucarioFinalTechniquePosition(int unk1); // TODO
    virtual int startAppear();                               // TODO
    virtual void setAppearKind();                            // TODO
    virtual void endAppear();                                // TODO
    virtual int getAppearTask();                             // TODO
    virtual void forceStopAppear();                          // TODO
    virtual int getFinalTechniqColor();                      // TODO
    virtual void setMotionRatio(float unk1, float unk2);     // TODO
    virtual void saveMotionRatio(int unk1);                  // TODO
    virtual void restoreMotionRatio(int unk1);               // TODO
    virtual void setMotionSubRatio(float unk1, float unk2);  // TODO
    virtual void saveMotionSubRatio(int unk1);               // TODO
    virtual void restoreMotionSubRatio(int unk1);            // TODO
    virtual bool isCameraLocked();                           // TODO
    virtual bool isBossBattleMode();                         // TODO
    virtual bool isSimpleBossBattleMode();                   // TODO
    virtual bool isAppear();                                 // TODO
    virtual bool isStartAppearTimming();                     // TODO
    virtual void getMadeinAiData();                          // TODO
    virtual bool isBamperVector();                           // TODO
    virtual void getBamperVector(int unk1);
    virtual void notifyEventInfoReady();        // TODO
    virtual void notifyEventInfoGo();           // TODO
    virtual void getDestroyBossParamCommon();   // TODO
    virtual void stAdventureEventGetItem(int, int, int, int, int);     // TODO
    virtual void setStageOutEffectInit();       // TODO
    virtual void setStageInEffectInit();        // TODO
    virtual int helperStarWarp();               // TODO
    virtual int initializeFighterAttackRatio(); // TODO
    virtual void startFighterEvent();           // TODO
    virtual int getZoneState();                 // TODO
    virtual void getZonePos(Vec3f* pos);
    virtual float getMagmaHeight();             // TODO
    virtual float getAcidHeight();              // TODO
    virtual int getIteamDropStatus();           // TODO
    virtual bool createWind2ndOnly();
    virtual int getWind2ndOnlyData();           // TODO
    virtual void updateWind2ndOnly();           // TODO
    virtual void setVision();                   // TODO
};