#include "view/view.h"
#include <locale>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Model model;
    s21::Controller controller(&model);
    s21::View w(&controller);
    setlocale(LC_ALL, "C");
    w.show();
    return a.exec();
}
