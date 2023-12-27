#ifndef OBSERVER_H
#define OBSERVER_H

#include "facerecognition.h"
/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class Observer
{
protected:
    //Picture we are observing
    std::shared_ptr<FaceRecognition> mFaceRecognition;

public:
    /// Copy constructor (disabled)
    Observer(const Observer &) = delete;

    ~Observer();
    /// Constructor (protected)
    Observer(QWidget *parent);
    /// Assignment operator
    void operator=(const Observer &) = delete;

    virtual void paintEvent(QPaintEvent *event) = 0;

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    virtual void SetFaceRecognition(std::shared_ptr<FaceRecognition> facrec);

    /**
     * Get the picture we are observing
     * @return Pointer to picture we are observing
     */
    std::shared_ptr<FaceRecognition> GetFaceRecognition() { return mFaceRecognition; }

    virtual void addItemDetectedView(cv::Mat pixmap) {}

    virtual void Clear() {}
};

#endif // OBSERVER_H
