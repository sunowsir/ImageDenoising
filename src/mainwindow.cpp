#include "mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
{

    this->resize( 740, 640 );

    this->w = new MainWidget( this );
    // this->resize(this->w->size()); //设置窗口大小
    setCentralWidget( this->w );

    this->t = new TrayWidget( this );

}

MainWindow::~MainWindow() {
    this->w->close();
    delete this->w;
    this->t->close();
    delete this->t;
}

/* slot */

void MainWindow::trayAction( QSystemTrayIcon::ActivationReason reason ) {
    if ( reason == QSystemTrayIcon::Trigger ) {
        this->showNormal();
    }
}


/* rewrite */

/*
void MainWindow::changeEvent( QEvent *e ) {
    if ( ( e->type() == QEvent::WindowStateChange ) && this->isMinimized() ) {
        QTimer::singleShot( 100, this, SLOT( close() ) );
    }
}


void MainWindow::closeEvent( QCloseEvent *e ) {
    e->ignore();
    this->hide();
}

*/

