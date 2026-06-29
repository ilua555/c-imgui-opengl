#define WIN32_LEAN_AND_MEAN
#include <windows.h>
import main;
import panic_close;





BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        DisableThreadLibraryCalls(hModule);
        c_main::init(hModule)->StartThread();
        break;
    }
    case DLL_PROCESS_DETACH: {
        c_close::init()->close_for_detach(hModule);
        break;
    }

    }
    return TRUE;
}

