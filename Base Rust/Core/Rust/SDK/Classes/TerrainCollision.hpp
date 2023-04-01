class TerrainCollision
{
public:
	CLASS("", "TerrainCollision");

	auto GetIgnore(Vector3 pos, float radius = 0.01f) -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(TerrainCollision*, Vector3, float), GetIgnore);
		return GetIgnore(this, pos, radius);
	}
};