class RecoilProperties
{
public:
	CLASS("", "RecoilProperties");

	MEMBER(RecoilProperties*, newRecoilOverride);
	MEMBER(float, recoilYawMin);
	MEMBER(float, recoilYawMax);
	MEMBER(float, recoilPitchMin);
	MEMBER(float, recoilPitchMax);

	MEMBER(float, aimconeCurveScale);
};



class BaseProjectile : public AttackEntity
{
public:
	CLASS("", "BaseProjectile");

	MEMBER(float, NoiseRadius);
	MEMBER(float, projectileVelocityScale);
	MEMBER(float, automatic);
	MEMBER(float, reloadTime);
	MEMBER(float, aimSway);
	MEMBER(float, aimSwaySpeed);
	MEMBER(bool, isReloading);
	MEMBER(float, nextReloadTime);
	MEMBER(float, lastShotTime);
	MEMBER(float, aimCone);
	MEMBER(float, hipAimCone);
	MEMBER(float, aimConePenaltyMax);
	MEMBER(float, aimconePenaltyRecoverDelay);
	MEMBER(float, aimconePenaltyPerShot);
	MEMBER(float, sightAimConeScale);
	MEMBER(float, hipAimConeScale);
	MEMBER(float, sightAimConeOffset);
	MEMBER(int, currentBurst);
	MEMBER(float, stancePenaltyScale);
	MEMBER(RecoilProperties*, recoil);
	MEMBER(float, aimconePenaltyRecoverTime);
	MEMBER(Transform*, MuzzlePoint);
	MEMBER(Magazine*, primaryMagazine);

	auto list_size() -> std::uint32_t { return *reinterpret_cast<std::uint32_t*>(this + 0x18); }

	auto DoReload() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), DoReload);
		return DoReload(this);
	}

	auto DoAttack() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), DoAttack);
		return DoAttack(this);
	}

	auto BeginCycle() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), BeginCycle);
		return BeginCycle(this);
	}

	auto LaunchProjectile() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), LaunchProjectile);
		return LaunchProjectile(this);
	}
	auto GetProjectileVelocityScale(bool getMax = false) -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseProjectile*, bool), GetProjectileVelocityScale);
		return GetProjectileVelocityScale(this, getMax);
	}
	auto UpdateAmmoDisplay() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), UpdateAmmoDisplay);
		return UpdateAmmoDisplay(this);
	}

	auto ShotFired() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), ShotFired);
		return ShotFired(this);
	}

	auto DidAttackClientside() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), DidAttackClientside);
		return DidAttackClientside(this);
	}
	void RemoveRecoil() {
		auto Recoil = this->recoil();//*reinterpret_cast<uintptr_t*>((uintptr_t)this + recoil);

		float recoilx = 0.0f;
		float recoily = 0.0f;

		//after update June 5th 2022
		auto NewRecoil = Recoil->newRecoilOverride();

		if (NewRecoil)
		{
			NewRecoil->recoilYawMin() = recoily; //yaw min
			NewRecoil->recoilYawMax() = recoily; //yaw max
			NewRecoil->recoilPitchMin() = -recoilx; //pitch min
			NewRecoil->recoilPitchMax() = -recoilx; //pitch max
		}
		else
		{
			Recoil->recoilYawMin() = recoily; //yaw min
			Recoil->recoilYawMax() = recoily; //yaw max
			Recoil->recoilPitchMin() = -recoilx; //pitch min
			Recoil->recoilPitchMax() = -recoilx; //pitch max
		}
	}
	void RemoveSpread(float scale = 0.f) {
		auto Recoil = this->recoil();
		auto NewRecoil = Recoil->newRecoilOverride();
		this->aimCone() = -3.f;
		this->hipAimCone() = -3.f;
		this->aimconePenaltyPerShot() = -3.f;
		//this->stancePenaltyScale() = -3.f;
		//this->sightAimConeScale() = -3.f;
		//printf("%f aimCone \n", this->aimCone());
		//printf("%f hipAimCone\n", this->hipAimCone());
		//printf("%f aimConePenaltyMax\n", this->aimConePenaltyMax());
		//printf("%f aimconePenaltyPerShot\n", this->aimconePenaltyPerShot());
		//printf("%f stancePenaltyScale\n", this->stancePenaltyScale());
		//printf("%f hipAimConeScale\n", this->hipAimConeScale());
		//printf("%f sightAimConeScale\n", this->hipAimConeScale());

		//if (NewRecoil)
		//{
		//	NewRecoil->aimconeCurveScale() = -1.0f; //aimconeCurveScale
		//}
		//else
		//{
		//	Recoil->aimconeCurveScale() = -1.0f; //aimconeCurveScale
		//}
		//printf("%f new aimconeCurveScale\n", NewRecoil->aimconeCurveScale());

		//printf("%f old aimconeCurveScale\n", Recoil->aimconeCurveScale());

	}
};
BaseProjectile* heldEntity = nullptr;