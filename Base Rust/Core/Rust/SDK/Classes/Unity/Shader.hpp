class Shader {
public:
	CLASS("UnityEngine", "Shader");

	static auto Find(UString shader) -> Shader*
	{
		METHOD(Shader * (**)(UString), Find);
		return Find(shader);
	}
};