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
    //void OnMouseMove(wxMouseEvent& event);
    //void OnLeftUp(wxMouseEvent& event);
    //void OnLeftDown(wxMouseEvent& event);
    //void OnDoubleClick(wxMouseEvent& event);

    void UpdateObserver() override;
};

#endif // FACERECOGNITIONVIEW_H
