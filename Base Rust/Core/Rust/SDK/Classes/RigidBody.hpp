class RigidBody
{
public:
	CLASS("UnityEngine", "Rigidbody");

	auto velocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(RigidBody*), get_velocity);
		return get_velocity(this);
	}
	auto set_velocity(Vector3 value) -> void
	{
		if (!this) return;
		METHOD(void(**)(RigidBody*, Vector3), set_velocity);
		return set_velocity(this, value);
	}
};