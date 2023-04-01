class GL
{
public:
	CLASS("UnityEngine", "GL");

	static inline uintptr_t draw_material;

	static auto Begin(int type) -> void
	{
		METHOD(void(**)(int), Begin);
		return Begin(type);
	}

	static auto End() -> void
	{
		METHOD(void(**)(), End);
		return End();
	}

	static auto PushMatrix() -> void
	{
		METHOD(void(**)(), PushMatrix);
		return PushMatrix();
	}

	static auto PopMatrix() -> void
	{
		METHOD(void(**)(), PopMatrix);
		return PopMatrix();
	}

	static auto LoadPixelMatrix() -> void
	{
		METHOD(void(**)(), LoadPixelMatrix);
		return LoadPixelMatrix();
	}

	static auto Vertex3(float x, float y, float z) -> void
	{
		METHOD(void(**)(float, float, float), Vertex3);
		return Vertex3(x, y, z);
	}
	static auto Vertex(Vector3 v) -> void
	{
		METHOD(void(**)(Vector3), Vertex);
		return Vertex(v);
	}


	static auto SetupMaterial() -> void {
		draw_material = Il2CppWrapper::il2cpp_object_new<uintptr_t>(Il2CppWrapper::GetClassFromName("UnityEngine", "Material"));
		Material::CreateWithShader(draw_material, (std::uintptr_t)Shader::Find(L"Hidden/Internal-Colored"));

		Material::SetInt(draw_material, L"_SrcBlend", 5);
		Material::SetInt(draw_material, L"_DstBlend", 10);
		Material::SetInt(draw_material, L"_Cull", 0);
		Material::SetInt(draw_material, L"_ZWrite", 0);
	}

	static auto SetupGL()
	{

		if (!draw_material)
			SetupMaterial();
	}

	static auto EndGL() {
		End();
		PopMatrix();
	}
};
