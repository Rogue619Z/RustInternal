class Material
{
public:
	CLASS("UnityEngine", "Material");

	static auto CreateWithShader(uintptr_t material, uintptr_t shader) -> void
	{
		METHOD(void(**)(uintptr_t, uintptr_t), CreateWithShader);
		return CreateWithShader(material, shader);
	}

	static auto SetPass(uintptr_t material, int zpass) -> bool
	{
		METHOD(bool(**)(uintptr_t, int), SetPass);
		return SetPass(material, zpass);
	}

	static auto SetInt(uintptr_t material, UString str, int set) -> void
	{

		METHOD(void(**)(uintptr_t, UString, int), SetInt);
		return SetInt(material, str, set);
	}
	auto SetInt2(UString name, int value) -> void
	{
		METHOD(void(**)(Material*, UString, int), SetInt);
		return SetInt(this, name, value);
	}
	auto set_shader(Shader* shader) -> void
	{
		if (!this) return;
		METHOD(void(**)(Material*, Shader*), set_shader);
		return set_shader(this, shader);
	}
	auto get_shader() -> Shader*
	{
		if (!this) return nullptr;
		METHOD(Shader*(**)(Material*), get_shader);
		return get_shader(this);
	}
	auto SetFloat(UString name, float value) -> void
	{
		if (!this) return;
		METHOD(void(**)(Material*, UString, float), SetFloat);
		return SetFloat(this, name, value);
	}

	auto SetColor(UString name, Color value) -> void
	{
		if (!this) return;
		METHOD(void(**)(Material*, UString, Color), SetColor);
		return SetColor(this, name, value);
	}
};
