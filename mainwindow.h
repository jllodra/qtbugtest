#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QList>
#include <QString>

// Model A

class ModelA : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelA(QObject *parent = 0)
        : QAbstractTableModel(parent)
    {}
    int rowCount(const QModelIndex &) const { return 5; }
    int columnCount(const QModelIndex &) const { return 1; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (role == Qt::DisplayRole)
        {
            return QString("Context %1").arg(index.row() + 1);
        }
        return QVariant();
    }
};


// Model B

class ModelB : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelB(QObject *parent = 0)
        : QAbstractTableModel(parent)
    {}
    int rowCount(const QModelIndex &) const { return 5; }
    int columnCount(const QModelIndex &) const { return 1; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (role == Qt::DisplayRole && index.row() == 4) {
            return QString("Obsolete");
        }
        else if (role == Qt::DisplayRole)
        {
           return QString("Message %1").arg(index.row() + 1);
        }
        return QVariant();
    }
};

// Model C

class ModelC : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelC(QObject *parent = 0)
        : QAbstractTableModel(parent)
    {}
    QModelIndex addPhrase(const QString &s)
    {
        int r = qs.count();

        qs.append(s);

        // update phrases as we add them
        beginInsertRows(QModelIndex(), r, r);
        QModelIndex i = index(r, 0);
        endInsertRows();
        return i;
    }
    void removePhrases()
    {
        int r = qs.count();
        if (r > 0) {
            beginResetModel();
            qs.clear();
            endResetModel();
        }
    }
    int rowCount(const QModelIndex &) const
    {
        return qs.size();
    }
    int columnCount(const QModelIndex &) const
    {
        return 1;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (role == Qt::DisplayRole)
           return qs.at(index.row());
        return QVariant();
    }
private:
    QList<QString> qs;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void selectedAChanged(const QModelIndex &sortedIndex, const QModelIndex &oldIndex);
    void selectedBChanged(const QModelIndex &sortedIndex, const QModelIndex &oldIndex);

private:
    Ui::MainWindow *ui;
    ModelA *m_modelA;
    ModelB *m_modelB;
    ModelC *m_modelC;
};

#endif // MAINWINDOW_H
