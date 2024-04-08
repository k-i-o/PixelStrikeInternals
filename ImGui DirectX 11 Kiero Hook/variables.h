#pragma once

//I recommend putting variables in sorted namespaces but for simplicity's sake I put them here like this.
bool debug = false;
bool tab = 0;
bool EnableNoRecoil = false;
bool EnableNoHipRecoil = false;
bool EnableFirerate = false;
bool isNoRecoilHooked = false;
bool isNoHipRecoilHooked = false;
bool isWeaponUpdateHooked = false;
float recoilValue = 0.0f;
float hipRecoilValue = 0.0f;
float firerate = 0.0f;

// Offsets
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");
// Avoid using long names, but be descriptive for the best looking code | In this case for the tutorial I'll have it be really descriptive.
uintptr_t setRecoilRVA = 0x276E490; 
uintptr_t setHipRecoilRVA = 0x276E534; 
uintptr_t updateNewWeaponRVA = 0x276E310;