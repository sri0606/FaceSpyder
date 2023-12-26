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

signals:
private:

    virtual void paintEvent(QPaintEvent *event);

    std::pair<int, int> GetNumofRowsCols(int contextWidth, int contextHeight);
    QGridLayout* mGridLayout;

    //views of all the detected faces
    std::vector<ItemDetectedView*> mDetectedViews;

public:
    void UpdateObserver() override;
    virtual void addItemDetectedView(cv::Mat pixmap) override;
    void SaveDetectedFaces(const QString& folderPath);
    void cleanDetectedViews();
    bool IsFacesDetected(){return mDetectedViews.size()!=0;}
    virtual void Clear() override;
};

#endif // FACEDETECTIONVIEW_H
