#pragma once

#pragma comment(lib, "Secur32.lib")
#pragma comment(lib, "ADSIid.lib")
#pragma comment(lib, "Activeds.lib")

#define SECURITY_WIN32

#include <Windows.h>
#include <Security.h>
#include <Iads.h>
#include <OaIdl.h>
#include <objbase.h>
#include <Adshlp.h>

// ѕолучение даты истечени€ срока действи€ парол€ текущего пользовател€.
// ѕри успешном завершении возвращает 0, при ошибке - код ошибки.
int GetPasswordExpirationDate(SYSTEMTIME *expirationDate);

// ¬озвращает разницу между двум€ датами в сутках.
int GetSystemTimeDifferenceInDays(SYSTEMTIME date1, SYSTEMTIME date2);

// ѕарсит аргументы командной строки, получает 2 целочисленных аргумента.
// ѕри ошибке значени€ аргументов - 0.
void ParseCommandLine(int *arg1, int *arg2);
