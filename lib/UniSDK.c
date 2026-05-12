#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <citro2d.h>
#include <malloc.h>
#include <opusfile.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>

#include <3ds/applets/swkbd.h>

#include <3ds/types.h>
#include <3ds/services/cfgu.h>

#include <curl/curl.h>

bool log = false;
char download_buffer[1024*1024];
size_t total_bytes = 0;

int U_Initialize() {
    fsInit();
	romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
}

void U_LogsOn() {
    consoleInit(GFX_TOP, NULL);
    log = true;
}

void U_Log(const char *text) {
    if (!log) {
        return;
    }
    printf("[Log] %s", text);
}


int U_InitSoc() {
    u32 *soc_buffer = memalign(0x1000, 0x100000);
    if (!soc_buffer) {
        return -1;
    }
    if (socInit(soc_buffer, 0x100000) != 0) {
        return -2;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return -3;
    }
}

int U_InitCURL() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    if (total_bytes + realsize >= 1024*1024) return 0;

    memcpy(&download_buffer[total_bytes], ptr, realsize);
    total_bytes += realsize;
    return realsize;
}

int U_GET(const char *url) {
    CURL *curl = curl_easy_init();
    if (!curl) return -1;

    total_bytes = 0;
    memset(download_buffer, 0, 1024*1024);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? total_bytes : -1;
}

int U_GETFile(const char *url, const char *filename) {
    CURL *curl = curl_easy_init();
    if (!curl) return -1;

    FILE *file = fopen(filename, "wb");
    if (!file) return -1;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    CURLcode res = curl_easy_perform(curl);
    fclose(file);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? 0 : -1;
}

int U_POST(const char *url, const char *body) {
    CURL *curl = curl_easy_init();
    if (!curl) return -1;

    total_bytes = 0;
    memset(download_buffer, 0, 1024*1024);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? total_bytes : -1;
}