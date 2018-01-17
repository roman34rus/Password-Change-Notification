#include "Functions.h"
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       cmdShow)
{
	int daysForNotification = 0;
	int minutesBetweenNotifications = 0;

	ParseCommandLine(&daysForNotification, &minutesBetweenNotifications);

	if (daysForNotification == 0 || minutesBetweenNotifications == 0)
		return 1;

	DWORD sleepTimeoutMilliseconds = minutesBetweenNotifications * 60000;

	SYSTEMTIME passwordExpirationDate;

	if (GetPasswordExpirationDate(&passwordExpirationDate) != 0)
		return 2;

	while (true)
	{
		SYSTEMTIME currentDate;

		GetLocalTime(&currentDate);

		int daysBeforePasswordExpires = GetSystemTimeDifferenceInDays(passwordExpirationDate, currentDate);

		if (daysBeforePasswordExpires <= daysForNotification)
		{
			wchar_t *caption = L"Внимание!";
			
			wchar_t message[256];

			swprintf_s(message, L"Ваш пароль истекает через %d дней. Рекомендуется сменить пароль.", daysBeforePasswordExpires);

			MessageBox(NULL, (LPCWSTR)message, (LPCWSTR)caption, MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		}

		Sleep(sleepTimeoutMilliseconds);
	}

	return 0;
}