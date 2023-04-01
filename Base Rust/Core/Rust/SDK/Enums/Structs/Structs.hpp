class Rect {
public:
	float x;
	float y;
	float w;
	float h;
	Rect(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	Rect() {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
	}
	bool Contains(Vector2 point)
	{
		return point.x >= x && point.x < (x + w) && point.y >= y && point.y < (y + h);
	}

	Rect& operator+=(const Vector2& v) {
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	Rect operator+(const Vector2& input) const {
		return Rect(this->x + input.x, this->y + input.y, this->w, this->h);
	}
};


class Color {
public:
	float r, g, b, a;
	Color(float _r, float _g, float _b, float _a) : r(_r / 255), g(_g / 255), b(_b / 255), a(_a / 255) {}
	Color(float _r, float _g, float _b) : r(_r / 255), g(_g / 255), b(_b / 255), a(1) {}

	static Color from_hsb(float hue, float saturation, float brightness) {
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1) {
			return Color((brightness * 255), (t * 255), (p * 255));
		}
		else if (h < 2) {
			return Color((q * 255), (brightness * 255), (p * 255));
		}
		else if (h < 3) {
			return Color((p * 255), (brightness * 255), (t * 255));
		}
		else if (h < 4) {
			return Color((p * 255), (q * 255), (brightness * 255));
		}
		else if (h < 5) {
			return Color((t * 255), (p * 255), (brightness * 255));
		}
		else {
			return Color((brightness * 255), (p * 255), (q * 255));
		}
	}
};