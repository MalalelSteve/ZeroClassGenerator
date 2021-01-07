#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtWidgets>
#include "FenCodeGenere.h"

class FenPrincipale : public QWidget {
    Q_OBJECT

public:
    FenPrincipale();

public slots:
    void ouvrirFenCodeGenere();

private:
    //////Méthodes
    QGroupBox *creerDefinitionClasse();
    QGroupBox *creerOptions();
    QGroupBox *creerAjoutCommentaires();

    QWidget *creerBoutons();

    QString genererEnTete();
    QString genererClasse();

    //////Attributs
    //Définition de la classe
    QLineEdit *m_nom;
    QLineEdit *m_classeMere;

    //Options
    QCheckBox *m_protegeHeader;
    QCheckBox *m_genereConstructeur;
    QCheckBox *m_genereDestructeur;

    //Ajouter des commentaires
    QGroupBox *m_ajoutCommentaires;
    QLineEdit *m_auteur;
    QDateEdit *m_dateCreation;
    QTextEdit *m_roleClasse;

};

#endif // FENPRINCIPALE_H
