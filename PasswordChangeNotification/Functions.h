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

// ��������� ���� ��������� ����� �������� ������ �������� ������������.
// ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
int GetPasswordExpirationDate(SYSTEMTIME *expirationDate);

// ���������� ������� ����� ����� ������ � ������.
int GetSystemTimeDifferenceInDays(SYSTEMTIME date1, SYSTEMTIME date2);

// ������ ��������� ��������� ������, �������� 2 ������������� ���������.
// ��� ������ �������� ���������� - 0.
void ParseCommandLine(int *arg1, int *arg2);
