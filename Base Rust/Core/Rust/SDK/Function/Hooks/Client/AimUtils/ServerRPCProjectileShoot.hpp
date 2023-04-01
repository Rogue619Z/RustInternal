static Vector3 SimulateProjectile(Vector3 position, Vector3 velocity, float partialTime, float travelTime, Vector3 gravity, float drag)
{
	float num = 0.03125f;
	Vector3 origin = position;
	if (partialTime >= 0)
	{
		float num2 = num - partialTime;
		if (travelTime < num2)
		{
			origin = position;
			position += velocity * travelTime;
			partialTime += travelTime;
			return origin;
		}
		origin = position;
		position += velocity * num2;
		velocity += gravity * num;
		velocity -= velocity * drag * num;
		travelTime -= num2;
	}

	int num3 = Mathf::FloorToInt(travelTime / num);

	for (int i = 0; i < num3; i++)
	{
		origin = position;
		position += velocity * num;
		velocity += gravity * num;
		velocity -= velocity * drag * num;
	}
	partialTime = travelTime - num * (float)num3;
	if (partialTime >= 0)
	{
		origin = position;
		position += velocity * partialTime;
	}
	return origin;
}
auto CustomHook::OnProjectileShootRpc(std::uint64_t instance) -> void
{
	if (!LocalPlayer::Entity())
		return;

	if (!target_ply)
		return;

	if (target_ply->IsDead())
		return;

	if (!target_ply->PlayerValid())
		return;

	if (!heldEntity)
		return;

	if (heldEntity->isReloading())
		return;




	Projectile* p;

	auto projectile_list = *reinterpret_cast<BaseProjectile**>(*reinterpret_cast<std::uintptr_t*>(heldEntity + 0x370) + 0x10);


	const auto shoot_list = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(instance + 0x18) + 0x10);
	const auto shoot_list_size = *reinterpret_cast<int*>(*reinterpret_cast<std::uintptr_t*>(instance + 0x18) + 0x18);

	//auto shoot_list_size = *reinterpret_cast<int*>(*reinterpret_cast<std::uintptr_t*>(instance + 0x18) + 0x18);
	auto visible = false;

	auto target_pos = target_ply->get_bone_transform(Enums::BoneList::spine4)->get_position();
	Vector3 aimbot_velocity = {};
	Vector3 rpc_position = {};
	Vector3 original_vel = {};
	bool manipulated = false;
	float travel_t = 0.0f;

	for (size_t i{ 0 }; i < shoot_list_size; i++) {
		std::uintptr_t projshoot = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);

		rpc_position = *reinterpret_cast<Vector3*>(projshoot + 0x18);
		original_vel = *reinterpret_cast<Vector3*>(projshoot + 0x24);



		if (Input::GetKey(Enums::KeyCode::X)) {
			auto rpcposv2 = rpc_position;
			if (m_manipulate != Vector3(0, 0, 0))
			{
				// rpc_position += misc::manipulate(esp::local_player, target.pos);
				rpc_position += (m_manipulate);
				visible = IsVisible(rpc_position, target_ply->get_bone_transform(Enums::head)->get_position());
				if (rpc_position != rpcposv2)
				{
					manipulated = true;

					if (visible) /* Needed for manipulator, dont remove! */
					{
						visible = true;
						*reinterpret_cast<Vector3*>(projshoot + 0x18) = rpc_position;
					}
				}
			}
		}
	}

	for (size_t i{ 0 }; i < projectile_list->list_size(); i++)
	{
		const auto baseProjectile = *(BaseProjectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
		p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);

		if (!baseProjectile)
			continue;

		Vector3 a;
		AimUtils::BulletPrediction(target_ply, rpc_position, target_pos, original_vel, aimbot_velocity, a, travel_t, p); /* Bullet Drop Prediction */
		break;
	}
	for (size_t i{ 0 }; i < shoot_list_size; i++) {
		const auto projectile = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);

		if (!projectile)
			continue;

		if (target_ply || manipulated) {
			*reinterpret_cast<Vector3*>(projectile + 0x24) = aimbot_velocity; //Don't worry about this, just don't remove
		}
	}
	for (size_t i{ 0 }; i < projectile_list->list_size(); i++)
	{

		const auto baseProjectile = *(BaseProjectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
		p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);

		if (!baseProjectile || !p)
			continue;

		p->currentVelocity() = aimbot_velocity;

		visible = IsVisible(rpc_position, target_ply->get_bone_transform(Enums::head)->get_position()); /* Only changes manip pos when the player is visible, do not remove */
		if (visible)
		{

			if (manipulated)
			{
				auto g = baseProjectile->get_gameObject();
				auto t = g->get_transform(); /* Changes manipulation pos */
				t->set_position(rpc_position);
			}
		}
	}
}


auto CustomHook::ProjectileShootRpc(void* _rcx, void* _rdx, void* a1, std::uint64_t instance, void* a3) -> void
{
	static auto o_func = reinterpret_cast<decltype(&CustomHook::ProjectileShootRpc)>(CustomHook::ProjectileShootRpchk);

	CustomHook::OnProjectileShootRpc(instance);

	return o_func(_rcx, _rdx, a1, instance, a3);
}