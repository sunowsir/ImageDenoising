#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QtGui>
#include <QWidget>

#include <QMainWindow>

#include <QMessageBox>

#include "mainwidget.h"
#include "traywidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /* 主界面上面的一系列控件的集合 */
    MainWidget  *w;

    /* 系统托盘控件 */
    TrayWidget  *t;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /*
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *e);
    */

public slots:
    void trayAction(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
