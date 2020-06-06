#include "denoising.h"
#include <QtDebug>

Denoising::Denoising(QObject *parent) : QObject(parent) {}

void Denoising::load_Initial_image(const QString &initial_image_name) {

    cv::Mat read_image = cv::imread(initial_image_name.toStdString());

    if (read_image.empty()) {
        qDebug() << "read image error.";
    }

    this->initial_image = read_image.clone();
    this->changed_image = this->initial_image.clone();

}

QImage Denoising::changed_Mat_image_to_QImage() {
    switch (this->changed_image.type()) {
        /* 8-bit, 4 channel */
        case CV_8UC4 : {
            QImage image( this->changed_image.data, this->changed_image.cols, this->changed_image.rows, this->changed_image.step, QImage::Format_RGB32);
            return image;
        };

        /* 8-bit, 3 channel */
        case CV_8UC3 : {
            QImage image( this->changed_image.data, this->changed_image.cols, this->changed_image.rows, this->changed_image.step, QImage::Format_RGB888 );
            return image.rgbSwapped();
        };

         /* 8-bit, 1 channel */
        case CV_8UC1 : {
            static QVector<QRgb>  sColorTable;
            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }
            QImage image( this->changed_image.data, this->changed_image.cols, this->changed_image.rows, this->changed_image.step, QImage::Format_Indexed8 );
            image.setColorTable( sColorTable );
            return image;
         };

        default : {
           qDebug("Image format is not supported: depth=%d and %d channels\n", this->changed_image.depth(), this->changed_image.channels());
        };
    }

    return QImage();
}

/* 盐噪声函数 */
QImage Denoising::salt_pepper_noise(const int &processint_times) {
    cv::RNG rng(123456);
    int h = this->changed_image.rows;
    int w = this->changed_image.cols;

    for (int i = 0; i < processint_times; i++) {
        // 生成噪声点
        int x = rng.uniform(0, w);
        int y = rng.uniform(0, h);

        // 把噪声点写到图像上
        if (i % 2 == 1) {
            this->changed_image.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
        }
        else {
            this->changed_image.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
        }
    }

    return this->changed_Mat_image_to_QImage();
}


/* 中值滤波 */
QImage Denoising::median_blur(const int &ksize) {
    medianBlur(this->initial_image, this->changed_image, ksize);
    return this->changed_Mat_image_to_QImage();
}


/* 均值滤波 */
QImage Denoising::mean_blur(const cv::Size &ksize) {
    cv::blur(this->initial_image, this->changed_image, ksize);
    return this->changed_Mat_image_to_QImage();
}


/* 傅里叶滤波 */
QImage Denoising::gaussian_blur(const cv::Size &ksize, const int &sigmax, const int &sigmay) {
    cv::GaussianBlur(this->initial_image, this->changed_image, ksize, sigmax, sigmay);
    return this->changed_Mat_image_to_QImage();
}


/* 小波滤波 */
QImage Denoising::bilateral_filter(const int &d, const int &sigma_color_value, const int &sigma_space_value) {
    cv::bilateralFilter(this->initial_image, this->changed_image, d, sigma_color_value, sigma_space_value);
    return this->changed_Mat_image_to_QImage();
}
