#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_modelA = new ModelA();
    m_modelB = new ModelB();
    m_modelC = new ModelC();
    ui->a->setModel(m_modelA);
    ui->b->setModel(m_modelB);
    ui->c->setModel(m_modelC);

    connect(ui->a->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(selectedAChanged(QModelIndex,QModelIndex)));
    connect(ui->b->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(selectedBChanged(QModelIndex,QModelIndex)));
}

void MainWindow::selectedAChanged(const QModelIndex &sortedIndex, const QModelIndex &oldIndex)
{
    qDebug("selected A");
    ui->b->setCurrentIndex(m_modelB->index(0, 0));
}

void MainWindow::selectedBChanged(const QModelIndex &sortedIndex, const QModelIndex &oldIndex)
{
    qDebug("selected B");
    int row = sortedIndex.row();

    m_modelC->removePhrases();

    if (row < 4) {
        m_modelC->addPhrase(QString("Phrases for message %1 here...").arg(row));
    } else if (row == 4) {
        m_modelC->removePhrases();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
