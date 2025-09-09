#pragma once

#include "RSDK/Core/RetroEngine.hpp"

namespace RSDK
{
namespace Legacy
{
namespace v4
{

struct EntityPressStart : Entity {
    int32 timer;
    bool32 visible;
};

void Init_PressStart();
void Create_PressStart(void *data);
void StageLoad_PressStart();
void Update_PressStart();
void LateUpdate_PressStart();
void StaticUpdate_PressStart();
void Draw_PressStart();

} // namespace v4
} // namespace Legacy
} // namespace RSDK
