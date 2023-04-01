class PlayerEyes
{
public:
	CLASS("", "PlayerEyes");

	MEMBER(Vector3, viewOffset);

	static auto EyeOffset() -> Vector3
	{
		auto graphic = Il2CppWrapper::GetClassFromName("", "PlayerEyes");

		return *reinterpret_cast<Vector3*>(*reinterpret_cast<uintptr_t*>(graphic + 0xB8) + 0x0);
	}

	auto MovementRight() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(PlayerEyes*), MovementRight);
		return MovementRight(this);
	}

	auto BodyRight() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(PlayerEyes*), BodyRight);
		return BodyRight(this);
	}
	auto get_center() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(PlayerEyes*), get_center);
		return get_center(this);
	}
	auto BodyForward() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(PlayerEyes*), BodyForward);
		return BodyForward(this);
	}

	auto BodyUp() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(PlayerEyes*), BodyUp);
		return BodyUp(this);
	}

	auto MovementForward() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(PlayerEyes*), MovementForward);
		return MovementForward(this);
	}

	auto get_position() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(PlayerEyes*), get_position);
		return get_position(this);
	}
	auto get_rotation() -> Vector4
	{
		if (!this) return Vector4::Zero();
		METHOD(Vector4(**)(PlayerEyes*), get_rotation);
		return get_rotation(this);
	}
};