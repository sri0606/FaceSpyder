#ifndef VIDEO_H
#define VIDEO_H

#include "item.h"

class Video : public Item
{
public:
    Video();
private:
    //image with the detected faces highlighted
    int mCurrentFrameIndex=0;

    std::vector<QPixmap> mFrames;

public:

    Video(const QString& filename, FaceRecognition* facrec);
    virtual void Process() override;
    virtual void OnPaint(std::shared_ptr<QPainter> painter) override;
    virtual void DetectFaces() override;
    void AddCurrentFrame(cv::Mat currentMatFrame);
    virtual void Update() override;
};

#endif // VIDEO_H
