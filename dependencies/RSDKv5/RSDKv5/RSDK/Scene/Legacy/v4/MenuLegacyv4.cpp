#if RETRO_USE_MOD_LOADER
#include "RSDK/Core/ModLoader.hpp"
#endif

#include "SceneLegacyv4.hpp"
#include "MenuLegacyv4.hpp"
#include "ObjectLegacyv4.hpp"
#include "ScriptLegacyv4.hpp"
#include "RSDK/Core/RetroEngine.hpp"
#include "MenuLegacyv4Objects.hpp"
#include "TitleLogo.hpp"
#include "ObjectLegacyv4.hpp"
#include "PressStart.hpp"
#include "RSDK/Core/Reader.hpp"

using namespace RSDK;
using namespace Legacy;

struct MenuObjectInfo {
    char name[0x40];
    void (*create)(void *data);
    void (*update)();
    void (*draw)();
};

MenuObjectInfo menuObjectList[LEGACY_v4_OBJECT_COUNT];
int32 menuObjectCount = 0;

void RegisterMenuObject(const char *name, void (*create)(void *data), void (*update)(), void (*draw)())
{
    if (menuObjectCount < LEGACY_v4_OBJECT_COUNT) {
        strcpy(menuObjectList[menuObjectCount].name, name);
        menuObjectList[menuObjectCount].create = create;
        menuObjectList[menuObjectCount].update = update;
        menuObjectList[menuObjectCount].draw = draw;
        menuObjectCount++;
    }
}

void CreateEntity(uint8 type, void *data, int32 x, int32 y)
{
    if (type > 0 && type < menuObjectCount) {
        for (int32 i = 0; i < LEGACY_v4_ENTITY_COUNT; ++i) {
            if (objectEntityList[i].type == 0) {
                objectEntityList[i].type = type;
                objectEntityList[i].xpos = x;
                objectEntityList[i].ypos = y;
                if (menuObjectList[type].create) {
                    Entity *originalSelf = self;
                    self = &objectEntityList[i];
                    menuObjectList[type].create(data);
                    self = originalSelf;
                }
                break;
            }
        }
    }
}

void ProcessMenu()
{
    switch (stageMode) {
        case STAGEMODE_LOAD:
            SetActivePalette(0, 0, 256);
            fadeMode = 0;
            InitCameras();
            vertexCount  = 0;
            faceCount    = 0;
            frameCounter = 0;
            pauseEnabled = false;
            timeEnabled  = false;
            stageMode    = STAGEMODE_NORMAL;

            ResetBackgroundSettings();
            LoadMenuAssets();
            break;

        case STAGEMODE_NORMAL:
            if (fadeMode > 0)
                fadeMode--;

            ProcessInput();

            if (controller[CONT_ANY].keyStart.press) {
                gameMode = ENGINE_MAINGAME;
                stageMode = STAGEMODE_LOAD;
            }

            for (int32 i = 0; i < LEGACY_v4_ENTITY_COUNT; ++i) {
                if (objectEntityList[i].type > 0 && objectEntityList[i].type < menuObjectCount) {
                    objectEntityList[i].state = (int32)menuObjectList[objectEntityList[i].type].update;
                    if (objectEntityList[i].state) {
                        Entity *originalSelf = self;
                        self = &objectEntityList[i];
                        ((void (*_RSDK)())objectEntityList[i].state)();
                        self = originalSelf;
                    }
                }
            }
            HandleCameras();

            currentScreen             = &screens[0];
            sceneInfo.currentScreenID = 0;
            DrawMenuGFX();
            break;

        default: break;
    }
}

void InitMenuObjects()
{
    menuObjectCount = 0;
    Init_TitleLogo();
    Init_PressStart();
}

void LoadMenuAssets()
{
    ClearGraphicsData();
    ClearAnimationData();
    ClearScriptData();

    StageLoad_TitleLogo();
    StageLoad_PressStart();

    memset(objectEntityList, 0, LEGACY_v4_ENTITY_COUNT * sizeof(Entity));
    for (int32 i = 0; i < LEGACY_v4_ENTITY_COUNT; ++i) {
        objectEntityList[i].drawOrder          = 3;
        objectEntityList[i].scale              = 512;
        objectEntityList[i].objectInteractions = true;
        objectEntityList[i].visible            = true;
        objectEntityList[i].tileCollisions     = true;
    }

    FileInfo info;
    InitFileInfo(&info);
    if (LoadFile(&info, "Jules/S1 menu/Game/Menu/MenuScene.bin", FMODE_RB)) {
        int32 objectCount = ReadInt16(&info);
        for (int32 i = 0; i < objectCount; ++i) {
            uint8 type = ReadInt8(&info);
            int32 x = ReadInt32(&info);
            int32 y = ReadInt32(&info);
            char buffer[256];
            ReadString(&info, buffer);
            CreateEntity(type, buffer, x, y);
        }
        CloseFile(&info);
    }

    ProcessStartupObjects();
}

void DrawMenuGFX()
{
    FillScreen(0x0000F0, 0, 0, 0);

    for (int32 i = 0; i < LEGACY_v4_ENTITY_COUNT; ++i) {
        if (objectEntityList[i].type > 0 && objectEntityList[i].type < menuObjectCount) {
            if (menuObjectList[objectEntityList[i].type].draw) {
                Entity *originalSelf = self;
                self = &objectEntityList[i];
                menuObjectList[objectEntityList[i].type].draw();
                self = originalSelf;
            }
        }
    }
}

} // namespace v4
} // namespace Legacy
} // namespace RSDK
