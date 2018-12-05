#include "mainwindow.h"
#include "welcome.h"
#include "petcreating.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    welcome dlp;
    if(dlp.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    else
        return 0;
}
