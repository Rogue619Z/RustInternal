class AttackEntity : public BaseEntity //not correct but may work???
{
public:
	CLASS("", "AttackEntity");

	MEMBER(float, nextAttackTime);
	MEMBER(float, repeatDelay);
	MEMBER(float, deployDelay);
	MEMBER(float, timeSinceDeploy);

	auto StartAttackCooldown(float test) -> void
	{
		if (!this) return;
		METHOD(void(**)(AttackEntity*, float), StartAttackCooldown);
		return StartAttackCooldown(this, test);
	}

	auto HasAttackCooldown() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(AttackEntity*), HasAttackCooldown);
		return HasAttackCooldown(this);
	}
};