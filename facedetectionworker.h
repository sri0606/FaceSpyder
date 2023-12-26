#ifndef FACEDETECTIONWORKER_H
#define FACEDETECTIONWORKER_H

#include <QObject>
#include "FaceRecognition.h"

class FaceDetectionWorker : public QObject {
    Q_OBJECT

public:
    FaceDetectionWorker(FaceRecognition* faceRecognition);

signals:
    void faceDetected(cv::Mat face);
    void finished();

public slots:
    void processImage();
    void processVideo();

private:
    FaceRecognition* mFaceRecognition;
};

#endif // FACEDETECTIONWORKER_H
