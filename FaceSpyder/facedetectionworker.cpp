#include "facedetectionworker.h"
#include "imagematching.h"
#include "pch.h"
#include <opencv2/opencv.hpp>

using namespace cv;

const std::string faceCascadePath
    = "C:/Program Files/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";

FaceDetectionWorker::FaceDetectionWorker(FaceRecognition *faceRecognition)
    : mFaceRecognition(faceRecognition)
{}

/**
*   Detect the faces in the image
*/
void FaceDetectionWorker::processImage()
{
    if (!mShouldStop) {
        // Load an image
        cv::Mat image = cv::imread(mFaceRecognition->GetItemPath().toStdString());
        if (image.empty()) {
            std::cerr << "Image not found. Make sure to provide a valid image path." << std::endl;
            return;
        }

        // Initialize face detection classifier
        cv::CascadeClassifier face_cascade;
        // Load pre-trained XML classifier for face detection
        if (!face_cascade.load(faceCascadePath)) {
            std::cerr << "Error loading face cascade." << std::endl;
            return;
        }

        // Convert the image to grayscale for detection
        cv::Mat gray_image;
        cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray_image, gray_image);

        // Detect faces
        std::vector<cv::Rect> allFaces;
        // Detected faces with no duplicates
        std::vector<cv::Rect> faces;

        face_cascade.detectMultiScale(gray_image, allFaces, 1.1, 3, 0);
        if (!mShouldStop) {
            // Extract and display detected faces
            for (size_t i = 0; i < allFaces.size(); i++) {
                // Crop the detected face region
                cv::Mat face = image(allFaces[i]);
                if (hasFace(face)) {
                    emit faceDetected(face);
                    faces.push_back(allFaces[i]);
                }
            }
        }
        if (!mShouldStop) {
            // Loop through the detected faces and draw bounding boxes
            for (const cv::Rect &face : faces) {
                cv::rectangle(image,
                              face,
                              cv::Scalar(10, 35, 215),
                              3); // Draw a red rectangle around the face
            }

            auto imageDetected = MatToQPixmap(image);
            mFaceRecognition->setProcessedImage(imageDetected);
        }
    }
}

/**
*   Detect the faces in the video
*/
void FaceDetectionWorker::processVideo()
{
    if (!mShouldStop) {
        // Open a video file or a camera stream
        cv::VideoCapture videoCapture(
            mFaceRecognition->GetItemPath().toStdString()); // or use 0 for the default camera

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

        while (true && !mShouldStop) {
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
            std::vector<cv::Rect> allFaces;
            // Detected faces with no duplicates
            std::vector<cv::Rect> faces;
            // auto minSize = cv::Size(140,100);
            // auto maxSize = cv::Size(480,270);
            // face_cascade.detectMultiScale(gray_frame, allFaces, 1.1, 3, 0, minSize, maxSize);
            face_cascade.detectMultiScale(gray_frame, allFaces, 1.1, 3, 0);

            // Extract and display detected faces
            for (size_t i = 0; i < allFaces.size(); i++) {
                // Crop the detected face region
                cv::Mat detected_face = currentMatFrame(allFaces[i]);
                if (hasFace(detected_face)) {
                    emit faceDetected(detected_face);
                    faces.push_back(allFaces[i]);
                }
            }
            // Loop through the detected faces and draw bounding boxes
            for (const cv::Rect &face : faces) {
                cv::rectangle(currentMatFrame,
                              face,
                              cv::Scalar(0, 0, 255),
                              2); // Draw a red rectangle around the face
            }
        }
        // Release the VideoCapture
        videoCapture.release();
    }
}
