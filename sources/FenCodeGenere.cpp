#include "FenCodeGenere.h"

FenCodeGenere::FenCodeGenere(QString &code) : QDialog() {
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QTextEdit *textEdit = new QTextEdit(code, this);
    QPushButton *boutonFermer = new QPushButton("Fermer", this);

    textEdit->setReadOnly(true);

    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(boutonFermer);

    QObject::connect(boutonFermer, SIGNAL(clicked()), this, SLOT(accept()));

    this->setLayout(mainLayout);
}
