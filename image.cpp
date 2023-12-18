#include "pch.h"
#include "Image.h"
#include <opencv2/opencv.hpp>
#include "FaceRecognition.h"
#include "imagematching.h"
#include "FaceRecognitionView.h"
using namespace cv;

const std::string faceCascadePath = "C:/Program Files/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";

/**
 * Image Constructor
 */
Image::Image(const QString& filename, FaceRecognition* facrec):Item(filename, facrec)
{

}

/**
 * Process the image to customize it as needed
 */
void Image::Process()
{
    // Load the image from the provided path
    mImage = QImage(mPath);

    if (mImage.isNull()) {
        // Handle image loading error
        qDebug() << "Failed to load image:" << mPath;
    }

    DetectFaces();
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


/**
*   Detect the faces in the image
*/
void Image::DetectFaces()
{
    // Load an image
    cv::Mat image = cv::imread(mPath.toStdString());
    if (image.empty()) {
        std::cerr << "Image not found. Make sure to provide a valid image path." << std::endl;
        return;
    }

    // Initialize face detection classifier
    cv::CascadeClassifier face_cascade;
    // Load pre-trained XML classifier for face detection
    if (!face_cascade.load(faceCascadePath)) {
        std::cerr << "Error loading face cascade." << std::endl;
        return ;
    }

    // Convert the image to grayscale for detection
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray_image, gray_image);

    // Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 3, 0);

    // Extract and display detected faces
    for (size_t i = 0; i < faces.size(); i++) {
        // Crop the detected face region
        cv::Mat face = image(faces[i]);
        mFaceRecognition->AddDetectedFace(face);
    }

    // Loop through the detected faces and draw bounding boxes
    for (const cv::Rect& face : faces) {
        cv::rectangle(image, face, cv::Scalar(0, 0, 255), 3);  // Draw a red rectangle around the face
    }
    mImageDetected = MatToQPixmap(image);
}

