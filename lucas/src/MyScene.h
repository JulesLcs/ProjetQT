#ifndef MYSCENE_H
#define MYSCENE_H

//changer ici les chemins pour les images ressources
//on definit ici les chemins d'acces aux images utilisées pour le jeu

//persos
#define goku_path ("../ressources/goku.png")
#define ssj_path ("../ressources/gokussj1.png")
#define ssj3_path ("../ressources/gokussj3.png")
#define ssjb_path ("../ressources/gokussjb.png")
#define rose_path ("../ressources/goku_rose.png")
//ennemis
#define frieza_path ("../ressources/frieza.png")
#define cell_path ("../ressources/cell.png")
#define buu_path ("../ressources/buu.png")
//ki
#define ki1_path ("../ressources/death_ball.png")
#define ki2_path ("../ressources/death_ball2.png")
#define ki3_path ("../ressources/death_ball3.png")
//aura
#define aura_path ("../ressources/aurassj.png")
#define aura2_path ("../ressources/aura_blue.png")
#define aura3_path ("../ressources/aura_rose.png")
//fichiers
#define scorefile_path ("../ressources/record.txt")
#define username_path ("../ressources/username.txt")
#define bestuser_path ("../ressources/userbest.txt")
//autres
#define background_path ("../ressources/background.png")
#define logo_dbz_path ("../ressources/dragonballz.png")
#define kame_path ("../ressources/kame.png")
#define eclair_path ("../ressources/eclair.png")
#define ball_path ("../ressources/ball.png")
#define nb_kame_path ("../ressources/nb_kame.png")
#define record_path ("../ressources/record.png")
#define eclair_path ("../ressources/eclair.png")
//police
#define police_path ("../ressources/police.ttf")
//ecran de fin
#define gokufin_path ("../ressources/gokufin.png")
#define gokufin_path2 ("../ressources/gokufin2.png")

#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <QString>
#include <QTextEdit>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFile>
#include <QFontDatabase>

class MyScene : public QGraphicsScene {
Q_OBJECT
public:
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();
public slots:
    void update();
private:

    QTimer* timer = new QTimer; //le timer du jeu
    QGraphicsPixmapItem* ennemy;//l'image de l'ennemi
    QGraphicsPixmapItem* ki;    //l'image des attaques ennemies
    QGraphicsPixmapItem* player;//l'image de notre personnage


    QGraphicsPixmapItem* aura;  //image de l'aura
    QGraphicsPixmapItem* eclair;//image de l'eclair
    int speed = 10;             //creation d'une variable qui va augmenter la vitesse
    QGraphicsPixmapItem* fond;  //image du fond d'ecran

    //score
    QGraphicsPixmapItem* sc;    //logo du score
    QGraphicsTextItem* livescore;//le texte du score en direct qui s'incrémente
    int score = 0;              //la variable du score qui s'incrémente

    //nb atq restants
    int nb_kame = 3;            //variable qui donnera la possibilite au joueur de supprimer un ki ennemi
    QGraphicsPixmapItem* nbK;   //le logo du nombre de kamehameha restants
    QGraphicsPixmapItem* kame;  //l'image du kamehameha
    QGraphicsTextItem* live_kame;//le texte des kamehameha qui va indiquer le nombre restants

    //ecran d'accueil
    QGraphicsTextItem* name_game;//texte avec le nom du jeu
    QGraphicsTextItem* description;//texte avec une rapide description du jeu
    QGraphicsPixmapItem* logo;//logo dragon ball z

    //ecran game over
    QGraphicsTextItem* game_over;//text game over
    QGraphicsTextItem* joueur_score;//le score fait par le joueur
    QGraphicsTextItem* restart;//l'affichage pour dire au joueur qu'il peut recommencer
    QGraphicsTextItem* new_score;//un texte qui s'affichera si le score a été battu
    QGraphicsPixmapItem* gokufin;//une image pour décorer
    QGraphicsPixmapItem* gokufin2;//idem

    //fichier score
    QGraphicsPixmapItem* record;//le logo du record (un trophée)
    QGraphicsTextItem* joueur_record;//le record actuel qui est affiché en jeu
    QFile* file;//le fichier qui contient le pseudo du meilleur joueur

    //Ma police importée
    QString my_own_font;

    //choix du style de jeu si cest 1, alors on se deplace sans le retour au relachement , si cest 0 alors il y a relachement
    int choix;

    //on recupere le nom de l'utilisateur actuel
    QString actual_username;

    //pause
    QGraphicsTextItem* pause;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};


#endif //MYSCENE_H
