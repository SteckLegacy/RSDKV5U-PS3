#include "MenuLegacyv4Objects.hpp"
#include "ObjectLegacyv4.hpp"
#include "MenuLegacyv4.hpp"

using namespace RSDK;
using namespace Legacy;

namespace RSDK
{
namespace Legacy
{
namespace v4
{

void Create_MenuObject(void *data)
{
    // Not implemented
}

void StageLoad_MenuObject()
{
    RegisterMenuObject("MenuObject", Update_MenuObject, StageLoad_MenuObject);
}

void Update_MenuObject()
{
    // Not implemented
}

void LateUpdate_MenuObject()
{
    // Not implemented
}

void StaticUpdate_MenuObject()
{
    // Not implemented
}

void Draw_MenuObject()
{
    // Not implemented
}

} // namespace v4
} // namespace Legacy
} // namespace RSDK
