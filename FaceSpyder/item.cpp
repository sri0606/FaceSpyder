#include "Item.h"
#include "FaceRecognition.h"
#include "FaceRecognitionView.h"
#include "pch.h"

/**
 *COnstructor for Item class
*/
Item::Item(const QString &filename, FaceRecognition *facrec)
{
    mPath = filename;
    mFaceRecognition = facrec;
}
