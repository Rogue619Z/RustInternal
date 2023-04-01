class Cursor
{
public:
	CLASS("UnityEngine", "Cursor");

	static auto set_lockState(Enums::CursorLockMode value) -> void
	{
		METHOD(void(**)(Enums::CursorLockMode), set_lockState);
		return set_lockState(value);
	}
	static auto set_visible(bool value) -> void
	{
		METHOD(void(**)(bool), set_visible);
		return set_visible(value);
	}
};