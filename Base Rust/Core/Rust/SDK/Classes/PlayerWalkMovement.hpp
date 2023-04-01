class PlayerWalkMovement : public BaseMovement
{
public:
	CLASS("", "PlayerWalkMovement");

	MEMBER(float, capsuleHeight);
	MEMBER(float, capsuleCenter);
	MEMBER(float, capsuleHeightDucked);
	MEMBER(float, capsuleCenterDucked);
	MEMBER(float, capsuleHeightCrawling);
	MEMBER(float, capsuleCenterCrawling);
	MEMBER(float, gravityMultiplier);
	MEMBER(float, gravityMultiplierSwimming);
	MEMBER(float, groundAngleNew);
	MEMBER(float, maxVelocity);

	MEMBER(float, jumpTime);

	MEMBER(bool, swimming);
	MEMBER(bool, grounded);
	MEMBER(bool, jumping);
	MEMBER(bool, climbing);
	MEMBER(void*, ladder);

	MEMBER(bool, sliding);
	MEMBER(bool, flying);

	MEMBER(RigidBody*, body);

	auto Jump(ModelState* state, bool s) -> void
	{
		if (!this) return;
		METHOD(void(**)(PlayerWalkMovement*, ModelState*, bool), Jump);
		return Jump(this, state, s);
	}
};