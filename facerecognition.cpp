#include "pch.h"
#include "facerecognition.h"
#include "Observer.h"
#include "image.h"
#include "video.h"
#include "facedetectionview.h"


using namespace std;

/**
 * FaceRecognition Constructor
 */
FaceRecognition::FaceRecognition()
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
    mItem->Process();
}

void FaceRecognition::LoadVideo( const QString& filename)
{
    mItem = std::make_unique<Video>(filename, this);
    mItem->Process();
}

void FaceRecognition::Clear()
{
    mItem= nullptr;
    mObservers.clear();
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

/**
 * @brief FaceRecognition::AddDetectedFace
 * @param faceImage
 */
void FaceRecognition::AddDetectedFace(cv::Mat faceImage)
{
    for (auto observer:mObservers){
        observer->addItemDetectedView(faceImage);
    }

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
