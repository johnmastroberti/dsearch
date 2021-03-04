#pragma once
#include <QMainWindow>
#include <QtConcurrent>
#include <memory>
#include <mutex>
#include <vector>

#include "searchengine.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void add_search_prog(const char *prog);

public slots:
  void on_lineEdit_textChanged(const QString &arg1);
  void display_results(int ix);

private:
  Ui::MainWindow *ui;
  std::vector<SearchEngine *> search_engines;
  QFutureWatcher<QString> watcher;

  QStringListModel model;
  QStringList search_results;
  mutable std::mutex model_mtx;
  bool stale_results;
};
