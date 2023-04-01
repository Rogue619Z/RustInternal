#pragma warning ( disable : 4172 )
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <memory.h>
#include <map>
#include <mutex>
#include <vector>
#include <atomic>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <unordered_map>	
#include <codecvt>


#define LOG( format, ... ) printf( ("[ DEBUG [] ] " format "\n"), ##__VA_ARGS__ );


//#include "Dependencies/MinHook/include/minhook.h"
#include "Dependencies/Vector/Vector.hpp"
#include "Dependencies/Il2cpp/IMPORTER/Importer.hpp"
#include "Dependencies/Il2cpp/PATTERN/Pattern.hpp"
#include "Dependencies/Il2cpp/Il2CPPSDK.hpp"

#include "Rust/SDK/Classes/Unity/Mathf.hpp"

#include "Dependencies/Misc/List.hpp"
#include "Dependencies/Misc/Variables.hpp"

#include "Dependencies/String/String.hpp"

#include "Rust/SDK/Enums/Enums.hpp"
#include "Rust/SDK/Enums/Structs/Structs.hpp"

class DDraw;
class Event;
class Screen;
class GUIStyle;
class Camera;
class ItemDefinition;
class GUI;
class Time;
class Physics;
class AimConeUtil;
class MainMenuSystem;
class BaseProjectile;
class Projectile;
class Transform;
class Component;
class HitTest;
class GUIContent;
class Shader;
class Model;
class BaseNetworkable;
class TerrainMeta;
class Material;
class GL;
class Terrain;
class PlayerWalkMovement;
class TerrainHeightMap;
class PlayerTick;
class TerrainCollision;
class Texture2D;
class Input;
class PlayerEyes;
class BaseMovement;
class RigidBody;
class GameObject;
class Item;
class ItemContainer;
class BaseEntity;
class AttackEntity;
class Magazine;
class GamePhysics;
class WaterLevel;
class BaseCombatEntity;
class Cursor;
class PlayerModel;
class ModelState;
class LocalPlayer;
class PlayerInventory;
class Graphics;
class BasePlayer;
class ProjectileWeaponMod;
class ExplosionsFPS;

std::uint64_t game_module = 0;
GUIStyle* guiStyle;
GUIStyle* skins;
GUIStyle* label_style;

Vector3 m_manipulate = Vector3(0, 0, 0);
Vector2 screen_size = Vector2::Zero();
Vector2 screen_center = Vector2::Zero();

bool inithooks = true;

class Bounds {
public:
	Vector3 m_center;
	Vector3 m_extents;
	Vector3 center;
	Vector3 extents;
	Vector3 max;
	Vector3 min;
	Vector3 size;
};

#include "Rust/SDK/Classes/Unity/Event.hpp"
#include "Rust/SDK/Classes/Unity/DDraw.hpp"
#include "Rust/SDK/Classes/Unity/Screen.hpp"
#include "Rust/SDK/Classes/Unity/Camera.hpp"
#include "Rust/SDK/Classes/Unity/GUI.hpp"
#include "Rust/SDK/Classes/Unity/Input.hpp"
#include "Rust/SDK/Classes/Unity/GUIContent.hpp"
#include "Rust/SDK/Classes/Unity/GUIStyle.hpp"
#include "Rust/SDK/Classes/Unity/Material.hpp"
#include "Rust/SDK/Classes/Unity/Shader.hpp"
#include "Rust/SDK/Classes/Unity/GL.hpp"
#include "Rust/SDK/Classes/Unity/Texture2D.hpp"
#include "Rust/SDK/Classes/Unity/Cursor.hpp"
#include "Rust/SDK/Classes/Unity/Physics.hpp"
#include "Rust/SDK/Classes/Unity/Time.hpp"

#include "Rust/SDK/Classes/Unity/Transform.hpp"
#include "Rust/SDK/Classes/Unity/Component.hpp"
#include "Rust/SDK/Classes/MainMenuSystem.hpp"
#include "Rust/SDK/Classes/ExplosionsFPS.hpp"
#include "Rust/SDK/Classes/TerrainHeightMap.hpp"
#include "Rust/SDK/Classes/Terrain.hpp"
#include "Rust/SDK/Classes/TerrainCollision.hpp"
#include "Rust/SDK/Classes/TerrainMeta.hpp"

#include "Rust/SDK/Classes/PlayerEyes.hpp"
#include "Rust/SDK/Classes/Model.hpp"
#include "Rust/SDK/Classes/BaseNetworkable.hpp"
#include "Rust/SDK/Classes/BaseMovement.hpp"
#include "Rust/SDK/Classes/RigidBody.hpp"
#include "Rust/SDK/Classes/PlayerTick.hpp"
#include "Rust/SDK/Classes/PlayerWalkMovement.hpp"
#include "Rust/SDK/Classes/ModelState.hpp"
#include "Rust/SDK/Classes/BaseEntity.hpp"
#include "Rust/SDK/Classes/ProjectileWeaponMod.hpp"
#include "Rust/SDK/Classes/HitTest.hpp"
#include "Rust/SDK/Classes/AimConeUtil.hpp"
#include "Rust/SDK/Classes/AttackEntity.hpp"
#include "Rust/SDK/Classes/Magazine.hpp"
#include "Rust/SDK/Classes/PlayerProjectileUpdate.hpp"
#include "Rust/SDK/Classes/Projectile.hpp"
#include "Rust/SDK/Classes/BaseProjectile.hpp"
#include "Rust/SDK/Classes/ItemDefinition.hpp"
#include "Rust/SDK/Classes/Item.hpp"
#include "Rust/SDK/Classes/GameObject.hpp"
#include "Rust/SDK/Classes/Graphics.hpp"
#include "Rust/SDK/Classes/ItemContainer.hpp"
#include "Rust/SDK/Classes/BaseCombatEntity.hpp"
#include "Rust/SDK/Classes/PlayerModel.hpp"
#include "Rust/SDK/Classes/PlayerInventory.hpp"
#include "Rust/SDK/Classes/BasePlayer.hpp"
#include "Rust/SDK/Classes/LocalPlayer.hpp"
#include "Rust/SDK/Classes/WaterLevel.hpp"
#include "Rust/SDK/Classes/GamePhysics.hpp"

#include "Rust/SDK/Function/Hooks/Client/AimUtils/AntiHack/projectile.hpp"

#include "Rust/SDK/Function/Features/Drawing/Drawing.hpp"


#include "Rust/SDK/Hooking/Hooks.hpp"
#include "Rust/SDK/Hooking/LoadHooks.hpp"

#include "Rust/SDK/Function/Hooks/Client/AimUtils/AntiHack/Antihack.hpp"

#include "Rust/SDK/Function/Hooks/Client/AimUtils/Prediction.hpp"
#include "Rust/SDK/Function/Hooks/Client/AimUtils/Manipulation.hpp"

#include "Rust/SDK/Function/Hooks/Client/AimUtils/ServerRPCProjectileShoot.hpp"
#include "Rust/SDK/Function/Hooks/Client/PerformanceUpdate.hpp"
#include "Rust/SDK/Function/Hooks/Client/MainMenuSystem.hpp"
#include "Rust/SDK/Function/Hooks/Client/ClientInput.hpp"
#include "Rust/SDK/Function/Hooks/Client/ClientMovement.hpp"
#include "Rust/SDK/Function/Hooks/Client/OnGUI.hpp"