#include "imagematching.h"
#include <opencv2/opencv.hpp>

/**
 * @brief QImageToMat
 * @param image
 * @return
 */
cv::Mat QPixmapToMat(const QPixmap& pixmap) {
    QImage image = pixmap.toImage();

    // Ensure the image has the correct format
    if (image.format() != QImage::Format_ARGB32_Premultiplied) {
        image = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }

    cv::Mat mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
    cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGR);
    return mat;
}


/**
 * @brief MatToQImage
 * @param mat
 * @return
 */
QPixmap MatToQPixmap(const cv::Mat& mat) {
    // Convert OpenCV's BGR image to RGB
    cv::Mat rgbMat;
    cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);

    // Create QImage from the OpenCV matrix
    QImage image(rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_RGB888);

    // Create QPixmap from QImage
    QPixmap pixmap = QPixmap::fromImage(image);

    return pixmap;  // No need to ensure deep copy as QPixmap is implicitly shared
}

/**
** Feature matching in images usong OpenCV's SIFT and knn match
*/
bool CompareImagesByFeatureMatching(const QPixmap& pixmap1, const QPixmap& pixmap2, int threshold) {
    // Convert QImage to cv::Mat
    cv::Mat img1 = QPixmapToMat(pixmap1);
    cv::Mat img2 = QPixmapToMat(pixmap2);

    // cv::resize(img1, img1, img2.size());

    // Convert images to grayscale
    cv::Mat gray1, gray2;
    cv::cvtColor(img1, gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2, gray2, cv::COLOR_BGR2GRAY);

    // Detect features and perform matching
    cv::Ptr<cv::Feature2D> detector = cv::SIFT::create();
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1,descriptors2;

    detector->detectAndCompute(gray1, cv::noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(gray2, cv::noArray(), keypoints2, descriptors2);

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    std::vector<std::vector<cv::DMatch>> knn_matches;

    matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);

    // Ratio test to filter good matches
    const float ratio_thresh = 0.7f;
    std::vector<cv::DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++) {
        if (knn_matches[i][0].distance < ratio_thresh* knn_matches[i][1].distance) {
            good_matches.push_back(knn_matches[i][0]);
        }
    }

    // If the number of good matches is above the threshold, consider the images similar
    return good_matches.size() > threshold;
}


/**
Image matching using Bhattacharya distance
*/
bool CompareImagesByHistogram(const QPixmap& pixmap1, const QPixmap& pixmap2, double threshold) {
    // Convert QImage to cv::Mat
    cv::Mat img1 = QPixmapToMat(pixmap1);
    cv::Mat img2 = QPixmapToMat(pixmap2);

    // Convert images to grayscale
    cv::Mat gray1, gray2;
    cv::cvtColor(img1, gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2, gray2, cv::COLOR_BGR2GRAY);

    // Calculate histograms
    cv::Mat hist1, hist2;
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };

    cv::calcHist(&gray1, 1, 0, cv::Mat(), hist1, 1, &histSize, &histRange);
    cv::calcHist(&gray2, 1, 0, cv::Mat(), hist2, 1, &histSize, &histRange);

    // Normalize histograms
    cv::normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    // Calculate Bhattacharyya distance
    double bhattacharyya = cv::compareHist(hist1, hist2, cv::HISTCMP_BHATTACHARYYA);

    // If the Bhattacharyya distance is below the threshold, consider the images similar
    return bhattacharyya < threshold;
}

