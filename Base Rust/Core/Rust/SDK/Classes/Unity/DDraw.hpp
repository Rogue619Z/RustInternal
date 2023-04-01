class DDraw
{
public:
	CLASS("UnityEngine", "DDraw");

	static auto Get() -> void
	{
		METHOD(void(**)(), Get);
		return Get();
	}
	static auto Sphere(Vector3 v3, float vl, Color va, float f2, bool fs) -> void
	{
		METHOD(void(**)(Vector3, float, Color, float, bool), Sphere);
		return Sphere(v3, vl, va, f2, fs);
	}
};