class Screen
{
public:
	CLASS("UnityEngine", "Screen");

	static auto width() -> int
	{
		METHOD(int(**)(), get_width);
		return get_width();
	}

	static auto height() -> int
	{
		METHOD(int(**)(), get_height);
		return get_height();
	}
};
