class GamePhysics
{
public:
	CLASS("", "GamePhysics");

	static auto LineOfSightRadius(Vector3 p0, Vector3 p1, int layerMask, float radius, float padding0, float padding1, BaseEntity* ignoreEntity) -> bool
	{
		METHOD(bool(**)(Vector3, Vector3, int, float, float, float padding1, BaseEntity*), LineOfSightRadius);
		return LineOfSightRadius(p0, p1, layerMask, radius, padding0, padding1, ignoreEntity);
	}
	static auto LineOfSightInternal(Vector3 p0, Vector3 p1, int layerMask, float radius, float padding0, float padding1, BaseEntity* ignoreEntity) -> bool
	{
		METHOD(bool(**)(Vector3, Vector3, int, float, float, float padding1, BaseEntity*), LineOfSightInternal);
		return LineOfSightInternal(p0, p1, layerMask, radius, padding0, padding1, ignoreEntity);
	}
};
bool IsVisible(Vector3 source, Vector3 destination, float p1 = 0.18f) {
	__try
	{
		auto layer = (int)Enums::Layers::ProjectileLineOfSightCheck | (int)Enums::Layers::Terrain | (int)Enums::Layers::z | (int)Enums::Layers::EntityLineOfSightCheck;


		return GamePhysics::LineOfSightRadius(source, destination, layer, p1, 0.0f, 0.0f, LocalPlayer::Entity()) && GamePhysics::LineOfSightRadius(destination, source, layer, p1, 0.0f, 0.0f, LocalPlayer::Entity());

	}
	__except (true)
	{
		printf("LOS Crash");
	}

}