#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include "MyScene.h"
#include "ConnectWindow.h"

class MainWindow : public QMainWindow {
Q_OBJECT

private :
    MyScene* mainScene;
    QGraphicsView* mainView;
    QAction* conn;
    QAction* info;
    QAction* about_record;
    QAction* pseudo_actuel;
    Username connexion;
public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void slot_info();
    void slot_record();
    void slot_connect();
    void slot_direct();
};


#endif //MAINWINDOW_H
