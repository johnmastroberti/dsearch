#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.add_search_prog("python -c");
  w.show();
  return a.exec();
}
