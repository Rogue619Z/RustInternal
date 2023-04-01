class Component
{
public:
	CLASS("UnityEngine", "Component");

	auto transform() -> Transform*
	{
		if (!this) return nullptr;
		METHOD(Transform* (**)(Component*), get_transform);
		return get_transform(this);
	}
	auto get_gameObject() -> GameObject*
	{
		if (!this) return nullptr;
		METHOD(GameObject * (**)(Component*), get_gameObject);
		return get_gameObject(this);
	}
	auto GetComponent(void* type) -> Component*
	{
		if (!this) return nullptr;
		METHOD(Component * (**)(Component*, void*), GetComponent);
		return GetComponent(this, type);
	}
};