float flyhackDistanceVertical = 0.0f;
float flyhackDistanceHorizontal = 0.0f;
float flyhackPauseTime = 0.0f;

float flyhack_forgiveness_vertical_inertia = 10.0f;
float flyhack_forgiveness_vertical = 1.5f;
float flyhack_forgiveness_horizontal_inertia = 10.0f;
float flyhack_forgiveness_horizontal = 1.5f;

float flyhack_stepsize = 0.1f;
int flyhack_maxsteps = 15;

float time_since_last_shot = 0.0f;
float fixed_time_last_shot = 0.0f;

bool just_shot = false;
bool did_reload = false;

//oat desyncTime = 0.03f;
float speedhackDistance = 0.f;
float speedhackPauseTime = 0.f;

float speedhack_slopespeed = 10.0f;
float speedhack_forgiveness_inertia = 10.0f;
float speedhack_forgiveness = 2.0f;
float speedhack_penalty = 0.0f;
bool speedhack_reject = true;

int HitScanBone = 48;
Vector3 FatHitPosition = {};
Vector3 RealGangstaShit = {};
bool CanMagicBoolet = false;