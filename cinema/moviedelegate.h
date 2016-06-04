#ifndef MOVIEDELEGATE_H
#define MOVIEDELEGATE_H








#include <QModelIndex>
#include <QPixmap>
#include <QSize>
#include <QSqlRelationalDelegate>

QT_FORWARD_DECLARE_CLASS(QPainter)

class MovieDelegate : public QSqlRelationalDelegate
{
public:
     MovieDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const;

private:
    QPixmap star;
};

#endif
