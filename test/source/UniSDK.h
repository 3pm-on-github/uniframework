#ifndef UNISDK_H
#define UNISDK_H

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

int U_Initialize();

void U_LogsOn();

void U_Log(const char *text);

int U_InitSoc();

int U_InitCURL();

// Calls a GET request and writes to download_buffer.
int U_GET(const char *url);

// Calls a GET request and writes to the file location specified.
int U_GETFile(const char *url, const char *filename);

// Calls a POST request and writes to download_buffer.
int U_POST(const char *url, const char *body);

void U_ScanInput();

bool U_KeyDown(const char* key);

#endif