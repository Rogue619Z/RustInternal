ExplosionsFPS* instances = 0;
static GameObject* GameObj = nullptr;

bool wakeup = true;
Shader* shader = 0;
static bool has_initialized{ false };

static void LoadInput(BasePlayer* player, std::uintptr_t state)
{
	if (!has_initialized)
	{
		static auto initialize_method = utl::pattern::find(L"GameAssembly.dll", "48 83 EC 48 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ?");
		static auto il2cpp_codegen_initialize_method = reinterpret_cast<void (*)(unsigned int)>(initialize_method);

		for (size_t idx{ 0 }; idx < 56229; idx++)
		{
			il2cpp_codegen_initialize_method(idx);
		}

		static auto projectile_shoot_sig = utl::pattern::find(L"GameAssembly.dll", "4C 8B 0D ? ? ? ? 48 8B 75 30");
		const auto relative_projectile_shoot = *reinterpret_cast<std::uintptr_t*>(projectile_shoot_sig + *reinterpret_cast<std::int32_t*>(projectile_shoot_sig + 3) + 7);

		if (relative_projectile_shoot)
		{
			const auto projectile_shoot_rpc = **reinterpret_cast<std::uintptr_t***>(relative_projectile_shoot + 0x30);
			HOOK_CUSTOM(projectile_shoot_rpc, CustomHook::ProjectileShootRpchk, &CustomHook::ProjectileShootRpc);
		}
		has_initialized = true;
	}

	static auto visiblePlayerList = BasePlayer::playerList();

	if (!visiblePlayerList || visiblePlayerList->vals->size == 0 || !cam || !LocalPlayer::Entity())
	{
		heldEntity = nullptr;
		target_ply = nullptr; /* Important caching right here, DO NOT DELETE! OR CRASHES MUCH MUCH MORE!!!! */
		cam = Camera::main();
	}


	/* Run ur zoom code here if u have*/

	if (const auto visiblePlayerList = BasePlayer::playerList())
	{
		if (visiblePlayerList || visiblePlayerList->vals->size != 0) {


			for (size_t i = 0; i < visiblePlayerList->vals->size; i++)
			{
				const auto& player = visiblePlayerList->vals->get<BasePlayer*>(i);
				if (!player || player == LocalPlayer::Entity())
					continue;



				if (true)
				{
					auto playerModel = player->playerModel();
					if (!playerModel)
						continue;

					auto multiMesh = playerModel->_multiMesh();
					if (!multiMesh)
						continue;

					auto Renderers = multiMesh->Renderers();
					if (!Renderers)
						continue;

					for (auto idx{ 0 }; idx < Renderers->size(); idx++)
					{
						auto Renderer = Renderers->value(idx);
						if (!Renderer)
							continue;

						auto Material = Renderer->material();
						if (!Material)
							continue;



						if (shader != Material->get_shader())
						{
							Material->set_shader((Shader*)shader);
						}
						if (!shader)
							shader = Material->get_shader()->Find(UString(L"Hidden/Internal-Colored"));

						Material->SetInt2(UString(L"_ZTest"), 8);
						Material->SetColor(UString(L"_Color"), Color(70, 52, 235, 255));

					}
				}
			}
		}
	}
	if (const auto item = LocalPlayer::Entity()->item())
	{
		heldEntity = item->heldEntity();
		if (heldEntity) {

			/* Could cause crashes here, i'd recommend to fix it. I may do in future for u */

			if (Input::GetKey(Enums::KeyCode::X)) {
				float time = Time::get_deltaTime();
				MagicBulletTimer += time;

				uint64_t State = (uint64_t)state;
				if (!State)
					return;

				uint64_t Current = *reinterpret_cast<uint64_t*>(State + 0x10);
				uint64_t Previous = *reinterpret_cast<uint64_t*>(State + 0x18);

				if (MagicBulletTimer >= 1.f)
				{
					player->clientTickInterval() = 0.05f;
					MagicBulletTimer = 0;
				}
				else
				{
					if (Previous && Current)
						*reinterpret_cast<int*>(Previous + 0x14) = *reinterpret_cast<int*>(Current + 0x14);//0;

					player->clientTickInterval() = 99999.f;
				}

			}
			else {
				player->clientTickInterval() = 0.05f;
				MagicBulletTimer = 0;
			}

			if (target_ply && target_ply->PlayerValid() && target_ply->IsAlive())
			{
				if (Input::GetKey(Enums::KeyCode::X)) {
					EyeManipulationAngle(player, target_ply, state);
				}
				else if (!m_manipulate.empty()) {
					m_manipulate = Vector3(0, 0, 0);
				}
				if (Input::GetKey(Enums::KeyCode::X)) {
					if (IsVisible(target_ply->get_bone_transform(48)->get_position(), LocalPlayer::Entity()->eyes()->get_position() + m_manipulate)) { /* AutoShoot binded to key X */
						if (heldEntity->primaryMagazine()->contents() != 0 && !heldEntity->isReloading()) {
							float NextShot = fixed_time_last_shot + heldEntity->repeatDelay();

							if (Time::get_fixedTime() > NextShot && heldEntity->timeSinceDeploy() > heldEntity->deployDelay()) {
								if (!heldEntity->HasAttackCooldown()) {
									heldEntity->LaunchProjectile();
									heldEntity->primaryMagazine()->contents()--;
									heldEntity->UpdateAmmoDisplay();
									heldEntity->ShotFired();
									heldEntity->DidAttackClientside();
									heldEntity->BeginCycle();
								}
								//	player->SendClientTick();
							}
						}
					}
				}
				AimUtils::MovementPrediction();/* Movement Prediction yay */
				//	AimUtils::MovementPrediction();
			}
		}
	}
}

auto Hooks::ClientInput(BasePlayer* player, std::uintptr_t state) -> void
{
	if (!player || !state)
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(player, state);

	__try {
		LoadInput(player, state);
		//unity::matrix = unity::viewMatrix();



		DDraw::Get();

	}
	__except (true)
	{
		printf("Client Input Crash \n");
	}
	Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(player, state);


}