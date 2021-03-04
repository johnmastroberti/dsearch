#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <algorithm>
#include <cstdio>
#include <fmt/core.h>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), watcher(this),
      stale_results(false) {
  ui->setupUi(this);
  connect(&watcher, &QFutureWatcher<std::string>::resultReadyAt, this,
          &MainWindow::display_results);

  ui->listView->setModel(&model);
  search_results << "Results will appear here";
  model.setStringList(search_results);

  QString style_sheet =
      R"(
QListView {
  font-family: Sans Serif;
  font-size: 48pt;
}
)";
  ui->listView->setStyleSheet(style_sheet);
  ui->listView->setWordWrap(true);
}

MainWindow::~MainWindow() {
  delete ui;
  for (auto p : search_engines)
    delete p;
}

void MainWindow::add_search_prog(const char *prog) { // TODO
  search_engines.emplace_back(new SearchProg(prog));
}

void MainWindow::on_lineEdit_textChanged(const QString &s) {
  // Process results in parallel with QtConcurrent, QFuture, and QFutureWatcher
  std::scoped_lock l(model_mtx);
  stale_results = true;

  const std::function<QString(SearchEngine *)> do_search =
      [s](const SearchEngine *engine) { return engine->search(s); };

  watcher.cancel();
  watcher.setFuture(QtConcurrent::mapped(search_engines, do_search));
}

void MainWindow::display_results(int ix) {
  // std::cerr << watcher.resultAt(ix) << '\n';
  std::scoped_lock l(model_mtx);
  if (stale_results)
    search_results.clear();

  QString result = watcher.resultAt(ix);
  if (result.length() == 0)
    return;
  search_results << result;
  model.setStringList(search_results);
  stale_results = false;
}
