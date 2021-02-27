#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.add_search_prog("test.py");
  w.add_search_prog("my_tuxi");
  w.show();
  return a.exec();
}
