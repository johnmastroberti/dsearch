#pragma once
#include <QMainWindow>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_search_prog(std::string prog);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    std::vector<std::string> search_progs;

};
