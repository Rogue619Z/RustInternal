class Magazine
{
public:
	CLASS("", "Magazine");

	int& contents()
	{
		__try
		{
			auto& ptr = *(int*)(this + 0x1C);
			return ptr;
		}
		__except (true)
		{
			printf("%s - Exception Occurred.", __FUNCTION__);
		}
		auto n = nullptr;
		return reinterpret_cast<int&>(n);
	}
	ItemDefinition* ammoType()
	{
		__try
		{
			return *(ItemDefinition**)(this + 0x20);
		}
		__except (true)
		{
			printf("%s - Exception Occurred.", __FUNCTION__);
		}
		return nullptr;
	}
	MEMBER(int, capacity);
	//MEMBER(ItemDefinition*, ammoType);
};