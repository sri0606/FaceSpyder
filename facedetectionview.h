#ifndef FACEDETECTIONVIEW_H
#define FACEDETECTIONVIEW_H

#include <QWidget>
#include "Observer.h"
#include "itemdetectedview.h"
#include <QGridLayout>


class FaceDetectionView final : public QWidget, public Observer
{
    Q_OBJECT
public:
    explicit FaceDetectionView(QWidget *parent = nullptr);

private slots:
    void RemoveDetectedView(ItemDetectedView* view);
private:
    virtual void paintEvent(QPaintEvent *event);
    QGridLayout* mGridLayout;
    int mViewCount=0;
public:
    void UpdateObserver() override;
    virtual void addItemDetectedView(cv::Mat pixmap) override;
    void SaveDetectedFaces(const QString& folderPath);
    void cleanDetectedViews();
    bool IsFacesDetected();
    virtual void Clear() override;

};

#endif // FACEDETECTIONVIEW_H
