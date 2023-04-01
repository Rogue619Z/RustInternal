class Object
{
public:
	CLASS("UnityEngine", "Object");

	static auto DontDestroyOnLoad(GameObject* object) -> void
	{
		METHOD(void(**)(GameObject*), DontDestroyOnLoad);
		return DontDestroyOnLoad(object);
	}
};

class GameObject
{
public:
	CLASS("UnityEngine", "GameObject");

	auto get_transform() -> Transform*
	{
		if (!this) return nullptr;
		METHOD(Transform * (**)(GameObject*), get_transform);
		return get_transform(this);
	}
	static auto Internal_CreateGameObject(GameObject* self, UString name) -> void
	{
		METHOD(void(**)(GameObject*, UString), Internal_CreateGameObject);
		return Internal_CreateGameObject(self, name);
	}
	auto AddComponent(void* componentType) -> Component*
	{
		if (!this) return nullptr;
		METHOD(Component * (**)(GameObject*, void*), AddComponent);
		return AddComponent(this, componentType);
	}
};