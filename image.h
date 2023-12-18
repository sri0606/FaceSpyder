#ifndef IMAGE_H
#define IMAGE_H

#include "item.h"

class Image : public Item
{
public:
    Image();


private:
    //original image
    QImage mImage;
    //image with the detected faces highlighted
    QPixmap mImageDetected;
public:

    Image( const QString& filename, FaceRecognition* facrec);
    virtual void Process() override;
    virtual void OnPaint(std::shared_ptr<QPainter> painter) override;
    virtual void DetectFaces() override;
};

#endif // IMAGE_H
