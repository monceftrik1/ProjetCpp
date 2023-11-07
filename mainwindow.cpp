#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->materielBtn->setStyleSheet("qproperty-icon:url(:/icons-green/icons-green/home.svg); color: #4A7C59; border-top-left-radius: 15px; border-bottom-left-radius: 15px; background: #FAF3DD;");
    ui->mainContentSTackWidget->setCurrentIndex(0);
    ui->etatComboBox->addItem("Fonctionnelle");ui->etatComboBox->addItem("Non Fonctionnelle");
    ui->etatComboBox_2->addItem("Fonctionnelle");ui->etatComboBox_2->addItem("Non Fonctionnelle");
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->idMatLE->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajoutMaterielPageBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(0);
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
}

void MainWindow::on_afficherMaterielPageBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(1);
    ui->materielTableView->setModel(m.afficherMateriel());
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
}

void MainWindow::on_materielModifBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(2);
}

void MainWindow::on_ajoutMaterielBtn_clicked()
{
    if(ui->prixLineEdit->text() =="" || ui->nomLE->text() == "" || ui->ageLE->text() =="" || ui->prixLineEdit->text() == "" || ui->capLineEdit->text() =="")
    {
        ui->alertAjout->show();ui->alertAjout_2->show();ui->alertAjout_3->show();ui->alertAjout_4->show();
        ui->alertAjout_5->show();
    }
    else{
        QString mat = ui->matLineEdit->text();
        QString nom = ui->nomLE->text();
        QString etat = ui->etatComboBox->currentText();
        int age = ui->ageLE->text().toInt();
        float prix = ui->prixLineEdit->text().toFloat();
        float cap = ui->capLineEdit->text().toFloat();
        materiel mtrl(0,age,nom,mat,etat,cap,prix);
        if(mtrl.ajouterMateriel())
        {
            ui->materielTableView->setModel(m.afficherMateriel());
            ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
            ui->alertAjout_5->hide();
            ui->mainContentSTackWidget->setCurrentIndex(1);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->materielTableView->model()->data(sibling).toString();

                QSqlQuery qry;
                qry.prepare("SELECT * FROM materiel WHERE id=:id" );
                qry.bindValue(":id",id);
                if(qry.exec())
                {
                    while(qry.next())
                    {
                        ui->idMatLE->setText(qry.value(0).toString());
                        ui->matLineEdit_2->setText(qry.value(1).toString());
                        ui->nomLE_2->setText(qry.value(2).toString());
                        ui->prixLineEdit_2->setText(qry.value(6).toString());
                        ui->etatComboBox_2->setCurrentText(qry.value(3).toString());
                        ui->ageLE_2->setText(qry.value(4).toString());
                        ui->capLineEdit_2->setText(qry.value(5).toString());
                    }
                }
}

void MainWindow::on_ajoutMaterielBtn_2_clicked()
{
    if(ui->prixLineEdit_2->text() =="" || ui->nomLE_2->text() == "" || ui->ageLE_2->text() =="" || ui->prixLineEdit_2->text() == "" || ui->capLineEdit_2->text() =="")
    {
        ui->alertAjout_6->show();ui->alertAjout_7->show();ui->alertAjout_8->show();ui->alertAjout_9->show();
        ui->alertAjout_10->show();
    }
    else{
        int id = ui->idMatLE->text().toInt();
        QString mat = ui->matLineEdit_2->text();
        QString nom = ui->nomLE_2->text();
        QString etat = ui->etatComboBox_2->currentText();
        int age = ui->ageLE_2->text().toInt();
        float prix = ui->prixLineEdit_2->text().toFloat();
        float cap = ui->capLineEdit_2->text().toFloat();
        materiel mtrl(id,age,nom,mat,etat,cap,prix);
        if(mtrl.modifierMateriel())
        {
            ui->materielTableView->setModel(m.afficherMateriel());
            ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
            ui->alertAjout_10->hide();
            ui->mainContentSTackWidget->setCurrentIndex(1);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielSuppBtn_clicked()
{
    QModelIndex indexItem = ui->materielTableView->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->materielTableView->model()->data(sibling).toInt();
    if(m.supprimerMateriel(id))
    {
       ui->materielTableView->setModel(m.afficherMateriel());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}
