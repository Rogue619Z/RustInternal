class TerrainMeta
{
public:
	CLASS("", "TerrainMeta");

	static auto New() -> TerrainMeta*
	{
		return *reinterpret_cast<TerrainMeta**>(*reinterpret_cast<uintptr_t*>(StaticClass() + 0xB8) + 0x8);
	}
	auto Position() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(TerrainMeta*), get_Position);
		return get_Position(this);
	}
	auto HeightMap() -> TerrainHeightMap*
	{
		if (!this) return nullptr;
		METHOD(TerrainHeightMap * (**)(TerrainMeta*), get_HeightMap);
		return get_HeightMap(this);
	}
	auto terrain() -> Terrain*
	{
		if (!this) return nullptr;
		METHOD(Terrain * (**)(TerrainMeta*), get_Terrain);
		return get_Terrain(this);
	}
	auto Collision() -> TerrainCollision*
	{
		if (!this) return nullptr;
		METHOD(TerrainCollision * (**)(TerrainMeta*), get_Collision);
		return get_Collision(this);
	}
};