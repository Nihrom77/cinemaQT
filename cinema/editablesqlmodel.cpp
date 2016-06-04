
#include <QtSql>

#include "editablesqlmodel.h"

EditableSqlModel::EditableSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

////! [0]
//Qt::ItemFlags EditableSqlModel::flags(
//        const QModelIndex &index) const
//{
//    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
//    if (index.column() == 1 || index.column() == 2)
//        flags |= Qt::ItemIsEditable;
//    return flags;
//}
////! [0]

////! [1]
//bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
//{
//    if (index.column() < 1 || index.column() > 2)
//        return false;

//    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
//    int id = data(primaryKeyIndex).toInt();

//    clear();

//    bool ok;
//    if (index.column() == 1) {
//        ok = setFirstName(id, value.toString());
//    } else {
//        ok = setLastName(id, value.toString());
//    }
//    refresh();
//    return ok;
//}
////! [1]

void EditableSqlModel::refresh()
{
    setQuery("select m.movie_id, m.name,m.duration, m.country, m.movie_company,m.age_restriction,  mg.genres,rls.roles from movies m "
                         "left join "
                         "(select m.movie_id as id,string_agg(g.name,', ') as genres from movies m inner join table_movie_genre t_mg on t_mg.movie_id = m.movie_id "
                         "inner join  genre g on g.genre_id = t_mg.genre_id "
                         "group by m.movie_id "
                         ") mg on mg.id = movie_id "
                         "left join "
                         "(select m.movie_id as id,string_agg(act.second_name || ' ' || substring(act.name,0,2) || '. в роли \"' ||p.role||'\"','; ') as roles from movies m inner join participation p on p.movie_id = m.movie_id "
                         "inner join actor act on act.actor_id = p.actor_id "
                         "group by m.movie_id) rls on rls.id = m.movie_id");
    // Устанавливаем в модели названи колонок
    setHeaderData(record().indexOf("name"), Qt::Horizontal, tr("Название"));
    setHeaderData(record().indexOf("duration"), Qt::Horizontal, tr("Продолжительность"));
    setHeaderData(record().indexOf("country"), Qt::Horizontal, tr("Снято в"));
    setHeaderData(record().indexOf("movie_company"), Qt::Horizontal, tr("Студия"));
    setHeaderData(record().indexOf("age_restriction"), Qt::Horizontal, tr("Ограничение +"));
    setHeaderData(record().indexOf("roles"), Qt::Horizontal, tr("Актеры"));
    setHeaderData(this->record().indexOf("genres"), Qt::Horizontal, tr("Жанры"));
   qDebug("refresh");
}

////! [2]
//bool EditableSqlModel::setFirstName(int personId, const QString &firstName)
//{
//    QSqlQuery query;
//    query.prepare("update person set firstname = ? where id = ?");
//    query.addBindValue(firstName);
//    query.addBindValue(personId);
//    return query.exec();
//}
////! [2]

//bool EditableSqlModel::setLastName(int personId, const QString &lastName)
//{
//    QSqlQuery query;
//    query.prepare("update person set lastname = ? where id = ?");
//    query.addBindValue(lastName);
//    query.addBindValue(personId);
//    return query.exec();
//}
