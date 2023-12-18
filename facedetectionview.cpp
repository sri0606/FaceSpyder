#include "pch.h"
#include "facedetectionview.h"
#include "imagematching.h"
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QPixmap>
/**
 * Constructor
 * @param parent
 *
 */
FaceDetectionView::FaceDetectionView(QWidget *parent)
    : QScrollArea{parent},Observer{parent}
{
    setAttribute(Qt::WA_StyledBackground);

    setStyleSheet("background-color: rgb(106, 117, 109);");
    // Create a grid layout
    mGridLayout = new QGridLayout(this);
    mGridLayout->setSpacing(5);

    setLayout(mGridLayout);
}

/**
 * Force an update of this window when the picture changes.
 */
void FaceDetectionView::UpdateObserver()
{
    update();
}

void FaceDetectionView::addItemDetectedView(cv::Mat faceImage){
    auto faceBitmap = MatToQPixmap(faceImage);

    for (auto detectedFace : mDetectedViews)
    {
        if (CompareImagesByHistogram(detectedFace->GetPixmap(), faceBitmap) ){//|| CompareImagesByFeatureMatching(*detectedFace, faceBitmap)) {
            return;
        }
        else {
            continue;
        }
    }
    // Assuming mParent is a QWidget* and faceBitmap is a QPixmap
    ItemDetectedView* view = new ItemDetectedView(this, faceBitmap);
    mDetectedViews.push_back(view);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FaceDetectionView::paintEvent(QPaintEvent *event)
{
    // Call the base class implementation
    QWidget::paintEvent(event);


    if (!mDetectedViews.empty()) {
        int minImageWidth = 250;
        int minImageHeight = 275;

        // Calculate the number of rows and columns in the grid layout
        auto pair = GetNumofRowsCols(width(), height());
        int rows = pair.first;
        int cols = pair.second;

        // Iterate through the images and add them to the grid layout
        for (int i = 0; i < mDetectedViews.size(); ++i) {
            // Add the ItemDetectedView directly to the QGridLayout
            auto viewWidget = mDetectedViews[i];
            QPixmap pixmap = viewWidget->GetPixmap();  // Assuming GetPixmap() returns the QPixmap instance
            // Set a fixed size for each widget
            viewWidget->setFixedSize(minImageWidth, minImageHeight);

            viewWidget->SetPixmap(pixmap.scaled(viewWidget->size(), Qt::KeepAspectRatio));
            viewWidget->setStyleSheet("background-color:red");
            viewWidget->setAttribute(Qt::WA_StyledBackground);
            mGridLayout->addWidget(viewWidget, i / cols, i % cols);
        }
    }
}

/**
* Save detected faces
*/
void FaceDetectionView::SaveDetectedFaces(const QString& folderPath) {
    QImage image;
    int i = 1;

    // Create a subfolder in the selected folder
    QString subfolderName = QFileInfo(mFaceRecognition->GetItemPath()).baseName()+"_facespyder";
    QString subfolderPath = folderPath + QDir::separator() + subfolderName;

    if (!QDir(subfolderPath).exists() && !QDir().mkpath(subfolderPath)) {
        QMessageBox::critical(nullptr, "Error", "Failed to create the folder.", QMessageBox::Ok);
        return;
    }

    for (auto detectedFace : mDetectedViews) {
        auto pixmap = detectedFace->GetPixmap();
        image = pixmap.toImage();

        QString filename = QString("detected_face_%1.png").arg(i);
        QString filePath = subfolderPath + QDir::separator() + filename;

        if (!image.save(filePath, "PNG")) {
            // Handle the error, e.g., show an error message
            QMessageBox::critical(nullptr, "Error", "Failed to save image.", QMessageBox::Ok);
            return;
        }
        i++;
    }

    QMessageBox::information(nullptr, "Success", "Images saved successfully.", QMessageBox::Ok);
}

std::pair<int,int> FaceDetectionView::GetNumofRowsCols(int contextWidth, int contextHeight) {
    int minImageWidth = 250;
    int minImageHeight = 275;
    int maxImageWidth = contextWidth;
    int maxImageHeight = contextHeight;
    size_t numFaces = mDetectedViews.size();

    int rows=1;
    int columns = 8;

    int maxScrollLengthHorizontal = 1.5*contextWidth;
    // 8 * 50 > 300
    if (numFaces * minImageWidth > maxScrollLengthHorizontal) {
        rows = static_cast<int>(numFaces * minImageWidth / maxScrollLengthHorizontal);
    }
    return std::pair<int,int>(2, 3);
}
