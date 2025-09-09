#pragma once

#include "RSDK/Core/RetroEngine.hpp"
#include "MenuButton.hpp"

namespace RSDK
{
namespace Legacy
{
namespace v4
{

struct EntityMainMenu : Entity {
    int32 optionCount;
    int32 selectedOption;
    EntityMenuButton *options[8];
};

void Init_MainMenu();
void Create_MainMenu(void *data);
void StageLoad_MainMenu();
void Update_MainMenu();
void LateUpdate_MainMenu();
void StaticUpdate_MainMenu();
void Draw_MainMenu();

} // namespace v4
} // namespace Legacy
} // namespace RSDK
