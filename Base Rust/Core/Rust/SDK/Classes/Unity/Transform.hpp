class Transform
{
public:
	CLASS("UnityEngine", "Transform");


	auto get_position() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**) (Transform*), get_position);
		return get_position(this);
	}
	auto get_up() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**) (Transform*), get_up);
		return get_up(this);
	}
	auto get_rotation() -> Vector4
	{
		if (!this) return Vector4::Zero();
		METHOD(Vector4(**) (Transform*), get_rotation);
		return get_rotation(this);
	}
	auto get_rotation(Vector4 value) -> void
	{
		if (!this) return;
		METHOD(void(**) (Transform*, Vector4), set_rotation);
		return set_rotation(this, value);
	}
	auto set_up(Vector3 value) -> void
	{
		if (!this) return;
		METHOD(void(**) (Transform*, Vector3), set_up);
		return set_up(this, value);
	}
	auto get_localToWorldMatrix() -> Matrix
	{
		if (!this) return Matrix();
		METHOD(Matrix(**) (Transform*), get_localToWorldMatrix);
		return get_localToWorldMatrix(this);
	}
	auto GetParent() -> Transform*
	{
		if (!this) return nullptr;
		METHOD(Transform*(**) (Transform*), GetParent);
		return GetParent(this);
	}
	auto get_forward() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**) (Transform*), get_forward);
		return get_forward(this);
	}
	auto InverseTransformDirection(Vector3 direction) -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**) (Transform*, Vector3), InverseTransformDirection);
		return InverseTransformDirection(this, direction);
	}
	auto TransformDirection(Vector3 direction) -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**) (Transform*, Vector3), TransformDirection);
		return TransformDirection(this, direction);
	}
	auto InverseTransformPoint(Vector3 direction) -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**) (Transform*, Vector3), InverseTransformPoint);
		return InverseTransformPoint(this, direction);
	}
	auto set_forward(Vector3 value) -> void
	{
		if (!this) return;
		METHOD(void(**) (Transform*, Vector3), set_forward);
		return set_forward(this, value);
	}

	auto set_position(Vector3 value) -> void
	{
		if (!this) return;
		METHOD(void(**) (Transform*, Vector3), set_position);
		return set_position(this, value);
	}
	auto set_localPosition(Vector3 value) -> void
	{
		if (!this) return;
		METHOD(void(**) (Transform*, Vector3), set_localPosition);
		return set_localPosition(this, value);
	}
};