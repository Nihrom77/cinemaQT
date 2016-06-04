#ifndef ACTORSDIALOG_H
#define ACTORSDIALOG_H


#include <QtWidgets>
#include <QtSql>
#include "ui_actorsdialog.h"

class ActorsDialog : public QDialog
{
    Q_OBJECT

public:
    ActorsDialog(QStandardItemModel *model,QString movieName, QWidget *parent = 0);



private:

    QDialogButtonBox *createButtons();
    QTableView *createInputWidgets();
    Ui::ActorsDialog ui;


    QStandardItemModel *model;


};

#endif // ACTORSDIALOG_H
