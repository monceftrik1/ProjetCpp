#ifndef MATERIEL_H
#define MATERIEL_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

class materiel
{
private:
    int id,age;
    QString matricul,nom_machine,etat;
    float capacite,prix;
public:
    materiel();
    materiel(int,int,QString,QString,QString,float,float);
    //CRUD functions
    bool ajouterMateriel();
    QSqlQueryModel * afficherMateriel();
    bool supprimerMateriel(int);
    bool modifierMateriel();
};

#endif // MATERIEL_H
