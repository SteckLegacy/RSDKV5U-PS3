#include "MainMenu.hpp"
#include "MenuLegacyv4.hpp"
#include "ObjectLegacyv4.hpp"
#include "RSDK/Core/RetroEngine.hpp"

using namespace RSDK;
using namespace Legacy;

namespace RSDK
{
namespace Legacy
{
namespace v4
{

void Action_StartGame()
{
    gameMode = ENGINE_MAINGAME;
    stageMode = STAGEMODE_LOAD;
}

void Action_Options()
{
    // Not implemented
}

void Action_Exit()
{
    engine.running = false;
}

void Init_MainMenu()
{
    RegisterMenuObject("MainMenu", Create_MainMenu, Update_MainMenu, Draw_MainMenu);
}

void Create_MainMenu(void *data)
{
    EntityMainMenu *entity = (EntityMainMenu *)self;
    entity->type = 4; // New object type
    entity->drawOrder = 0;
    entity->visible = true;
    entity->state = (int32)Update_MainMenu;
    entity->optionCount = 0;
    entity->selectedOption = 0;

    for (int32 i = 0; i < LEGACY_v4_ENTITY_COUNT; ++i) {
        if (objectEntityList[i].type == 3) { // 3 is MenuButton
            entity->options[entity->optionCount++] = (EntityMenuButton *)&objectEntityList[i];
        }
    }

    if (entity->optionCount > 0) {
        entity->options[0]->selected = true;
        entity->options[0]->action = Action_StartGame;
    }
    if (entity->optionCount > 1) {
        entity->options[1]->action = Action_Options;
    }
    if (entity->optionCount > 2) {
        entity->options[2]->action = Action_Exit;
    }
}

void StageLoad_MainMenu()
{
    // No assets to load
}

void Update_MainMenu()
{
    EntityMainMenu *entity = (EntityMainMenu *)self;

    if (controller[CONT_ANY].keyUp.press) {
        if (entity->optionCount > 0) {
            entity->options[entity->selectedOption]->selected = false;
            entity->selectedOption--;
            if (entity->selectedOption < 0) {
                entity->selectedOption = entity->optionCount - 1;
            }
            entity->options[entity->selectedOption]->selected = true;
        }
    }

    if (controller[CONT_ANY].keyDown.press) {
        if (entity->optionCount > 0) {
            entity->options[entity->selectedOption]->selected = false;
            entity->selectedOption++;
            if (entity->selectedOption >= entity->optionCount) {
                entity->selectedOption = 0;
            }
            entity->options[entity->selectedOption]->selected = true;
        }
    }

    if (controller[CONT_ANY].keyStart.press) {
        if (entity->optionCount > 0) {
            EntityMenuButton *button = entity->options[entity->selectedOption];
            if (button->action) {
                button->action();
            }
        }
    }
}

void LateUpdate_MainMenu()
{
    // Not implemented
}

void StaticUpdate_MainMenu()
{
    // Not implemented
}

void Draw_MainMenu()
{
    // Not implemented
}

} // namespace v4
} // namespace Legacy
} // namespace RSDK
