class Mathf {
public:
	static float Abs(float f)
	{
		return (f >= 0 ? f : -f);
	}
	static float Max(float a, float b)
	{
		return (a > b) ? a : b;
	}
	static float Min(float a, float b)
	{
		return (a < b) ? a : b;
	}
	static float Distance(Vector3 a, Vector3 b)
	{
		float num = a.x - b.x;
		float num2 = a.y - b.y;
		float num3 = a.z - b.z;
		return (float)std::sqrt((double)(num * num + num2 * num2 + num3 * num3));
	}
	static int FloorToInt(float f)
	{
		return (int)std::floor((double)f);
	}
	static float Clamp(float value, float min, float max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
		return value;
	}
	static float Sign(float f)
	{
		return (f >= 0.f) ? 1.f : (-1.f);
	}
	static int Clamp(int value, int min, int max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
		return value;
	}
	static float MoveTowards(float current, float target, float maxDelta)
	{
		if (Abs(target - current) <= maxDelta)
		{
			return target;
		}
		return current + Sign(target - current) * maxDelta;
	}
	static float Clamp01(float value)
	{
		if (value < 0.f)
		{
			return 0.f;
		}
		if (value > 1.f)
		{
			return 1.f;
		}
		return value;
	}
	static float Lerp(float a, float b, float t)
	{
		return a + (b - a) * Clamp01(t);
	}
	static float LerpUnclamped(float a, float b, float t)
	{
		return a + (b - a) * t;
	}
	static float Max3(float f1, float f2, float f3)
	{
		return Mathf::Max(Mathf::Max(f1, f2), f3);
	}
};