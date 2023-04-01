
Camera* cam;
class Camera
{
public:
    CLASS("UnityEngine", "Camera");

	static auto main() -> Camera*
	{
		METHOD(Camera*(**)(), get_main);
		return get_main();
	}
	auto WorldToScreenPoint(Vector3 pos) -> Vector3
	{
		static auto WorldToScreenPoint = *reinterpret_cast<Vector3(**)(Camera*, Vector3)>(StaticClass()->GetMethodFromName("WorldToScreenPoint", 1));
		return WorldToScreenPoint(this, pos);
	}
	Vector3 ScreenTransform(Vector3 WorldPoint)
	{
		if (!this) return {};

		Vector3 W2SPoint = this->WorldToScreenPoint(WorldPoint);

		// due to unity having 0,0 as bottom left, not top left
		W2SPoint.y = Screen::height() - W2SPoint.y;

		if (W2SPoint.z < 0.01f) return { 0, 0, 0 };

		return W2SPoint;
	}
	bool WorldToScreen(Vector3 position, Vector2& screen)
	{
		if (!this) return false;

		Vector3 ret = WorldToScreenPoint(position);
		ret.y = Screen::height() - ret.y;
		screen =
		{
			ret.x,
			ret.y
		};

		return ret.z > 0.0f;
	}
};
namespace unity
{



	//inline auto viewMatrix() -> mat4x4_t
	//{
	//	if (!cam) {
	//		cam = Camera::main();
	//		LOG("Camera Set");
	//	}
	//	auto camera_ = *reinterpret_cast<std::uintptr_t*>(cam + 0x10);
	//	if (!camera_) {
	//		return {};
	//	}

	//	auto matrix = *reinterpret_cast<mat4x4_t*>(camera_ + 0x2e4);
	//	if (!matrix.m) {
	//		return {};
	//	}
	//	return matrix;
	//}
	//inline bool w2s(const Vector3& EntityPos, Vector2& ScreenPos)
	//{
	//	auto matrix = viewMatrix();

	//	if (!matrix.m) {
	//		return false;
	//	}
	//	const auto temp = matrix.transpose();

	//	auto translation_vector = Vector3{ temp[3][0], temp[3][1], temp[3][2] };
	//	auto up = Vector3{ temp[1][0], temp[1][1], temp[1][2] };
	//	auto right = Vector3{ temp[0][0], temp[0][1], temp[0][2] };

	//	float w = translation_vector.dot(EntityPos) + temp[3][3];

	//	if (w < 0.098f) {
	//		return false;
	//	}

	//	float x = up.dot(EntityPos) + temp._24;
	//	float y = right.dot(EntityPos) + temp._14;

		//ScreenPos.x = (static_cast<float>(Screen::width()) / 2) * (1 + y / w);
		//ScreenPos.y = (static_cast<float>(Screen::height()) / 2) * (1 - x / w);

	//	//ScreenPos = out;

	//	return true;
	//}
}