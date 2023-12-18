#ifndef ITEM_H
#define ITEM_H

class FaceRecognition;
class FaceRecognitionView;
/**
*Base class for the items taht are detectable using OpenCV library
*/
class Item
{
protected:
    FaceRecognition* mFaceRecognition;
    QString mPath;
    // FaceRecognitionView* mParentView;
public:
    Item( const QString& filename,FaceRecognition* facrec);
    Item() = delete; // Disable the default constructor.
    Item(const Item&) = delete; // Disable the copy constructor.
    Item& operator=(const Item&) = delete; // Disable the copy assignment operator.
    virtual ~Item() {}
    virtual void OnPaint(std::shared_ptr<QPainter> painter){};
    virtual void Process();
    virtual void DetectFaces() {};

    /**
     * Get the pointer to the FaceRecognition object
     * @return Pointer to FaceRecognition object
     */
    FaceRecognition* GetFaceRecognition() { return mFaceRecognition; }

    /**
     * Set the pointer to the FaceRecognition object
     * @return Pointer to FaceRecognition object
     */
    virtual void SetFaceRecognition(FaceRecognition* facrec) { mFaceRecognition=facrec; }

    /**
    Getter for item path
    */
    QString GetPath() { return mPath; }

    virtual void Update() {};
};

#endif // ITEM_H
