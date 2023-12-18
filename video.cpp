#include "pch.h"
#include "Video.h"
#include <opencv2/opencv.hpp>
#include "FaceRecognition.h"
#include "FaceRecognitionView.h"
#include "imagematching.h"

using namespace cv;

const std::string faceCascadePath = "C:/Program Files/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";

/**
 * Video Constructor
 */
Video::Video(const QString& filename, FaceRecognition* facrec) :Item(filename, facrec)
{

}

/**
* Process the image to customize it to as needed
*/
void Video::Process()
{
    DetectFaces();
}


void Video::OnPaint(std::shared_ptr<QPainter> painter)
{
    // Get the dimensions of the painter
    double contextWidth = painter->device()->width();
    double contextHeight = painter->device()->height();

    // Half-width of the window
    int halfWidth = static_cast<int>(contextWidth / 2.0);

    // Assuming mFrames is a QVector<QPixmap> or similar container for video frames
    auto currentVideoFrame = mFrames[mCurrentFrameIndex];

    // Calculate the scaling factors to fit the video within the context while maintaining aspect ratio
    double scaleX = halfWidth / static_cast<double>(currentVideoFrame.width());
    double scaleY = contextHeight / static_cast<double>(currentVideoFrame.height());
    double scaleFactor = std::min(scaleX, scaleY);

    int newWidth = static_cast<int>(currentVideoFrame.width() * scaleFactor);
    int newHeight = static_cast<int>(currentVideoFrame.height() * scaleFactor);

    // Calculate the position to center the video in the context
    int xPos = halfWidth - newWidth / 2;
    int yPos = static_cast<int>((contextHeight - newHeight) / 2);

    // Draw the video frame on the painter
    painter->drawPixmap(xPos, yPos, newWidth, newHeight, currentVideoFrame);
}


// Event handler
void Video::AddCurrentFrame(cv::Mat currentMatFrame)
{
    if (!currentMatFrame.empty()) {
        auto currentVideoFrame = MatToQPixmap(currentMatFrame);
        mFrames.push_back(currentVideoFrame);
        //mFaceRecognition->ClearDetectedFaces();
    }
}

void Video::Update()
{
    if (mCurrentFrameIndex<mFrames.size()-1)
        mCurrentFrameIndex++;
}

/**
*   Detect the faces in the image
*/
void Video::DetectFaces()
{
    // Open a video file or a camera stream
    cv::VideoCapture videoCapture(mPath.toStdString());  // or use 0 for the default camera

    // Check if the video/camera opened successfully
    if (!videoCapture.isOpened()) {
        std::cerr << "Error opening video stream or file!" << std::endl;
        return;
    }

    // Initialize face detection classifier
    cv::CascadeClassifier face_cascade;
    // Load pre-trained XML classifier for face detection
    if (!face_cascade.load(faceCascadePath)) {
        std::cerr << "Error loading face cascade." << std::endl;
        return;
    }

    while (true) {

        cv::Mat currentMatFrame;
        // Read a frame from the video stream
        videoCapture >> currentMatFrame;

        // Break the loop if the video is over
        if (currentMatFrame.empty()) {
            break;
        }

        // Convert the frame to grayscale for detection
        cv::Mat gray_frame;
        cv::cvtColor(currentMatFrame, gray_frame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray_frame, gray_frame);

        // Detect faces
        std::vector<cv::Rect> faces;
        auto minSize = cv::Size(140,100);
        auto maxSize = cv::Size(480,270);
        face_cascade.detectMultiScale(gray_frame, faces, 1.1, 3, 0, minSize, maxSize);

        // Loop through the detected faces and draw bounding boxes
        for (const cv::Rect& face : faces) {
            cv::rectangle(currentMatFrame, face, cv::Scalar(0, 0, 255), 1);  // Draw a red rectangle around the face
        }

        // Extract and display detected faces (if needed)
        for (size_t i = 0; i < faces.size(); i++) {
            // Crop the detected face region
            cv::Mat detected_face = currentMatFrame(faces[i]);
            mFaceRecognition->AddDetectedFace(detected_face);
        }

        AddCurrentFrame(currentMatFrame);
    }

    // Release the VideoCapture
    videoCapture.release();
}

