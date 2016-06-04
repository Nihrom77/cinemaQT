#include "moviewindow.h"

#include "moviedelegate.h"
#include "initDB.h"
#include <QtSql>


MovieWindow::MovieWindow()
{

    ui.setupUi(this);
     createMenuBar();
    //Проверка наличия драйвера postgres
    if (!QSqlDatabase::drivers().contains("QPSQL"))
        QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver");

    //Инициализация подключения к БД
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    // Create the data model
    movieModel = new EditableSqlModel(ui.movieTable);//связываем модель и UI
   // movieModel->setEditStrategy(QSqlTableModel::OnFieldChange);
//    movieModel->setTable("movies");//связываем модель и таблицу в БД
    movieModel->setQuery("select m.movie_id, m.name,m.duration, m.country, m.movie_company,m.age_restriction,  mg.genres,rls.roles from movies m "
                         "left join "
                         "(select m.movie_id as id,string_agg(g.name,', ') as genres from movies m inner join table_movie_genre t_mg on t_mg.movie_id = m.movie_id "
                         "inner join  genre g on g.genre_id = t_mg.genre_id "
                         "group by m.movie_id "
                         ") mg on mg.id = movie_id "
                         "left join "
                         "(select m.movie_id as id,string_agg(act.second_name || ' ' || substring(act.name,0,2) || '. в роли \"' ||p.role||'\"','; ') as roles from movies m inner join participation p on p.movie_id = m.movie_id "
                         "inner join actor act on act.actor_id = p.actor_id "
                         "group by m.movie_id) rls on rls.id = m.movie_id "
                         "order by m.name");



    // Устанавливаем связь с таблицей
    /* Устанавливаем связи с таблицей "фильм_жанр", по которым будет производится
         * подстановка данных
         * В метода setRelation указывается номер колонки, в которой будет
         * производится подстановка, а также с помощью класса
         * QSqlRelation указывается имя таблицы,
         * параметр, по которому будет произведена выборка строки
         * и колонка, из которой будут взяты данные
         * */
//    movieModel->setRelation(movieModel->fieldIndex("movie_id"), QSqlRelation("table_movie_genre", "movie_id", "genre_id"));
//    movieModel->setRelation(genreIdx, QSqlRelation("genre", "genre_id", "name"));

    // Устанавливаем в модели названи колонок
    movieModel->setHeaderData(movieModel->record().indexOf("name"), Qt::Horizontal, tr("Название"));
    movieModel->setHeaderData(movieModel->record().indexOf("duration"), Qt::Horizontal, tr("Продолжительность"));
    movieModel->setHeaderData(movieModel->record().indexOf("country"), Qt::Horizontal, tr("Снято в"));
    movieModel->setHeaderData(movieModel->record().indexOf("movie_company"), Qt::Horizontal, tr("Студия"));
    movieModel->setHeaderData(movieModel->record().indexOf("age_restriction"), Qt::Horizontal, tr("Ограничение +"));
    movieModel->setHeaderData(movieModel->record().indexOf("roles"), Qt::Horizontal, tr("Актеры"));
    movieModel->setHeaderData(movieModel->record().indexOf("genres"), Qt::Horizontal, tr("Жанры"));

    // Populate the model
//    if (!movieModel->select()) {
//        showError(movieModel->lastError());
//        return;
//    }

    // Set the model and hide the ID column
    ui.movieTable->setModel(movieModel);
 //   ui.movieTable->setItemDelegate(new MovieDelegate(ui.movieTable));
    ui.movieTable->setColumnHidden(movieModel->record().indexOf("movie_id"), true);

      // Устанавливаем размер колонок по содержимому
    ui.movieTable->resizeColumnsToContents();

    // Разрешаем выделение строк
    ui.movieTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui.movieTable->setSelectionMode(QAbstractItemView::SingleSelection);




    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(movieModel);
    mapper->setItemDelegate(new MovieDelegate(this));
    mapper->addMapping(ui.titleEdit, movieModel->record().indexOf("name"));
    mapper->addMapping(ui.durationEdit, movieModel->record().indexOf("duration"));
    mapper->addMapping(ui.madeInEdit, movieModel->record().indexOf("country"));
    mapper->addMapping(ui.studioEdit, movieModel->record().indexOf("movie_company"));
    mapper->addMapping(ui.ageRestrictionEdit, movieModel->record().indexOf("age_restriction"));



    connect(ui.movieTable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    ui.movieTable->setCurrentIndex(movieModel->index(0, 0));
    on_movieTable_clicked(movieModel->index(0, 0));
}

void MovieWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}


void MovieWindow::deleteMovie()
{
    QString ID = movieModel->data(movieModel->index(ui.movieTable->selectionModel()->currentIndex().row(),0)).toString();

    if (!ID.isNull() && !ID.isEmpty()) {
        QString name = movieModel->data(movieModel->index(ui.movieTable->selectionModel()->currentIndex().row(),movieModel->record().indexOf("name"))).toString();

        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("Удаление фильма"),
                                       tr("Уверены, что нужно удалить "
                                          "фильм '%1' ?")
                                       .arg(name),
                                       QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {

                 QSqlQuery query_participation;
                    query_participation.prepare("delete from participation where movie_id = :id");
                    query_participation.bindValue(":id", ID.toInt());

                    query_participation.exec();

                    //showError(query_participation.lastError());


                    QSqlQuery query_genre;
                    query_genre.prepare("delete from table_movie_genre where movie_id = :id");
                    query_genre.bindValue(":id", ID.toInt());
                    query_genre.exec();


                    QSqlQuery query_movie;
                    query_movie.prepare("delete from movies where movie_id = ?");
                    query_movie.addBindValue(ID);
                    query_movie.exec();

                    movieModel->refresh();

        }
    } else {
        QMessageBox::information(this, tr("Удаление фильма"),
                                 tr("Выберите фильм, чтобы его удалить."));
    }
}


void MovieWindow::on_deleteMovie_clicked()
{
     deleteMovie();
}

void MovieWindow::createMenuBar()
{

    QAction *quitAction = new QAction(tr("&Quit"), this);
    QAction *aboutAction = new QAction(tr("&About"), this);

    quitAction->setShortcuts(QKeySequence::Quit);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);

    connect(quitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

}

void MovieWindow::about()
{

    QMessageBox::about(this, tr("About Cinema"),
            tr("<p>The <b>Music Archive</b> example shows how to present "
               "data from different data sources in the same application. "
               "The album titles, and the corresponding artists and release dates, "
               "are kept in a database, while each album's tracks are stored "
               "in an XML file. </p><p>The example also shows how to add as "
               "well as remove data from both the database and the "
               "associated XML file using the API provided by the Qt SQL and "
               "Qt XML modules, respectively.</p>"));
}

void MovieWindow::addMovie()
{

        QSqlQuery query_addMovie;
        query_addMovie.prepare("insert into movies (name, duration, country, movie_company,age_restriction)   values(:title, :duration, :country, :studio, :restriction)");
        query_addMovie.bindValue(":title", ui.titleEdit->text());
        query_addMovie.bindValue(":duration", ui.durationEdit->text().toInt());
        query_addMovie.bindValue(":country", ui.madeInEdit->text());
        query_addMovie.bindValue(":studio", ui.studioEdit->text());
        query_addMovie.bindValue(":restriction", ui.ageRestrictionEdit->text().toInt());

       query_addMovie.exec();

     // showError(query_addMovie.lastError());
}

void MovieWindow::on_addFilmButton_clicked()
{
    QMessageBox::about(this, tr("Add movie"),
            tr("<p>movie added. %1</p>").arg(ui.titleEdit->text()));
    addMovie();
    movieModel->refresh();
}

void MovieWindow::on_movieTable_clicked(const QModelIndex &index)
{
    //обновить значения actor & genre
    QString movie_id = movieModel->data(movieModel->index(index.row(),movieModel->record().indexOf("movie_id"))).toString();


if (!movie_id.isNull() && !movie_id.isEmpty()) {
    genreModel = new QSqlQueryModel(this);
    QSqlQuery query_genres;
    query_genres.prepare("select g.name,g.genre_id,case when coalesce(tg.id) is null then false else true end as check1 from genre g "
                         "left join (select g.genre_id as id "
                         "from genre g inner join table_movie_genre t_mg on t_mg.genre_id = g.genre_id "
                         "where t_mg.movie_id = :movie_id) tg on tg.id = g.genre_id order by g.name ");
    query_genres.bindValue(":movie_id", movie_id.toInt());
//    genreModel->setQuery(query_genres);
query_genres.exec();


//    ui.genreEdit->setColumnHidden(genreEdit->record().indexOf("genre_id"), true);
//    ui.genreEdit->setColumnHidden(genreEdit->record().indexOf("check1"), true);
//    ui.genreEdit->setModel(genreModel);
//    ui.genreEdit->setModelColumn(genreModel->record().indexOf("name"));

    QStandardItemModel *model1 = new QStandardItemModel(query_genres.size(), 1);
   // qDebug("pp "+query_genres.size());
       int i = 0;
       while (query_genres.next())
       {
            QString name = query_genres.value(0).toString();
            int genre_id = query_genres.value(1).toInt();
            boolean check1 = query_genres.value(2).toBool();

         //  qDebug("kek "+name.toUtf8()+" "+check1);
           QStandardItem* item = new QStandardItem(name);//name

           item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
           if(check1){
           item->setData(Qt::Checked, Qt::CheckStateRole);
           }else{
              item->setData(Qt::Unchecked, Qt::CheckStateRole);
           }
           model1->setItem(i, 0, item);
           i++;
       }
       ui.genreEdit->setModel(model1);
}
}
