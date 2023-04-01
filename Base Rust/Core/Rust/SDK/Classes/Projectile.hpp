class ItemModProjectile
{
public:
	CLASS("", "ItemModProjectile");

	MEMBER(float, projectileVelocity);
	MEMBER(float, projectileSpread);
	MEMBER(float, projectileVelocitySpread);

	auto GetSpreadScalar() -> float
	{
		METHOD(float(**)(ItemModProjectile*), GetSpreadScalar);
		return GetSpreadScalar(this);
	}
	auto GetRandomVelocity() -> float
	{
		METHOD(float(**)(ItemModProjectile*), GetRandomVelocity);
		return GetRandomVelocity(this);
	}
	auto GetIndexedSpreadScalar(int shotIndex, int maxShots) -> float
	{
		METHOD(float(**)(ItemModProjectile*, int, int), GetIndexedSpreadScalar);
		return GetIndexedSpreadScalar(this, shotIndex, maxShots);
	}
};

class Projectile : public Component
{
public:
	CLASS("", "Projectile");

	MEMBER(float, thickness);
	MEMBER(Vector3, currentPosition);
	MEMBER(Vector3, currentVelocity);
	MEMBER(Vector3, initialVelocity);
	MEMBER(Vector3, previousPosition);
	MEMBER(Vector3, sentPosition);
	MEMBER(Vector3, previousVelocity);
	MEMBER(HitTest*, hitTest);
	MEMBER(float, traveledTime);
	MEMBER(float, traveledDistance);
	MEMBER(float, gravityModifier);
	MEMBER(float, drag);
	MEMBER(float, closeFlybyDistance);
	MEMBER(float, maxDistance);
	MEMBER(bool, createDecals);
	MEMBER(Vector3, tumbleAxis);
	MEMBER(float, previousTraveledTime);
	MEMBER(float, launchTime);
	MEMBER(int, projectileID);
	MEMBER(ItemModProjectile*, mod);
	MEMBER(float, initialDistance);
	//MEMBER(ItemModProjectile*, mod);
	MEMBER(float, integrity);

	auto isAuthoritative() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(Projectile*), get_isAuthoritative);
		return get_isAuthoritative(this);
	}
	auto SetEffectScale(float eScale) -> void
	{
		if (!this) return;
		METHOD(void(**)(Projectile*, float), SetEffectScale);
		return SetEffectScale(this, eScale);
	}
	auto DoHit(HitTest* test, Vector3 point, Vector3 normal) -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(Projectile*, HitTest*, Vector3, Vector3), DoHit);
		return DoHit(this, test, point, normal);
	}
	auto isAlive() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(Projectile*), get_isAlive);
		return get_isAlive(this);
	}
	bool IsAlive() {
		return (this->integrity() > 0.001f && this->traveledDistance() < this->maxDistance() && this->traveledTime() < 8);
	}
};