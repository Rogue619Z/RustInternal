class ModelState
{
public:
	CLASS("", "ModelState");


	auto SetFlag(Enums::ModelStateFlags flag) -> void
	{
		if (!this) return;
		METHOD(void(**)(ModelState*, Enums::ModelStateFlags, bool), SetFlag);
		return SetFlag(this, flag, true);
	}
	auto set_jumped(bool value) -> void
	{
		if (!this) return;
		METHOD(void(**)(ModelState*, bool), set_jumped);
		return set_jumped(this, value);
	}
	auto get_onground() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(ModelState*), get_onground);
		return get_onground(this);
	}
	auto set_onLadder(bool value) -> void
	{
		if (!this) return;
		METHOD(void(**)(ModelState*, bool), set_onLadder);
		return set_onLadder(this, value);
	}
	auto set_ducked(bool value) -> void
	{
		if (!this) return;
		METHOD(void(**)(ModelState*, bool), set_ducked);
		return set_ducked(this, value);
	}
};