#include "pathmodel.h"

PathModel * PathModel::model()
{
    static PathModel * model = new PathModel();
    return model;
}

void PathModel::save()
{
}

void PathModel::load()
{
}

void PathModel::clear()
{
    this->beginResetModel();
    m_data.clear();
    this->endResetModel();
}

int PathModel::addPathData()
{
    PathDataPointer ptr(new PathData());
    return this->addPathData(ptr);
}

int PathModel::addPathData(PathDataPointer data)
{
    this->beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(data);
    this->endInsertRows();
    return m_data.size() - 1;
}

int PathModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

QVariant PathModel::data(const QModelIndex & index, int role) const
{
    Q_UNUSED(role);
    return QVariant::fromValue(m_data[index.row()].toWeakRef());
}

PathDataPointer PathModel::pathData(int row) const
{
    return m_data[row];
}

QHash<int, QByteArray> PathModel::roleNames() const
{
    QHash<int, QByteArray> hash = QAbstractListModel::roleNames();
    hash.insert(Roles::Default, "path");
    return hash;
}

PathModel::PathModel(QObject * parent)
    : QAbstractListModel(parent)
{
}
