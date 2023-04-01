
#define rgba(r,g,b,a) Color(r / 255.f, g / 255.f, b / 255.f, a)

namespace Renderer
{
	static int active_tab = 0;
	static Vector2 tab_size;

	static auto get_target(BasePlayer* player) -> float
	{
		if (!player)
			return 1000.0f;

		Vector2 ScreenPos;
		if (!cam->WorldToScreen(player->transform()->get_position(), ScreenPos)) return 1000.0f;
		return Vector2(Screen::width() / 2, Screen::height() / 2).distance_2d(ScreenPos);
	}

	GUIStyle* style = nullptr;

	inline std::uintptr_t  skins, white_texture;

	static auto init() -> bool
	{
		if (!skins) {
			skins = GUI::skin();
		}
		if (!style)
			style = *reinterpret_cast<GUIStyle**>(skins + 0x38);

		if (!white_texture) {
			white_texture = Texture2D::get_whiteTexture();
		}

		if (!skins)
			return false;

		if (!style)
			return false;

		if (!white_texture)
			return false;



		return true;
	}
	//auto init() -> void
	//{
	//	if (style && skins && white_texture)
	//		return;

	//	skins = GUI::skin();
	//	style = *reinterpret_cast<GUIStyle**>(skins + 0x38);
	//	white_texture = Texture2D::get_whiteTexture();

	//	style->set_alignment(Enums::TextAnchor::UpperLeft);
	//	GUI::set_color({ 255, 255, 255, 255 });


	//}
	static void HorizontalLine(Vector2 pos, float size, Color clr)
	{
		GUI::set_color(clr);

		GUI::DrawTexture(Rect(pos.x, pos.y, size, 1), white_texture);
	}

	static void VerticalLine(Vector2 pos, float size, Color clr)
	{
		GUI::set_color(clr);

		GUI::DrawTexture(Rect(pos.x, pos.y, 1, size), white_texture);
	}

	static void FillBox(Rect pos, Color clr)
	{
		GUI::set_color(clr);
		GUI::DrawTexture(pos, white_texture);
	}
	static void OutlineBox(Vector2 pos, Vector2 size, Color clr)
	{
		GUI::set_color(clr);

		GUI::DrawTexture(Rect(pos.x, pos.y, 1, size.y), white_texture);
		GUI::DrawTexture(Rect(pos.x + size.x, pos.y, 1, size.y), white_texture);
		GUI::DrawTexture(Rect(pos.x, pos.y, size.x, 1), white_texture);
		GUI::DrawTexture(Rect(pos.x, pos.y + size.y, size.x, 1), white_texture);
	}

	static auto draw_filled_rect(Rect pos, Color clr) -> void
	{
		GUI::set_color(clr);
		GUI::DrawTexture(pos, white_texture);
	}

	static auto DrawMenuLabel(Rect pos, UString* text, Color clr, bool centered = true, float size = 10) -> void {
		GUI::set_color(clr);

		GUIContent* content = GUIContent::Temp(text);

		style->set_fontSize(size);

		if (centered)
			style->set_alignment(Enums::TextAnchor::MiddleCenter);
		else
			style->set_alignment(Enums::TextAnchor::UpperLeft);

		GUI::Label(pos, content, style);
	}
	static void Label(Rect position, UString* text, Color color = Color(1, 1, 1, 1))
	{
		GUIContent* content = GUIContent::Temp(text);
		style->set_alignment(Enums::TextAnchor::UpperLeft);
		position.x -= style->CalcSize(content).x / 2.0f;

		style->set_fontSize(10.0f);

		if (true)
		{
			GUI::set_color({ 0, 0, 0, (color.a * 255) });
			GUI::Label({ position.x, position.y + 1, position.w, position.h }, content, style);
			GUI::Label({ position.x, position.y - 1, position.w, position.h }, content, style);
			GUI::Label({ position.x - 1, position.y, position.w, position.h }, content, style);
			GUI::Label({ position.x + 1, position.y, position.w, position.h }, content, style);
		}
		GUI::set_color(color);
		GUI::Label(position, content, style);
	}
	static void String(Vector2 position, UString* text, Color color = Color(1, 1, 1, 1))
	{
		Label(Rect(position.x, position.y, 300.0f, 25.0f), text, color);
	}
	static void StringRect(Rect position, UString* text, Color color = Color(1, 1, 1, 1))
	{
		Label(Rect(position.x, position.y, position.x, position.y), text, color);
	}
	//static void Line(Vector2 start, Vector2 end, Color clr, float thickness = 1.f, bool outline = false)
	//{
	//	//GUI::set_color({ 0, 0, 0, (clr.a * 255) });

	//	//GL::PushMatrix();
	//	//GL::Begin(1);

	//	//GL::Vertex(Vector3(start.x - thickness, start.y, 0));
	//	//GL::Vertex(Vector3(end.x + thickness, end.y, 0));
	//	//GUI::set_color({ 0, 0, 0, (clr.a * 255) });
	//	//GL::Vertex(Vector3(start.x, start.y, 0));
	//	//GL::Vertex(Vector3(end.x, end.y, 0));

	//	////printf("Skeletonen \n");

	//	//GL::End();
	//	//GL::PopMatrix();
	//	return;
	//}
	//static auto tab_vert(Enums::EventType event, Vector2 pos, Vector2 mouse, const wchar_t* tab_name, int id) -> void {
	//	if (event == Enums::EventType::MouseDown) {
	//		if (Rect(pos.x + id * tab_size.x + 2.0f, pos.y - 4, tab_size.x, tab_size.y).Contains(mouse)) {
	//			active_tab = id;
	//		}
	//	}
	//	else if (event == Enums::EventType::Repaint) {
	//		if (active_tab == id) {
	//			draw_filled_rect(Rect(tab_size.x + 640, pos.y + 8, 2, tab_size.y - 16), Color(50, 61, 112, 255));
	//			DrawMenuLabel(Rect{ pos.x + id * tab_size.x + 2.0f + 1, pos.y + 1, tab_size.x, tab_size.y }, tab_name, Color(0, 0, 0, 120), true, 12);
	//			DrawMenuLabel(Rect{ pos.x + id * tab_size.x + 2.0f, pos.y, tab_size.x, tab_size.y }, tab_name, Color(50, 61, 112, 255), true, 12);
	//		}
	//		else {
	//			DrawMenuLabel(Rect{ pos.x + id * tab_size.x + 2.0f + 1, pos.y + 1, tab_size.x, tab_size.y }, tab_name, Color(0, 0, 0, 120), true, 12);
	//			DrawMenuLabel(Rect{ pos.x + id * tab_size.x + 2.0f, pos.y, tab_size.x, tab_size.y }, tab_name, Color(255, 255, 255, 255), true, 12);
	//		}
	//	}
	//}
}