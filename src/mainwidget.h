#ifndef loginWIDGET_H
#define loginWIDGET_H

#include <QtGui>
#include <QMenu>
#include <QList>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QProcess>
#include <QCheckBox>
#include <QComboBox>
#include <QSettings>
#include <QPushButton>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QtNetwork/QNetworkInterface>
#include <QProcessEnvironment>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <QMainWindow>
#include <qfiledialog.h>
#include <qpixmap.h>


#include "denoising.h"


class MainWidget : public QWidget
{
    Q_OBJECT

    QSettings       *settings;
    QMainWindow     *parent;


    /* Button */

    QPushButton     *image_select_button;
    QPushButton     *add_noise_button;
    QPushButton     *execute_method_button;
    QPushButton     *clear_button;


    /* ComboBox */

    QComboBox		*denoising_method_combobox;


    /* Label */

    QLabel 			*show_initial_image_label;
    QLabel 			*show_image_with_noise_label;
    QLabel 			*show_noiseless_image_label;


    /* TextEdit */

    QTextEdit 		*show_edit;


    /* LineEdit */

    QLineEdit 		*noise_frequency_edit;


    /* Denoising class */

    Denoising 		*denoising_master;

    /* information */

    int 			noise_frequency;
    QString 		initial_image_name;
    QString 		noiseless_image_name;
    QString			denoising_method;
    QStringList		denoising_method_list;


    void get_denoising_method_list();
    static QString runProOnce(QString pro_name = "", QStringList arg = QStringList());
signals:

public:
    explicit MainWidget(QMainWindow *parent = nullptr);
    ~MainWidget();

public slots:
    void select_image_from_local();
    void add_noise();
    void excute_method();
    void clear();
    void get_noise_frequency(const QString&);
    void get_denoising_method(const QString&);
};

#endif // loginWIDGET_H
