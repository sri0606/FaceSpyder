#ifndef SPYDERWINDOW_H
#define SPYDERWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include "FaceDetectionView.h"
#include "FaceRecognitionView.h"
#include "facerecognition.h"
#include "menubutton.h"

class SpyderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SpyderWindow(QWidget *parent = nullptr);
    ~SpyderWindow();
    // void processCloseEvent();

private slots:
    void onHomeButtonClicked();
    void onImageButtonClicked();
    void onVideoButtonClicked();
    void onSettingsButtonClicked();
    void onNewSessionButtonClicked();
    void onAboutButtonClicked();
    void onSaveFacesButtonClicked();

private:
    std::shared_ptr<FaceRecognition> mFaceRecognition;
    // std::unique_ptr<FaceRecognitionView> mFaceRecognitionView;
    // std::unique_ptr<FaceDetectionView> mFaceDetectionView;
    FaceRecognitionView *mFaceRecognitionView;
    FaceDetectionView *mFaceDetectionView;
    QTimer mTimer;

    MenuButton *homeButton;
    MenuButton *imageButton;
    MenuButton *videoButton;
    MenuButton *settingsButton;
    MenuButton *saveDetectedFacesButton;
    QPushButton *newSessionButton;
    QPushButton *aboutButton;
};

#endif // SPYDERWINDOW_H
