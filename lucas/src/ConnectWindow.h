//
// Created by Jules on 30/05/2021.
//


#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H


#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QLabel>
#include<QMessageBox>
#include "MyScene.h"

#include "iostream"
using namespace std;

class Username : public QMainWindow{
    Q_OBJECT
public:
    explicit Username();
private:
    QLabel* label = new QLabel;
    QTextEdit* username = new QTextEdit;
    QPushButton* btn = new QPushButton;
    QFile* user;
public slots:
    void envoyer();
};


#endif //CONNECTWINDOW_H
