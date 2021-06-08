#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {
    //creation de ma police
    int id = QFontDatabase::addApplicationFont(police_path);
    my_own_font = QFontDatabase::applicationFontFamilies(id).at(0);

    //allocation du fichier pour ecrire le meilleur score
    this->file = new QFile(scorefile_path);

    //fond d'ecran
    QPixmap background(background_path);
    this->fond = new QGraphicsPixmapItem(background);
    this->addItem(fond);

    //affichage du logo dragon ball z
    QPixmap logo_dbz(logo_dbz_path);
    this->logo = new QGraphicsPixmapItem(logo_dbz);
    logo->setPos(60,50);
    this->addItem(logo);

    //affichage nom du jeu
    this->name_game = new QGraphicsTextItem(QStringLiteral("Goku's training"));
    this->name_game->setDefaultTextColor(Qt::white);
    this->name_game->setFont(QFont(my_own_font, 24));
    name_game->setPos(20,200);
    this->addItem(name_game);

    //description
    this->description = new QGraphicsTextItem(QStringLiteral("Si vous avez besoin d'aide,"
                                                             "\ncliquez sur le bouton info"
                                                             "\n\n\n\n\n  Pour commencer le jeu,"
                                                             "\n      appuyez sur S"));
    this->description->setDefaultTextColor(Qt::white);
    this->description->setFont(QFont(my_own_font, 14));
    description->setPos(0,300);
    this->addItem(description);


    //allocation du joueur, et ajout de celui ci à la scene
    QPixmap player_img(goku_path);
    this->player = new QGraphicsPixmapItem(player_img);
    player->setPos(165,600);

    //allcoation de l'ennemi, et ajout de celui ci à la scene
    QPixmap ennemy_img(frieza_path);
    this->ennemy = new QGraphicsPixmapItem(ennemy_img);
    ennemy->setPos(165,0);

    //allocation du projectile, et ajout de celui ci à la scene
    QPixmap ki_img(ki1_path);
    this->ki = new QGraphicsPixmapItem(ki_img);
    ki->setPos(155,0);

    //allocation du kamehameha
    QPixmap kame_img(kame_path);
    this->kame = new QGraphicsPixmapItem(kame_img);

    //allocation de l'aura et eclair
    QPixmap aura_img(aura_path);
    this->aura = new QGraphicsPixmapItem(aura_img);
    QPixmap eclair_img(eclair_path);
    this->eclair = new QGraphicsPixmapItem(eclair_img);

    //affichage du score
    QPixmap ball(ball_path);
    this->sc = new QGraphicsPixmapItem(ball);
    sc->setPos(0,-2);

    this->livescore = new QGraphicsTextItem(QStringLiteral("%1").arg(score));
    this->livescore->setDefaultTextColor(Qt::white);
    this->livescore->setFont(QFont(my_own_font, 14));
    livescore->setPos(35,2);

    //affichage du nombre de kamehameha restants
    QPixmap logo_k(nb_kame_path);
    this->nbK = new QGraphicsPixmapItem(logo_k);
    nbK->setPos(2,27);

    this->live_kame = new QGraphicsTextItem(QStringLiteral("%1").arg(nb_kame));
    this->live_kame->setDefaultTextColor(Qt::white);
    this->live_kame->setFont(QFont(my_own_font, 14));
    live_kame->setPos(35,33);

    //affichage du record
    QPixmap logo_r(record_path);
    this->record = new QGraphicsPixmapItem(logo_r);
    record->setPos(2,60);
    this->new_score= new QGraphicsTextItem(QStringLiteral("Nouveau Record"));
    this->new_score->setDefaultTextColor(Qt::green);
    this->new_score->setFont(QFont(my_own_font,14));
    new_score->setPos(102,300);

    //on ouvre le fichier du record
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray best = file->readLine();
    int Best = best.toInt();
    file->close();
    this->joueur_record = new QGraphicsTextItem(QStringLiteral("%1").arg(Best));
    this->joueur_record->setDefaultTextColor(Qt::yellow);
    this->joueur_record->setFont(QFont(my_own_font, 14));
    joueur_record->setPos(35,60);

    //game over
    this->game_over = new QGraphicsTextItem(QStringLiteral("GAME OVER"));
    this->game_over->setDefaultTextColor(Qt::white);
    this->game_over->setFont(QFont(my_own_font, 30));
    game_over->setPos(30,200);

    this->restart = new QGraphicsTextItem(QStringLiteral(" Appuyez sur R,"
                                                         "\npour recommencer"));
    this->restart->setDefaultTextColor(Qt::white);
    this->restart->setFont(QFont(my_own_font, 14));
    restart->setPos(80,500);

    QPixmap gokufin1(gokufin_path);
    this->gokufin = new QGraphicsPixmapItem(gokufin1);
    gokufin->setPos(0,370);
    QPixmap goku_fin2(gokufin_path2);
    this->gokufin2 = new QGraphicsPixmapItem(goku_fin2);
    gokufin2->setPos(250,370);

    //pause
    this->pause = new QGraphicsTextItem(QStringLiteral("PAUSE"));
    this->pause->setDefaultTextColor(Qt::white);
    this->pause->setFont(QFont(my_own_font, 50));
    pause->setPos(50,400);

    //Debut du timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));


}
void MyScene::update(){

    int r = rand()%3;           //on crée un chiffre aléatoire pour définir la position du l'ennemi
    QPointF pos = ki->pos();    //récupération de la position de l'objet ki
    ki->setPos(pos.rx(), pos.ry()+speed); //incrémentation de la coordonnée y

    if(ki->pos().ry() >= 700){  //si le projectile ennemi atteint la ligne horizontale en bas
        QPointF pos_e = ennemy->pos();
        if(r == 0){             //position "0" : située à gauche
            ennemy->setPos(65,pos_e.ry());
            ki->setPos(45,0);
        }
        if(r == 1) {            //position "1" : située au milieu
            ennemy->setPos(165,pos_e.ry());
            ki->setPos(155,0);
        }
        if(r == 2){             //position "2" : située à droite
            ennemy->setPos(285,pos_e.ry());
            ki->setPos(265,0);
        }
        //on bloque la vitesse des projectiles à 40px sinon ca devient trop dur
        if(speed < 40){
        speed += 1;
        }
        score += 1;//on incrémente le score à chaque "retour à la ligne"

        //on change la couleur du score en direct si on est en train de faire le record
        file->open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray new_best = file->readLine();
        int new_Best = new_best.toInt();

        if(score > new_Best){
            this->livescore->setDefaultTextColor(Qt::green);
        }
        file->close();
        this->livescore->setPlainText(QStringLiteral("%1").arg(score));

    }
    if(score == 25){
        QPointF pos2 = player->pos();
        //on va ici changer l'image du personnage pour le faire level up en super sayan
        const QPixmap ssj_img(ssj_path);
        if(aura->isActive()){       //on regarde si l'objet aura est actif dans la scene et si oui, on le retire car l'update va en faire ajouter trop
            this->removeItem(aura); //à la scene donc on va en ajouter un a la fin et le retirer au debut de la condition ce aque
        }
        this->removeItem(player);   //meme demarche que pour l'aura
        this->player = new QGraphicsPixmapItem(ssj_img);
        player->setPos(pos2.rx(),pos2.ry());
        aura->setPos(pos2.rx()-20,pos2.ry()-45);
        this->addItem(aura);        //ici on ajoute l'item aura
        this->addItem(player);      //on ajoute l'item player a la scene mais avec une nouvelle image a la scene
    }
    if(score == 50){
        QPointF pos3 = player->pos();
        const QPixmap ssj3_img(ssj3_path);
        const QPixmap eclair_img(eclair_path);
        if(eclair->isActive()){     //meme procédé que pour l'aura au dessus
            this->removeItem(eclair);
        }
        this->removeItem(player);
        this->player = new QGraphicsPixmapItem(ssj3_img);//on definit la nouvelle image du personnage
        this->eclair = new QGraphicsPixmapItem(eclair_img);//on creer une image eclair pour accompagner le personnage
        player->setPos(pos3.rx(),pos3.ry());
        eclair->setPos(pos3.rx()-20,pos3.ry()-45);
        this->addItem(eclair);
        this->addItem(player);
    }
    if(score == 75){
        QPointF pos4 = player->pos();
        //on enleve les eclairs
        if(eclair->isActive()){
        this->removeItem(eclair);
        }
        //changement de personnage
        const QPixmap ssjb_img(ssjb_path);
        const QPixmap aurab_img(aura2_path);
        this->removeItem(aura);
        this->removeItem(player);
        this->player = new QGraphicsPixmapItem(ssjb_img);
        this->aura = new QGraphicsPixmapItem(aurab_img);
        player->setPos(pos4.rx(),pos4.ry());
        aura->setPos(pos4.rx()-20,pos4.ry()-45);
        this->addItem(aura);
        this->addItem(player);
        //changement d'ennemi
        QPointF pos5 = ennemy->pos();
        QPointF posk = ki->pos();
        const QPixmap cell_img(cell_path);
        const QPixmap cell_db(ki2_path);
        this->removeItem(ennemy);
        this->removeItem(ki);
        this->ennemy = new QGraphicsPixmapItem(cell_img);
        this->ki = new QGraphicsPixmapItem(cell_db);
        ennemy->setPos(pos5.rx(),pos5.ry());
        ki->setPos(posk.rx(),posk.ry());
        this->addItem(ennemy);
        this->addItem(ki);
        speed = 45;//on augmente la difficulté
    }
    if(score == 125){

        //changement de perso
        QPointF pos6 = player->pos();
        const QPixmap rose_img(rose_path);
        const QPixmap aura_img(aura3_path);
        this->removeItem(aura);
        this->removeItem(player);
        this->player = new QGraphicsPixmapItem(rose_img);
        this->aura = new QGraphicsPixmapItem(aura_img);
        player->setPos(pos6.rx(),pos6.ry());
        aura->setPos(pos6.rx()-20,pos6.ry()-45);
        this->addItem(aura);
        this->addItem(player);

        //changement d'ennemi
        QPointF pos7 = ennemy->pos();
        QPointF posk2 = ki->pos();
        const QPixmap buu_img(buu_path);
        const QPixmap buu_db(ki3_path);
        this->removeItem(ennemy);
        this->removeItem(ki);
        this->ennemy = new QGraphicsPixmapItem(buu_img);
        this->ki = new QGraphicsPixmapItem(buu_db);
        ennemy->setPos(pos7.rx(),pos7.ry());
        ki->setPos(posk2.rx(),posk2.ry());
        this->addItem(ennemy);
        this->addItem(ki);
        speed = 50;//on augmente encore plus la difficulté
    }
    if (ki->collidesWithItem(player)) {

        //on recupere le pseudo actuel du joueur
        QFile actual_player(username_path);
        actual_player.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&actual_player);
        actual_username = QString(in.readLine());


        qDebug() << "Collision !";
        qDebug() << "Votre score : "<< score;
        timer->stop();//on arrete le timer

        //on retire les elements inutiles de la scene
        this->removeItem(player);
        this->removeItem(ennemy);
        this->removeItem(ki);
        this->removeItem(sc);
        this->removeItem(livescore);
        this->removeItem(nbK);
        this->removeItem(live_kame);
        if(eclair->isActive()){
            this->removeItem(eclair);
        }
        if(aura->isActive()){
            this->removeItem(aura);
        }
        this->removeItem(record);

        //on ajoute les elements de l'ecran du game over
        this->removeItem(joueur_record);
        this->addItem(game_over);
        this->addItem(restart);
        this->addItem(gokufin);
        this->addItem(gokufin2);

        //score du joueur
        this->joueur_score = new QGraphicsTextItem(QStringLiteral("Votre score : %1").arg(score));
        this->joueur_score->setDefaultTextColor(Qt::white);
        this->joueur_score->setFont(QFont(my_own_font, 14));
        joueur_score->setPos(81,400);
        this->addItem(joueur_score);

        //enregistre dans le fichier
        file->open(QIODevice::ReadWrite | QIODevice::Text);
        QByteArray best = file->readLine(); //on va lire dans le fichier qui contient le meilleur score
        int Best = best.toInt();            //on converti ce qu'on avait lu dans le fichier en int
        QFile file2(bestuser_path);         //on definit le fichier du pseudo du meilleur joueur
        file2.open(QIODevice::ReadWrite | QIODevice::Text); //on ouvre le fichier du pseudo du meilleur joueur
        if(score > Best){       //si le meilleur score a été battu
            file->resize(0);//on vide le fichier pour avoir uniquement le meilleur score
            QTextStream stream(file);
            stream << score;//on remplit le fichier avec le meilleur score

            file2.resize(0);//on vide le fichier avec le pseudo du meilleur score
            QTextStream stream2(&file2);
            QString text = actual_username;
            stream2 << text;//on remplit le fichier le fichier avec le pseudo du meilleur joueur

            //on actualise l'affichage du  record si jamais on recommence sans relancer le programme
            joueur_record = new QGraphicsTextItem(QStringLiteral("%1").arg(score));
            joueur_record->setDefaultTextColor(Qt::yellow);
            joueur_record->setFont(QFont(my_own_font, 14));
            joueur_record->setPos(35,65);

            //on va afficher un message pour dire que le meilleur score a été battu
            this->addItem(new_score);
        }
        file->close();//on ferme les 2 fichiers
        file2.close();
    }
    if(nb_kame == 0){
        this->live_kame->setDefaultTextColor(Qt::red);//si on a plus d'attaques, on le met en rouge
    }
}
MyScene::~MyScene() {

}
void MyScene::keyPressEvent(QKeyEvent *event) {
    QPointF pos = player->pos(); //récupération de la position de l'objet player
    if(timer->isActive()) { //si le jeu est en train de "tourner"
        if (event->key() == Qt::Key_Left) { // appui sur la touche <- du clavier
            if (pos.rx() - 110 >= 0) {
                if (choix == 1) {   // choix definit le style de jeu du joueur
                    player->setPos(pos.rx() - 110, pos.ry());
                    aura->setPos(pos.rx() - 130, pos.ry() - 45);
                    eclair->setPos(pos.rx() - 130, pos.ry() - 45);
                }
                if (choix == 0) {
                    player->setPos(pos.rx() - 110, pos.ry());
                    aura->setPos(pos.rx() - 130, pos.ry() - 45);
                    eclair->setPos(pos.rx() - 130, pos.ry() - 45);
                }
            }
        }
        if (event->key() == Qt::Key_Right) { // appui sur la touche -> du clavier
            if (pos.rx() + 150 < 400) {
                if (choix == 1) {
                    player->setPos(pos.rx() + 110, pos.ry());
                    aura->setPos(pos.rx() + 90, pos.ry() - 45);
                    eclair->setPos(pos.rx() + 90, pos.ry() - 45);
                }
                if (choix == 0) {
                    player->setPos(pos.rx() + 110, pos.ry());
                    aura->setPos(pos.rx() + 90, pos.ry() - 45);
                    eclair->setPos(pos.rx() + 90, pos.ry() - 45);
                }
            }
        }
        if (event->key() == Qt::Key_Space && nb_kame != 0) {//on regarde si on a toujours des attaques et si on appui sur espace
            int r = rand() % 3;//on redéfinit une variable aleatoire
            kame->setPos(pos.rx(), pos.ry() - 350);//on definit la position de l'image kamehameha
            this->addItem(kame);
            nb_kame -= 1;
            this->live_kame->setPlainText(QStringLiteral("%1").arg(nb_kame));//on actualise le compteur d'attaque en direct
            if (kame->collidesWithItem(ki)) {//si l'attaque du joueur touche une attaque ennemi
                QPointF pos_e = ennemy->pos();
                if (r == 0) {//on remplace l'attaque ennemie comme dans le update avec les 3 positions définies par r
                    ennemy->setPos(65, pos_e.ry());
                    ki->setPos(45, 0);
                }
                if (r == 1) {
                    ennemy->setPos(165, pos_e.ry());
                    ki->setPos(155, 0);
                }
                if (r == 2) {
                    ennemy->setPos(285, pos_e.ry());
                    ki->setPos(265, 0);
                }
                score += 1;
                this->livescore->setPlainText(QStringLiteral("%1").arg(score));
            }
        }
    }
    if(event->key() == Qt::Key_P) { // appui sur la touche p du clavier

        if(timer->isActive()) {
            timer->stop();//on fait pause sur le timer
            addItem(pause);
        }else
        {
            timer->start();//on remet le timer en marche
            removeItem(pause);
        }
    }
    if(event->key() == Qt::Key_S){
        //on va afficher la scene de jeu et faire disparaitre l'ecran d'accueil
        this->removeItem(name_game);
        this->removeItem(description);
        this->removeItem(logo);
        timer->start(30);
        this->addItem(player);
        this->addItem(ennemy);
        this->addItem(ki);
        this->addItem(sc);
        this->addItem(livescore);
        this->addItem(nbK);
        this->addItem(live_kame);
        this->addItem(record);
        this->addItem(joueur_record);
        choix = 0;//on definit le style de jeu avec relachement par defaut
    }
    if(event->key()==Qt::Key_C){//pour changer le choix du  deplacement du joueur
        if(choix == 0){
            choix = 1;
        }else{
            choix = 0;
        }
    }
    if(event->key() == Qt::Key_R){
        timer->start();
        //on remet les compteurs à 0
        speed = 10;
        score = 0;
        nb_kame = 3;
        //joueur
        //on remet l'image de goku normal  par defaut
        QPixmap player_img(goku_path);
        this->player = new QGraphicsPixmapItem(player_img);
        player->setPos(165,600);
        //ennemi
        //on remet l'image de frieza comme ennemi par defaut
        QPixmap frieza_img(frieza_path);
        this->ennemy = new QGraphicsPixmapItem(frieza_img);
        ennemy->setPos(165,0);
        //on remet l'image du ki  par defaut
        QPixmap ki_img(ki1_path);
        this->ki = new QGraphicsPixmapItem(ki_img);
        ki->setPos(155,0);
        //on remet l'image de l'aura par defaut
        QPixmap aura_img(aura_path);
        this->aura = new QGraphicsPixmapItem(aura_img);
        //on les reaffiche
        this->addItem(player);
        this->addItem(ennemy);
        this->addItem(ki);
        this->addItem(sc);
        this->livescore->setPlainText(QStringLiteral("%1").arg(score));
        this->livescore->setDefaultTextColor(Qt::white);
        this->addItem(livescore);
        this->addItem(nbK);
        this->live_kame->setPlainText(QStringLiteral("%1").arg(nb_kame));
        this->live_kame->setDefaultTextColor(Qt::white);
        this->addItem(live_kame);
        //on enleve l'ecran game over
        this->removeItem(game_over);
        this->removeItem(joueur_score);
        this->removeItem(restart);
        this->removeItem(gokufin);
        this->removeItem(gokufin2);
        this->removeItem(new_score);
        //
        this->addItem(record);
        this->addItem(joueur_record);
    }
}
void MyScene::keyReleaseEvent(QKeyEvent *event) {
    QPointF pos = player->pos(); //récupération de la position de l'objet player
    if(timer->isActive()) {
        if (event->key() == Qt::Key_Left) {
            //ici si le jeu est a 0, cest le style de jeu avec relachement donc quand on va lacher la touche, le personnage reviendra au milieu
            if (event->KeyRelease && choix == 0) {
                player->setPos(pos.rx() + 110, pos.ry());
                aura->setPos(pos.rx() + 90, pos.ry() - 45);
                eclair->setPos(pos.rx() + 90, pos.ry() - 45);
            }
        }
        if (event->key() == Qt::Key_Right) {
            if (event->KeyRelease && choix == 0) {
                player->setPos(pos.rx() - 110, pos.ry());
                aura->setPos(pos.rx() - 130, pos.ry() - 45);
                eclair->setPos(pos.rx() - 130, pos.ry() - 45);
            }
        }
    }
    if (event->key() == Qt::Key_Space) {
        //quand on lachera la touche espace, l'image du kamehameha disparaitra
        if (event->KeyRelease) {
            this->removeItem(kame);
        }
    }
}