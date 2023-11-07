#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "materiel.h"
#include <QMessageBox>

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


    void on_ajoutMaterielPageBtn_clicked();

    void on_afficherMaterielPageBtn_clicked();

    void on_materielModifBtn_clicked();

    void on_ajoutMaterielBtn_clicked();

    void on_materielTableView_clicked(const QModelIndex &index);

    void on_ajoutMaterielBtn_2_clicked();

    void on_materielSuppBtn_clicked();

private:
    Ui::MainWindow *ui;
    materiel m;
};
#endif // MAINWINDOW_H
