#ifndef SPYDERWINDOW_H
#define SPYDERWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include "menubutton.h"
#include "FaceDetectionView.h"
#include "FaceRecognitionView.h"
#include "facerecognition.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SpyderWindow;
}

class SpyderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SpyderWindow(QWidget *parent = nullptr);
    ~SpyderWindow();


private slots:
    void onHomeButtonClicked();
    void onImageButtonClicked();
    void onVideoButtonClicked();
    void onSettingsButtonClicked();
    void onNewSessionButtonClicked();
    void onSaveFacesButtonClicked();


private:
    Ui::SpyderWindow *ui;
    std::shared_ptr<FaceRecognition> mFaceRecognition;
    // std::unique_ptr<FaceRecognitionView> mFaceRecognitionView;
    // std::unique_ptr<FaceDetectionView> mFaceDetectionView;
    FaceRecognitionView* mFaceRecognitionView;
    FaceDetectionView* mFaceDetectionView;
    QTimer mTimer;

    MenuButton* homeButton;
    MenuButton* imageButton;
    MenuButton* videoButton;
    MenuButton* settingsButton;
    MenuButton* saveDetectedFacesButton;
    QPushButton* newSessionButton;
};

#endif // SPYDERWINDOW_H
