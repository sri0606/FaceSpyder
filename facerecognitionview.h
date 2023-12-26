#ifndef FACERECOGNITIONVIEW_H
#define FACERECOGNITIONVIEW_H

#include "Observer.h"

class FaceRecognitionView final : public QWidget, public  Observer
{
    Q_OBJECT
public:
    explicit FaceRecognitionView(QWidget *parent = nullptr);

signals:

private:

    virtual void paintEvent(QPaintEvent *event) override;

public:
    void UpdateObserver() override;
     virtual void Clear() override;
};

#endif // FACERECOGNITIONVIEW_H
