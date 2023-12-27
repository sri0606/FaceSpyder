#include "pch.h"
#include "facerecognition.h"
#include "Observer.h"
#include "image.h"
#include "video.h"
#include "facedetectionworker.h"


using namespace std;

/**
 * FaceRecognition Constructor
 */
FaceRecognition::FaceRecognition(QObject *parent)
{

}

FaceRecognition::~FaceRecognition(){
    if (mDetectionThread && mDetectionThread->isRunning()) {
        mDetectionThread->terminate();
        // emit requestStopProcessing();

        // // Stop the thread's event loop
        // mDetectionThread->quit();
        // if (!mDetectionThread->wait(500)) { // Wait for 3 seconds
        //     mDetectionThread->terminate(); // Forcefully terminate if not finished
        // }
    }
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
    mDetectionWorker = new FaceDetectionWorker(this);
    mDetectionThread = new QThread(this);

    mDetectionWorker->moveToThread(mDetectionThread);

    connect(mDetectionThread, &QThread::started, mDetectionWorker, &FaceDetectionWorker::processImage);
    connect(mDetectionWorker, &FaceDetectionWorker::finished, mDetectionThread, &QThread::quit);
    connect(mDetectionWorker, &FaceDetectionWorker::finished, mDetectionWorker, &QObject::deleteLater);
    connect(mDetectionThread, &QThread::finished, mDetectionThread, &QObject::deleteLater);
    connect(this, &FaceRecognition::requestStopProcessing, mDetectionWorker, &FaceDetectionWorker::stopProcessing);

    // Connect the signal for detected faces to a slot in your main class
    connect(mDetectionWorker, &FaceDetectionWorker::faceDetected, this, &FaceRecognition::AddDetectedFace);

    // Start the thread
    mDetectionThread->start();
}

void FaceRecognition::LoadVideo( const QString& filename, QWidget* parent)
{
    mItem = std::make_unique<Video>(filename, this, parent);

    // In your main class (FaceDetectionView)
   mDetectionWorker = new FaceDetectionWorker(this);
    mDetectionThread = new QThread(this);

    mDetectionWorker->moveToThread(mDetectionThread);

    connect(mDetectionThread, &QThread::started, mDetectionWorker, &FaceDetectionWorker::processVideo);
    connect(mDetectionWorker, &FaceDetectionWorker::finished, mDetectionThread, &QThread::quit);
    connect(mDetectionWorker, &FaceDetectionWorker::finished, mDetectionWorker, &QObject::deleteLater);
    connect(mDetectionThread, &QThread::finished, mDetectionThread, &QObject::deleteLater);
    connect(this, &FaceRecognition::requestStopProcessing, mDetectionWorker, &FaceDetectionWorker::stopProcessing);

    // Connect the signal for detected faces to a slot in your main class
    connect(mDetectionWorker, &FaceDetectionWorker::faceDetected, this, &FaceRecognition::AddDetectedFace);

    // Start the thread
    mDetectionThread->start();
}

void FaceRecognition::AddDetectedFace(cv::Mat faceImage){
    for (auto observer: mObservers){
        observer->addItemDetectedView(faceImage);
    }
}
void FaceRecognition::Clear()
{
    if (mDetectionThread && mDetectionThread->isRunning()) {
        // Signal the worker to stop processing
        emit requestStopProcessing();

        // Wait for the thread to finish
        mDetectionThread->quit();
        mDetectionThread->wait();
        mDetectionThread=nullptr;
    }
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
