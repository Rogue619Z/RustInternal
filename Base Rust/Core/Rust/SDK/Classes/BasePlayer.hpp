class BasePlayer : public BaseCombatEntity
{
public:
	CLASS("", "BasePlayer");

	MEMBER(std::uintptr_t, playerFlags);
	MEMBER(std::uint32_t, clActiveItem);
	MEMBER(std::uint32_t, mounted);
	MEMBER(PlayerModel*, playerModel);
	MEMBER(PlayerInventory*, inventory);
	MEMBER(UString*, _displayName);
	MEMBER(BaseMovement*, movement);
	MEMBER(float, lastSentTickTime);
	MEMBER(float, clientTickInterval);
	MEMBER(float, serverTickInterval);
	MEMBER(int, clientTickRate);
	MEMBER(bool, Frozen);
	MEMBER(PlayerTick*, lastSentTick);
	MEMBER(unsigned long long, userID);
	MEMBER(PlayerEyes*, eyes);

	auto GetHeight(bool ducked) -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BasePlayer*, bool), GetHeight);
		return GetHeight(this, ducked);
	}
	auto GetHeight() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BasePlayer*), GetHeight);
		return GetHeight(this);
	}
	auto GetBounds() -> Bounds
	{
		if (!this) return Bounds();
		METHOD(Bounds(**)(BasePlayer*), GetBounds);
		return GetBounds(this);
	}
	auto GetSpeed(float running, float ducking, float crawling) -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BasePlayer*, float, float, float), GetSpeed);
		return GetSpeed(this, running, ducking, crawling);
	}
	auto GetMountVelocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BasePlayer*), GetMountVelocity);
		return GetMountVelocity(this);
	}
	auto GetRadius() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BasePlayer*), GetRadius);
		return GetRadius(this);
	}
	auto NoClipOffset() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BasePlayer*), NoClipOffset);
		return NoClipOffset(this);
	}
	auto get_lookingAtPoint() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BasePlayer*), get_lookingAtPoint);
		return get_lookingAtPoint(this);
	}
	auto GetJumpHeight() -> float
	{
		if (!this ) return 0.0f;
		METHOD(float(**)(BasePlayer*), GetJumpHeight);
		return GetJumpHeight(this);
	}
	auto Menu_AssistPlayer(BasePlayer* player) -> void
	{
		if (!this) return;
		METHOD(void(**)(BasePlayer*, BasePlayer*), Menu_AssistPlayer);
		return Menu_AssistPlayer(this, player);
	}
	auto InFirstPersonMode() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BasePlayer*), InFirstPersonMode);
		return InFirstPersonMode(this);
	}
	auto OnLadder() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BasePlayer*), OnLadder);
		return OnLadder(this);
	}
	auto IsSwimming() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BasePlayer*), IsSwimming);
		return IsSwimming(this);
	}
	auto IsOnGround() -> bool
	{
		if (!this ) return false;
		METHOD(bool(**)(BasePlayer*), IsOnGround);
		return IsOnGround(this);
	}
	auto IsCrawling() -> bool
	{
		if (!this ) return false;
		METHOD(bool(**)(BasePlayer*), IsCrawling);
		return IsCrawling(this);
	}
	auto IsRunning() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BasePlayer*), IsRunning);
		return IsRunning(this);
	}
	auto IsDucked() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BasePlayer*), IsDucked);
		return IsDucked(this);
	}
	auto SendClientTick() -> void
	{
		if (!this) return;
		METHOD(void(**)(BasePlayer*), SendClientTick);
		return SendClientTick(this);
	}
	auto ForcePositionTo(Vector3 pos) -> void
	{
		if (!this) return;
		METHOD(void(**)(BasePlayer*, Vector3), ForcePositionTo);
		return ForcePositionTo(this, pos);
	}
	auto GetMaxSpeed() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BasePlayer*), GetMaxSpeed);
		return GetMaxSpeed(this);
	}
	auto MaxEyeVelocity() -> float
	{
		if (!this) return 0.0f;

		float speed = this->GetMaxSpeed();

		const auto mounted = this->mounted();
		if (mounted)
		{
			return speed * 4.0f;
		}
		return speed;
	}
	auto velocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		auto newVelocity = Il2CppWrapper::GetClassFromName("", "PlayerModel")->GetFieldFromName("newVelocity");

		if (newVelocity == 0)
			return Vector3::Zero();

		return *reinterpret_cast<Vector3*>(this->playerModel() + newVelocity);
	}
	Vector3 midPoint()
	{
		if (!this) return Vector3::Zero();
		return this->get_bone_transform(Enums::r_foot)->get_position().midPoint(this->get_bone_transform(Enums::l_foot)->get_position()) - Vector3(0.0f, 0.1f, 0.0f);
	}
	auto get_bone_transform(int index) -> Transform*
	{
		const auto model = this->model();
		if (!model)
			return { };

		const auto boneTransforms = (std::uintptr_t)model->boneTransforms();
		if (!boneTransforms)
			return { };

		return *reinterpret_cast<Transform**>(boneTransforms + 0x20 + (index * 0x8));
	}	

	auto item() -> Item*
	{
		const auto ActiveUid = this->clActiveItem();
		if (!ActiveUid)
			return { };

		const auto inventory = this->inventory();
		if (!inventory)
			return { };

		const auto belt = inventory->containerBelt();
		if (!belt)
			return { };

		const auto itemList = belt->itemList();
		if (!itemList)
			return { };

		const auto items = *reinterpret_cast<uint64_t*>(itemList + 0x10);
		if (!items)
			return { };

		for (int i = 0; i < 6; i++)
		{
			const auto item = *reinterpret_cast<Item**> (items + 0x20 + (i * 0x8));
			if (!item)
				continue;

			if (ActiveUid == item->uid())
				return item;
		}

		return { };
	}
	static auto playerList() -> ListDictionary*
	{
		static auto visiblePlayerList = Il2CppWrapper::GetClassFromName("", "BasePlayer")->GetFieldFromName("visiblePlayerList");

		return *reinterpret_cast<ListDictionary**>(*reinterpret_cast<uintptr_t*>(StaticClass() + 0xB8) + visiblePlayerList);
	}
	inline auto HasFlag(Enums::PlayerFlags flag) -> bool
	{
		return (playerFlags() & uintptr_t(flag)) == uintptr_t(flag);
	}
};
BasePlayer* target_ply{ nullptr };