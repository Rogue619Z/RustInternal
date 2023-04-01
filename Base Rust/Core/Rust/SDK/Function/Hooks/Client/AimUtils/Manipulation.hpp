float MagicBulletTimer = 0.0f;

void get_sphere_points_z(std::vector<Vector3>& re, float radius, unsigned int sectors = 25, unsigned int rings = 25) /* If you lag with manip, lower sectors and rings between 15 - 20 */
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	for (r = 0; r < rings; r++)
		for (s = 0; s < sectors; s++)
		{
			float y = sin(-(M_PI / 2) + M_PI * r * R);
			float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			x *= radius;
			y *= radius;
			z *= radius;

			re.push_back(Vector3(x, y, z));
		}
}


auto EyeManipulationAngle(BasePlayer* local, BasePlayer* target, std::uintptr_t input) -> void
{


	Vector3 re_p = LocalPlayer::Entity()->transform()->get_position() + LocalPlayer::Entity()->transform()->get_up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);

	Vector3 target_pos = target->get_bone_transform(47)->get_position();

	Vector3 choice = Vector3::Zero();

	if (IsVisible(re_p, target_pos)) {
		m_manipulate = Vector3::Zero();
		return;
	}

	float desyncTimeRaw = Mathf::Max(AntiHack::timeSinceLastTick() - Time::get_deltaTime(), 0.f);
	float desyncTimeClamped = Mathf::Min(desyncTimeRaw, 1.0f);

	float num = 1.5f;
	float eye_clientframes = 2.0f;
	float eye_serverframes = 2.0f;
	float num2 = eye_clientframes / 60.f;
	float num3 = eye_serverframes * Mathf::Max3(Time::get_deltaTime(), Time::get_smoothDeltaTime(), Time::get_fixedDeltaTime());
	float num4 = (desyncTimeClamped + num2 + num3) * num;
	float num5 = local->MaxEyeVelocity() + local->GetParentVelocity().magnitude();

	float max_eye_range = local->BoundsPadding() + num4 * num5; /* Max eye recreated from the game, makes manipulation as big as possible without invalids, not fully perfected yet */



	//float mm_max_eye = ((0.01f + ((desyncTime + 2.f / 60.f + 0.125f)	* LocalPlayer::Entity()->MaxEyeVelocity())));


	printf("mm_max_eye %f \n", max_eye_range);


	auto _right = LocalPlayer::Entity()->eyes()->MovementRight();
	auto forward = LocalPlayer::Entity()->eyes()->MovementForward();

	std::vector<Vector3> arr = {};


	get_sphere_points_z(arr, max_eye_range); /* Cylinder angles (Circle pretty much) */

	for (auto& s : arr) {
		Vector3 point = re_p + s;

		//DDraw::Sphere(point, 0.05f, Color(99, 23, 75, 100), 0.2f, true);

		if (!IsVisible(point, re_p))
			continue;

		if (!IsVisible(point, target_pos))
			continue;

		if (!AntiHack::ValidateEyePos(local, point))
			continue;

		if (!AntiHack::ValidateEyePos(local, re_p))
			continue;



		//DDraw::Sphere(point, 0.18f, 2.0f);

		choice = s;
		break;
	}
	if (choice.empty()) {
		m_manipulate = Vector3::Zero();
		return;
	}


	m_manipulate = choice;
}