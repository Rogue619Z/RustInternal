Vector3 cLastTickPos{};

void do_jump(PlayerWalkMovement* pwm,
	ModelState* state,
	float force = 10.f) {
	if (!pwm || !state) return;
	state->SetFlag(Enums::ModelStateFlags::on_ground);
	state->set_jumped(true);
	pwm->jumpTime() = Time::get_time();
	auto vel = pwm->body()->velocity();
	pwm->set_TargetMovement(Vector3(vel.x, force, vel.z));
}
auto Hooks::ClientMovement(PlayerWalkMovement* movement, std::uintptr_t a, ModelState* state) -> void
{
	if (!movement || !a || !state)
		return Hooks::ClientMovementhk.get_original< decltype(&ClientMovement)>()(movement, a, state);

	__try {

		Hooks::ClientMovementhk.get_original< decltype(&ClientMovement)>()(movement, a, state);

		if (!LocalPlayer::Entity()->HasFlag(Enums::Connected) || !LocalPlayer::Entity())
			return Hooks::ClientMovementhk.get_original< decltype(&ClientMovement)>()(movement, a, state);

		state->SetFlag(Enums::ModelStateFlags::sprinting); /* Needed for omnisprint to work, gives u more forgiveness */
		Vector3 vel = movement->get_TargetMovement();


		movement->groundAngleNew() = -1.0f;


		//if (Input::GetKeyDown(Enums::KeyCode::Space))
		//{
		//	do_jump(movement, state);
		//}
		//if (true)
		//{
		//	Vector3 curr = LocalPlayer::Entity()->transform()->get_position();
		//	Vector3 old = cLastTickPos;
		//	Vector3 v4 = (curr - cLastTickPos);
		//	Vector3 ov = Vector3(curr.x, curr.y, curr.z);

		//	if (flyhackDistanceVertical >= 2.5f)
		//		ov = Vector3(ov.x, curr.y < old.y ? (curr.y - 0.3f) : old.y, ov.z);
		//	if (flyhackDistanceHorizontal >= 6.f)
		//		ov = Vector3(old.x, ov.y, old.z);

		//	if (flyhackDistanceVertical >= 2.5f
		//		|| flyhackDistanceHorizontal >= 6.f) {
		//		if (ov != curr)
		//			movement->TeleportTo(ov, LocalPlayer::Entity());
		//		//dont_move = true;
		//	}
		//}

		/* If you want antiflyhack kick u can uncommented this, though it may not work. Havent tested in a while, and if it does work it may not be perfect horizontal wise */


		cLastTickPos = LocalPlayer::Entity()->transform()->get_position();
		AntiHack::ticks.AddPoint(cLastTickPos);
		AntiHack::ServerUpdate(Time::get_deltaTime(), LocalPlayer::Entity());


		if (!movement->flying()) /* Omni Sprint, wont omnisprint if ur using fakeadmin noclip or real admin noclip, dont delete check. */
		{
			float max_speed = (movement->swimming() || movement->ducking() > 0.5) ? 1.7f : 5.5f;

			if (vel.length() > 0.f) {
				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				movement->set_TargetMovement(target_vel);
			}
		}
	}
	__except (true)
	{
		printf("Movement Crash \n");
	}
}