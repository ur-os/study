#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QDialog>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() {
    about* about = new class about;
    about->show();
}

void MainWindow::on_textEdit_textChanged() {
    QString style = "font: ";

    if(ui->checkBox->checkState())
        style += "bold ";
    if(ui->checkBox_2->checkState())
        style += "italic ";

    switch(ui->comboBox_2->currentIndex()) {
        case 0:
            style += "9pt \"";
            break;
        case 1:
            style += "10pt \"";
            break;
        case 2:
            style += "12pt \"";
            break;
        case 3:
            style += "14pt \"";
            break;
        case 4:
            style += "18pt \"";
            break;
        case 5:
            style += "20pt \"";
            break;
    }

    switch(ui->comboBox->currentIndex()) {
        case 0:
            style += "Liberation Sans";
            break;
        case 1:
            style += "Liberation Serif";
            break;
        case 2:
            style += "Open Sans";
            break;
        case 3:
            style += "Ubuntu Mono";
            break;
        case 4:
            style += "Source Code Pro";
            break;
        case 5:
            style += "Roboto Slab";
            break;
    }

    style += "\";";
    ui->textEdit->setStyleSheet(style + "background-color: rgb(51, 51, 51);");
}

void MainWindow::on_comboBox_highlighted(int index) {
    ui->comboBox->setCurrentIndex(index);
    on_textEdit_textChanged();
}

void MainWindow::on_comboBox_2_highlighted(int index) {
    ui->comboBox_2->setCurrentIndex(index);
    on_textEdit_textChanged();
}

void MainWindow::on_checkBox_released() {
    on_textEdit_textChanged();
}

void MainWindow::on_checkBox_2_released() {
    on_textEdit_textChanged();
}

void MainWindow::on_pushButton_3_released() {

}
