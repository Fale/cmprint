#include "mainwindow.h"
#include "ui_mainwindow.h"

/* TO BE FIXED
   - Sistemare stretch dell'ultima colonna
   - Chiusura del db
   - FInire refresh tabelle e committare

   ANNOTAZIONI
   - forse questa gestione a widget dove tutti sono creati e caricati all'avvio occupa parecchia ram e un avvio più lento.
     bisogna valutare se ciò costituisce un problema. Per ora appena avviato sono 4.3Mb e 5.2 dopo che carica il db

*/

/*
 La gui è gestita a widget. Ogni volta che se ne mostra uno bisogna nascondere tutti gli altri.

 */


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   //setAttribute(Qt::WA_DeleteOnClose);

    caricaDb("dboggetti.db"); //carica il file del database dalla cartella stessa dell'eseguibile
    n=0;

    ui->setupUi(this);

    MainWindow::on_bottone_benvenuto_clicked();
}

MainWindow::~MainWindow()
{
    database.close();  //chiudo il database! ma non funziona


    delete ui;
}



// se esiste il database lo apre, altrimenti lo crea
void MainWindow::caricaDb(QString nome)
{
    QFile db(nome);
    if( db.exists() )
        apriDb(nome);
    else
    {
        apriDb(nome);
        creaTabelle();
    }
}


 //crea tutte le tabelle necessarie in caso di database vuoto
void MainWindow::creaTabelle()
{
    QSqlQuery creazione;
    QString query;

    query = "CREATE TABLE plastificazione (formati char(15), lucidabianca int, lucidabiancavolta int, opacabianca int, opacabiancavolta int)";
    creazione.prepare(query);
    creazione.exec();
    creazione.clear();
    query.clear();

    query = "CREATE TABLE serigrafia (descrizione char(15), prezzo int)"; //occhio che il prezzo non è un intero, guardare altri tipi di dati
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();


    query = "CREATE TABLE plastificazione2 (formati char(15), lucidabianca int, lucidabiancavolta int, opacabianca int, opacabiancavolta int)";
    creazione.prepare(query);
    creazione.exec();
    creazione.clear();
    query.clear();

    //Aggiungere qui le altre tabelle necessarie

}

void MainWindow::apriDb(QString nome)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(nome);
    database.open();
}


void MainWindow::showHide(QString show)
{

    ui->widget_navigazione->show();

    //nasconde tutto tranne la sezione voluta
    if ( show == "benvenuto" )
    {
        ui->widget_benvenuto->show();
        ui->widget_navigazione->hide(); //poco elegante il show/hide delle stesso widget ma molto più veloce nell'implementazione
    }
        else
        ui->widget_benvenuto->hide();
    if ( show == "preventivi" )
        ui->widget_preventivi->show();
    else
        ui->widget_preventivi->hide();
    if ( show == "carta_formato" )
        ui->widget_carta_formato->show();
    else
        ui->widget_carta_formato->hide();
    if ( show == "carta_grammatura" )
        ui->widget_carta_grammatura->show();
    else
        ui->widget_carta_grammatura->hide();
    if ( show == "carta_tipo" )
        ui->widget_carta_tipo->show();
    else
        ui->widget_carta_tipo->hide();
    if ( show == "clienti" )
        ui->widget_clienti->show();
    else
        ui->widget_clienti->hide();
    if ( show == "plastificazione" )
        ui->widget_plastificazione->show();
    else
        ui->widget_plastificazione->hide();
    if ( show == "serigrafia" )
        ui->widget_serigrafia->show();
    else
        ui->widget_serigrafia->hide();

}

void MainWindow::on_actionPreventivi_triggered()
{
    this->showHide("preventivi");
}

void MainWindow::on_actionTipo_triggered()
{
    this->showHide("carta_tipo");

}

void MainWindow::on_actionFormato_triggered()
{
    this->showHide("carta_formato");
}

void MainWindow::on_actionGrammatura_triggered()
{
    this->showHide("carta_grammatura");
}

void MainWindow::on_actionClienti_triggered()
{
     this->showHide("clienti");

}

void MainWindow::on_actionSerigrafia_triggered()
{
    this->showHide("serigrafia");

    refreshTabelle();
}

void MainWindow::on_actionPlastificazione_triggered()
{
   this->showHide("plastificazione");

    //refresh di TUTTE le tabelle
    refreshTabelle();
}

void MainWindow::on_pushButton_preventivi_clicked()
{
    MainWindow::on_actionPreventivi_triggered();
}

void MainWindow::on_pushButton_clienti_clicked()
{
    MainWindow::on_actionClienti_triggered();
}

void MainWindow::on_pushButton_carta_tipo_clicked()
{
    MainWindow::on_actionTipo_triggered();
}

void MainWindow::on_pushButton_carta_formato_clicked()
{
    MainWindow::on_actionFormato_triggered();
}

void MainWindow::on_pushButton_carta_grammatura_clicked()
{
    MainWindow::on_actionGrammatura_triggered();
}

void MainWindow::on_pushButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_actionEsci_triggered()
{
    qApp->quit();
}


void MainWindow::on_pushButton_serigrafia_clicked()
{
    MainWindow::on_actionSerigrafia_triggered();
}


void MainWindow::on_pushButton_plastificazione_clicked()
{
    MainWindow::on_actionPlastificazione_triggered();
}

void MainWindow::refreshTabelle()
{
    /* Questa funzione fa ogni volta il refresh di TUTTE le tabelle.
       In futuro sarebbe meglio fare il refresh solo di quella necessaria */

    QSqlTableModel *tabella_plastificazione = new QSqlTableModel;
    tabella_plastificazione->setTable("plastificazione");
    tabella_plastificazione->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_plastificazione->select();
    tabella_plastificazione->setHeaderData(0, Qt::Horizontal, "Formati");
    tabella_plastificazione->setHeaderData(1, Qt::Horizontal, "Lucida Bianca");
    tabella_plastificazione->setHeaderData(2, Qt::Horizontal, "Lucida Bianca/Volta");
    tabella_plastificazione->setHeaderData(3, Qt::Horizontal, "Opaca Bianca");
    tabella_plastificazione->setHeaderData(4, Qt::Horizontal, "Opaca Bianca/Volta");
    ui->tableView_plastificazione->setModel(tabella_plastificazione);


    QSqlTableModel *tabella_serigrafia = new QSqlTableModel;
    tabella_serigrafia->setTable("serigrafia");
    tabella_serigrafia->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_serigrafia->select();
    tabella_serigrafia->setHeaderData(0, Qt::Horizontal, "Descrizione");
    tabella_serigrafia->setHeaderData(1, Qt::Horizontal, "Prezzo");
    ui->tableView_serigrafia->setModel(tabella_serigrafia);

    //Aggiungere qui il refresh di altre tabelle
}

void MainWindow::on_bottone_plastificazione_aggiungi_clicked()
{
    QSqlQuery query;
    n=n+1;
    query.prepare("INSERT INTO plastificazione (formati, lucidabianca, lucidabiancavolta, opacabianca, opacabiancavolta)"
                  "VALUES(:formati, :lucidabianca, :lucidabiancavolta, :opacabianca, :opacabiancavolta) ") ;
    query.bindValue(":formati", n);
    query.bindValue(":lucidabianca", 0);
    query.bindValue(":lucidabiancavolta", 0);
    query.bindValue(":opacabianca", 0);
    query.bindValue(":opacabiancavolta", 0);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();

/*WORKAROUND: numera le nuove righe*/
}

void MainWindow::on_bottone_serigrafia_aggiungi_clicked()
{
    /*QSqlQuery query;
    n=n+1;
    query.prepare("INSERT INTO serigrafia (formati, lucidabianca, lucidabiancavolta, opacabianca, opacabiancavolta)"
                  "VALUES(:formati, :lucidabianca, :lucidabiancavolta, :opacabianca, :opacabiancavolta) ") ;
    query.bindValue(":formati", n);
    query.bindValue(":lucidabianca", 0);
    query.bindValue(":lucidabiancavolta", 0);
    query.bindValue(":opacabianca", 0);
    query.bindValue(":opacabiancavolta", 0);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle(); */

    QSqlQuery query;
    n=n+1;
    qDebug() << query.prepare("INSERT INTO serigrafia (descrizione, prezzo)"
                              "VALUES(:descrizione, :prezzo) ");
    query.bindValue(":descrizione", "test");
    query.bindValue(":prezzo", 0);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();

}
void MainWindow::on_bottone_benvenuto_clicked()
{
    //queste righe nascondono tutto tranne la schermata di benvenuto
    ui->widget_benvenuto->show();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->hide();
    ui->widget_navigazione->hide();
}


