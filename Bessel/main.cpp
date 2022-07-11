#include "canvas_form.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CanvasForm canvas_form;
    canvas_form.show();
    a.exec();
    return 0;
}
