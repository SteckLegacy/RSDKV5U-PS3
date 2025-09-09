#pragma once

#include "RSDK/Core/RetroEngine.hpp"

namespace RSDK
{
namespace Legacy
{
namespace v4
{

struct EntityTitleLogo : Entity {
    int32 timer;
    Animator animator;
};

void Init_TitleLogo();
void Create_TitleLogo(void *data);
void StageLoad_TitleLogo();
void Update_TitleLogo();
void LateUpdate_TitleLogo();
void StaticUpdate_TitleLogo();
void Draw_TitleLogo();

} // namespace v4
} // namespace Legacy
} // namespace RSDK
