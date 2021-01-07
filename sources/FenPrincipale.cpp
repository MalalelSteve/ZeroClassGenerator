#include "FenPrincipale.h"

FenPrincipale::FenPrincipale() : QWidget() {
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(creerDefinitionClasse());
    mainLayout->addWidget(creerOptions());
    mainLayout->addWidget(creerAjoutCommentaires());
    mainLayout->addWidget(creerBoutons());

    this->setLayout(mainLayout);
}

void FenPrincipale::ouvrirFenCodeGenere() {
    QString enTete = genererEnTete();
    QString classe = genererClasse();

    QString code;
    code.append("<pre>");
    if (m_ajoutCommentaires->isChecked()) {
        code.append(enTete);
    }
    code.append(classe + "</pre>");

    FenCodeGenere *secondeFenetre = new FenCodeGenere(code);
    secondeFenetre->exec();
}

QGroupBox *FenPrincipale::creerDefinitionClasse() {
    QGroupBox *groupBox = new QGroupBox("Définition de la classe", this);
    QFormLayout *layoutForm = new QFormLayout(this);

    m_nom = new QLineEdit;
    m_classeMere = new QLineEdit;

    layoutForm->addRow("&Nom :", m_nom);
    layoutForm->addRow("Classe &mère :", m_classeMere);

    groupBox->setLayout(layoutForm);

    return groupBox;
}

QGroupBox *FenPrincipale::creerOptions() {
    QGroupBox *groupBox = new QGroupBox("Options", this);
    QVBoxLayout *layout = new QVBoxLayout;

    m_protegeHeader = new QCheckBox("Protéger le &header contre les inclusions multiples", this);
    m_genereConstructeur = new QCheckBox("Générer un &constructeur par défaut", this);
    m_genereDestructeur = new QCheckBox("Générer un &destructeur", this);

    m_protegeHeader->setChecked(true);
    m_genereConstructeur->setChecked(true);
    m_genereDestructeur->setChecked(true);

    layout->addWidget(m_protegeHeader);
    layout->addWidget(m_genereConstructeur);
    layout->addWidget(m_genereDestructeur);

    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *FenPrincipale::creerAjoutCommentaires() {
    m_ajoutCommentaires = new QGroupBox("Ajouter des commentaires");
    m_ajoutCommentaires->setCheckable(true);
    QFormLayout *layoutForm = new QFormLayout(this);

    m_auteur = new QLineEdit;
    m_dateCreation = new QDateEdit(QDate::currentDate(), this);
    m_roleClasse = new QTextEdit;

    layoutForm->addRow("&Auteur :", m_auteur);
    layoutForm->addRow("Da&te de création :", m_dateCreation);
    layoutForm->addRow("&Rôle de la classe :", m_roleClasse);

    m_dateCreation->date().toString(QString("ddd d MMM yyyy"));

    m_ajoutCommentaires->setLayout(layoutForm);

    return m_ajoutCommentaires;
}

QWidget *FenPrincipale::creerBoutons() {
    QWidget *widget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignRight);

    QPushButton *generer = new QPushButton("Générer !", this);
    QPushButton *quitter = new QPushButton("Quitter", this);

    layout->addWidget(generer);
    layout->addWidget(quitter);

    widget->setLayout(layout);

    QObject::connect(generer, SIGNAL(clicked()), this, SLOT(ouvrirFenCodeGenere()));
    QObject::connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    return widget;
}

QString FenPrincipale::genererEnTete() {
    QString result;

    result.append("/*<br/>Auteur : " + m_auteur->text() + "\n");
    result.append("Date de création : " + m_dateCreation->date().toString(QString("ddd d MMM yyyy")) +"\n\n");
    result.append("Rôle : \n" + m_roleClasse->toPlainText() + "\n*/\n\n\n");

    return result;
}

QString FenPrincipale::genererClasse() {
    QString result;

    //Création des morceaux
    QString nomClasse = m_nom->text();
    QString classeMere;
    if (m_classeMere->text().length() > 0){
        classeMere = " : public " + m_classeMere->text();
    }
    QString constructeur;
    QString destructeur;
    if (m_genereConstructeur->isChecked()){
        constructeur = "\t" + nomClasse + "()\n";
    }
    if (m_genereDestructeur->isChecked()){
        destructeur = "\t~" + nomClasse + "()\n";
    }

    //Mise en place du texte
    result.append("class " + nomClasse + classeMere + " {\n");
    result.append("public:\n" + constructeur + destructeur + "\n");
    result.append("protected:\n\n");
    result.append("private:\n\n}");

    return result;
}



