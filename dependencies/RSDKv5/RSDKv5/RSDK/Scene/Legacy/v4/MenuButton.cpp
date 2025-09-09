#include "MenuButton.hpp"
#include "MenuLegacyv4.hpp"
#include "ObjectLegacyv4.hpp"
#include "../../Graphics/Legacy/v4/DrawingLegacyv4.hpp"
#include "../../Storage/Legacy/TextLegacy.hpp"

using namespace RSDK;
using namespace Legacy;

namespace RSDK
{
namespace Legacy
{
namespace v4
{

int32 menuButtonSpriteSheet;

void Init_MenuButton()
{
    RegisterMenuObject("MenuButton", Create_MenuButton, Update_MenuButton, Draw_MenuButton);
}

void Create_MenuButton(void *data)
{
    EntityMenuButton *entity = (EntityMenuButton *)self;
    entity->type = 3; // New object type
    entity->drawOrder = 0;
    entity->visible = true;
    entity->state = (int32)Update_MenuButton;
    if (data) {
        entity->text = (const char*)data;
    }
    entity->action = nullptr;
}

void StageLoad_MenuButton()
{
    menuButtonSpriteSheet = LoadSpriteSheet("Jules/S1 menu/Game/Menu/Heading_EN.fnt");
}

void Update_MenuButton()
{
    // Not implemented
}

void LateUpdate_MenuButton()
{
    // Not implemented
}

void StaticUpdate_MenuButton()
{
    // Not implemented
}

void Draw_MenuButton()
{
    EntityMenuButton *entity = (EntityMenuButton *)self;
    int32 x = (entity->xpos >> 16);
    int32 y = (entity->ypos >> 16);
    if (entity->selected) {
        // Draw something to indicate selection
        DrawRectangle(x - 64, y - 8, 128, 16, 0xFFFF00, 0xFF, INK_BLEND, false);
    }
    DrawText(x - (entity->text.length() * 8) / 2, y - 8, entity->text.c_str(), 0, menuButtonSpriteSheet);
}

} // namespace v4
} // namespace Legacy
} // namespace RSDK
