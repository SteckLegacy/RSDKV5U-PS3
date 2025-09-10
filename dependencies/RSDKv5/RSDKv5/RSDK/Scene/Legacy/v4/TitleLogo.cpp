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
    titleLogoSpriteSheet = LoadGIF("Jules/S1 menu/Game/Menu/SonicLogo.png", 0);

    objectScriptList[1].frameCount     = 1;
    objectScriptList[1].spriteSheetID  = titleLogoSpriteSheet;
    objectScriptList[1].frameListOffset = scriptFrameCount;

    animFrames[scriptFrameCount].sprX    = 0;
    animFrames[scriptFrameCount].sprY    = 0;
    animFrames[scriptFrameCount].width   = 256;
    animFrames[scriptFrameCount].height  = 48;
    animFrames[scriptFrameCount].pivotX  = 0;
    animFrames[scriptFrameCount].pivotY  = 0;
    animFrames[scriptFrameCount].hitboxID = -1;
    scriptFrameCount++;
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
