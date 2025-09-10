#include "PressStart.hpp"
#include "MenuLegacyv4.hpp"
#include "ObjectLegacyv4.hpp"
#include "../../Graphics/Legacy/v4/DrawingLegacyv4.hpp"
#include "../../Storage/Legacy/TextLegacy.hpp"
#include <string>

using namespace RSDK;
using namespace Legacy;

namespace RSDK
{
namespace Legacy
{
namespace v4
{

int32 pressStartSpriteSheet;
std::string pressStartText;

void Create_PressStart(void *data)
{
    EntityPressStart *entity = (EntityPressStart *)self;
    entity->type = 2;
    entity->xpos = SCREEN_CENTERX << 16;
    entity->ypos = (SCREEN_CENTERY + 48) << 16;
    entity->drawOrder = 0;
    entity->visible = true;
    entity->state = (int32)Update_PressStart;
}

void Init_PressStart()
{
    RegisterMenuObject("PressStart", Create_PressStart, Update_PressStart, Draw_PressStart);
}

#include "RSDK/Core/Reader.hpp"

void StageLoad_PressStart()
{
    pressStartSpriteSheet = LoadSpriteSheet("Data/Menu/Heading_EN.fnt");

    FileInfo info;
    InitFileInfo(&info);
    if (LoadFile(&info, "Data/Menu/MenuText.txt", FMODE_RB)) {
        char buffer[256];
        ReadString(&info, buffer);
        pressStartText = buffer;
        CloseFile(&info);
    }
}

void Update_PressStart()
{
    EntityPressStart *entity = (EntityPressStart *)self;
    entity->timer++;
    if (entity->timer > 30) {
        entity->timer = 0;
        entity->visible = !entity->visible;
    }
}

void LateUpdate_PressStart()
{
    // Not implemented
}

void StaticUpdate_PressStart()
{
    // Not implemented
}

void Draw_PressStart()
{
    EntityPressStart *entity = (EntityPressStart *)self;
    if (entity->visible) {
        DrawText((entity->xpos >> 16) - 64, (entity->ypos >> 16), pressStartText.c_str(), 0, pressStartSpriteSheet);
    }
}

} // namespace v4
} // namespace Legacy
} // namespace RSDK
