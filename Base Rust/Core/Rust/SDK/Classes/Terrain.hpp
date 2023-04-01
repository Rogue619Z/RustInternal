class Terrain
{
public:
	CLASS("UnityEngine", "Terrain");

	auto SampleHeight(Vector3 worldPos) -> float
	{
		METHOD(float(**)(Terrain*, Vector3), SampleHeight);
		return SampleHeight(this, worldPos);
	}
};