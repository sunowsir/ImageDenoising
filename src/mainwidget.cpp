#include "mainwidget.h"


MainWidget::MainWidget(QMainWindow *parent) : QWidget(parent)
{
    
    this->settings = new QSettings( QCoreApplication::applicationDirPath() + "/Config.ini", QSettings::IniFormat );
    qDebug() << QCoreApplication::applicationDirPath() + "/Config.ini";

    this->parent = parent;


    /* set default noise frequency. */

    this->noise_frequency = 1000;


    /* Initialize denoising method and denoising method choise list. */

    this->denoising_method = QString("中值滤波");
    this->denoising_method_list << QString("中值滤波")
                                << QString("均值滤波")
                                << QString("傅里叶滤波")
                                << QString("小波滤波");


    /* Select image button */

    this->image_select_button = new QPushButton(this);
    this->image_select_button->setText(QString("选择图片"));
    this->image_select_button->move(410, 490);
    this->image_select_button->resize(100, 30);


    /* Add noise button */

    this->add_noise_button = new QPushButton(this);
    this->add_noise_button->setText(QString("添加噪声"));
    this->add_noise_button->move(410, 590);
    this->add_noise_button->resize(100, 30);


    /* excute denoising method use button*/

    this->execute_method_button = new QPushButton(this);
    this->execute_method_button->setText(QString("消除噪声"));
    this->execute_method_button->move(600, 540);
    this->execute_method_button->resize(100, 30);


    /* Clear button */

    this->clear_button = new QPushButton(this);
    this->clear_button->setText((QString("清除")));
    this->clear_button->move(600, 590);
    this->clear_button->resize(100, 30);


    /* Use QLineEdit to setup the noise fequency. */

    this->noise_frequency_edit = new QLineEdit(this);
    this->noise_frequency_edit->setPlaceholderText(QString("加噪次数"));
    this->noise_frequency_edit->move(410, 540);
    this->noise_frequency_edit->resize(100, 30);


    /* Use the QComboBox to select denoising method. */

    this->denoising_method_combobox = new QComboBox(this);
    this->denoising_method_combobox->addItems(this->denoising_method_list);
    this->denoising_method_combobox->move(600, 490);
    this->denoising_method_combobox->resize(100, 30);


    /* Use the QLabel to display the initial image. */

    this->show_initial_image_label = new QLabel(this);
    this->show_initial_image_label->move(10, 10);
    this->show_initial_image_label->resize(350, 300);


    /* Use the QLabel to display noisy image. */

    this->show_image_with_noise_label = new QLabel(this);
    this->show_image_with_noise_label->move(10, 330);
    this->show_image_with_noise_label->resize(350, 300);

    /* Use the QLabel to display noiseless image. */

    this->show_noiseless_image_label = new QLabel(this);
    this->show_noiseless_image_label->move(380, 10);
    this->show_noiseless_image_label->resize(350, 300);


    /* Use QTextEdit to display run information. */

    this->show_edit = new QTextEdit(this);
    this->show_edit->setReadOnly(true);
    this->show_edit->move(380, 330);
    this->show_edit->resize(350, 150);
    this->show_edit->setText(QString("程序已启动"));


    /* Use the Denoising class to denoising image. */

    this->denoising_master = new Denoising(this);


    /* connect signal with slot */

    QWidget::connect(this->image_select_button, SIGNAL(released()),
                      this, SLOT(select_image_from_local()),
                      Qt::AutoConnection);
    QWidget::connect(this->add_noise_button, SIGNAL(released()),
                      this, SLOT(add_noise()),
                      Qt::AutoConnection);
    QWidget::connect(this->execute_method_button, SIGNAL(released()),
                      this, SLOT(excute_method()),
                      Qt::AutoConnection);
    QWidget::connect(this->clear_button, SIGNAL(released()),
                      this, SLOT(clear()),
                      Qt::AutoConnection);
    QWidget::connect(this->noise_frequency_edit, SIGNAL(textChanged(QString)),
                      this, SLOT(get_noise_frequency(const QString&)),
                      Qt::AutoConnection);
    QWidget::connect(this->denoising_method_combobox, SIGNAL(activated(const QString&)),
                      this, SLOT(get_denoising_method(QString)),
                      Qt::AutoConnection);

}

MainWidget::~MainWidget() {

}


/* slot */

void MainWidget::select_image_from_local() {

    QFileDialog *image_select_file_dialog = new QFileDialog(this);

    image_select_file_dialog->setWindowTitle(QString("打开图片"));
    image_select_file_dialog->setDirectory(".");
    image_select_file_dialog->setNameFilter(QString("Images(*.png *.jpg *.jpeg *.bmp)"));
    image_select_file_dialog->setFileMode(QFileDialog::ExistingFiles);
    image_select_file_dialog->setViewMode(QFileDialog::Detail);

    if (image_select_file_dialog->exec()) {
        QStringList image_list;
        image_list = image_select_file_dialog->selectedFiles();
        this->initial_image_name = image_list[0];
        QPixmap pix(this->initial_image_name);
        QPixmap dest=pix.scaled(this->show_initial_image_label->size(),Qt::KeepAspectRatio);

        this->denoising_master->load_Initial_image(this->initial_image_name);
        this->show_edit->append(QString("已选图片 : ") + this->initial_image_name);

        this->show_initial_image_label->setPixmap(QPixmap());
        this->show_initial_image_label->setPixmap(dest);
    }

    delete image_select_file_dialog;
}

void MainWidget::add_noise() {

    if (this->initial_image_name.isEmpty()) {
        this->show_edit->append(QString("图片为空"));
        return ;
    }


    QImage ret_image = this->denoising_master->salt_pepper_noise(this->noise_frequency);
    this->show_edit->append(QString("椒盐噪声已添加"));


    /* 将已经加噪的图片显示出来 */

    QPixmap pix = QPixmap::fromImage(ret_image);
    QPixmap dest=pix.scaled(this->show_initial_image_label->size(),Qt::KeepAspectRatio);
    this->show_image_with_noise_label->setPixmap(QPixmap(dest));

}

void MainWidget::excute_method() {

    if (this->initial_image_name.isEmpty()) {
        this->show_edit->append(QString("图片为空"));
        return ;
    }


    QImage ret_image;


    if (this->denoising_method == QString("中值滤波")) {
        ret_image = this->denoising_master->median_blur(3);
    } else if (this->denoising_method == QString("均值滤波")) {
        ret_image = this->denoising_master->mean_blur(cv::Size(3, 3));
    } else if (this->denoising_method == QString("傅里叶滤波")) {
        ret_image = this->denoising_master->gaussian_blur(cv::Size(3, 3), 10, 20);
    } else {
        ret_image = this->denoising_master->bilateral_filter(30, 30, 30);
    }
    this->show_edit->append(QString("降噪完成"));


    /* 将已经去噪的图片显示出来 */

    QPixmap pix = QPixmap::fromImage(ret_image);
    QPixmap dest=pix.scaled(this->show_initial_image_label->size(),Qt::KeepAspectRatio);
    this->show_noiseless_image_label->setPixmap(QPixmap(dest));

}

void MainWidget::clear() {
    this->show_edit->setText(QString());
    this->show_initial_image_label->setPixmap(QPixmap());
    this->initial_image_name.clear();
    this->show_image_with_noise_label->setPixmap(QPixmap());
    this->show_noiseless_image_label->setPixmap(QPixmap());
}

void MainWidget::get_noise_frequency(const QString &input_str) {
    this->noise_frequency = input_str.toInt();
}


void MainWidget::get_denoising_method( const QString& choice_str ) {
    this->denoising_method = choice_str;
    this->show_edit->append((QString("已选降噪方式 : ") + this->denoising_method));
}


