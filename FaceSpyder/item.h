#ifndef ITEM_H
#define ITEM_H

class FaceRecognition;
/**
*Base class for the items taht are detectable using OpenCV library
*/
class Item
{
protected:
    QString mPath;
    FaceRecognition *mFaceRecognition;

public:
    Item(const QString &filename, FaceRecognition *facrec);
    Item() = delete;                        // Disable the default constructor.
    Item(const Item &) = delete;            // Disable the copy constructor.
    Item &operator=(const Item &) = delete; // Disable the copy assignment operator.
    virtual ~Item() {}
    virtual void OnPaint(std::shared_ptr<QPainter> painter){};
    // virtual void Process();

    /**
     * Get the pointer to the FaceRecognition object
     * @return Pointer to FaceRecognition object
     */
    FaceRecognition *GetFaceRecognition() { return mFaceRecognition; }

    /**
     * Set the pointer to the FaceRecognition object
     * @return Pointer to FaceRecognition object
     */
    virtual void SetFaceRecognition(FaceRecognition *facrec) { mFaceRecognition = facrec; }

    /**
    Getter for item path
    */
    QString GetPath() { return mPath; }

    virtual void Update(){};
    virtual void setProcessedImage(QPixmap pixmap) {}
};

#endif // ITEM_H
