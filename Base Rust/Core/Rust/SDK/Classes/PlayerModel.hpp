class Renderersa
{
public:
	CLASS("UnityEngine", "Renderer");

	auto material() -> Material*
	{
		METHOD(Material * (**)(Renderersa*), get_material);
		return get_material(this);
	}
};
class SkinnedMultiMesh
{
public:
	CLASS("", "SkinnedMultiMesh");

	auto Renderers() -> List< Renderersa*>*
	{
		METHOD(List< Renderersa*>*(**)(SkinnedMultiMesh*), get_Renderers);
		return get_Renderers(this);
	}
};

class PlayerModel
{
public:
	CLASS("", "PlayerModel");

	MEMBER(Vector3, position);
	MEMBER(SkinnedMultiMesh*, _multiMesh);

	auto PlayerNPC() -> bool
	{
		if (!this) return false;
		auto npc = Il2CppWrapper::GetClassFromName("", "PlayerModel")->GetFieldFromName("<IsNpc>k__BackingField");
		return *reinterpret_cast<bool*>(this + npc);
	}

};