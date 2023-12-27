#include "pch.h"
#include "Image.h"
#include "FaceRecognition.h"

/**
 * Image Constructor
 */
Image::Image(const QString& filename, FaceRecognition* facrec):Item(filename, facrec)
{
    // Load the image from the provided path
    mImage = QImage(filename);
}

void Image::setProcessedImage(QPixmap pixmap){
    mImageDetected=pixmap;
    mFaceRecognition->UpdateObservers();
}

void Image::OnPaint(std::shared_ptr<QPainter> painter)
{
    // Get the dimensions of the painter
    double contextWidth = painter->device()->width()*0.5;
    double contextHeight = painter->device()->height();

    // Calculate the scaling factors to fit the image within the painter while maintaining aspect ratio
    double scaleX = contextWidth / mImage.width();
    double scaleY = contextHeight / mImage.height();
    double scaleFactor = std::min(scaleX, scaleY);

    int newWidth, newHeight;
    // Calculate the new dimensions
    if (scaleFactor == 0) {
        // If the image dimensions are very large, extending the painter size
        newWidth = static_cast<int>(contextWidth * 0.98);
        newHeight = contextHeight;
    }
    else {
        newWidth = static_cast<int>(mImage.width() * scaleFactor);
        newHeight = static_cast<int>(mImage.height() * scaleFactor);
    }

    // Calculate the X,Y position for the image to center it
    int imageX = (contextWidth - newWidth) / 2;
    int imageY = 0;  // Adjust as needed for vertical centering

    // Rescale the image
    QImage scaledImage = mImage.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Draw the scaled image
    painter->drawImage(imageX, imageY, scaledImage);

    QPixmap scaledDetectedPixmap = mImageDetected.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(imageX + contextWidth, imageY, scaledDetectedPixmap);
}


