#define M_PI 3.14159265358979323846f
#define M_PI_2     1.57079632679489661923   // pi/2

class Vector3
{
public:
	float x, y, z;

	Vector3() {
		x = y = z = 0.f;
	}

	Vector3(float fx, float fy, float fz) {
		x = fx;
		y = fy;
		z = fz;
	}

	static Vector3 Zero() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	static Vector3 One() {
		return Vector3(1.0f, 1.0f, 1.0f);
	}

	static Vector3 Up() {
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	static Vector3 Down() {
		return Vector3(0.0f, -1.0f, 0.0f);
	}

	static Vector3 Left() {
		return Vector3(-1.0f, 0.0f, 0.0f);
	}

	static Vector3 Right() {
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	static Vector3 Forward() {
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	static Vector3 Back() {
		return Vector3(0.0f, 0.0f, -1.0f);
	}
	static float Clamp01(float value)
	{
		if (value < 0.f)
			return 0.f;
		else if (value > 1.f)
			return 1.f;
		else
			return value;
	}

	static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		t = Clamp01(t);
		return Vector3(
			a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t,
			a.z + (b.z - a.z) * t
		);
	}

	Vector3 operator+(const Vector3& input) const {
		return Vector3{ x + input.x, y + input.y, z + input.z };
	}

	Vector3 operator+(const float& input) const {
		return Vector3{ x + input, y + input, z + input };
	}

	Vector3 operator-(const Vector3& input) const {
		return Vector3{ x - input.x, y - input.y, z - input.z };
	}

	Vector3 operator/(float input) const {
		return Vector3{ x / input, y / input, z / input };
	}

	Vector3 operator*(float input) const {
		return Vector3{ x * input, y * input, z * input };
	}

	Vector3 operator*(Vector3 input) const {
		return Vector3{ x * input.x, y * input.y, z * input.z };
	}

	Vector3 operator/(Vector3 input) const {
		return Vector3{ x / input.x, y / input.y, z / input.z };
	}

	bool operator>(float input) const
	{
		if (x > input) return true;
		if (y > input) return true;
		if (z > input) return true;
		return false;
	}

	bool operator<(float input) const
	{
		if (x < input) return true;
		if (y < input) return true;
		if (z < input) return true;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}

	float operator[](int i) const {
		return ((float*)this)[i];
	}

	Vector3& operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3& operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator/=(float input) {
		x /= input;
		y /= input;
		z /= input;
		return *this;
	}

	Vector3& operator*=(float input) {
		x *= input;
		y *= input;
		z *= input;
		return *this;
	}

	bool operator==(const Vector3& input) const {
		return x == input.x && y == input.y && z == input.z;
	}
	bool operator!=(const Vector3& input) const {
		if (x != input.x || y != input.y || z != input.z)
			return true;

		return false;
	}

	void make_absolute() {
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	float UnityMagnitude()
	{
		return (float)sqrt((double)(this->x * this->x + this->y * this->y + this->z * this->z));
	}

	float magnitude2d()
	{
		return sqrt(x * x + z * z);
		//return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
	{
		float toVector_x = target.x - current.x;
		float toVector_y = target.y - current.y;
		float toVector_z = target.z - current.z;

		float sqdist = toVector_x * toVector_x + toVector_y * toVector_y + toVector_z * toVector_z;

		if (sqdist == 0 || (maxDistanceDelta >= 0 && sqdist <= maxDistanceDelta * maxDistanceDelta))
			return target;
		auto dist = (float)std::sqrt(sqdist);

		return Vector3(current.x + toVector_x / dist * maxDistanceDelta,
			current.y + toVector_y / dist * maxDistanceDelta,
			current.z + toVector_z / dist * maxDistanceDelta);
	}
	float magnitude()
	{
		return sqrt((double)this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float length_sqr() const {
		return (x * x) + (y * y) + (z * z);
	}

	float length() const {
		return std::sqrt(length_sqr());
	}

	float length_2d() const {
		return std::sqrt((x * x) + (y * y));
	}

	void UnityNormalize()
	{
		Vector3 tis(x, y, z);
		float num = Vector3(x, y, z).magnitude();
		if (num > 1E-05f)
		{
			tis /= num;
		}
		else
		{
			tis = Vector3::Zero();
		}
		x = tis.x;
		y = tis.y;
		z = tis.z;
	}

	Vector3 normalized() const {
		return { x / length(), y / length(), z / length() };
	}

	Vector3 midPoint(Vector3 v2) {
		return Vector3((x + v2.x) / 2, (y + v2.y) / 2, (z + v2.z) / 2);
	}

	float dot_product(float input) const {
		return (x * input) + (y * input) + (z * input);
	}

	float dot_product(Vector3 input) const {
		return (x * input.x) + (y * input.y) + (z * input.z);
	}

	float distance(Vector3 input) const {
		return (*this - input).length();
	}

	float distance_2d(Vector3 input) const {
		return (*this - input).length_2d();
	}

	Vector3 multiply(const Vector3& ref) const
	{
		return Vector3(x * ref.x, y * ref.y, z * ref.z);
	}
	bool empty() const {
		return x == 0.f && y == 0.f && z == 0.f;
	}

	inline float UnityDot(Vector3 lhs, Vector3 rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	static Vector3 XZ3D(Vector3 v)
	{
		return Vector3(v.x, 0.f, v.z);
	}
	static Vector3 XZ3DV2(Vector3 v)
	{
		return Vector3(v.x, 0.f, v.z);
	}
	inline float Dot(const Vector3& Vec2) {
		return this->x * Vec2.x + this->y * Vec2.y + this->z * Vec2.z;
	}
	static float StaticDot(Vector3 lhs, Vector3 rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	inline Vector3 Cross(const Vector3& Vec2) {
		return Vector3(this->y * Vec2.z - this->z * Vec2.y, this->z * Vec2.x - this->x * Vec2.z, this->x * Vec2.y - this->y * Vec2.x);
	}

	inline float Distance(const Vector3& Dst) {
		return sqrtf(pow((this->x - Dst.x), 2) + pow((this->y - Dst.y), 2) + pow((this->z - Dst.z), 2));
	}
};
class Vector2
{
public:
	Vector2() {
		x = y = 0.f;
	}

	Vector2(float fx, float fy) {
		x = fx;
		y = fy;
	}

	float x, y;

	Vector2 operator+(const Vector2& input) const {
		return Vector2{ x + input.x, y + input.y };
	}

	Vector2 operator-(const Vector2& input) const {
		return Vector2{ x - input.x, y - input.y };
	}

	Vector2 operator/(float input) const {
		return Vector2{ x / input, y / input };
	}

	Vector2 operator*(float input) const {
		return Vector2{ x * input, y * input };
	}

	Vector2& operator-=(const Vector2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2& operator+=(const Vector2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2& operator/=(float input) {
		x /= input;
		y /= input;
		return *this;
	}

	Vector2& operator*=(float input) {
		x *= input;
		y *= input;
		return *this;
	}

	float length() const {
		return std::sqrt((x * x) + (y * y));
	}

	Vector2 normalized() const {
		return { x / length(), y / length() };
	}

	void Normalize() {
		if (y < -89) y = -89;
		else if (y > 89) y = 89;
		if (x < -360) x += 360;
		else if (x > 360) x -= 360;
	}

	float dot_product(Vector2 input) const {
		return (x * input.x) + (y * input.y);
	}

	float distance(Vector2 input) const {
		return (*this - input).length();
	}

	Vector2 midPoint(Vector2 v2) {
		return Vector2((x + v2.x) / 2, (y + v2.y) / 2);
	}

	float distance_2d(Vector2 input) {
		return sqrt(powf(x - input.x, 2) + powf(y - input.y, 2));
	}

	bool empty() const {
		return x == 0.f && y == 0.f;
	}

	static Vector2 Zero()
	{
		return Vector2(0, 0);
	}
};
class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4()
	{}

	Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}

	Vector3 forward()
	{
		Vector3  point = { 0, 0, 1 };
		float num = x * 2;
		float num2 = y * 2;
		float num3 = z * 2;
		float num4 = x * num;
		float num5 = y * num2;
		float num6 = z * num3;
		float num7 = x * num2;
		float num8 = x * num3;
		float num9 = y * num3;
		float num10 = w * num;
		float num11 = w * num2;
		float num12 = w * num3;
		Vector3  result;
		result.x = (1 - (num5 + num6)) * point.x + (num7 - num12) * point.y +
			(num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1 - (num4 + num6)) * point.y +
			(num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y +
			(1 - (num4 + num5)) * point.z;
		return result;
	}



	inline float dot(const Vector4& vector)
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	inline float distance(const Vector4& vector)
	{
		return sqrtf(
			(x - vector.x) * (x - vector.x) +
			(y - vector.y) * (y - vector.y) +
			(z - vector.z) * (z - vector.z) +
			(w - vector.w) * (w - vector.w));
	}

	bool operator==(const Vector4& vector) const
	{
		return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
	}

	Vector4 operator*(const Vector4& v) const
	{
		return Vector4(this->x * v.x,
			this->y * v.y,
			this->z * v.z,
			this->w * v.w);
	}

	bool operator!=(const Vector4& vector) const
	{
		return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
	}

	Vector3 vm(const Vector3& point)
	{
		float x = x * 2.f;
		float y = y * 2.f;
		float z = z * 2.f;
		float xx = x * x;
		float yy = y * y;
		float zz = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		Vector3 res;
		res.x = (1.f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
		res.y = (xy + wz) * point.x + (1.f - (xx + zz)) * point.y + (yz - wx) * point.z;
		res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.f - (xx + yy)) * point.z;
		return res;
	}
	static Vector4 Zero()
	{
		return Vector4(0, 0, 0, 0);
	}
	Vector4 LookRotation(Vector3& forward, Vector3& up)
	{
		/*
		forward = forward.normalize();

		Vector3 right = Vector3.Normalize(Vector3.Cross(up, forward));
		up = Vector3.Cross(forward, right);
		var m00 = right.x;
		var m01 = right.y;
		var m02 = right.z;
		var m10 = up.x;
		var m11 = up.y;
		var m12 = up.z;
		var m20 = forward.x;
		var m21 = forward.y;
		var m22 = forward.z;


		float num8 = (m00 + m11) + m22;
		var quaternion = new MyVector4();
		if (num8 > 0f)
		{
			var num = (float)System.Math.Sqrt(num8 + 1f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			var num7 = (float)System.Math.Sqrt(((1f + m00) - m11) - m22);
			var num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			var num6 = (float)System.Math.Sqrt(((1f + m11) - m00) - m22);
			var num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		var num5 = (float)System.Math.Sqrt(((1f + m22) - m00) - m11);
		var num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
		*/
	}

	Vector4 operator+(const Vector4& vector) const
	{
		return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
	}

	Vector4 operator-(const Vector4& vector) const
	{
		return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
	}

	Vector4 operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	Vector4 operator*(float number) const
	{
		return Vector4(x * number, y * number, z * number, w * number);
	}

	Vector4 operator/(float number) const
	{
		return Vector4(x / number, y / number, z / number, w / number);
	}

	Vector4& operator+=(const Vector4& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}

	Vector4& operator*=(float number)
	{
		x *= number;
		y *= number;
		z *= number;
		w *= number;
		return *this;
	}

	Vector4& operator/=(float number)
	{
		x /= number;
		y /= number;
		z /= number;
		w /= number;
		return *this;
	}
};
class Matrix
{
public:
	Matrix()
		: m{ { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 } }
	{}

	Matrix(const Matrix&) = default;

	Matrix transpose() {
		Matrix m;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m.m[i][j] = this->m[j][i];

		return m;
	}
	void matrix_identity() {
		memset(this, 0, sizeof(Matrix));
		m[0][0] = 1.0f;
		m[1][1] = 1.0f;
		m[2][2] = 1.0f;
		m[3][3] = 1.0f;
	}

	bool is_empty() {
		if (!m[3][0] && !m[3][1] && !m[3][2] && !m[2][1] && !m[2][0] && !m[2][2])
			return true;

		return false;
	}
	Vector3 MultiplyPoint3x4(Vector3 point)
	{
		Vector3 result;
		result.x = m[0][0] * point.x + m[0][1] * point.y + m[0][2] * point.z + m[0][3];
		result.y = m[1][0] * point.x + m[1][1] * point.y + m[1][2] * point.z + m[1][3];
		result.z = m[2][0] * point.x + m[2][1] * point.y + m[2][2] * point.z + m[2][3];
		return result;
	}
	Vector3 operator*(const Vector3& vec) {
		Matrix m;

		m[3][0] = vec.x;
		m[3][1] = vec.y;
		m[3][2] = vec.z;

		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;


		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;

		auto result = m * (*this);

		return Vector3{ result[3][0], result[3][1], result[3][2] };
	}

	Matrix operator*(const Matrix& _m2) {
		auto _m = *this;

		Matrix out;
		out[0][0] = _m[0][0] * _m2[0][0] + _m[0][1] * _m2[1][0] + _m[0][2] * _m2[2][0] + _m[0][3] * _m2[3][0];
		out[0][1] = _m[0][0] * _m2[0][1] + _m[0][1] * _m2[1][1] + _m[0][2] * _m2[2][1] + _m[0][3] * _m2[3][1];
		out[0][2] = _m[0][0] * _m2[0][2] + _m[0][1] * _m2[1][2] + _m[0][2] * _m2[2][2] + _m[0][3] * _m2[3][2];
		out[0][3] = _m[0][0] * _m2[0][3] + _m[0][1] * _m2[1][3] + _m[0][2] * _m2[2][3] + _m[0][3] * _m2[3][3];
		out[1][0] = _m[1][0] * _m2[0][0] + _m[1][1] * _m2[1][0] + _m[1][2] * _m2[2][0] + _m[1][3] * _m2[3][0];
		out[1][1] = _m[1][0] * _m2[0][1] + _m[1][1] * _m2[1][1] + _m[1][2] * _m2[2][1] + _m[1][3] * _m2[3][1];
		out[1][2] = _m[1][0] * _m2[0][2] + _m[1][1] * _m2[1][2] + _m[1][2] * _m2[2][2] + _m[1][3] * _m2[3][2];
		out[1][3] = _m[1][0] * _m2[0][3] + _m[1][1] * _m2[1][3] + _m[1][2] * _m2[2][3] + _m[1][3] * _m2[3][3];
		out[2][0] = _m[2][0] * _m2[0][0] + _m[2][1] * _m2[1][0] + _m[2][2] * _m2[2][0] + _m[2][3] * _m2[3][0];
		out[2][1] = _m[2][0] * _m2[0][1] + _m[2][1] * _m2[1][1] + _m[2][2] * _m2[2][1] + _m[2][3] * _m2[3][1];
		out[2][2] = _m[2][0] * _m2[0][2] + _m[2][1] * _m2[1][2] + _m[2][2] * _m2[2][2] + _m[2][3] * _m2[3][2];
		out[2][3] = _m[2][0] * _m2[0][3] + _m[2][1] * _m2[1][3] + _m[2][2] * _m2[2][3] + _m[2][3] * _m2[3][3];
		out[3][0] = _m[3][0] * _m2[0][0] + _m[3][1] * _m2[1][0] + _m[3][2] * _m2[2][0] + _m[3][3] * _m2[3][0];
		out[3][1] = _m[3][0] * _m2[0][1] + _m[3][1] * _m2[1][1] + _m[3][2] * _m2[2][1] + _m[3][3] * _m2[3][1];
		out[3][2] = _m[3][0] * _m2[0][2] + _m[3][1] * _m2[1][2] + _m[3][2] * _m2[2][2] + _m[3][3] * _m2[3][2];
		out[3][3] = _m[3][0] * _m2[0][3] + _m[3][1] * _m2[1][3] + _m[3][2] * _m2[2][3] + _m[3][3] * _m2[3][3];

		return out;
	}

	float* operator[](size_t i) { return m[i]; }
	const float* operator[](size_t i) const { return m[i]; }

	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};
struct Ray {
public:
	Vector3 m_Origin;
	Vector3 m_Direction;

	Ray() {
		this->m_Origin = Vector3(0, 0, 0);
		this->m_Direction = Vector3(0, 0, 0);
	}

	Ray(Vector3 origin, Vector3 direction) {
		this->m_Origin = origin;
		this->m_Direction = direction;
	}

	Vector3 ClosestPoint(Vector3 pos) {
		return this->m_Origin + this->m_Direction * (pos - this->m_Origin).dot_product(this->m_Direction);
	}
};