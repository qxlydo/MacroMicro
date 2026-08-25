#include "MegaByteFinder.h"
#include <QApplication>
#include <QDebug>
#include <QStyle>
#include <algorithm>
#include <system_error>

MMEngine::MMEngine(QObject* parent)
    : QObject(parent)
{
    m_trayIcon = new QSystemTrayIcon(this);

    // Задаем стандартную системную иконку (или вашу собственную),
    // так как без иконки уведомления в Windows могут не показываться
    m_trayIcon->setIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon));
    m_trayIcon->show();

}

void MMEngine::showNotification(const QString& title, const QString& message)
{
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        m_trayIcon->showMessage(
            title,
            message,
            QSystemTrayIcon::Information,
            3000 // Длительность показа в мс
            );
    }
}

QVariantList MMEngine::disksList() const
{
    return m_disksList;
}

QVariantList MMEngine::filesList() const
{
    return m_filesList;
}

QString MMEngine::currentPath() const
{
    return m_currentPath;
}

QString MMEngine::status() const
{
    return m_status;
}

void MMEngine::setCurrentPath(const QString& path)
{
    if (m_currentPath != path) {
        m_currentPath = path;
        emit currentPathChanged();
    }
}

// ============================================================
// Поиск
// ============================================================

void MMEngine::scanDirectory(const QUrl& dirUrl)
{
    const QString dirPath = dirUrl.toLocalFile();

    if (dirPath.isEmpty()) {
        emit error("Не удалось получить путь к выбранной папке.");
        return;
    }

    const path p(dirPath.toStdWString());

    std::error_code ec;

    if (!exists(p, ec) || ec) {
        emit error("Папка не существует:\n" + dirPath);
        return;
    }

    if (!is_directory(p, ec) || ec) {
        emit error("Выбранный путь не является директорией:\n" + dirPath);
        return;
    }

    // Очистка и установка статуса происходят в GUI-потоке перед запуском
    MD.clear();
    updateFilesList();

    setCurrentPath(dirPath);

    m_status = "Сканирование: " + dirPath;
    emit statusChanged();

    emit scanStarted();

    // Запуск фонового асинхронного сканирования
    QtConcurrent::run([this, p, dirPath]() {
        processScan(p, dirPath);
    });
}

void MMEngine::processScan(const path& p, const QString& dirPath)
{
    YesOrNot(p);
    IterForDir(p);

    QMetaObject::invokeMethod(this, [this]() {
        updateFilesList();

        const QString message = "Найдено файлов: " + QString::number(MD.size());
        m_status = "Готово. " + message;

        emit statusChanged();
        emit scanFinished();

        // Показываем системное всплывающее уведомление
        showNotification("Сканирование завершено", message);
    });
}
// ============================================================
// Диски
// ============================================================

void MMEngine::refreshDisks()
{
    const int count = getAvailableDisks();

    updateDisksList();

    m_status = "Дисков найдено: " + QString::number(count);
    emit statusChanged();
}

// ============================================================
// Ручное добавление файла
// ============================================================

void MMEngine::addFile(const QString& name, qint64 size)
{
    addToList(MD, name, size);
    updateFilesList();
}

// ============================================================
// Очистка
// ============================================================

void MMEngine::clearFiles()
{
    MD.clear();
    updateFilesList();

    m_status = "Список очищен";
    emit statusChanged();
}

// ============================================================
// Конвертация данных для QML
// ============================================================

void MMEngine::updateFilesList()
{
    m_filesList.clear();

    for (const auto& meta : MD) {
        QVariantMap item;

        item["name"] = meta.nameFile;
        item["size"] = meta.sizeFile;

        m_filesList.append(item);
    }

    emit filesListChanged();
}

void MMEngine::updateDisksList()
{
    m_disksList.clear();

    for (const auto& disk : listDisks) {
        QVariantMap item;

        item["letter"] = disk.diskLetter;
        item["label"] = disk.typeDisk;

        m_disksList.append(item);
    }

    emit disksListChanged();
}

// ============================================================
// Добавление MetaData
// ============================================================

void MMEngine::addToList(std::vector<MetaData>& md,
                         const QString& newNameFile,
                         qint64 newSizeFile)
{
    md.emplace_back(newNameFile, newSizeFile);
}

// ============================================================
// Сортировка по размеру
// ============================================================

void MMEngine::getData()
{
    std::sort(
        MD.begin(),
        MD.end(),
        [](const MetaData& a, const MetaData& b) {
            return a.sizeFile > b.sizeFile;
        }
        );
}

// ============================================================
// Получение доступных дисков Windows
// ============================================================

int MMEngine::getAvailableDisks()
{
    listDisks.clear();

    const DWORD drivesMask = GetLogicalDrives();

    if (drivesMask == 0) {
        return 0;
    }

    for (int i = 0; i < 26; ++i) {
        if (!(drivesMask & (1u << i))) {
            continue;
        }

        const char driveLetter = static_cast<char>('A' + i);
        const std::string drivePath =
            std::string(1, driveLetter) + ":\\";

        const UINT driveType = GetDriveTypeA(drivePath.c_str());

        switch (driveType) {
        case DRIVE_UNKNOWN:
            typeDiskStr = "Неизвестный тип диска";
            break;

        case DRIVE_NO_ROOT_DIR:
            typeDiskStr = "Неверный путь";
            break;

        case DRIVE_REMOVABLE:
            typeDiskStr = "Съёмный диск";
            break;

        case DRIVE_FIXED:
            typeDiskStr = "Фиксированный диск";
            break;

        case DRIVE_REMOTE:
            typeDiskStr = "Сетевой диск";
            break;

        case DRIVE_CDROM:
            typeDiskStr = "CD/DVD-ROM";
            break;

        case DRIVE_RAMDISK:
            typeDiskStr = "RAM-диск";
            break;

        default:
            typeDiskStr = "Неизвестный тип";
            break;
        }

        Disk disk;
        disk.diskLetter =
            QString("%1:\\").arg(QChar(driveLetter));
        disk.typeDisk =
            QString::fromStdString(typeDiskStr);

        listDisks.push_back(disk);
    }

    return static_cast<int>(listDisks.size());
}

// ============================================================
// Проверка директории
// ============================================================

void MMEngine::YesOrNot(const path& dirPath)
{
    std::error_code ec;

    if (!exists(dirPath, ec) || ec) {
        emit error("Директория недоступна.");
    }
}

// ============================================================
// Рекурсивный поиск файлов
// ============================================================

void MMEngine::IterForDir(const path& dirPath)
{
    std::error_code ec;

    recursive_directory_iterator it(
        dirPath,
        directory_options::skip_permission_denied,
        ec
        );

    if (ec) {
        emit error(
            "Не удалось открыть директорию:\n" +
            QString::fromStdWString(dirPath.wstring())
            );
        return;
    }

    const recursive_directory_iterator end;

    while (it != end) {
        const directory_entry& entry = *it;

        ec.clear();

        if (entry.is_regular_file(ec) && !ec) {
            const auto size = entry.file_size(ec);

            if (!ec) {
                const QString filePath =
                    QString::fromStdWString(entry.path().wstring());

                const qint64 fileSize =
                    static_cast<qint64>(size);

                // Храним реальный размер в байтах.
                addToList(MD, filePath, fileSize);

                // Сообщаем QML сразу после нахождения файла.
                emit fileFound(filePath, fileSize);
            }
        }

        ec.clear();
        it.increment(ec);

        if (ec) {
            // Например, нет доступа к следующей директории.
            // Просто продолжаем сканирование остальных файлов.
            ec.clear();
        }
    }
}
