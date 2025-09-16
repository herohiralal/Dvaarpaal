#define DVRPL_IMPLEMENTATION
#include "EntryPoint.h"

#ifndef DVRPL_SKIP_ENTRY_PT

    #if PNSLR_WINDOWS

        int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
        {
            int argc;
            WCHAR** argv = CommandLineToArgvW(pCmdLine, &argc);

            PNSLR_ArraySlice(utf8str) args = PNSLR_MakeSlice(utf8str, argc, false, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
            if (!args.data || !args.count) return -1;

            for (i32 i = 0; i < argc; i++)
            {
                WCHAR* arg = argv[i];
                i64    len = 0;
                while (arg[len] != L'\0') len++;
                args.data[i] = PNSLR_MakeString(len, false, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
                if (!args.data[i].data || !args.data[i].count) return -1;
            }

            LocalFree(argv);

            i32 returnCode = DVRPL_Main(args);
            for (i32 i = 0; i < argc; i++) PNSLR_FreeString(args.data[i], PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
            PNSLR_FreeSlice(&args, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);

            return returnCode;
        }

        BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
        {
            switch (fdwReason)
            {
                case DLL_PROCESS_ATTACH:
                case DLL_THREAD_ATTACH:
                case DLL_THREAD_DETACH:
                case DLL_PROCESS_DETACH:
                    break;
            }
            return TRUE; // Successful DLL_PROCESS_ATTACH.
        }

    #endif

    #if PNSLR_LINUX || PNSLR_OSX

        i32 main(i32 argc, cstring* argv)
        {
            PNSLR_ArraySlice(utf8str) args = PNSLR_MakeSlice(utf8str, argc, false, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
            if (!args.data || !args.count) return -1;

            for (i32 i = 0; i < argc; ++i)
            {
                args.data[i] = PNSLR_StringFromCString(argv[i]);
                if (!args.data[i].data || !args.data[i].count) return -1;
            }

            i32 returnCode = DVRPL_Main(args);
            for (i32 i = 0; i < argc; i++) PNSLR_FreeString(args.data[i], PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
            PNSLR_FreeSlice(&args, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);

            return returnCode;
        }

    #endif

#endif
