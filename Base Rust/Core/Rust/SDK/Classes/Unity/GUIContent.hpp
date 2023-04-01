class GUIContent
{
public:
	CLASS("UnityEngine", "GUIContent");

	static auto Temp(UString* text) -> GUIContent*
	{
		METHOD(GUIContent * (**)(UString*), Temp);
		return Temp(text);
	}
};