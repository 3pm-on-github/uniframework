#include "../src/uniframework.h"

U_RGBA red = {255, 0, 0, 255};
U_RGBA green = {0, 255, 0, 255};
U_RGBA blue = {0, 0, 255, 255};
U_RGBA orange = {255, 165, 0, 255};

void DrawPixelTest(U_Context* ctx) {
    U_DrawPixel(ctx, 0, 100, red);
    U_DrawPixel(ctx, 100, 100, green);
    U_DrawPixel(ctx, 200, 100, blue);
    U_DrawPixel(ctx, 300, 100, orange);
}

void DrawRectTest(U_Context* ctx) {
    U_DrawRect(ctx, 0, 0, 100, 100, red);
    U_DrawRect(ctx, 100, 0, 100, 100, green);
    U_DrawRect(ctx, 200, 0, 100, 100, blue);
    U_DrawRect(ctx, 300, 0, 100, 100, orange);
}

void DrawTextTest(U_Context* ctx) {
    U_DrawText(ctx, 0, 150, "This orange text is normal.", orange);
    U_SetFont(ctx, "assets/defaultFont.otf", 48);
    U_DrawText(ctx, 0, 200, "This red text is LARGE!", red);
    U_SetFont(ctx, "assets/defaultFont.otf", 8);
    U_DrawText(ctx, 0, 250, "and this green text is tiny!", green);
}

int main() {
    U_Context ctx;
    U_BeginScreen(&ctx, "UniFramework Test", 1280, 720);
    U_ClearScreen(&ctx);
    U_SetFont(&ctx, "assets/defaultFont.otf", 24);
    
    DrawPixelTest(&ctx);
    DrawRectTest(&ctx);
    DrawTextTest(&ctx);
    
    U_PresentScreen(&ctx);

    U_Delay(3000);
    U_Exit(&ctx);
    return 0;
}