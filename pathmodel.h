#ifndef PATHMODEL_H
#define PATHMODEL_H

#include <QAbstractListModel>
#define QT_SHAREDPOINTER_TRACK_POINTER
#include <QSharedPointer>

#include "pathdata.h"

class PathModel : public QAbstractListModel
{
        Q_OBJECT

    public:

        enum Roles
        {
            Default = Qt::UserRole
        };

        static PathModel * model();

        void    save();
        void    load();

        ////////////////////////////////////////////////////////////////////

        void        clear();

        ////////////////////////////////////////////////////////////////////

        int addPathData();
        int addPathData(PathDataPointer data);

        ////////////////////////////////////////////////////////////////////

        int         rowCount(const QModelIndex & parent) const override;
        QVariant    data(const QModelIndex & index, int role) const override;
        PathDataPointer pathData(int row) const;

        QHash<int, QByteArray> roleNames() const override;

    private:

        explicit PathModel(QObject * parent = nullptr);

        QList<PathDataPointer > m_data;
};

#endif // PATHMODEL_H
