#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QFile>
#include <QString>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSqlDatabase database;
    QSqlQueryModel queryModel;
    float n;
//   QSqlTableModel tabella_plastificazione;

    void caricaDb(QString nome);
    void creaTabelle();
    void apriDb(QString nome);
    void refreshTabelle();
//void visualizzaRicerca(QString nome);
    void showHide(QString show);


private slots:
    void on_bottone_carta_grammatura_aggiungi_clicked();
    void on_bottone_carta_formato_aggiungi_clicked();
    void on_bottone_clienti_aggiungi_clicked();
    void on_bottone_carta_tipo_aggiungi_clicked();
    void on_bottone_serigrafia_aggiungi_clicked();
    void on_bottone_benvenuto_clicked();
    void on_bottone_plastificazione_aggiungi_clicked();
    void on_pushButton_plastificazione_clicked();
    void on_pushButton_serigrafia_clicked();
    void on_actionPlastificazione_triggered();
    void on_actionSerigrafia_triggered();
    void on_actionEsci_triggered();
    void on_pushButton_clicked();
    void on_pushButton_carta_grammatura_clicked();
    void on_pushButton_carta_formato_clicked();
    void on_pushButton_carta_tipo_clicked();
    void on_pushButton_clienti_clicked();
    void on_pushButton_preventivi_clicked();
    void on_actionClienti_triggered();
    void on_actionGrammatura_triggered();
    void on_actionFormato_triggered();
    void on_actionTipo_triggered();
    void on_actionPreventivi_triggered();
};

#endif // MAINWINDOW_H
