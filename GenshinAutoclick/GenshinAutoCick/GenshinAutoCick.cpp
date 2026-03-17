// AutoClickGenshin.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

// This is our "Callback" function - Windows calls this for every window it finds
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    // Only look at windows that are actually visible to the user
    if (IsWindowVisible(hwnd)) {
        int length = GetWindowTextLength(hwnd);
        if (length > 0) {
            std::vector<char> buffer(length + 1);
            GetWindowTextA(hwnd, buffer.data(), length + 1);
            std::string title(buffer.data());
            std::cout << "Window Title: " << title << std::endl;
            if (title.find("Genshin Impact") != std::string::npos) {
                HWND* lGenshinWindow = (HWND*)lParam;
                *lGenshinWindow = hwnd; // Store the handle of the Genshin Impact window
                return FALSE; // Return the title if it contains "Genshin Impact"
            }
        }
    }
    return TRUE; // Continue to the next window
}

int main() {
    std::cout << "Listing all active window titles:" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    // Start the enumeration
    HWND GenshinWindow = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&GenshinWindow);
    bool isActive = false; // Variable to track the active state of the autoclick
    if (GenshinWindow != NULL)
    {
        std::cout << "Genshin Impact window found!" << std::endl;
        while (true)
        {
            HWND currentWindow = GetForegroundWindow();
            if (GetAsyncKeyState(VK_F9) & 0x8000)
            {
                isActive = !isActive; // Toggle the active state
                std::cout << "Status: " << (isActive ? "ON" : "OFF") << std::endl;
                // Mission A: "Debounce" - Wait until the user lets go of F9
                while (GetAsyncKeyState(VK_F9) & 0x8000) {

                    Sleep(10);
                }
            }
            if (currentWindow == GenshinWindow)
            {
                std::cout << "Genshin is focused" << std::endl;
                if (isActive)
                { // Check if F1 
                    std::cout << "F" << std::endl;
                    // Simulate a keystroke (e.g., press 'F')
                    INPUT input = { 0 };
                    input.type = INPUT_KEYBOARD;
                    input.ki.wVk = 'F'; // Virtual-key code for 'F'
                    SendInput(1, &input, sizeof(INPUT));
                    // Simulate key release
                    input.ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(1, &input, sizeof(INPUT));

                }
            }
            Sleep(50); // Sleep for a short time to prevent high CPU usage 
        }
    }
    else {
        std::cout << "Genshin Impact window not found." << std::endl;
        system("pause");
        return 0;
    }
    return 0;
}