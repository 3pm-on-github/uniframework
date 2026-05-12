#include "UniSDK.h"

int main() {
    U_Initialize();
    U_LogsOn();
    U_Log("UniSDK Testing Application v0");
    U_Log("i want a chicken sandiwhc");
    U_Log("give me it");
    U_Log("im breaking out.");
    while (aptMainLoop()) {
        U_ScanInput();
        if (U_KeyDown("a")) {
            U_Log("stop pressing a");
        }
    }
    gfxExit();
    return 0;
}