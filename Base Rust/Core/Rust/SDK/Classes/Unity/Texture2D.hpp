class Texture2D
{
public:
	CLASS("UnityEngine", "Texture2D");

	static auto get_whiteTexture() -> std::uintptr_t
	{
		METHOD(std::uintptr_t(**)(), get_whiteTexture);
		return get_whiteTexture();
	}

};