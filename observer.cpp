#include "pch.h"
#include "Observer.h"
#include "FaceRecognition.h"


Observer::Observer(QWidget *parent)
{
    // mParentPanel = parent;
}

/** Destructor */
Observer::~Observer()
{

    if (mFaceRecognition != nullptr)
    {
        mFaceRecognition->RemoveObserver(this);
    }

}

void Observer::SetFaceRecognition(std::shared_ptr<FaceRecognition> facrec)
{
    mFaceRecognition = facrec;
    mFaceRecognition->AddObserver(this);
}
