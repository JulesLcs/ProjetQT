#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);
    this->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //cache la barre sur le bas
    this->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //cache la barre sur le cote
    this->mainView->setFixedSize(400,800);                            //on definit la taille fixe sur 400x800
    this->setCentralWidget(mainView);
    this->setWindowTitle("Jules's Game");                                   //le nom de ma fenetre
    this->setFixedSize(400, 800);
    mainScene->setSceneRect(0,0,400,800);//on definit la scene du rectangle pour 0,0 dans le coin haut-gauche


    conn = menuBar()->addAction(tr("Se connecter"));                //on cree une action se connecter dans la barre du menu
    pseudo_actuel = menuBar()->addAction(tr("Joueur actuel"));      //on cree une action joueur_actuel dans la barre du menu pour savoir si on est connecté en tant que ...
    info = menuBar()->addAction(tr("Info"));                        //on cree une action info dans la barre du menu
    about_record = menuBar()->addAction(tr("Record"));              //on cree une action record dans la barre du menu pour savoir qui detient le record avec combien

    //on active les slots avec des signaux clicked()
    connect(info, SIGNAL(triggered()), this, SLOT(slot_info()));
    connect(about_record, SIGNAL(triggered()), this, SLOT(slot_record()));
    connect(conn, SIGNAL(triggered()), this, SLOT(slot_connect()));
    connect(pseudo_actuel, SIGNAL(triggered()), this, SLOT(slot_direct()));

}

MainWindow::~MainWindow(){

}

//le slot qui va afficher les infos
void MainWindow::slot_info(){
    QMessageBox msgBox;
    msgBox.setText("Règles : Evitez les attaques ennemies et obtenez le meilleur score\n\n"
                   "Commandes :\n\n"
                   "* S pour commencer la 1ère partie\n"
                   "* <- flèche gauche pour aller à gauche\n"
                   "* -> flèche droite pour aller à droite\n"
                   "* Espace pour envoyer un kamehama\n"
                   "* P pour faire pause\n"
                   "* R pour recommencer \n\n "
                   "Pour changer le mode de déplacement : appuyez 1 fois sur C \n\n "
                   "Choix 0(par défaut) = Retour au milieu au relachement \n "
                   "Choix 1 = Retour manuel avec les touches");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}
//le slot qui va afficher le record
void MainWindow::slot_record() {
    QMessageBox msgBox;

    QFile file(scorefile_path);//on lit le fichier du meilleur score
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray best = file.readLine();
    int Best = best.toInt();
    file.close();

    QFile file2(bestuser_path);//on lit le fichier du meilleur joueur
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file2);
    QString joueur(in.readLine());
    file2.close();
    msgBox.setText(QStringLiteral("%1 a fait le meilleur score avec %2").arg(joueur).arg(Best));//on affiche tout ca dans un messagebox
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}
//le slot qui va afficher la classe username
void MainWindow::slot_connect() {
    connexion.show();//on va afficher l'objet de la classe username en attribut
}
//le slot qui va afficher le pseudo du joueur actuel
void MainWindow::slot_direct() {
    QMessageBox msgBox;
    QFile file(username_path);//on recupere le pseudo du joueur dans le fichier
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString joueur_direct(in.readLine());
    file.close();
    msgBox.setText(QStringLiteral("Vous êtes connecté en tant que %1").arg(joueur_direct));
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}