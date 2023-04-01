#include "Library/Library.hpp"

#define CREATE_HOOK( type, name, args ) inline static VMT name##hk; static type name args; 
#define CREATE_POINTER_HOOK( type, name, args ) inline static Pointer name##hk; static type name args; 
#define HOOK_CUSTOM( addr, orig, repl ) orig = *addr; *addr = reinterpret_cast< std::uintptr_t >( repl ); 

class Hooks
{
private:
	CREATE_POINTER_HOOK(void, OnGUI, (std::uintptr_t));
	CREATE_POINTER_HOOK(void, Update, (MainMenuSystem*));

	CREATE_HOOK(void, ClientInput, (BasePlayer*, std::uintptr_t));
	CREATE_HOOK(void, ClientMovement, (PlayerWalkMovement*, std::uintptr_t, ModelState*));
public:
	static auto Enable() -> void;
	//static auto Disable(void) -> void;
};
namespace CustomHook
{
	static std::uintptr_t ProjectileShootRpchk;
	static auto ProjectileShootRpc(void* _rcx, void* _rdx, void* a1, std::uint64_t projectile_shoot, void* a3) -> void;
	static auto OnProjectileShootRpc(std::uint64_t instance) -> void;
}