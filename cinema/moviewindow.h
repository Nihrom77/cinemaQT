#ifndef MOVIEWINDOW_H
#define MOVIEWINDOW_H
#include <QtWidgets>
#include <QtSql>

#include "ui_moviewindow.h"


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

    void on_changeMovie_clicked();

    void on_actorsShowButton_clicked();

private:
    void createMenuBar();
    void showError(const QSqlError &err);
     void deleteMovie();
     void refresh();
     QStandardItemModel* createActorModel(QString &movie_id);
    Ui::MovieWindow ui;
    QSqlQueryModel *movieModel;
    QSqlQueryModel *genreModel;
    QSqlQueryModel *actorModel;
    QStandardItemModel *actorsItemModel;
    QStandardItemModel *genresItemModel;
    QString currentMovie;

};

#endif // MOVIEWINDOW_H


