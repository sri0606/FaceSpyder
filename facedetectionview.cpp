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
    : QWidget{parent},Observer{parent}
{
    setAttribute(Qt::WA_StyledBackground);

    setStyleSheet("background-color: rgb(106, 117, 109);");

    // Create a grid layout
    mGridLayout = new QGridLayout(this);
    mGridLayout->setSpacing(3);

    setLayout(mGridLayout);
}

/**
 * Force an update of this window when the picture changes.
 */
void FaceDetectionView::UpdateObserver()
{
    update();
}

void FaceDetectionView::addItemDetectedView(cv::Mat faceImage)
{
    auto faceBitmap = MatToQPixmap(faceImage);
    ItemDetectedView* viewWidget = new ItemDetectedView(this, faceBitmap);
    connect(viewWidget, &ItemDetectedView::removeRequested, this, &FaceDetectionView::RemoveDetectedView);

    //add to grid layout
    int minImageWidth = 235;
    int minImageHeight = 260;
    int totalColumns=3;

    QPixmap pixmap = viewWidget->GetPixmap();
    // Set a fixed size for each widget
    viewWidget->setFixedSize(minImageWidth, minImageHeight);

    viewWidget->SetPixmap(pixmap.scaled(viewWidget->size(), Qt::KeepAspectRatio));
    viewWidget->setStyleSheet("color:white;background-color: rgb(16, 7, 20)");
    viewWidget->setAttribute(Qt::WA_StyledBackground);
    mGridLayout->addWidget(viewWidget,mViewCount/totalColumns,mViewCount%totalColumns);
    mViewCount++;
}

/**
 * @brief IsFacesDetected: checks if any faces detected yet
 * @return
 */
bool FaceDetectionView::IsFacesDetected(){
    return mViewCount!=0;
}

/**
 * @brief cleanDetectedViews: clean duplicates
 * @return
 */
void FaceDetectionView::cleanDetectedViews()
{
    cv::Mat faceImage;
    auto faceBitmap = MatToQPixmap(faceImage);
    for (int i = 0; i < mGridLayout->count(); ++i) {
        QLayoutItem *item = mGridLayout->itemAt(i);

        // Check if the item is a widget
        if (QWidget *widget = item->widget()) {
            // Cast it to your custom widget type
            ItemDetectedView *detectedView = qobject_cast<ItemDetectedView*>(widget);

            // Check if the cast was successful
            if (detectedView) {
                if (CompareImagesByHistogram(detectedView->GetPixmap(), faceBitmap) ){//|| CompareImagesByFeatureMatching(*detectedFace, faceBitmap)) {
                    return;
                }
                else {
                    continue;
                }
            }
        }
    }
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FaceDetectionView::paintEvent(QPaintEvent *event)
{
    // Call the base class implementation
    QWidget::paintEvent(event);
}

/**
* Save detected faces
*/
void FaceDetectionView::SaveDetectedFaces(const QString& folderPath) {
    QImage image;
    // Create a subfolder in the selected folder
    QString subfolderName = QFileInfo(mFaceRecognition->GetItemPath()).baseName()+"_facespyder";
    QString subfolderPath = folderPath + QDir::separator() + subfolderName;

    if (!QDir(subfolderPath).exists() && !QDir().mkpath(subfolderPath)) {
        QMessageBox::critical(nullptr, "Error", "Failed to create the folder.", QMessageBox::Ok);
        return;
    }
    for (int i = 0; i < mGridLayout->count(); ++i) {
        QLayoutItem *item = mGridLayout->itemAt(i);

        // Check if the item is a widget
        if (QWidget *widget = item->widget()) {
            // Cast it to your custom widget type
            ItemDetectedView *detectedView = qobject_cast<ItemDetectedView*>(widget);

            // Check if the cast was successful
            if (detectedView) {
                auto pixmap = detectedView->GetPixmap();
                image = pixmap.toImage();

                QString filename = QString("detected_face_%1.png").arg(i);
                QString filePath = subfolderPath + QDir::separator() + filename;

                if (!image.save(filePath, "PNG")) {
                    // Handle the error, e.g., show an error message
                    QMessageBox::critical(nullptr, "Error", "Failed to save image.", QMessageBox::Ok);
                    return;
                }
            }
        }
    }

    QMessageBox::information(nullptr, "Success", "Images saved successfully.", QMessageBox::Ok);
}

void FaceDetectionView::Clear() {
    if (mGridLayout != nullptr) {
        // Remove all items in the layout
        QLayoutItem* item;
        while ((item = mGridLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                // Delete the widget
                delete item->widget();
            } else {
                // Delete the layout item
                delete item;
            }
        }
        // Delete the old layout
        delete mGridLayout;
    }
    // Create a new grid layout
    mGridLayout = new QGridLayout(this);
    mGridLayout->setSpacing(3);
    setLayout(mGridLayout);

    // Update the observer
    UpdateObserver();
}

void FaceDetectionView::RemoveDetectedView(ItemDetectedView* view) {
    if (view) {
        mGridLayout->removeWidget(view);
        view->deleteLater();
    }
}
