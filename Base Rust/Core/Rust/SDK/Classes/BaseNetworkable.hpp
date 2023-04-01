class BaseNetworkable : public Component
{
public:
	CLASS("", "BaseNetworkable");

	MEMBER(std::uintptr_t*, net);


	bool PlayerValid() {
		if (!this) return false;
		return !this->PlayerDestroyed() && this->net() != nullptr;
	}
		auto get_ShortPrefabName(UString entity) ->  std::uint32_t
		{
			if (!this) return 0;
			METHOD(std::uint32_t(**)(Component*, UString), get_ShortPrefabName);
			return get_ShortPrefabName(this, entity);
		}
	auto HasParent() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseNetworkable*), HasParent);
		return HasParent(this);
	}

	auto PlayerDestroyed() -> bool
	{
		if (!this) return false;
		static auto k__BackingField = Il2CppWrapper::GetClassFromName("", "BaseNetworkable")->GetFieldFromName("<IsDestroyed>k__BackingField");
		return *reinterpret_cast<bool*>(this + k__BackingField);
	}
};