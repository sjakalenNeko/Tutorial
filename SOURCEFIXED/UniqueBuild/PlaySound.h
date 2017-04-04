#pragma once

#include "Main.h"

using PlaySoundFn = void(__stdcall*)(const char*);
extern PlaySoundFn oPlaySound;

void __stdcall PlaySoundHook(const char* pSample);