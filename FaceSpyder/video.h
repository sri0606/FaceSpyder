#ifndef VIDEO_H
#define VIDEO_H

#include "item.h"
#include "observer.h"
#include "videoplayer.h"
class Video : public Item
{
public:
    Video();

private:
    std::unique_ptr<VideoPlayer> mVideoPlayer;

public:
    Video(const QString &filename, FaceRecognition *facrec, QWidget *);
    virtual void OnPaint(std::shared_ptr<QPainter> painter) override;
};

#endif // VIDEO_H
