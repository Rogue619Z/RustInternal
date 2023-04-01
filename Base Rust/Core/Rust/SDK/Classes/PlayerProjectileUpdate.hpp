class PlayerProjectileUpdate
{
public:
	CLASS("", "PlayerProjectileUpdate");

	MEMBER(Vector3, curPosition);
	MEMBER(Vector3, curVelocity);
	MEMBER(int, projectileID);
	MEMBER(int, travelTime);
};