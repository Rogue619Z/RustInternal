class BaseMovement
{
public:
	CLASS("", "BaseMovement");

	MEMBER(bool, adminCheat);
	MEMBER(float, adminSpeed);

	auto get_TargetMovement() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseMovement*), get_TargetMovement);
		return get_TargetMovement(this);
	}
	auto get_InheritedVelocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseMovement*), get_InheritedVelocity);
		return get_InheritedVelocity(this);
	}
	auto CurrentVelocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseMovement*), CurrentVelocity);
		return CurrentVelocity(this);
	}
	auto get_Running() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseMovement*), get_Running);
		return get_Running(this);
	}
	auto get_Ducking() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseMovement*), get_Ducking);
		return get_Ducking(this);
	}
	auto set_TargetMovement(Vector3 value) -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseMovement*, Vector3), set_TargetMovement);
		return set_TargetMovement(this, value);
	}
	auto TeleportTo(Vector3 pos, BasePlayer* player) -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseMovement*, Vector3, BasePlayer*), TeleportTo);
		return TeleportTo(this, pos, player);
	}
	auto get_Crawling() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseMovement*), get_Crawling);
		return get_Crawling(this);
	}
	auto get_Grounded() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseMovement*), get_Grounded);
		return get_Grounded(this);
	}
	auto get_IsRunning() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseMovement*), get_IsRunning);
		return get_IsRunning(this);
	}
	auto get_IsDucked() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseMovement*), get_IsDucked);
		return get_IsDucked(this);
	}
	auto get_RecentlyTeleported() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseMovement*), get_RecentlyTeleported);
		return get_RecentlyTeleported(this);
	}
	auto get_IsCrawling() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseMovement*), get_IsCrawling);
		return get_IsCrawling(this);
	}
	auto get_IsGrounded() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseMovement*), get_IsGrounded);
		return get_IsGrounded(this);
	}
	auto CurrentMoveSpeed() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseMovement*), CurrentMoveSpeed);
		return CurrentMoveSpeed(this);
	}
	auto get_Owner() -> BasePlayer*
	{
		if (!this) return nullptr;
		METHOD(BasePlayer*(**)(BaseMovement*), get_Owner);
		return get_Owner(this);
	}
	auto ducking() -> float
	{
		if (!this) return 0.0f;
		auto k__BackingField = Il2CppWrapper::GetClassFromName("", "BaseMovement")->GetFieldFromName("<Ducking>k__BackingField");
		return *reinterpret_cast<float*>(this + k__BackingField);
	}
	auto grounded() -> float
	{
		if (!this) return 0.0f;
		auto grounded = Il2CppWrapper::GetClassFromName("", "BaseMovement")->GetFieldFromName("<Grounded>k__BackingField");
		return *reinterpret_cast<float*>(this + grounded);
	}
};