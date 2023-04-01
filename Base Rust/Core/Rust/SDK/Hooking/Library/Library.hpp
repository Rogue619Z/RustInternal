#pragma once

class Pointer
{
private:
	uintptr_t m_original{ 0 };
public:
	auto InitialiseHook(const char* nameSpace, const char* klass, const char* method, void* ourFunction) -> void
	{
		auto il2cppMethod = Il2CppWrapper::GetClassFromName(nameSpace, klass)->GetMethodFromName(method, -1, "");
		m_original = *reinterpret_cast<uintptr_t*>(il2cppMethod);
		*reinterpret_cast<void**>(il2cppMethod) = ourFunction;

		if (!ourFunction)
		{
			printf("[ DEBUG ] Failed to hook %s.\n", method);
		}
		else
			printf("[ DEBUG ] Hooked %s.\n", method);
	}
};
class VMT
{
private:
	std::uintptr_t m_original{ 0 };
public:
	auto InitialiseHook(const char* nameSpace, const char* klass, const char* method, void* ourFunction) -> void
	{
	    //const auto st = sanitize_method_name(method);

		const auto search_method = *reinterpret_cast<std::uintptr_t*>(Il2CppWrapper::GetClassFromName(nameSpace, klass)->GetMethodFromName(method, -1, ""));
	//	const auto search_method = (std::uintptr_t)Il2CppWrapper::GetClassFromName(nameSpace, klass)->GetMethodFromName(method, -1, "");
		const auto class_base = Il2CppWrapper::GetClassFromName(nameSpace, klass);

		if (search_method == std::uintptr_t(ourFunction))
			return;

		if (!ourFunction)
		{
			printf("[ DEBUG ] Failed to hook %s.\n", method);
		}
		else
			printf("[ DEBUG ] Hooked %s.\n", method);

		for (auto idx{ class_base }; idx <= class_base + 0x1500; idx += 0x1) {
			const auto addr = *reinterpret_cast<std::uintptr_t*>(idx);
			if (addr == search_method) {
				//printf("Sui");
				m_original = search_method;
				*reinterpret_cast<std::uintptr_t*>(idx) = std::uintptr_t(ourFunction);
			}
		}
	}

	template< typename type >
	auto get_original() -> type { return reinterpret_cast<type>(m_original); }

	auto restore(void* our_function) -> void {
		*reinterpret_cast<void**>(our_function) = &m_original;
	}
};
//class VMT
//{
//private:
//	uintptr_t* m_original{ 0 };
//public:
//	auto InitialiseHook(const char* nameSpace, const char* klass, const char* method, void* ourFunction, int argCount = -1) -> void
//	{
//		auto searchMethod = *reinterpret_cast<uintptr_t**>(Il2CppWrapper::GetClassFromName(nameSpace, klass)->GetMethodFromName(method, argCount, ""));
//		if (!method)
//			return;
//
//		const auto classBase = *reinterpret_cast<uintptr_t**>(Il2CppWrapper::GetClassFromName(nameSpace, klass));
//
//		if (method == ourFunction)
//			return;
//
//		if (!ourFunction)
//		{
//			printf("[ DEBUG ] Failed to hook %s.\n", method);
//		}
//		else
//			printf("[ DEBUG ] Hooked %s.\n", method);
//
//		for (auto idx{ classBase }; idx <= classBase + 0x1500; idx += 0x1) {
//			const auto Address = *reinterpret_cast<uintptr_t**>(idx);
//			if (Address == searchMethod)
//			{
//				m_original = searchMethod;
//				*reinterpret_cast<uintptr_t*>(idx) = uintptr_t(ourFunction);
//			}
//		}
//	}
//
//
//	template< typename t>
//	auto get_original() -> t
//	{
//		return reinterpret_cast<t>(m_original);
//	}
//
//};
//class HookLib
//{
//private:
//	std::uintptr_t m_original{ 0 };
//public:
//
//	static auto Awake() -> bool
//	{
//		if (MH_Initialize() != MH_OK)
//			return false;
//
//		return true;
//	}
//
//	auto InitializeHook(const char* name_space, const char* klass, const char* method, void* our_function) -> void
//	{
//		auto function = *reinterpret_cast<void**>(Il2CppWrapper::GetClassFromName(name_space, klass)->GetMethodFromName(method));
//		if (!function)
//			return;
//
//		if (!function)
//		{
//			printf("[ DEBUG ] Failed to hook %s.\n", method);
//		}
//		else
//			printf("[ DEBUG ] Hooked %s.\n", method);
//
//		MH_CreateHook((void*)function, our_function, (void**)&m_original);
//		MH_EnableHook(function);
//	}
//
//
//	template< typename t>
//	auto get_original() -> t
//	{
//		return reinterpret_cast<t>(m_original);
//	}
//};