#include "pch.h"
#include "facerecognition.h"
#include "Observer.h"
#include "image.h"
#include "video.h"
#include "facedetectionworker.h"
#include <QThread>

using namespace std;

/**
 * FaceRecognition Constructor
 */
FaceRecognition::FaceRecognition(QObject *parent)
{

}

/**
 * Draw the face rec
 * @param dc The device context to draw on
 */
void FaceRecognition::OnPaint(std::shared_ptr<QPainter> painter)
{
    if (mItem) {
        mItem->OnPaint(painter);
    }
}

void FaceRecognition::LoadImage(const QString& filename)
{
    mItem = std::make_unique<Image>(filename,this);
    // In your main class (FaceDetectionView)
    FaceDetectionWorker* worker = new FaceDetectionWorker(this);
    QThread* thread = new QThread(this);

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &FaceDetectionWorker::processImage);
    connect(worker, &FaceDetectionWorker::finished, thread, &QThread::quit);
    connect(worker, &FaceDetectionWorker::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    // Connect the signal for detected faces to a slot in your main class
    connect(worker, &FaceDetectionWorker::faceDetected, this, &FaceRecognition::AddDetectedFace);

    // Start the thread
    thread->start();
}

void FaceRecognition::LoadVideo( const QString& filename, QWidget* parent)
{
    mItem = std::make_unique<Video>(filename, this, parent);

    // In your main class (FaceDetectionView)
    FaceDetectionWorker* worker = new FaceDetectionWorker(this);
    QThread* thread = new QThread(this);

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &FaceDetectionWorker::processVideo);
    connect(worker, &FaceDetectionWorker::finished, thread, &QThread::quit);
    connect(worker, &FaceDetectionWorker::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    // Connect the signal for detected faces to a slot in your main class
    connect(worker, &FaceDetectionWorker::faceDetected, this, &FaceRecognition::AddDetectedFace);

    // Start the thread
    thread->start();
}

void FaceRecognition::AddDetectedFace(cv::Mat faceImage){
    for (auto observer: mObservers){
        observer->addItemDetectedView(faceImage);
    }
}
void FaceRecognition::Clear()
{
    mItem.reset();
    for (auto observer: mObservers){
        observer->Clear();
    }
}

/**
 * Add an observer.
 * @param observer The observer to add
 */
void FaceRecognition::AddObserver(Observer* observer)
{
    mObservers.push_back(observer);
}


/**
 * Remove an observer
 * @param observer The observer to remove
 */
void FaceRecognition::RemoveObserver(Observer* observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/**
 * Update all observers to indicate the picture has changed.
 */
void FaceRecognition::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

void FaceRecognition::setProcessedImage(QPixmap pixmap){
    mItem->setProcessedImage(pixmap);
}

void FaceRecognition::setProcessedVideo(){
    // mItem->setProcessedItem(pixmap);
}
/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void FaceRecognition::Update()
{
    if (mItem!=nullptr)
        mItem->Update();
}
