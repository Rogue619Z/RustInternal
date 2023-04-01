class Physics
{
public:
	CLASS("UnityEngine", "Physics");

	static auto get_gravity() -> Vector3
	{
		METHOD(Vector3(**)(), get_gravity);
		return get_gravity();
	}
	static auto CheckCapsule(Vector3 start, Vector3 end, float radius, int layerMask, Enums::QueryTriggerInteraction query) -> bool
	{
		METHOD(bool(**)(Vector3, Vector3, float, int, Enums::QueryTriggerInteraction), CheckCapsule);
		return CheckCapsule(start, end, radius, layerMask, query);
	}
	//void ServerRPC(const wchar_t* func) {
	//	if (!this) return;
	//	auto off = reinterpret_cast<void (*)(BaseEntity*, UString)>(*reinterpret_cast<uintptr_t*>(StaticClass()->GetMethodFromName("ServerRPC", 1, "funcName")));
	//	return off(this, UString(func));
	//}

	//static auto Raycast(Ray pos, float distance, int layerMask) -> bool
	//{
	//	static auto RayCast = reinterpret_cast<bool(*)(Ray, float, int)>(StaticClass()->GetMethodFromName("Raycast", 3));
	//	return RayCast(pos, distance, layerMask);
	//}
};
static auto Raycast = reinterpret_cast<bool (*)(Ray, float, int)>(*reinterpret_cast<uintptr_t*>(Il2CppWrapper::GetClassFromName("UnityEngine", "Physics")->GetMethodFromName("Raycast", 3)));
static auto SphereCast = reinterpret_cast<bool (*)(Ray, float, float, int)>(*reinterpret_cast<uintptr_t*>(Il2CppWrapper::GetClassFromName("UnityEngine", "Physics")->GetMethodFromName("SphereCast", 4)));