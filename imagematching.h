#ifndef IMAGEMATCHING_H
#define IMAGEMATCHING_H

cv::Mat QPixmapToMat(const QImage& image);
QPixmap MatToQPixmap(const cv::Mat& mat);
bool CompareImagesByFeatureMatching(const QPixmap& pixmap1, const QPixmap& pixmap2, int threshold = 30);
bool CompareImagesByHistogram(const QPixmap& pixmap1, const QPixmap& pixmap2, double threshold = 0.2);
bool hasFace(const cv::Mat& image);
#endif // IMAGEMATCHING_H
