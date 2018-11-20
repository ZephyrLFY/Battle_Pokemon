#include "mainwindow.h"
#include "welcome.h"
#include "connection.h"
#include "petcreating.h"
#include "udpreceiver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    welcome dlp;
    if(dlp.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else return 0;
}
