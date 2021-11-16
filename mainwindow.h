#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QStandardItemModel>
#include "randomvariable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddVariable_clicked();

    void on_btnLoadSeed_clicked();

    void on_activeVariable_currentIndexChanged(int index);

    void on_btnAddColumn_clicked();

    void on_btnRemoveColumn_clicked();

    void on_btnSaveSeed_clicked();

    void on_bnNormalize_clicked();

    void on_btnSimulate_clicked();

    void on_pushButton_clicked();

private:
    int savedSeed;
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    vector <RandomVariable*> random_variables;
    RandomVariable *getRandomVariable();
    void loadRandomVariable();
    void addColumn(int i);
    void removeColumn(int i);
    void removeAllColumns();
    void refreshGridLayout(QGridLayout *layout);
    void valueUpdated(int i);
    void ProbabilityUpdated(int i);
    void bigSimulation();
};
#endif // MAINWINDOW_H
