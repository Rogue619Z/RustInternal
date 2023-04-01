class GUIStyle
{
public:
	CLASS("UnityEngine", "GUIStyle");


	auto set_alignment(Enums::TextAnchor value) -> bool
	{
		static auto alig = *reinterpret_cast<bool(**)(GUIStyle*, Enums::TextAnchor)>(Il2CppWrapper::GetClassFromName("UnityEngine", "GUIStyle")->GetMethodFromName("set_alignment"));
		return alig(this, value);
	}
	auto CalcSize(GUIContent* content) -> Vector2
	{
		if (!this) return Vector2::Zero();
		Vector2 ret = Vector2::Zero();
		reinterpret_cast<void(__fastcall*)(GUIStyle*, GUIContent*, Vector2*)>(LI_MODULE_SAFE_("GameAssembly.dll") + 0x1CE65B0)(this, content, &ret);
		return ret;
	}
	 auto set_fontSize(int size) -> void
	{
		METHOD(void(**)(GUIStyle*, int), set_fontSize);
		return set_fontSize(this, size);
	}
};