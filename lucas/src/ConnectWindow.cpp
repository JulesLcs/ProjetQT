//
// Created by Jules on 30/05/2021.
//
#include "ConnectWindow.h"
Username::Username() {
    this->user = new QFile(username_path);
    this->setWindowTitle("Connexion");
    this->setMinimumSize(200,30);

    label->setText("Entrez votre pseudo :");
    username->setFixedSize(200,30); //le username va prendre le texte rentré soit le pseudo du joueur
    btn->setText("Confirmer");

    QWidget* mainWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout();

    mainLayout->addWidget(label);
    mainLayout->addWidget(username);
    mainLayout->addWidget(btn);



    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
    connect(btn,SIGNAL(clicked()),this,SLOT(envoyer()));//quand on va appuyer sur le bouton confirmer, on va activer le slot envoyer

}
//le slot va envoyer le texte de la fenetre qui est entré dans le QTextEdit dans le fichier username.txt ( qui contient le pseudo actuel )
void Username::envoyer() {
    user->open(QIODevice::WriteOnly | QIODevice::Text);
    user->resize(0);
    QTextStream stream(user);
    QString text = username->toPlainText();
    if(text != ""){
        stream << text;
    }else{
        QMessageBox msgBox;
        msgBox.setText("Rentrez un pseudo (votre pseudo a été défini par défaut en tant que 'invite') ");
        msgBox.exec();
        stream << "invite";
    }
    user->close();
    this->close();
}
