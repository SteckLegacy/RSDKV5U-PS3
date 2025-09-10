#include "TitleLogo.hpp"
#include "MenuLegacyv4.hpp"
#include "ObjectLegacyv4.hpp"
#include "ScriptLegacyv4.hpp"
#include "../../Graphics/Legacy/v4/DrawingLegacyv4.hpp"
#include "../../Graphics/Legacy/AnimationLegacy.hpp"
#include "RSDK/Core/Reader.hpp"

using namespace RSDK;
using namespace Legacy;

namespace RSDK
{
namespace Legacy
{
namespace v4
{

void Create_TitleLogo(void *data)
{
    EntityTitleLogo *entity = (EntityTitleLogo *)self;
    entity->type = 1;
    entity->xpos = SCREEN_CENTERX << 16;
    entity->ypos = SCREEN_CENTERY << 16;
    entity->drawOrder = 0;
    entity->visible = true;
    entity->state = (int32)Update_TitleLogo;
}

int32 titleLogoSpriteSheet;

void Init_TitleLogo()
{
    RegisterMenuObject("TitleLogo", Create_TitleLogo, Update_TitleLogo, Draw_TitleLogo);
}

void StageLoad_TitleLogo()
{
    titleLogoSpriteSheet = LoadGIF("Data/Menu/SonicLogo.png", 0);

    FileInfo info;
    InitFileInfo(&info);
    if (LoadFile(&info, "Data/Menu/MenuAnimations.bin", FMODE_RB)) {
        int32 animCount = ReadInt16(&info);
        for (int32 i = 0; i < animCount; ++i) {
            int32 frameCount = ReadInt16(&info);
            int32 sheetID = ReadInt16(&info);
            objectScriptList[i + 1].frameCount = frameCount;
            objectScriptList[i + 1].spriteSheetID = sheetID;
            objectScriptList[i + 1].frameListOffset = scriptFrameCount;
            for (int32 f = 0; f < frameCount; ++f) {
                animFrames[scriptFrameCount].sprX = ReadInt16(&info);
                animFrames[scriptFrameCount].sprY = ReadInt16(&info);
                animFrames[scriptFrameCount].width = ReadInt16(&info);
                animFrames[scriptFrameCount].height = ReadInt16(&info);
                animFrames[scriptFrameCount].pivotX = ReadInt16(&info);
                animFrames[scriptFrameCount].pivotY = ReadInt16(&info);
                animFrames[scriptFrameCount].hitboxID = -1;
                scriptFrameCount++;
            }
        }
        CloseFile(&info);
    }
}

void Update_TitleLogo()
{
    // Not implemented
}

void LateUpdate_TitleLogo()
{
    // Not implemented
}

void StaticUpdate_TitleLogo()
{
    // Not implemented
}

void Draw_TitleLogo()
{
    EntityTitleLogo *entity = (EntityTitleLogo *)self;
    SpriteFrame *frame      = &animFrames[objectScriptList[1].frameListOffset + entity->frame];

    DrawSprite((entity->xpos >> 16) - xScrollOffset + frame->pivotX, (entity->ypos >> 16) - yScrollOffset + frame->pivotY, frame->width,
               frame->height, frame->sprX, frame->sprY, titleLogoSpriteSheet);
}

} // namespace v4
} // namespace Legacy
} // namespace RSDK
