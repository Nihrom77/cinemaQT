#include "moviewindow.h"

#include <QtWidgets>

int main(int argc, char *argv[])
{


    QApplication app(argc, argv);

    MovieWindow win;
    win.show();

    return app.exec();
}



