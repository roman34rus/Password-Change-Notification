#include "Functions.h"

int GetPasswordExpirationDate(SYSTEMTIME *expirationDate)
{
	// Получаем FQDN текущего пользователя

	const int USER_FQDN_LENGTH = 1024;

	WCHAR userFqdn[USER_FQDN_LENGTH + 1];

	ULONG userFqdnLength = USER_FQDN_LENGTH;

	if (GetUserNameEx(NameFullyQualifiedDN, userFqdn, &userFqdnLength) == 0)
		return 1;

	// Получаем объект - пользователя AD по FQDN

	const int USER_LDAP_PATH_LENGTH = USER_FQDN_LENGTH + 7;

	WCHAR userLdapPath[USER_LDAP_PATH_LENGTH] = L"LDAP://";

	wcscat_s(userLdapPath, USER_LDAP_PATH_LENGTH, userFqdn);

	IADsUser *user;

	CoInitialize(NULL);

	HRESULT hr = ADsGetObject(userLdapPath, IID_IADsUser, (void**)&user);

	if (FAILED(hr))
		return 2;

	// Получаем дату истечения пароля пользователя

	DATE date;

	hr = user->get_PasswordExpirationDate(&date);

	if (FAILED(hr))
		return 3;

	// Конвертируем DATE в SYSTEMTIME

	VariantTimeToSystemTime(date, expirationDate);

	return 0;
}

int GetSystemTimeDifferenceInDays(SYSTEMTIME date1, SYSTEMTIME date2)
{
	FILETIME ft1, ft2;

	SystemTimeToFileTime(&date1, &ft1);
	SystemTimeToFileTime(&date2, &ft2);

	ULARGE_INTEGER ul1, ul2, ulDiff;

	ul1.LowPart = ft1.dwLowDateTime;
	ul1.HighPart = ft1.dwHighDateTime;
	
	ul2.LowPart = ft2.dwLowDateTime;
	ul2.HighPart = ft2.dwHighDateTime;

	ulDiff.QuadPart = (ul1.QuadPart - ul2.QuadPart) / 10000000 / 60 / 60 / 24;

	return (int)ulDiff.QuadPart;
}

void ParseCommandLine(int *arg1, int *arg2)
{
	LPWSTR *szArgList;

	int argCount;

	szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);

	if (argCount > 2)
	{
		*arg1 = _wtoi(szArgList[1]);
		*arg2 = _wtoi(szArgList[2]);
	}
	else
	{
		*arg1 = 0;
		*arg2 = 0;
	}
}