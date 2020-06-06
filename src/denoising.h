#ifndef DENOISING_H
#define DENOISING_H

#include <QObject>
#include <QString>
#include <qimage.h>


#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/core.hpp>


class Denoising : public QObject
{
    Q_OBJECT

    cv::Mat initial_image;
    cv::Mat changed_image;

    QImage changed_Mat_image_to_QImage();
public:
    explicit Denoising(QObject *parent = nullptr);

    void load_Initial_image(const QString&);
    QImage salt_pepper_noise(const int&);
    QImage median_blur(const int&);
    QImage mean_blur(const cv::Size&);
    QImage gaussian_blur(const cv::Size&, const int&, const int&);
    QImage bilateral_filter(const int&, const int&, const int&);
signals:

};

#endif // DENOISING_H
