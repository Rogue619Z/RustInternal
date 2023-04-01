namespace AntiHack
{


	struct OBB {
	public:
		Vector4 rotation;
		Vector3 position;
		Vector3 extents;
		Vector3 forward;
		Vector3 right;
		Vector3 up;
		float reject;
		OBB(Vector3 position, Vector4 rotation, Bounds bounds) {
			this->rotation = rotation;
			auto r = Vector3(rotation.x, rotation.y, rotation.z);
			this->position = (position + r).multiply(bounds.center);
			this->extents = bounds.extents;
			auto temp = rotation * Vector4(0, 0, 1, 0);
			this->forward = Vector3(temp.x, temp.y, temp.z);
			temp = rotation * Vector4(1, 0, 0, 0);
			this->right = Vector3(temp.x, temp.y, temp.z);
			temp = rotation * Vector4(0, 1, 0, 0);
			this->up = Vector3(temp.x, temp.y, temp.z);
			this->reject = this->extents.length();
		}

		Vector3 ClosestPoint(Vector3 target)
		{
			bool flag = false;
			bool flag2 = false;
			bool flag3 = false;
			Vector3 vector = this->position;
			Vector3 lhs = target - this->position;
			float num = lhs.Dot(this->right);
			if (num > this->extents.x)
			{
				vector += this->right * this->extents.x;
			}
			else if (num < -this->extents.x)
			{
				vector -= this->right * this->extents.x;
			}
			else
			{
				flag = true;
				vector += this->right * num;
			}
			float num2 = lhs.Dot(this->up);
			if (num2 > this->extents.y)
			{
				vector += this->up * this->extents.y;
			}
			else if (num2 < -this->extents.y)
			{
				vector -= this->up * this->extents.y;
			}
			else
			{
				flag2 = true;
				vector += this->up * num2;
			}
			float num3 = lhs.Dot(this->forward);
			if (num3 > this->extents.z)
			{
				vector += this->forward * this->extents.z;
			}
			else if (num3 < -this->extents.z)
			{
				vector -= this->forward * this->extents.z;
			}
			else
			{
				flag3 = true;
				vector += this->forward * num3;
			}
			if (flag && flag2 && flag3)
			{
				return target;
			}
			return vector;
		}

		float Distance(OBB other) {
			OBB obb = *this;
			OBB obb2 = other;
			Vector3 vector = obb.position;
			Vector3 vector2 = obb2.position;
			vector = obb.ClosestPoint(vector2);
			vector2 = obb2.ClosestPoint(vector);
			vector = obb.ClosestPoint(vector2);
			vector2 = obb2.ClosestPoint(vector);
			return vector.distance(vector2);
		}
		float Distance(Vector3 position) { return position.distance(this->ClosestPoint(position)); }
	};

	class _Line {
	public:
		Vector3 start;
		Vector3 end;
		_Line(Vector3 s, Vector3 e) {
			start = s; end = e;
		}
		_Line() { }
		Vector3 ClosestPoint(Vector3 pos)
		{
			Vector3 a = end - start;
			float magnitude = a.length();
			if (magnitude == 0.f) return start;
			Vector3 vector = a / magnitude;
			Vector3 lhs = pos - start;
			return start + vector * std::clamp(lhs.Dot(vector), 0.f, magnitude);
		}
	};


	class TickInterpolator {
	private:
		struct Segment {
			Vector3 point;
			float length;
			Segment(Vector3 a, Vector3 b) {
				this->point = b;
				this->length = a.distance(b);
			}
		};
	public:
		std::vector<Segment> points = std::vector<Segment>();
		int index;
		float len;
		Vector3 currentPoint;
		Vector3 startPoint;
		Vector3 endPoint;

		void Reset() {
			this->index = 0;
			this->currentPoint = this->startPoint;
		}
		void Reset(Vector3 point) {
			this->points.clear();
			this->index = 0;
			this->len = 0.f;
			this->currentPoint = (this->startPoint = (this->endPoint = point));
		}
		void AddPoint(Vector3 point) {
			Segment segment = Segment(this->endPoint, point);
			this->points.push_back(segment);
			this->len += segment.length;
			this->endPoint = segment.point;
		}
		bool MoveNext(float distance)
		{
			float num = 0.f;
			while (num < distance && this->index < this->points.size())
			{
				Segment segment = this->points[this->index];
				this->currentPoint = segment.point;
				num += segment.length;
				this->index++;
			}
			return num > 0.f;
		}
		bool HasNext() {
			return this->index < this->points.size();
		}
	};
	template<typename T>
	void pop_front(std::vector<T>& vec)
	{
		if (vec.empty()) return;
		vec.front() = std::move(vec.back());
		vec.pop_back();
	}
	class TickHistory
	{
	public:
		std::vector<Vector3> points = {};
		int Count()
		{
			return points.size();
		}

		float Distance(BasePlayer* ent, Vector3 point)
		{
			Vector3 position = ent->transform()->get_position();
			if (Count() == 0)
			{
				return position.distance(point);
			}
			Vector4 rotation = ent->transform()->get_rotation();
			Bounds bounds = ent->GetBounds();

			//auto trans = ent->transform();
			//bool flag = trans ? !(!trans) : false;
			//Matrix _mv; _mv.matrix_identity();
			//Matrix matrix4x = flag ? _mv : trans->get_localToWorldMatrix();

			//Matrix tickHistoryMatrix = matrix4x;
			//float num = FLT_MAX;
			//for (int i = 0; i < Count(); i++)
			//{
			//	Vector3 point2 = tickHistoryMatrix.MultiplyPoint3x4(points[i]);
			//	Vector3 point3 = (i == Count() - 1) ? position : tickHistoryMatrix.MultiplyPoint3x4(points[i + 1]);
			//	_Line line(point2, point3);
			//	Vector3 position2 = line.ClosestPoint(point);
			//	OBB obb(position2, rotation, bounds);
			//	num = min(num, obb.Distance(point));
			//}
			return 0.0f; //return num;
		}

		void AddPoint(Vector3 point, int limit = -1)
		{
			while (limit > 0 && Count() >= limit)
			{
				pop_front(this->points);
				//this->points.pop_back();
				//this->points.insert(this->points.begin(), 1, point);
			}
			this->points.push_back(point);
		}

		void TransformEntries(Matrix matrix)
		{
			for (int i = 0; i < Count(); i++)
			{
				Vector3 vector = this->points[i];
				vector = matrix.MultiplyPoint3x4(vector);
				this->points[i] = vector;
			}
		}
	};
	struct TimeAverageValueData
	{
	public:
		int Calculate()
		{
			float realtimeSinceStartup = Time::realtimeSinceStartup();//UnityEngine::Time::get_realtimeSinceStartup();
			float num = realtimeSinceStartup - refreshTime;
			if (num >= 1.0)
			{
				counterPrev = (int)(counterNext / num + 0.5);
				counterNext = 0;
				refreshTime = realtimeSinceStartup;
				num = 0;
			}
			return (int)(counterPrev * (1.0 - num)) + counterNext;
		}

		void Increment()
		{
			this->Calculate();
			counterNext += 1;
		}

		void Reset()
		{
			counterPrev = 0;
			counterNext = 0;
		}

		float refreshTime;

		int counterPrev;

		int counterNext;
	};
	AntiHack::TickHistory tickHistory;
	AntiHack::TickInterpolator ticks;
	AntiHack::TimeAverageValueData ticksPerSecond = {};


	float tickDeltaTime = 0.f;
	float timeSinceLastTick()
	{

		if (LocalPlayer::Entity()->lastSentTickTime() == 0.f)
		{
			return 0.f;
		}

		return Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime();
	}
	static float NoClipRadius(float margin)
	{
		return 0.5f - margin;
	}
	bool TestNoClipping(BasePlayer* ply, Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool spHerecast) {
		int num = 429990145;
		//Ulog("6");
		Vector3 normalized = (newPos - oldPos).normalized();
		Vector3 vector = oldPos - normalized * backtracking;
		float magnitude = (newPos - vector).magnitude();

		typedef bool (*RayCast)(Ray, float, int);

		bool flag = Raycast(Ray(vector, normalized), magnitude + radius, 429990145);
		//bool flag = ((RayCast)(LI_MODULE_SAFE_("GameAssembly.dll") + 0x2527850))(Ray(vector, normalized), magnitude + radius, 429990145); //public static bool Raycast(Ray ray, float maxDistance, int layerMask) { }

		//bool flag = Physics::Raycast(Ray(vector, normalized), magnitude + radius, 429990145);
		if (!flag || spHerecast) {
			typedef bool (*Sphere)(Ray, float, float, int);

			flag = SphereCast(Ray(vector, normalized), radius, magnitude, 429990145);
		//	flag = ((Sphere)(LI_MODULE_SAFE_("GameAssembly.dll") + 0x2528890))(Ray(vector, normalized), radius, magnitude, 429990145);

		}
		return flag;
	}

	bool ValidateEyePos(BasePlayer* player, Vector3 eyePos)
	{
		float desyncTimeRaw = Mathf::Max(timeSinceLastTick() - Time::get_deltaTime(), 0.f);
		float desyncTimeClamped = Mathf::Min(desyncTimeRaw, 1.0f);
		bool flag = true;

		if (true)
		{
			float num = 1.5f;
			float eye_clientframes = 2.0f;
			float eye_serverframes = 2.0f;
			float num2 = eye_clientframes / 60.f;
			float num3 = eye_serverframes * Mathf::Max3(Time::get_deltaTime(), Time::get_smoothDeltaTime(), Time::get_fixedDeltaTime());
			float num4 = (desyncTimeClamped + num2 + num3) * num;
			float num5 = player->MaxEyeVelocity() + player->GetParentVelocity().magnitude();

			float max_eye_range = player->BoundsPadding() + num4 * num5;

		

			//float mm_max_eye = LocalPlayer::Entity()->BoundsPadding() + num4 * LocalPlayer::Entity()->MaxEyeVelocity();
			int layerMask = (int)Enums::Layers::ProjectileLineOfSightCheck | (int)Enums::Layers::Terrain | (int)Enums::Layers::z | (int)Enums::Layers::EntityLineOfSightCheck;
		//	int layerMask = (true ? 10551296 : 2162688);
			if (true)
			{
				float num5 = player->MaxEyeVelocity() + player->GetParentVelocity().magnitude();
				float num6 = player->BoundsPadding() + num4 * num5;
				float num7 = Mathf::Distance(player->eyes()->get_position(), eyePos);
				if (num7 > num6)
				{
					printf("Eye Distance Invalidated at [ %f ]\n", num6);
					flag = false;
				}
			}
			if (true)
			{
				float num8 = Mathf::Abs(player->GetMountVelocity().y + player->GetParentVelocity().y);
				float num9 = player->BoundsPadding() + num4 * num8 + player->GetJumpHeight();
				float num10 = Mathf::Abs(player->eyes()->get_position().y - eyePos.y);
				if (num10 > num9)
				{
					flag = false;
				}
			}

			Vector3 position2 = player->eyes()->get_position();
			Vector3 vector2 = eyePos;
			float num11 = Mathf::Distance(position2, vector2);
			if (num11 > 0.06f)
			{
				if (TestNoClipping(player, position2, vector2, NoClipRadius(0.21f), 0.01f, true))
				{
					flag = false;
				}
			}
			else if (num11 > 0.01f && TestNoClipping(player, position2, vector2, 0.01f, 0.01f, true))
			{
				flag = false;
			}
			if (!flag)
			{
			}
		}
		return flag;
	}
	bool isInAir = false;
	bool TestFlying2(BasePlayer* ply,
		Vector3 oldPos = Vector3(0, 0, 0),
		Vector3 newPos = Vector3(0, 0, 0),
		bool verifyGrounded = true)
	{
		if (verifyGrounded)
		{
			auto extrusion = 2.f;
			Vector3 vec = (oldPos + newPos) * 0.5f;
			auto margin = 0.05f;
			float radius = ply->GetRadius();
			float height = ply->GetHeight(false);
			Vector3 vec2 = vec + Vector3(0.f, radius - extrusion, 0.f);
			Vector3 vec3 = vec + Vector3(0.f, height - radius, 0.f);
			float radius2 = radius - margin;
			isInAir = !Physics::CheckCapsule(vec2, vec3, radius2, 1503731969, Enums::Ignore);

			if (isInAir)
			{
				bool flag = false;
				Vector3 vec4 = newPos - oldPos;
				float num2 = std::fabs(vec4.y);
				float num3 = vec4.length_2d();

				if (vec4.y >= 0.f)
				{
					flag = true;
					flyhackDistanceVertical += vec4.y;
				}

				if (num2 < num3)
				{
					flag = true;
					flyhackDistanceHorizontal += num3;
				}

				if (flag)
				{
					float num4 = max((flyhackPauseTime > 0.f ? 10.f : 1.5f), 0.f);
					float num5 = ply->GetJumpHeight() + num4;
					if (flyhackDistanceVertical > num5)
						return true;

					float num6 = num4;
					float num7 = 5.f + num6;
					if (flyhackDistanceHorizontal > num7)
						return true;
				}
				printf("flyhackDistanceHorizontal %f \n", flyhackDistanceHorizontal);
				printf("flyhackDistanceVertical %f \n", flyhackDistanceVertical);
			}
			else
			{
				flyhackDistanceVertical = 0.0f;
				flyhackDistanceHorizontal = 0.0f;
			}
		}
		return false;
	}
	//static bool TestFlying(BasePlayer* ply, Vector3 oldPos, Vector3 newPos, bool verifyGrounded)
	//{
	//	isInAir = false;
	//	if (verifyGrounded)
	//	{
	//		float flyhack_extrusion = 2.0f;
	//		Vector3 vector = (oldPos + newPos) * 0.5f;
	//		if (!ply->OnLadder() && !WaterLevel::Test(vector - Vector3(0.0f, flyhack_extrusion, 0.0f), true, ply))
	//		{

	//			float flyhack_margin = 0.05f;
	//			float radius = ply->GetRadius();
	//			float height = ply->GetHeight(false);
	//			Vector3 vector2 = vector + Vector3(0.f, radius - flyhack_extrusion, 0.f);
	//			Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
	//			float radius2 = radius - flyhack_margin;

	//			isInAir = !Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, Enums::QueryTriggerInteraction::Ignore);
	//		}
	//		if (isInAir)
	//		{
	//			bool flag = false;
	//			Vector3 vec4 = newPos - oldPos;
	//			float num2 = Mathf::Abs(vec4.y);
	//			float num3 = vec4.magnitude2d();

	//			if (vec4.y >= 0.f)
	//			{
	//				flyhackDistanceVertical += vec4.y;
	//				flag = true;
	//			}

	//			if (num2 < num3)
	//			{
	//				flyhackDistanceHorizontal += num3;
	//				flag = true;
	//			}

	//			if (flag)
	//			{
	//				float num4 = Mathf::Max((flyhackPauseTime > 0.f ? 10.f : 1.5f), 0.f);
	//				float num5 = ply->GetJumpHeight() + num4;
	//				if (flyhackDistanceVertical > num5)
	//				{
	//					return true;
	//				}

	//				float num6 = Mathf::Max((flyhackPauseTime > 0.f) ? flyhack_forgiveness_horizontal_inertia : flyhack_forgiveness_horizontal, 0.f);
	//				float num7 = 5.f + num6;
	//				if (flyhackDistanceHorizontal > num7)
	//					return true;
	//			}
	//		}
	//		else {
	//			flyhackDistanceVertical = 0.0f;
	//			flyhackDistanceHorizontal = 0.0f;
	//		}
	//	}
	//	return false;
	//}
	static bool IsFlying(BasePlayer* ply, TickInterpolator ticks, float deltaTime)
	{

		auto lp = LocalPlayer::Entity();
		bool flag = deltaTime > 1.f;

		flyhackPauseTime = Mathf::Max(0.f, flyhackPauseTime - deltaTime);
		ticks.Reset();
		auto trans = LocalPlayer::Entity()->transform();

		if (ticks.HasNext()) {
			bool flag = trans ? !(!trans) : false;
			Matrix v; v.matrix_identity();
			Matrix matrix4x = flag ? v : trans->get_localToWorldMatrix();

			Vector3 oldPos = flag ? ticks.startPoint :
				matrix4x.MultiplyPoint3x4(ticks.startPoint);
			Vector3 vector = flag ? ticks.startPoint :
				matrix4x.MultiplyPoint3x4(ticks.endPoint);
			float num = 0.1f;
			float num2 = 15.0f;
			num = Mathf::Max(ticks.len / num2, num);
			while (ticks.MoveNext(num))
			{
				vector = (flag ? ticks.currentPoint
					: matrix4x.MultiplyPoint3x4(ticks.currentPoint));

				if (TestFlying2(lp, oldPos, vector, true))
					return true;
				oldPos = vector;
			}
		}
		return false;
	}
	//bool IsFlying(float deltaTime) {
	//	auto lp = LocalPlayer::Entity();
	//	bool flag = deltaTime > 1.f;

	//	flyhackPauseTime = max(0.f, flyhackPauseTime - deltaTime);
	//	ticks.Reset();
	//	auto trans = LocalPlayer::Entity()->transform();

	//	if (ticks.HasNext()) {
	//		bool flag = trans ? !(!trans) : false;
	//		Matrix v; v.matrix_identity();
	//		Matrix matrix4x = flag ? v : trans->get_localToWorldMatrix();

	//		Vector3 oldPos = flag ? ticks.startPoint :
	//			matrix4x.MultiplyPoint3x4(ticks.startPoint);
	//		Vector3 vector = flag ? ticks.startPoint :
	//			matrix4x.MultiplyPoint3x4(ticks.endPoint);
	//		float num = 0.1f;
	//		float num2 = 15.0f;
	//		num = max(ticks.len / num2, num);
	//		while (ticks.MoveNext(num))
	//		{
	//			vector = (flag ? ticks.currentPoint
	//				: matrix4x.MultiplyPoint3x4(ticks.currentPoint));

	//			if (TestFlying2(lp, oldPos, vector, true))
	//				return true;
	//			oldPos = vector;
	//		}
	//	}
	//	return false;
	//}
	bool speedhack = true;

	//static bool IsSpeeding(BasePlayer* ply, TickInterpolator ticks, float deltaTime)
	//{
	//	bool result;
	//	speedhackPauseTime = Mathf::Max(0.f, speedhackPauseTime - deltaTime);

	//	auto trans = LocalPlayer::Entity()->transform();
	//	bool num = trans->GetParent() == nullptr;
	//	Matrix _mv; _mv.matrix_identity();


	//	Matrix matrix4x = num ? _mv : trans->get_localToWorldMatrix();

	//	Vector3 vector = num ? ticks.startPoint :
	//		matrix4x.MultiplyPoint3x4(ticks.startPoint);

	//	Vector3 obj = num ? ticks.endPoint :
	//		matrix4x.MultiplyPoint3x4(ticks.endPoint);

	//	float running = 1.f;
	//	float ducking = 0.f;
	//	float crawling = 0.f;

	//	bool flag = ply->IsRunning();
	//	bool flag2 = ply->IsDucked();
	//	bool flag3 = ply->IsSwimming();
	//	bool num2 = ply->IsCrawling();
	//	running = (flag ? 1.f : 0.f);
	//	ducking = ((flag2 || flag3) ? 1.f : 0.f);
	//	crawling = (num2 ? 1.f : 0.f);

	//	float speed = ply->GetSpeed(running, ducking, crawling);
	//	Vector3 v = obj - vector;
	//	float num3 = v.magnitude2d();
	//	float num4 = deltaTime * speed;
	//	if (num3 > num4)
	//	{
	//		Vector3 v2 = (TerrainMeta::New()->HeightMap() ? TerrainMeta::New()->HeightMap()->GetNormal(vector) : Vector3::Up());
	//		float num5 = Mathf::Max(0.f, Vector3::StaticDot(Vector3::XZ3D(v2), Vector3::XZ3D(v))) * speedhack_slopespeed * deltaTime;
	//		num3 = Mathf::Max(0.f, num3 - num5);
	//	}
	//	float num6 = Mathf::Max((speedhackPauseTime > 0.f) ? speedhack_forgiveness_inertia : speedhack_forgiveness, 0.1f);
	//	float num7 = num6 + Mathf::Max(speedhack_forgiveness, 0.1f);
	//	speedhackDistance = Mathf::Clamp(speedhackDistance, 0.f - num7, num7);
	//	speedhackDistance = Mathf::Clamp(speedhackDistance - num4, 0.f - num7, num7);
	//	if (speedhackDistance > num6)
	//	{
	//		speedhack = true;
	//		result = true;
	//	}
	//	speedhackDistance = Mathf::Clamp(speedhackDistance + num3, 0.f - num7, num7);
	//	if (speedhackDistance > num6)
	//	{
	//		speedhack = true;
	//		result = true;
	//	}
	//	else
	//	{
	//		speedhack = false;
	//		result = false;
	//	}
	//	return result || speedhack;
	//}
	bool ValidateMove(BasePlayer* ply,
		AntiHack::TickInterpolator ticks,
		float deltaTime)
	{
		bool flag = deltaTime > 1.0f;
		//IsNoClipping


		if (IsFlying(ply, ticks, deltaTime))
		{
			if (flag)
				return false;
			auto penalty = 100.0f * ticks.len;
			if (penalty > 0)
			{
				//AddViolation(ply, Enums::FlyHack, penalty);

				return false;
			}
		}

		//if (AntiHack::IsSpeeding(ply, ticks, deltaTime))
		//{
		//	if (flag)
		//		return false;

		//	auto penalty = 0.f * ticks.len;
		//	if (penalty > 0)
		//	{
		//		//AddViolation(ply, Enums::SpeedHack, penalty);
		//		if (speedhack_reject)
		//			return false;
		//	}
		//}
		return true;
	}
	void FinalizeTick(float deltatime) {

		auto lp = LocalPlayer::Entity();
		AntiHack::tickDeltaTime += deltatime;
		bool flag = AntiHack::ticks.startPoint != AntiHack::ticks.endPoint;
		if (flag) {
			if (ValidateMove(lp, AntiHack::ticks, deltatime))
			{
				AntiHack::ticksPerSecond.Increment();
				int tickHistoryCapacity = Mathf::Max(1, std::ceil((float)AntiHack::ticksPerSecond.Calculate() * 0.5f));
				AntiHack::tickHistory.AddPoint(AntiHack::ticks.endPoint, tickHistoryCapacity);
				//FadeViolations(lp, tickDeltaTime);
			}
			else {
				flag = false;

			}
		}
		AntiHack::ticks.Reset(LocalPlayer::Entity()->transform()->get_position());
	}
	void ServerUpdate(float deltaTime,
		BasePlayer* ply) {
		FinalizeTick(deltaTime);
	}
}