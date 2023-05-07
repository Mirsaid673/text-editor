#include <QApplication>
#include <QWidget>
#include "editor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Editor editor;

    editor.show();
    return a.exec();
}
