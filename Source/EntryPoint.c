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

            i32 returnCode = DVRPL_Main(DVRPL_MAKE_APP_HANDLE(hInstance), args);
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

            i32 returnCode = DVRPL_Main((DVRPL_App) {0}, args);
            for (i32 i = 0; i < argc; i++) PNSLR_FreeString(args.data[i], PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
            PNSLR_FreeSlice(&args, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);

            return returnCode;
        }

    #endif

    #if PNSLR_ANDROID

        cstring* DVRPL_Internal_GetAndroidCmdLineArgs(i32* argc_out)
        {
            FILE* f = fopen("/proc/self/cmdline", "rb");
            if (!f) return NULL;

            cstring buf = NULL;
            size_t size = 0;
            ssize_t len = getdelim(&buf, &size, '\0', f); // reads until EOF
            fclose(f);

            if (len <= 0)
            {
                free(buf);
                return NULL;
            }

            // Count arguments
            i32 argc = 0;
            for (ssize_t i = 0; i < len; i++)
            {
                if (buf[i] == '\0')
                    argc++;
            }

            // Build argv
            cstring* argv = calloc((size_t) argc + 1, sizeof(cstring));
            i32 argi = 0;
            cstring p = buf;
            for (ssize_t i = 0; i < len; i++)
            {
                if (buf[i] == '\0')
                {
                    argv[argi++] = p;
                    p = &buf[i + 1];
                }
            }
            argv[argc] = NULL;

            *argc_out = argc;
            return argv;
        }

        void DVRPL_Internal_DisposeAndroidCmdLineArgs(cstring* argv)
        {
            if (argv)
            {
                free(argv[0]); // the buffer
                free(argv);    // the array
            }
        }

        void android_main(struct android_app* app)
        {
            i32 argc; cstring* argv;
            argv = DVRPL_Internal_GetAndroidCmdLineArgs(&argc);

            PNSLR_ArraySlice(utf8str) args = PNSLR_MakeSlice(utf8str, argc, false, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
            if (!args.data || !args.count) return;

            for (i32 i = 0; i < argc; ++i)
            {
                args.data[i] = PNSLR_StringFromCString(argv[i]);
                if (!args.data[i].data || !args.data[i].count) return;
            }

            DVRPL_Internal_FlushEventsTillInFocus();
            i32 returnCode = DVRPL_Main(DVRPL_MAKE_APP_HANDLE(app), args);

            __android_log_print(ANDROID_LOG_INFO, "Dvaarpaal", "Exiting with code %d", returnCode);

            for (i32 i = 0; i < argc; i++) PNSLR_FreeString(args.data[i], PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);
            PNSLR_FreeSlice(&args, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);

            DVRPL_Internal_DisposeAndroidCmdLineArgs(argv);
            ANativeActivity_finish(app->activity);
        }

    #endif

#endif
