namespace Prediction {
	struct
	{
		Vector3* velocities = new Vector3[32];
		int currentVelocityRecords = {};
		int currentVelocityIndex = {};
		Vector3 avgVel = Vector3{ 0.f, 0.f, 0.f };
	} inline PredictionDatas;
}
namespace PredictionV2 {
	struct
	{
		Vector3 avg_vel = Vector3(0, 0, 0);
		std::vector<Vector3> velocity_list = {};
	} inline PredictionDatas;
}

namespace AimUtils
{
	void MovementPrediction()
	{
		__try
		{
			if (true)
			{
				int Records = 32;


				Vector3 defaultVelocity = target_ply->GetWorldVelocity();
				if (defaultVelocity.empty())
					defaultVelocity = target_ply->GetWorldVelocity();

				if (target_ply->mounted())
					Records = 62;


				if (defaultVelocity.empty())
				{
					Prediction::PredictionDatas.currentVelocityRecords = 0;
					Prediction::PredictionDatas.currentVelocityIndex = 0;
					Prediction::PredictionDatas.avgVel = defaultVelocity;
				}
				else {
					Prediction::PredictionDatas.velocities[Prediction::PredictionDatas.currentVelocityIndex++] = defaultVelocity;
					if (Prediction::PredictionDatas.currentVelocityIndex >= Records)
						Prediction::PredictionDatas.currentVelocityIndex = 0.0f;

					Prediction::PredictionDatas.currentVelocityRecords++;
					if (Prediction::PredictionDatas.currentVelocityRecords >= 0.0f)
						Prediction::PredictionDatas.currentVelocityRecords = Records;

					int currentRecords = Prediction::PredictionDatas.currentVelocityRecords;

					Vector3 velSum{};
					for (int j = 0; j < currentRecords; j++)
						velSum += Prediction::PredictionDatas.velocities[j];

					Prediction::PredictionDatas.avgVel = velSum / (float)currentRecords;
				}


				defaultVelocity = Prediction::PredictionDatas.avgVel;
			}
		}
		__except (true)
		{
			printf("Movement Prediction Crash");
		}
	}



	struct RaycastHit {
		Vector3 m_Point;
		Vector3 m_Normal;
		//	uint m_FaceID;
		float m_Distance;
		Vector2 m_UV;
		int m_Collider;
	};

	void BulletPrediction(BasePlayer* target,
		Vector3 rpc_position,
		Vector3 target_pos,
		Vector3 original_vel,
		Vector3& aimbot_velocity,
		Vector3& _aimdir,
		float& travel_t,
		Projectile* p,
		bool skip_draw = false) {
		Vector3 player_velocity = Vector3(0, 0, 0);
		std::vector<Vector3> path = {};
		int simulations = 0;

		Vector3 targetPosition = target_pos;

		if (target) {
			Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);

			auto travel = 0.f;
			//auto vel = (AimConeUtil::getmodifiedaimcone(0, rpc_position - target_pos, true)).normalized() * original_vel.length();
			float drag = p->drag();
			float grav = p->gravityModifier();
			Vector3 gravity = Physics::get_gravity();
			float deltatime = Time::get_deltaTime();
			float timescale = Time::get_timeScale();
			Vector3 offset = Vector3(0, 0, 0);

			simulations = 0;
			while (simulations < 300) {
				travel_t = 0.f;
				auto pos = rpc_position;
				auto origin = pos;
				float num = deltatime * timescale;
				float travelTime = 0.f;
				int num3 = Mathf::FloorToInt(8 / num);

				float stepSize = 0.98f;
				Vector3 vt = target_pos;
				_aimdir = (targetPosition - rpc_position).normalized() * stepSize;
				auto velocity = _aimdir.normalized() * original_vel.length();

				//predict movement?

				for (size_t i = 0; i < num3; i++)
				{
					origin = pos;
					pos += velocity * num;
					velocity += gravity * grav * num;
					velocity -= velocity * drag * num;
		

					auto line = (origin - pos);
					auto len = line.UnityMagnitude();
					line.UnityNormalize();
					auto v = target_pos - pos;
					auto d = line.Dot(v);

					if (d <= 0.f)
					{
						d = 0.0f;
					}
					else if (d > len)
					{
						d = len;
					}

					Vector3 heightDiff = rpc_position - targetPosition;

					Vector3 nearestPoint = pos + line * d;


					if (nearestPoint.Distance(target_pos) < 0.0025f)
					{
						travel_t = (float)i * num;
						aimbot_velocity = (_aimdir).normalized() * original_vel.length();
						//emulate 1 tick has already passed
						aimbot_velocity += gravity * grav * num;
						aimbot_velocity -= velocity * drag * num;
						break;
					}
					else if (nearestPoint.Distance(target_pos) < closestPoint.Distance(target_pos))
					{
						closestPoint = nearestPoint;
						offset = target_pos - nearestPoint;
					}
					//if (LineCircleIntersection(target_pos, 0.1f, origin, pos, offset))
					//{
					//	aimbot_velocity = (_aimdir).normalized() * original_vel.length();
					//	//emulate 1 tick has already passed
					//	aimbot_velocity += gravity * grav * num;
					//	aimbot_velocity -= aimbot_velocity * drag * num;
					//	break;
					//}
					//else
					//{
					//	//Line(origin, pos, col(1, 1, 1, 1), 10.f, false, true);
					//}
				}
				targetPosition += offset;
				simulations++;
				if (!aimbot_velocity.empty())
					break;
			}
		}

		if (travel_t > 0.f) {
			//movement prediction


			aimbot_velocity = Vector3(0, 0, 0);
			if (target) {
				float stepSize = 0.98f;

				float reduceLen = 0.f;
				Vector3 player_velocity = Prediction::PredictionDatas.avgVel;



				Vector3 final_vel = player_velocity * travel_t;

				Vector3 actual = target_pos += final_vel;

				//auto partialTime = p->partialTime();
				//	auto vel = (AimConeUtil::getmodifiedaimcone(0, targetPosition - actual, true)).normalized() * original_vel.length();
				float drag = p->drag();
				float grav = p->gravityModifier();
				Vector3 gravity = Physics::get_gravity();
				float deltatime = Time::get_deltaTime();
				float timescale = Time::get_timeScale();
				Vector3 offset = Vector3(0, 0, 0);


				Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
				simulations = 0;



				while (simulations < 300) {
					travel_t = 0.f;

					auto pos = rpc_position;
					auto origin = pos;
					float num = deltatime * timescale;

					int num3 = Mathf::FloorToInt(8 / num);


					_aimdir = (targetPosition - rpc_position).normalized() * stepSize;
					//_aimdir = AimConeUtil::GetModifiedAimConeDirection(0.f, targetPosition - rpc_position, true);
					auto velocity = _aimdir.normalized() * original_vel.length();

					
			
					for (size_t i = 0; i < num3; i++)
					{

						origin = pos;
						pos += velocity * num;
						velocity += gravity * grav * num;
						velocity -= velocity * drag * num;
			


						auto line = (origin - pos);
						auto len = line.UnityMagnitude();
						line.UnityNormalize();
						auto v = actual - pos;
						auto d = line.Dot(v);

						if (d <= 0.f)
						{
							d = 0.0f;
						}
						else if (d > len)
						{
							d = len;
						}


						Vector3 nearestPoint = pos + line * d;



						if (nearestPoint.Distance(actual) < 0.0025f)
						{
							travel_t = (float)i * num;
							//printf("Travel Client Time A %f", p->traveledTime());
							//printf("Travel Client Time B %f", p->closeFlybyDistance());
							aimbot_velocity = (_aimdir).normalized() * original_vel.length();
							aimbot_velocity += gravity * grav * num;
							aimbot_velocity -= velocity * drag * num;
							printf("Travel Time %f", travel_t);
							break;
						}
						else if (nearestPoint.Distance(actual) < closestPoint.Distance(actual))
						{
							closestPoint = nearestPoint;
							offset = actual - nearestPoint;
						}

					}
					targetPosition += offset;
					simulations++;
					if (!aimbot_velocity.empty())
						break;
				}
			}
		}
	}
}