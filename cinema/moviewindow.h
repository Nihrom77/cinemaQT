#ifndef MOVIEWINDOW_H
#define MOVIEWINDOW_H
#include <QtWidgets>
#include <QtSql>

#include "ui_moviewindow.h"
#include "editablesqlmodel.h"

class MovieWindow: public QMainWindow
{
    Q_OBJECT


public: MovieWindow();


private slots:
    void on_deleteMovie_clicked();
    void about();
    void addMovie();


    void on_addFilmButton_clicked();

    void on_movieTable_clicked(const QModelIndex &index);

private:
    void createMenuBar();
    void showError(const QSqlError &err);
     void deleteMovie();
    Ui::MovieWindow ui;
    EditableSqlModel *movieModel;
    QSqlQueryModel *genreModel;
    QSqlQueryModel *actorModel;

};

#endif // MOVIEWINDOW_H


