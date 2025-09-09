#pragma once

#include "RSDK/Core/RetroEngine.hpp"
#include <string>

namespace RSDK
{
namespace Legacy
{
namespace v4
{

struct EntityMenuButton : Entity {
    int32 timer;
    bool32 selected;
    std::string text;
    void (*action)();
};

void Init_MenuButton();
void Create_MenuButton(void *data);
void StageLoad_MenuButton();
void Update_MenuButton();
void LateUpdate_MenuButton();
void StaticUpdate_MenuButton();
void Draw_MenuButton();

} // namespace v4
} // namespace Legacy
} // namespace RSDK
