#include "pch.h"
#include "Item.h"
#include "FaceRecognitionView.h"
#include "FaceRecognition.h"

/**
 *COnstructor for Item class
*/
Item::Item(const QString& filename, FaceRecognition* facrec)
{
    mPath = filename;
    mFaceRecognition = facrec;
    // mParentView = parent;
}

void Item::Process()
{
}

