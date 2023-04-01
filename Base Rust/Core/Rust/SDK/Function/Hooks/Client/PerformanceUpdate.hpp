
//
//auto Hooks::PerformanceUpdate(void* instance) -> void
//{
//	if (!instance)
//		return;
//
//	if (Input::GetKey(Enums::KeyCode::Home))
//		inithooks = false;
//
//	if (Input::GetKey(Enums::KeyCode::Insert))
//		inithooks = true;
//
//	//Hooks::PerformanceUpdatehk.get_original<decltype(&PerformanceUpdate)>()(instance); /* Don't return this or hook wont work */ 
//}