#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QDebug>
#include <QLineEdit>
#include <QWidget>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel)
{
    ui->setupUi(this);
    ui->listOfSimulations->setModel(model);
    savedSeed = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

RandomVariable* MainWindow::getRandomVariable() {
    return random_variables[ui->activeVariable->currentData().toInt()];
}

void MainWindow::refreshGridLayout(QGridLayout *layout) {
    QWidget *widget = new QWidget();
    layout->addWidget(widget);
    layout->removeWidget(widget);
    delete widget;
}

void MainWindow::addColumn(int i) {
    QLineEdit *line = new QLineEdit();
    connect(line, &QLineEdit::textEdited,
            [this, i] { this->valueUpdated(i); });
    line->setText(QString::number(getRandomVariable()->values()[i]));
    ui->gridLayoutTable->addWidget(line, 0, i);
    QLineEdit *line2 = new QLineEdit();
    connect(line2, &QLineEdit::textEdited,
            [this, i] { this->ProbabilityUpdated(i); });
    line2->setText(QString::number(getRandomVariable()->probabilities()[i]));
    ui->gridLayoutTable->addWidget(line2, 1, i);
}

void MainWindow::removeColumn(int i) {
    if ( ui->gridLayoutTable != NULL && ui->gridLayoutTable->count() > 0)
    {
        QLayoutItem* item;
        item = ui->gridLayoutTable->takeAt( ui->gridLayoutTable->count() - 1);
        delete item->widget();
        delete item;
        item = ui->gridLayoutTable->takeAt( ui->gridLayoutTable->count() - 1);
        delete item->widget();
        delete item;
        refreshGridLayout(ui->gridLayoutTable);
    }
}

void MainWindow::removeAllColumns() {
    if ( ui->gridLayoutTable != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->gridLayoutTable->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
}

void MainWindow::loadRandomVariable()
{
    if(ui->activeVariable->currentIndex() < 0) {
        return;
    }
    removeAllColumns();
    for(int i = 0; i < getRandomVariable()->size(); i++) {
        addColumn(i);
    }
}

void MainWindow::bigSimulation() {
    model->clear();
    int count = ui->countField->text().toInt();
    double avarage = 0;
    for(int i = 0; i < count; i++) {
        double value = getRandomVariable()->simulate();
        QString line = QString("%1) %2").arg(QString::number(i+1),
                                             QString::number(value));
        avarage += value;
        model->insertRow(i);
        auto item = new QStandardItem(line);
        model->setItem(i, item );
    }
    avarage /= count;
    ui->fieldForAvarage->setText(QString::number(avarage));
}

void MainWindow::valueUpdated(int i) {
    double value = qobject_cast<QLineEdit*>(ui->gridLayoutTable->itemAt(i*2)->widget())->text().toDouble();
    getRandomVariable()->setValue(i, value);
}

void MainWindow::ProbabilityUpdated(int i) {
    double value = qobject_cast<QLineEdit*>(ui->gridLayoutTable->itemAt(i*2+1)->widget())->text().toDouble();
    //qDebug() << value;
    getRandomVariable()->setProbability(i, value);
}

void MainWindow::on_btnAddVariable_clicked()
{
    QString inputName = QInputDialog::getText(this, "Add", "Enter name of variable");
    random_variables.push_back(new RandomVariable(inputName, 0));
    ui->activeVariable->addItem(inputName, ui->activeVariable->count());
}


void MainWindow::on_btnLoadSeed_clicked()
{
    ifstream fin("F:\\QtProjects\\laba2FINAL\\seed.txt");
    int seed;
    fin >> seed;
    getRandomVariable()->setSeed(seed);
}

void MainWindow::on_btnSaveSeed_clicked()
{
    ofstream fout("F:\\QtProjects\\laba2FINAL\\seed.txt");
    fout << getRandomVariable()->seed();
}

void MainWindow::on_activeVariable_currentIndexChanged(int index)
{
    loadRandomVariable();
}

void MainWindow::on_btnAddColumn_clicked()
{
    if(random_variables.size() < 1) return;
    getRandomVariable()->setSize(getRandomVariable()->size() + 1);
    addColumn(getRandomVariable()->size() - 1);
}


void MainWindow::on_btnRemoveColumn_clicked()
{
    if(random_variables.size() < 1) return;
    getRandomVariable()->setSize(getRandomVariable()->size() - 1);
    getRandomVariable()->normalize();
    loadRandomVariable();
}



void MainWindow::on_bnNormalize_clicked()
{
    getRandomVariable()->normalize();
    loadRandomVariable();
}


void MainWindow::on_btnSimulate_clicked()
{
    if(random_variables.size() < 1) return;
    ui->simulateField->setText(QString::number(getRandomVariable()->simulate()));
}


void MainWindow::on_pushButton_clicked()
{
    if(random_variables.size() < 1) return;
    ui->fieldForExpectedValue->setText(QString::number(getRandomVariable()->expectedValue()));
    bigSimulation();
}

