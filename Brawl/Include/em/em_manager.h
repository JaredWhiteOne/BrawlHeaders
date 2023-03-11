#pragma once

#include <types.h>
#include <StaticAssert.h>
#include <em/em_archive.h>
#include <em/enemy.h>

class emManager {

    template <typename T>
    class Entry {
        char _0[0x4];
        EnemyKind m_enemyKind;
        int m_parentCreateId;
        int m_createId;
        int m_soundGroupOffset;
        T* m_dataPtr;

        STATIC_CHECK(sizeof(Entry) == 0x14)
    };

    u32 m_numEnemyEntries;
    Entry<Enemy>* m_enemyEntries;
    char _8[4];
    u32 m_numArchiveEntries;
    Entry<emArchive>* m_archiveEntries;
    char _20[4];
    u8 m_primidFaceType;
    char _25[3];

    virtual ~emManager();

public:
    int getPreloadArchiveCountFromKind(EnemyKind enemyKind);
    int preloadArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind, bool isSoundRequest);
    int createEnemy(emCreate* create);
    void removeEnemyAll();
    void removeArchiveAll();
    static void create(u32 numEntries1, u32 numEntries2, u8 primidFaceType);
    static void remove();
    static emManager* getInstance();

    STATIC_CHECK(sizeof(emManager) == 32)
};

