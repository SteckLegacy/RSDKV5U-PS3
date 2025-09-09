namespace RSDK
{
namespace Legacy
{
namespace v4
{

// Forward Declarations
struct Entity;

void ProcessMenu();
void LoadMenuAssets();
void DrawMenuGFX();

void RegisterMenuObject(const char *name, void (*create)(void *data), void (*update)(), void (*draw)());
void InitMenuObjects();

} // namespace v4
} // namespace Legacy
} // namespace RSDK
