class Time
{
public:
	CLASS("UnityEngine", "Time");

	static auto get_time() -> float
	{
		METHOD(float(**)(), get_time);
		return get_time();
	}
	static auto get_deltaTime() -> float
	{
		METHOD(float(**)(), get_deltaTime);
		return get_deltaTime();
	}
	static auto get_frameCount() -> int
	{
		METHOD(float(**)(), get_frameCount);
		return get_frameCount();
	}
	static auto get_timeScale() -> float
	{
		METHOD(float(**)(), get_timeScale);
		return get_timeScale();
	}
	static auto get_fixedDeltaTime() -> float
	{
		METHOD(float(**)(), get_fixedDeltaTime);
		return get_fixedDeltaTime();
	}
	static auto get_smoothDeltaTime() -> float
	{
		METHOD(float(**)(), get_smoothDeltaTime);
		return get_smoothDeltaTime();
	}
	static auto get_fixedTime() -> float
	{
		METHOD(float(**)(), get_fixedTime);
		return get_fixedTime();
	}
	static auto realtimeSinceStartup() -> float
	{
		METHOD(float(**)(), get_realtimeSinceStartup);
		return get_realtimeSinceStartup();
	}
	static auto set_timeScale(float value) -> void
	{
		METHOD(void(**)(float), set_timeScale);
		return set_timeScale(value);
	}

};