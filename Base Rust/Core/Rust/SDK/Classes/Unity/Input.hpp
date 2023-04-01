class Input
{
public:
	CLASS("UnityEngine", "Input");

	static auto get_mousePosition() -> Vector3
	{
		METHOD(Vector3(**)(), get_mousePosition);
		return get_mousePosition();
	}
	static auto GetKey(Enums::KeyCode code) -> bool
	{
		METHOD(bool(**)(Enums::KeyCode), GetKey);
		return GetKey(code);
	}
	static auto GetKeyDown(Enums::KeyCode code) -> bool
	{
		METHOD(bool(**)(Enums::KeyCode), GetKeyDown);
		return GetKeyDown(code);
	}
};