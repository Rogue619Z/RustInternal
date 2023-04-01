#include "Core/Core.hpp"



bool DllMain(void*, std::uint32_t callReason, void*)
{
	if (callReason != 1)
		return false;

	if (AllocConsole()) {
		SetConsoleTitleA("[+] Debug Console");
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}

	Il2CppWrapper::il2cpp_thread_attach();
	{
		Hooks::Enable();
	}

	return true;

}

//auto DllMain(void*, std::uint32_t call_reason, void*) -> bool {
//	if (call_reason != 1)
//		return false;
//
//	Il2CppWrapper::il2cpp_thread_attach();
//	{
//		Hooks::Enable();
//	}
//
//	return true;
//}

