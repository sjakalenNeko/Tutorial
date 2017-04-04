#include "PlaySound.h"

PlaySoundFn oPlaySound;
void __stdcall PlaySoundHook(const char* pSample)
{
	static DWORD dwOrgPlaysound = g_phkPlaySound->dwGetMethodAddress(82);

	/*__asm
	{
		PUSH pSample;
		CALL dwOrgPlaysound;
	}*/

	oPlaySound(pSample);

	if (!g_pEngine->isinGame())
	{
		//ReadyCallbackFn fnAccept = (ReadyCallbackFn)PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x51\x56\x8B\x35\x00\x00\x00\x00\x80\x7E\x48\x00", "xxxxxxx????xxxx", NULL, NULL);
		using IsReadyFn = void(__cdecl*)();
		auto add = PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x08\x56\x8B\x35\x00\x00\x00\x00\x57\x8B\x4E\x00", "xxxxxxxxxxxx????xxx?", NULL, NULL);
		IsReadyFn fnAccept = (IsReadyFn)add;

		/*
			if (dword_12EDCA74)
			{
				*(_DWORD *)(this + 2380) = 1;
				(*(void (__stdcall **)(_DWORD))(*(_DWORD *)dword_14B5C7C8 + 328))("UI/menu_accept.wav");
				sub_10466100(); <- callback
			}
		*/

		if (!strcmp(pSample, "weapons/hegrenade/beep.wav"))
		{
			fnAccept();
		}
	}
}