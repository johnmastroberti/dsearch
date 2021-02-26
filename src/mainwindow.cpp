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
    : QMainWindow(parent), ui(new Ui::MainWindow), watcher(this) {
  ui->setupUi(this);
  connect(&watcher, &QFutureWatcher<std::string>::resultReadyAt, this,
          &MainWindow::display_results);
}

MainWindow::~MainWindow() {
  delete ui;
  for (auto p : search_engines)
    delete p;
}

void MainWindow::add_search_prog(std::string prog) { // TODO
  search_engines.emplace_back(new SearchProg(prog));
}

void MainWindow::on_lineEdit_textChanged(const QString &s) {
  // Process results in parallel with QtConcurrent, QFuture, and QFutureWatcher

  const std::function<std::string(SearchEngine *)> do_search =
      [s](const SearchEngine *engine) {
        return engine->search(s.toStdString());
      };

  watcher.cancel();
  watcher.setFuture(QtConcurrent::mapped(search_engines, do_search));
}

void MainWindow::display_results(int ix) {
  std::cerr << watcher.resultAt(ix) << '\n';
}
