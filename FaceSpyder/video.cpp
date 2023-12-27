#include "Video.h"
#include "FaceRecognition.h"
#include "pch.h"

/**
 * Video Constructor
 */
Video::Video(const QString &filename, FaceRecognition *facrec, QWidget *parent)
    : Item(filename, facrec)
{
    mVideoPlayer = std::make_unique<VideoPlayer>(filename, parent);
    mVideoPlayer->play();
}

void Video::OnPaint(std::shared_ptr<QPainter> painter) {}
