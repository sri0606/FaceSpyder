#ifndef FACEDETECTIONVIEW_H
#define FACEDETECTIONVIEW_H

#include <QScrollArea>
#include "Observer.h"
#include "itemdetectedview.h"
#include <QGridLayout>


class FaceDetectionView final : public QScrollArea, public Observer
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
    static const int Height = 90;      ///< Height to make this window

    void UpdateObserver() override;
    virtual void addItemDetectedView(cv::Mat pixmap) override;
    void SaveDetectedFaces(const QString& folderPath);
};

#endif // FACEDETECTIONVIEW_H
