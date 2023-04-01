class UString
{
public:
	CLASS("System", "String");
public:
	char zpad[0x10]{ };
	int size{ };
	wchar_t buffer[128 + 1];


	static UString* New(const char* str)
	{
		static auto il2cpp_object_new = reinterpret_cast<UString * (*)(const char*)>(Crt::il2cpp_export("il2cpp_string_new"));
		return il2cpp_object_new(str);
	}
	//static UString* New(const char* str) {
	//	__try {


	//		return CallFunction<UString*, const char*>("il2cpp_string_new", str);
	//	}
	//	__except (1) { return 0; };
	//}
public:
	UString(const wchar_t* st)
	{
		size = Mathf::Min(Crt::wcslen(st), 128);
		for (int idx = 0; idx < size; idx++)
		{
			buffer[idx] = st[idx];
		}
		buffer[size] = 0;
	}

};