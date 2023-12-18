#include "pch.h"
#include "facerecognitionview.h"
#include "FaceRecognition.h"
#include "Observer.h"


/// Frame duration in milliseconds
const int FrameDuration = 30;

FaceRecognitionView::FaceRecognitionView(QWidget *parent)
    : QWidget{parent},Observer{parent}
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background-color:rgb(121, 152, 173);");
}

void FaceRecognitionView::UpdateObserver()
{
    // Trigger a repaint
    update();
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FaceRecognitionView::paintEvent(QPaintEvent *event)
{
    // Call the base class implementation
    QWidget::paintEvent(event);

    // Compute the time that has elapsed
    //     // since the last call to OnPaint.
    //     auto newTime = mStopWatch.Time();
    //     auto elapsed = (double)(newTime - mTime) * 0.001;
    //     mTime = newTime;
    if (mFaceRecognition!=nullptr)
        mFaceRecognition->Update();

    // Use a QPainter to draw on the widget
    auto painter = std::make_shared<QPainter>(this);

    // Set up the painter as needed
    painter->setRenderHint(QPainter::Antialiasing, true);


    mFaceRecognition->OnPaint(painter);

    // End the painting operations
    painter->end();
}
