#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QThread>
#include "Item.h"
class FaceDetectionWorker;
class Observer;

/**
**
*/
class FaceRecognition : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<Item> mItem = nullptr;
    std::vector<Observer *> mObservers;
    QThread *mDetectionThread = nullptr;
    FaceDetectionWorker *mDetectionWorker = nullptr;

public:
    explicit FaceRecognition(QObject *parent = nullptr);
    ~FaceRecognition();
    void OnPaint(std::shared_ptr<QPainter> painter);
    void LoadImage(const QString &filename);
    void LoadVideo(const QString &filename, QWidget *);
    void Clear();
    void AddObserver(Observer *observer);
    void RemoveObserver(Observer *observer);
    void UpdateObservers();
    void Update();
    QString GetItemPath() { return mItem->GetPath(); }
    void setProcessedImage(QPixmap pixmap);
    void setProcessedVideo();
signals:
    // Define signals here
    void requestStopProcessing();

public slots:
    void AddDetectedFace(cv::Mat faceImage);
};

#endif // FACERECOGNITION_H
