class WaterLevel
{
public:
	CLASS("", "WaterLevel");

	static auto Test(Vector3 a, bool a1, BaseEntity* a2) -> bool
	{
		METHOD(bool(**)(Vector3, bool, BaseEntity*), Test);
		return Test(a, a1, a2);
	}
};