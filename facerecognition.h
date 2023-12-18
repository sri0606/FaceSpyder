#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include "Item.h"
class Observer;

/**
**
*/
class FaceRecognition
{
private:

    //item we want implement face recogniton on
    std::unique_ptr<Item> mItem = nullptr;

    //The observers of this picture
    std::vector<Observer*> mObservers;

public:
    void OnPaint(std::shared_ptr<QPainter> painter);
    FaceRecognition();
    void LoadImage(const QString& filename);
    void LoadVideo( const QString& filename);
    void Clear();
    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);
    void UpdateObservers();
    /**
   * Add the face that has been detected
  */
    virtual void AddDetectedFace(cv::Mat faceImage);

    void Update();

    QString GetItemPath(){return mItem->GetPath();}
};

#endif // FACERECOGNITION_H
