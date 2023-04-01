class Event
{
public:
	CLASS("UnityEngine", "Event");


	static auto current() -> Event*
	{
		METHOD(Event*(**)(), get_current);
		return get_current();
	}

	auto type() -> Enums::EventType
	{
		if (!this) return Enums::EventType();
		METHOD(Enums::EventType(**)(Event*), get_type);
		return get_type(this);
	}
};