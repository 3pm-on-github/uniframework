#include "../../win/uniframework.h"

int main() {
    U_Context ctx;
    U_BeginScreen(&ctx, "UniFramework Test", 800, 600);
    SDL_Delay(3000);
    U_Shutdown(&ctx);
    return 0;
}