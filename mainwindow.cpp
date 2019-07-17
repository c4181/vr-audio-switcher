#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_setupMenu_triggered() {
  SetupDialog dialog(this);
  dialog.exec();
}
