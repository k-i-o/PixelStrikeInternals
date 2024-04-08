#pragma once
#include "../includes.h"
#include "../kiero/minhook/include/MinHook.h"
#include "../il2cpp.h"
#include "../variables.h"
#include "stdio.h"

// UPDATE
typedef void(__fastcall* weaponUpdate_Orig)(void* __this, void* method);
weaponUpdate_Orig weaponUpdate_Instance = nullptr;

//Creating the "replacement" function
void __fastcall weaponUpdateDetour(NewWeapon_o* __this, void* method) {
    if (EnableFirerate) {
        __this->fields.fireRate = firerate;
    }
    if (EnableNoRecoil) {
        __this->fields.recoil = recoilValue;
    }
    if (EnableNoHipRecoil) {
        __this->fields.hipRecoil = hipRecoilValue;
    }

    //Call the original function so it resumes/functions like normal.
    weaponUpdate_Instance(__this, method);
}

void weaponUpdate() {                                                                        /*   Put the rva below   */
    void* targetFunction = reinterpret_cast<void*>(reinterpret_cast<char*>(GameAssembly) + updateNewWeaponRVA);

    // Here we create the hook if it hasn't been created already.
    if (!isWeaponUpdateHooked) {
        if (MH_CreateHook(targetFunction, &weaponUpdateDetour, reinterpret_cast<void**>(&weaponUpdate_Instance)) == MH_OK) {
            MH_EnableHook(targetFunction);
            printf("Hook for weaponUpdate enabled successfully.\n");
            isWeaponUpdateHooked = true;
        }
        else {
            printf("Failed to create and enable the hook for weaponUpdate.\n");
        }
    }
}


// SET RECOIL
typedef void(__fastcall* setRecoil_Orig)(void* __this, float recoil, void* method);
setRecoil_Orig setRecoil_Instance = nullptr;

//Creating the "replacement" function
void __fastcall setRecoilDetour(NewWeapon_o* __this, float recoil, void* method) {
    if (EnableNoRecoil) {
        recoil = recoilValue;
    }

    //Call the original function so it resumes/functions like normal.
    setRecoil_Instance(__this, recoil, method);
}

void noRecoil() {                                                                        /*   Put the rva below   */
    void* targetFunction = reinterpret_cast<void*>(reinterpret_cast<char*>(GameAssembly) + setRecoilRVA);

    // Here we create the hook if it hasn't been created already.
    if (!isNoRecoilHooked) {
        if (MH_CreateHook(targetFunction, &setRecoilDetour, reinterpret_cast<void**>(&setRecoil_Instance)) == MH_OK) {
            MH_EnableHook(targetFunction);
            printf("Hook for noRecoil enabled successfully.\n");
            isNoRecoilHooked = true;
        }
        else {
            printf("Failed to create and enable the hook for noRecoil.\n");
        }
    }
}


//SET HIP RECOIL

typedef void(__fastcall* setRecoil_Orig)(void* __this, float recoil, void* method);
setRecoil_Orig setHipRecoil_Instance = nullptr;

//Creating the "replacement" function
void __fastcall setHipRecoilDetour(NewWeapon_o* __this, float recoil, void* method) {
    if (EnableNoHipRecoil) {
        recoil = hipRecoilValue;
    }

    //Call the original function so it resumes/functions like normal.
    setHipRecoil_Instance(__this, recoil, method);
}

void noHipRecoil() {                                                                        /*   Put the rva below   */
    void* targetFunction = reinterpret_cast<void*>(reinterpret_cast<char*>(GameAssembly) + setHipRecoilRVA);

    // Here we create the hook if it hasn't been created already.
    if (!isNoHipRecoilHooked) {
        if (MH_CreateHook(targetFunction, &setHipRecoilDetour, reinterpret_cast<void**>(&setHipRecoil_Instance)) == MH_OK) {
            MH_EnableHook(targetFunction);
            printf("Hook for noHipRecoil enabled successfully.\n");
            isNoHipRecoilHooked = true;
        }
        else {
            printf("Failed to create and enable the hook for noHipRecoil.\n");
        }
    }
}