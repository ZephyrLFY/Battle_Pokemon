#include "mainwindow.h"
#include "welcome.h"
#include "connection.h"
#include "petcreating.h"
#include "udpreceiver.h"
#include <QApplication>

//Log *loger = NULL;
udpReceiver *interact = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //loger = new Log;
    interact = new udpReceiver;
    MainWindow w;
    w.show();
    interact->show();
    return a.exec();
    /*welcome dlp;
    if(dlp.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else return 0;*/
}
