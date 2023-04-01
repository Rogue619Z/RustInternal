auto Hooks::Enable() -> void
{
	Hooks::OnGUIhk.InitialiseHook("UnityEngine", "DDraw", "OnGUI", &Hooks::OnGUI);
	Hooks::ClientInputhk.InitialiseHook("", "BasePlayer", "ClientInput", &Hooks::ClientInput); /* Loads and hooks the hooks*/
	Hooks::ClientMovementhk.InitialiseHook("", "PlayerWalkMovement", "ClientInput", &Hooks::ClientMovement);

}