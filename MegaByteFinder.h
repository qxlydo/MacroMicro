#ifndef MEGABYTEFINDER_H
#define MEGABYTEFINDER_H

#include <filesystem>
#include <cstdint>
#include <string>
#include <vector>
#include <windows.h>

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QApplication>
#include <QString>
#include <QUrl>
#include <QtConcurrent/QtConcurrent>
#include <QSystemTrayIcon>
using namespace std::filesystem;

struct MetaData
{
    QString nameFile;
    qint64 sizeFile; // размер в байтах

    MetaData(const QString& name, qint64 size)
        : nameFile(name), sizeFile(size)
    {
    }
};

struct Disk
{
    QString diskLetter;
    QString typeDisk;
};

class MMEngine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList disksList READ disksList NOTIFY disksListChanged)
    Q_PROPERTY(QVariantList filesList READ filesList NOTIFY filesListChanged)
    Q_PROPERTY(QString currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)

public:
    explicit MMEngine(QObject* parent = nullptr);

    QVariantList disksList() const;
    QVariantList filesList() const;
    QString currentPath() const;
    QString status() const;

    void setCurrentPath(const QString& path);

    // Вызывается кнопкой "Начать поиск".
    // QML передаёт URL, который возвращает FolderDialog.
    Q_INVOKABLE void scanDirectory(const QUrl& dirUrl);

    Q_INVOKABLE void refreshDisks();

    Q_INVOKABLE void addFile(const QString& name, qint64 size);

    Q_INVOKABLE void clearFiles();

    Q_INVOKABLE void showNotification(const QString& title, const QString& message);

signals:
    void disksListChanged();
    void filesListChanged();
    void currentPathChanged();
    void statusChanged();

    void scanStarted();
    void scanFinished();
    void error(const QString& msg);

    // Отправляется в QML для каждой найденной директории.
    // size — размер файла в байтах.
    void fileFound(const QString& path, qint64 size);

private:
    void processScan(const path& p, const QString& dirPath);
    void YesOrNot(const path& dirPath);
    void IterForDir(const path& dirPath);

    void addToList(std::vector<MetaData>& md,
                   const QString& newNameFile,
                   qint64 newSizeFile);

    void getData();
    int getAvailableDisks();

    void updateFilesList();
    void updateDisksList();

private:
    std::vector<MetaData> MD;
    std::vector<Disk> listDisks;
    std::string typeDiskStr;

    QVariantList m_disksList;
    QVariantList m_filesList;
    QString m_currentPath;
    QString m_status;

    QSystemTrayIcon* m_trayIcon;
};

#endif
