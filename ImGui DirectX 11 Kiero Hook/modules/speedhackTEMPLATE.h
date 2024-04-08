/*
*  This is a functioning hook to change your speed in gum ball run incase you can't figure it out
*  Try creating the cheat without this.
*/
#pragma once
#include "../../includes.h"
#include "../../kiero/minhook/include/MinHook.h"
#include "../../il2cpp.h"
#include "../../variables.h"
#include "stdio.h"

typedef void(__fastcall* update_Orig)(void* __this, void* method);
update_Orig playerUpdate_Instance = nullptr;

//Creating the "replacement" function
void __fastcall playerCUpdateDetour(PlayerCharacter_o* __this, void* method) {
    if (isSpeedhack) {
        __this->fields.walkSpeed = speed;
        __this->fields.runSpeed = speed;
    }

    //Call the original function so it resumes/functions like normal.
    playerUpdate_Instance(__this, method);
}

void speedhack() {                                                                        /*   Put the rva below   */
    void* targetFunction = reinterpret_cast<void*>(reinterpret_cast<char*>(GameAssembly) + playerCharacterUpdateRVA);

    // Here we create the hook if it hasn't been created already.
    if (!isUpdateHooked) {
        if (MH_CreateHook(targetFunction, &playerCUpdateDetour, reinterpret_cast<void**>(&playerUpdate_Instance)) == MH_OK) {
            MH_EnableHook(targetFunction);
            printf("Hook for PlayerCharacter$$Update enabled successfully.\n");
            isUpdateHooked = true;
        }
        else {
            printf("Failed to create and enable the hook for PlayerCharacter$$Update.\n");
        }
    }
}
