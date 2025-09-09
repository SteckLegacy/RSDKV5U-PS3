#pragma once

#include "RSDK/Core/RetroEngine.hpp"

namespace RSDK
{
namespace Legacy
{
namespace v4
{

// Example Menu Object
struct EntityMenuObject : Entity {
    // Custom variables for the menu object
};

// Object-specific functions
void Create_MenuObject(void *data);
void StageLoad_MenuObject();
void Update_MenuObject();
void LateUpdate_MenuObject();
void StaticUpdate_MenuObject();
void Draw_MenuObject();

} // namespace v4
} // namespace Legacy
} // namespace RSDK
