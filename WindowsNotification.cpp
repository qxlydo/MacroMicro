#include "WindowsNotification.h"

#ifdef Q_OS_WIN

#include <windows.h>

void showWindowsNotification(
    const QString& title,
    const QString& message)
{
    MessageBoxW(
        nullptr,
        message.toStdWString().c_str(),
        title.toStdWString().c_str(),
        MB_OK | MB_ICONINFORMATION
        );
}

#else

void showWindowsNotification(
    const QString&,
    const QString&)
{
}

#endif
