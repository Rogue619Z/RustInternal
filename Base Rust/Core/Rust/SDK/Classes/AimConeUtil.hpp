class AimConeUtil
{
public:
	CLASS("", "AimConeUtil");

	static auto GetModifiedAimConeDirection(float a, Vector3 a1, bool a2) -> Vector3
	{
		METHOD(Vector3(**)(float, Vector3, bool), GetModifiedAimConeDirection);
		return GetModifiedAimConeDirection(a, a1, a2);
	}
};