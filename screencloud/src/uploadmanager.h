#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include <QObject>
#include <plugin/pluginmanager.h>
#include <QSettings>
#include <models/uploaderslistmodel.h>
#include <uploaders/screenclouduploader.h>
#include <uploaders/clipboarduploader.h>
#include <QtConcurrentRun>
#include <QSettings>

class UploadManager : public QObject
{
    Q_OBJECT
public:
    explicit UploadManager(QObject *parent = 0);
    ~UploadManager();
    void loadServices();
    void unloadServices();
    void reloadServices();
    bool upload(const QImage& screenshot, QString serviceShortname, QString screenshotName, bool wait);
    QString getDefaultService();
    QList<Uploader*>* list();
    UploadersListModel* listModel();
    Uploader* getUploader(QString shortname);
    QString getLastScreenshotName();

private:
    PluginManager pluginManager;
    QList<Uploader*> uploaders;
    UploadersListModel* uploadersModel;
    //Default uploaders
    ScreenCloudUploader screencloudUploader;
    ClipboardUploader clipboardUploader;
    bool uploadFinished;
    QString lastScreenshotName;

signals:
    void finished(QString url);
    void error(QString errorMessage);
    void startUpload(const QImage& screenshot);

public slots:
    void uploaderFinished(QString url);
    void uploaderError(QString errorMessage);

};

#endif // UPLOADMANAGER_H
