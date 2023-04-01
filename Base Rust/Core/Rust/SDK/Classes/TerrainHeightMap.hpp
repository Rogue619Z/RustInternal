class TerrainHeightMap
{
public:
	CLASS("", "TerrainHeightMap");

	auto GetHeight(Vector3 worldPos) -> float
	{
		METHOD(float(**)(TerrainHeightMap*, Vector3), GetHeight);
		return GetHeight(this, worldPos);
	}
	auto GetNormal(Vector3 worldPos) -> Vector3
	{
		METHOD(Vector3(**)(TerrainHeightMap*, Vector3), GetNormal);
		return GetNormal(this, worldPos);
	}
};