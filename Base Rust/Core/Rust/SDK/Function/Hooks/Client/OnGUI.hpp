#include <format>

struct box_t
{
	Vector2 pos;
	Vector2 size;
};
struct bounds_t {
	float left, right, top, bottom;
};


void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	if (s == 0.0f)
	{
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = my_fmod(h, 1.0f) / (60.0f / 360.0f);
	int   i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i)
	{
	case 0: out_r = v; out_g = t; out_b = p; break;
	case 1: out_r = q; out_g = v; out_b = p; break;
	case 2: out_r = p; out_g = v; out_b = t; break;
	case 3: out_r = p; out_g = q; out_b = v; break;
	case 4: out_r = t; out_g = p; out_b = v; break;
	case 5: default: out_r = v; out_g = p; out_b = q; break;
	}
}
struct bone_t {
	Vector3 screen;
	int8_t     index;
	bool       on_screen;
	Vector3 world_position;
	bool visible;
};
std::array<bone_t, 20> bones = {

	bone_t{ Vector3{}, 2, false, Vector3{}, false },  // l_hip
	bone_t{ Vector3{}, 3, false, Vector3{}, false },  // l_knee
	bone_t{ Vector3{}, 6, false, Vector3{}, false },  // l_ankle_scale
	bone_t{ Vector3{}, 5, false, Vector3{}, false },  // l_toe
	bone_t{ Vector3{}, 24, false, Vector3{}, false }, // l_upperarm
	bone_t{ Vector3{}, 25, false, Vector3{}, false }, // l_forearm
	bone_t{ Vector3{}, 26, false, Vector3{}, false }, // l_hand
	bone_t{ Vector3{}, 27, false, Vector3{}, false }, // l_index1

	bone_t{ Vector3{}, 48, false, Vector3{}, false }, // jaw
	bone_t{ Vector3{}, 18, false, Vector3{}, false }, // spine1
	bone_t{ Vector3{}, 21, false, Vector3{}, false }, // spine3
	bone_t{ Vector3{}, 1, false, Vector3{}, false },  // pelvis
	bone_t{ Vector3{}, 23, false, Vector3{}, false }, // l_clavicle

	bone_t{ Vector3{}, 17, false, Vector3{}, false }, // r_ankle_scale
	bone_t{ Vector3{}, 15, false, Vector3{}, false }, // r_foot
	bone_t{ Vector3{}, 14, false, Vector3{}, false }, // r_knee
	bone_t{ Vector3{}, 55, false, Vector3{}, false }, // r_upperarm
	bone_t{ Vector3{}, 56, false, Vector3{}, false }, // r_forearm
	bone_t{ Vector3{}, 57, false, Vector3{}, false }, // r_hand
	bone_t{ Vector3{}, 76, false, Vector3{}, false }  // r_ulna
};
Color HSV(float h, float s, float v, float a = 1.0f) { float r, g, b; ColorConvertHSVtoRGB(h, s, v, r, g, b); return Color(r, g, b, a); }

static auto LoadESP(std::uintptr_t draw) -> void
{
	static auto current = Event::current();
	const auto event_type = current->type();



	//auto mousePos = Input::get_mousePosition();
	//auto height = Screen::height();
	//auto width = Screen::width();


	//if (true) {
	//	Cursor::set_visible(true);
	//	Cursor::set_lockState(Enums::CursorLockMode::None);

	//	auto aimbot_tab = 0, weapon_tab = 1, visual_tab = 2, misc_tab = 3, settings_tab = 4;
	//	Renderer::tab_size = Vector2(100, 35);

	//	Vector2 pos, menu_pos = { 650, 200 }, menu_size = { 600, 400 }, button_size = { 200, 0 }, mouse_pos = { mousePos.x, height - mousePos.y };

	//	if (event_type == Enums::EventType::MouseDrag) {
	//		if (Rect(menu_pos.x, menu_pos.y, menu_size.x, menu_size.y).Contains(mouse_pos)) {
	//			menu_pos = { menu_pos.x + mouse_pos.x, menu_pos.y + mouse_pos.y };
	//			menu_size = { menu_size.x - mouse_pos.x, menu_size.y - mouse_pos.y };
	//		}
	//	}

	//	Renderer::draw_filled_rect(Rect(menu_pos.x, menu_pos.y, menu_size.x, menu_size.y), Color(28, 28, 28, 255));
	//	menu_pos.y += 10;

	//	Renderer::tab_vert(event_type, menu_pos, mouse_pos, (L"Aimbot"), aimbot_tab);
	//	menu_pos.y += 50; menu_pos.x -= 100.f;
	//	Renderer::tab_vert(event_type, menu_pos, mouse_pos, (L"Weapon"), weapon_tab);
	//	menu_pos.y += 50; menu_pos.x -= 100.f;
	//	Renderer::tab_vert(event_type, menu_pos, mouse_pos, (L"Visuals"), visual_tab);
	//	menu_pos.y += 50; menu_pos.x -= 100.f;
	//	Renderer::tab_vert(event_type, menu_pos, mouse_pos, (L"Misc"), misc_tab);
	//	menu_pos.y += 195; menu_pos.x -= 100.f;
	//	Renderer::tab_vert(event_type, menu_pos, mouse_pos, (L"Settings"), settings_tab);


	//}

	/* This is the menu that i was working on, it works but no checkboxes, sliders, keybinds yet for it, it's not finished at all */

	if (event_type == Enums::EventType::Repaint)
	{
		bounds_t bounds;


		if (inithooks)
		{

			if (!Renderer::init())
				return;

			if (!cam)
				return;


			if (const auto visiblePlayerList = BasePlayer::playerList())
			{
				if (!visiblePlayerList || visiblePlayerList->vals->size < 0)
					return;


				if (target_ply != nullptr) {
					if (target_ply->IsDead() || !target_ply->PlayerValid() || Renderer::get_target(target_ply) > 500.0f) { /* Target Player Null Checks [Needed for aimbot and more otherwise u could crash if target player is not exisiting ]*/
						target_ply = nullptr;
					}
				}

				for (size_t i = 0; i < visiblePlayerList->vals->size; i++)
				{

					const auto& player = visiblePlayerList->vals->get<BasePlayer*>(i);

					if (!player || player == LocalPlayer::Entity())
					{

						continue;
					}

					if (player->IsDead())
					{
						continue;
					}
					if (!player->PlayerValid())
					{
						continue;
					}
					if (player->HasFlag(Enums::Sleeping))
					{

						continue;
					}
					static const auto get_bounds = [&](bounds_t& out, float expand = 0) -> bool {
						bounds = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

						for (auto& [bone_screen, bone_idx, on_screen, world_position, visible] : bones) {

							auto Transform = player->get_bone_transform(bone_idx);

							world_position = Transform->get_position();

							if (bone_idx == 48) // lol
								world_position.y += 0.2f;

							bone_screen = cam->ScreenTransform(world_position);
							if (bone_screen.x < bounds.left)
								bounds.left = bone_screen.x;
							if (bone_screen.x > bounds.right)
								bounds.right = bone_screen.x;
							if (bone_screen.y < bounds.top)
								bounds.top = bone_screen.y;
							if (bone_screen.y > bounds.bottom)
								bounds.bottom = bone_screen.y;
							on_screen = true;
						}

						if (bounds.left == FLT_MAX)
							return false;
						if (bounds.right == FLT_MIN)
							return false;
						if (bounds.top == FLT_MAX)
							return false;
						if (bounds.bottom == FLT_MIN)
							return false;

						bounds.left -= expand;
						bounds.right += expand;
						bounds.top -= expand;
						bounds.bottom += expand;

						out = bounds;

						return true;
					};


					Color col = Color{ 255, 0, 0, 255 };

					if (get_bounds(bounds, 4)) {
						float box_width = bounds.right - bounds.left;
						float box_height = bounds.bottom - bounds.top;


						Vector2 base_pos = Vector2::Zero();
						auto base_poss = cam->WorldToScreen(player->transform()->get_position(), base_pos);
						if (!base_pos.empty()) {
							if (IsVisible(LocalPlayer::Entity()->get_bone_transform(48)->get_position(), player->get_bone_transform(48)->get_position()))
								col = Color{ 0, 255, 0, 255 };

							/* Turns esp color green when visible, esp color red when not*/


							//if (true) {
							//	//corner box
							//	auto wid = box_width / 4;
							//	Renderer::HorizontalLine(Vector2{ bounds.left, bounds.top }, wid, col); //tl
							//	Renderer::HorizontalLine(Vector2{ bounds.right, bounds.top }, -(wid), col); //tr
							//	Renderer::HorizontalLine(Vector2{ bounds.left, bounds.top + 1 }, wid, col);
							//	Renderer::HorizontalLine(Vector2{ bounds.right, bounds.top + 1 }, -(wid), col);

							//	Renderer::HorizontalLine(Vector2{ bounds.left, bounds.bottom }, wid, col);
							//	Renderer::HorizontalLine(Vector2{ bounds.right + 1.f, bounds.bottom }, -(wid), col);
							//	Renderer::HorizontalLine(Vector2{ bounds.left, bounds.bottom + 1 }, wid, col);
							//	Renderer::HorizontalLine(Vector2{ bounds.right + 1.f, bounds.bottom + 1 }, -(wid), col);

							//	Renderer::VerticalLine(Vector2{ bounds.left, bounds.top }, wid, col);
							//	Renderer::VerticalLine(Vector2{ bounds.right, bounds.top }, wid, col);
							//	Renderer::VerticalLine(Vector2{ bounds.left + 1, bounds.top }, wid, col);
							//	Renderer::VerticalLine(Vector2{ bounds.right + 1, bounds.top }, wid, col);

							//	Renderer::VerticalLine(Vector2{ bounds.left, bounds.bottom }, -(wid), col);
							//	Renderer::VerticalLine(Vector2{ bounds.right, bounds.bottom }, -(wid), col);
							//	Renderer::VerticalLine(Vector2{ bounds.left + 1, bounds.bottom }, -(wid), col);
							//	Renderer::VerticalLine(Vector2{ bounds.right + 1, bounds.bottom }, -(wid), col);
							//	//corner box
							//}

							/* You can uncomment box esp if u want, though it is quite laggy :( */

							float y = 0.0f;


							Renderer::String(Vector2((bounds.left + bounds.right) / 2, bounds.top - 14.0f), player->_displayName(), col); /* Nigga Name ESP */

							Renderer::String(Vector2((bounds.left + bounds.right) / 2, bounds.bottom + 2.0f), UString::New(std::format("{:.0f} HP", player->_health()).c_str()), col); /* Health ESP, quite obvious :skull: */

							/* Yay actual good looking esp!!!! */

							y += 14.0f;
							Renderer::String(Vector2((bounds.left + bounds.right) / 2, bounds.bottom + y), UString::New(std::format("{:.0f} M", LocalPlayer::Entity()->transform()->get_position().distance(player->transform()->get_position())).c_str()), col); /* Distance ESP */

							//const Vector2 screen_center = Vector2(Screen::height() / 2, Screen::width() / 2);

						}

					}

					if (Renderer::get_target(player) < 500.0f) {
						if (target_ply == nullptr)
							target_ply = player;
						else if (Renderer::get_target(target_ply) > Renderer::get_target(player)) /* Target Player [Needed for aimbot and more ]*/
							target_ply = player;

					}
				}
			}
		}
	}
}

auto Hooks::OnGUI(std::uintptr_t draw) -> void
{
	__try {
		LoadESP(draw);
	}
	__except (true)
	{
		printf("ESP Crash \n");
	}
	
}