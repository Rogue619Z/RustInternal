class HitTest
{
public:
	CLASS("", "HitTest");

	MEMBER(float, Radius);
	MEMBER(float, Forgiveness);
	MEMBER(float, MaxDistance);
	MEMBER(bool, DidHit);
	MEMBER(Vector3, HitPoint);
	MEMBER(Vector3, HitNormal);
	MEMBER(BaseNetworkable*, HitEntity);
	MEMBER(float, HitDistance);
	MEMBER(Ray, AttackRay);
	MEMBER(Transform*, HitTransform);
	MEMBER(UString*, HitMaterial);

	auto HitPointWorld() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(HitTest*), HitPointWorld);
		return HitPointWorld(this);
	}
	auto HitNormalWorld() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(HitTest*), HitNormalWorld);
		return HitNormalWorld(this);
	}
};