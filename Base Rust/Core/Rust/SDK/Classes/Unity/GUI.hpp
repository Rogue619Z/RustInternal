class GUI
{
public:
	CLASS("UnityEngine", "GUI");


	static void Label(Rect position, GUIContent* text, GUIStyle* style) {
		auto off = reinterpret_cast<void (*)(Rect, GUIContent*, GUIStyle*)>(*reinterpret_cast<uintptr_t*>(StaticClass()->GetMethodFromName("Label", 3, "content", 2)));
		return off(position, text, style);
	}
	//auto set_alignment(Enums::TextAnchor value) -> bool
	//{
	//	static auto alig = *reinterpret_cast<bool(**)(GUIStyle*, Enums::TextAnchor)>(Il2CppWrapper::GetClassFromName("UnityEngine", "GUIStyle")->GetMethodFromName("set_alignment"));
	//	return alig(this, value);
	//}
	//static auto Label(Rect position, UString* text, GUIStyle* style)  -> void {
	//	METHOD(void(**)(Rect, UString*, GUIStyle*), Label);
	//	return Label(position, text, style);
	//}
	static auto set_color(Color color) -> void{
		METHOD(void(**)(Color), set_color);
		return set_color(color);
	}
	static void DrawTexture(Rect pos, std::uintptr_t pointer) {
		auto off = reinterpret_cast<void (*)(Rect, std::uintptr_t)>(*reinterpret_cast<uintptr_t*>(StaticClass()->GetMethodFromName("DrawTexture", 2, "image", 2)));
		return off(pos, pointer);
	}
	//static auto DrawTexture(Rect pos, std::uintptr_t pointer) -> void {
	//	METHOD(void(**)(Rect, std::uintptr_t), DrawTexture);
	//	return DrawTexture(pos, pointer);
	//}
	static auto skin() -> std::uintptr_t
	{
		METHOD(std::uintptr_t(**)(), get_skin);
		return get_skin();
	}
};