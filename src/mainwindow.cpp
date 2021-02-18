#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <fmt/core.h>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->hide();
    ui->label->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_search_prog(std::string prog) {
  search_progs.emplace_back(std::move(prog));
}

void MainWindow::on_lineEdit_textChanged(const QString & s)
{
  std::string results;
  for (const auto& prog : search_progs) {
    auto cmd = fmt::format("{} '{}'", prog, s.toStdString());
    std::cerr << cmd << '\n';
    FILE *process = popen(cmd.c_str(), "r");
    std::stringstream process_output;
    char buf[1024];
    while( fgets(buf, sizeof(buf), process) )
      process_output << buf;

    auto ret = pclose(process);
    std::cerr << ret << '\n';
    if (ret) continue;
    results += fmt::format("{}\n", prog);
    results += process_output.str();
    std::cerr << results << '\n';
  }


  if (results.size()) {
    ui->label->setText(QString::fromStdString(results));
    ui->label->show();
  } else {
    ui->label->setText("");
    ui->label->hide();
  }

}

