#include "mainwindow.h"
#include "ui_mainwindow.h"

/* TO BE FIXED
   - Chiusura del db
   - NUMERO DI CIFRE
   - MIGLIORARE RICERCA (Like non va)
   - RISOLVERE PROBLEMA SELEZIONE
   - AGGIUNGERE SCROLL FOGLIO 5?


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
    rigadacancellare = 0;
    pulire = true;
    caricaDb("database.db"); //carica il file del database dalla cartella stessa dell'eseguibile
    n=0;
    ui->setupUi(this);
    ui->logo->setPixmap(QPixmap("cmprint.png"));
    ui->logo_grimp->setPixmap(QPixmap("grimp.png"));
    MainWindow::on_bottone_benvenuto_clicked();
    ui->dateEdit_foglio1->setDate(QDate::currentDate());
   QString a;
    a.setNum(8.00, 'f', 3 );
    //ui->label_27->setText(QString::setNum);
    /*QString data;
    data = "25/12/2011";

    ;
    */
    ui->bottone_torna_preventivo->hide();
    ui->bottone_salva_preventivo->hide();
    popolaComboBox();

}

MainWindow::~MainWindow()
{
    database.close();  //chiudo il database! ma non funziona
    delete ui;
}



void MainWindow::caricaDb(QString nome)
{
    // se esiste il database lo apre, altrimenti lo crea
    QFile db(nome);
    if( db.exists() )
        apriDb(nome);
    else
    {
        apriDb(nome);
        creaTabelle();
    }
}


void MainWindow::creaTabelle()
{
     //crea tutte le tabelle necessarie in caso di database vuoto
    QSqlQuery creazione;
    QString query;

    query = "CREATE TABLE plastificazione (formato char(15), lucidabianca real, lucidabiancavolta real, opacabianca real, opacabiancavolta real)";
    creazione.prepare(query);
    creazione.exec();
    creazione.clear();
    query.clear();

    query = "CREATE TABLE clienti (nome char(30))";
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();

    query = "CREATE TABLE cartaformato (formato char(30))";
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();


    query = "CREATE TABLE cartagrammatura (grammatura int)";
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();

    query = "CREATE TABLE serigrafia (formato char(30), prezzo real)";
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();

    query = "CREATE TABLE cartatipo (descrizione char(30))";
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();

    query = "CREATE TABLE npreventivo (numero int)";
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();


    //manca la data!!

    //foglio1
    query = "CREATE TABLE preventivo (numero int, data char(10), cliente char(30), descrizione char(100), ncopie int, ";
    //foglio2
    query.append("lastren1 int, lastren2 int, lastren3 int, lastren4 int, lastren5 int, lastren6 int, rismen1 int, rismen2 int, rismen3 int, rismen4 int, rismen5 int, rismen6 int, lastreeuro1 real, lastreeuro2 real, lastreeuro3 real, lastreeuro4 real, lastreeuro5 real, lastreeuro6 real, rismeeuro1 real, rismeeuro2 real, rismeeuro3 real, rismeeuro4 real, rismeeuro5 real, rismeeuro6 real, lastravvprime real, lastravvsucc real, stampaprime real, stampasucc real, stampadigprime real, stampadigsucc real, percf2 real, ");
    //foglio3
    //query.append("tipo1 char(30), tipo2 char(30), tipo3 char(30), tipo4 char(30), tipo5 char(30), tipo6 char(30), tipo7 char(30), tipo8 char(30), formato1 char(30), formato2 char(30), formato3 char(30), formato4 char(30), formato5 char(30), euro1 real, euro2 real, euro3 real, euro4 real, euro5 real, europrime1 real, europrime2 real, europrime3 real, eurosucc1 real, eurosucc2 real, eurosucc3 real, percf3 real, ");
    query.append("tipo1 char(30), tipo2 char(30), tipo3 char(30), tipo4 char(30), tipo5 char(30), tipo6 char(30), tipo7 char(30), tipo8 char(30), formato1 char(30), formato2 char(30), formato3 char(30), formato4 char(30), formato5 char(30), grammatura1 real, grammatura2 real, grammatura3 real, grammatura4 real, grammatura5 real, nfogli1 int, nfogli2 int, nfogli3 int, nfogli4 int, nfogli5 int, euro1 real, euro2 real, euro3 real, euro4 real, euro5 real, europrime1 real, europrime2 real, europrime3 real, eurosucc1 real, eurosucc2 real, eurosucc3 real, percf3 real, ");

    //foglio4
    query.append("plopbformato char(30), plopbnfogli int, plopbavv real, plopbvformato char(30), plopbvnfogli int, plopbvavv real, pllubformato char(30), pllubnfogli int, pllubavv real, pllubvformato char(30), pllubvnfogli int, pllubvavv real, serformato char(30), sernfogli int, seravv real, sertelaio real, fustella real, fustellaturanfogli int, fustellaturaeuro real, fustellaturaavv real, cordonaturaprime real, cordonaturasucc real, cordonaturaavv real, accoppiaturaprime int, accoppiaturasucc real, stampacaldoprime real, stampacaldosucc real, cliche real, piegacopien int, piegacopieeuro real, tagliocopien int, tagliocopieeuro real, puntometncopie int, puntometeuro real, puntometavv real, brosfresncopie int, brosfreseuro real, brosfresavv real, brosfiloncopie int, brosfiloeuro real, brosfiloavv real, cartncopie int, carteuro real, cartavv real, spirncopie int, spireuro real, pacchipolincopie int, pacchipolieuro real, trasporto real, riga1 char(30), riga2 char(30), riga3 char(30), riga4 char(30), riga5 char(30), riga1prime real, riga2prime real, riga3prime real, riga4prime real, riga5prime real, riga1succ real, riga2succ real, riga3succ real, riga4succ real, riga5succ real, percf4 real");
    query.append(")");
    qDebug() << creazione.prepare(query);
    qDebug() << creazione.exec();
    creazione.clear();
    query.clear();

    //Aggiungere qui le altre tabelle necessarie

}

void MainWindow::caricaComboBox(QComboBox *comboBox, QVariant valore)
{
    if (comboBox->findText(valore.toString()) == -1)
            comboBox->insertItem(0,valore.toString());
    comboBox->setCurrentIndex( comboBox->findText(valore.toString()));

}

void MainWindow::caricaPreventivo(int numero)
{
    QSqlQuery query;
    QString str_numero;
    QSqlRecord campo;

    str_numero.setNum(numero);
    ui->label_npreventivo->setNum(numero);


    query.clear();
    query = "SELECT * FROM preventivo WHERE numero = '"+str_numero+"'";
    qDebug()<<query.exec();
    query.next();
    campo= query.record();
    ui->dateEdit_foglio1->setDate(QDate::fromString(campo.value(1).toString(),"dd/MM/yyyy"));
    caricaComboBox(ui->comboBox_clienti_seleziona, campo.value(2));

    ui->plainTextEdit_descrizione->setPlainText(campo.value(3).toString());

    ui->spinBox_foglio1_ncopie->setValue( campo.value(4).toInt());

    //foglio2
    ui->spinBox_foglio2_lastre_n_1->setValue( campo.value(5).toInt() );
    ui->spinBox_foglio2_lastre_n_2->setValue( campo.value(6).toInt() );
    ui->spinBox_foglio2_lastre_n_3->setValue( campo.value(7).toInt() );
    ui->spinBox_foglio2_lastre_n_4->setValue( campo.value(8).toInt() );
    ui->spinBox_foglio2_lastre_n_5->setValue( campo.value(9).toInt() );
    ui->spinBox_foglio2_lastre_n_6->setValue( campo.value(10).toInt() );
    ui->spinBox_foglio2_risme_n_1->setValue( campo.value(11).toInt() );
    ui->spinBox_foglio2_risme_n_2->setValue( campo.value(12).toInt() );
    ui->spinBox_foglio2_risme_n_3->setValue( campo.value(13).toInt() );
    ui->spinBox_foglio2_risme_n_4->setValue( campo.value(14).toInt() );
    ui->spinBox_foglio2_risme_n_5->setValue( campo.value(15).toInt() );
    ui->spinBox_foglio2_risme_n_6->setValue( campo.value(16).toInt() );
    ui->doubleSpinBox_foglio2_lastre_prezzo_1->setValue(campo.value(17).toDouble());
    ui->doubleSpinBox_foglio2_lastre_prezzo_2->setValue(campo.value(18).toDouble());
    ui->doubleSpinBox_foglio2_lastre_prezzo_3->setValue(campo.value(19).toDouble());
    ui->doubleSpinBox_foglio2_lastre_prezzo_4->setValue(campo.value(20).toDouble());
    ui->doubleSpinBox_foglio2_lastre_prezzo_5->setValue(campo.value(21).toDouble());
    ui->doubleSpinBox_foglio2_lastre_prezzo_6->setValue(campo.value(22).toDouble());
    ui->doubleSpinBox_foglio2_risme_prezzo_1->setValue(campo.value(23).toDouble());
    ui->doubleSpinBox_foglio2_risme_prezzo_2->setValue(campo.value(24).toDouble());
    ui->doubleSpinBox_foglio2_risme_prezzo_3->setValue(campo.value(25).toDouble());
    ui->doubleSpinBox_foglio2_risme_prezzo_4->setValue(campo.value(26).toDouble());
    ui->doubleSpinBox_foglio2_risme_prezzo_5->setValue(campo.value(27).toDouble());
    ui->doubleSpinBox_foglio2_risme_prezzo_6->setValue(campo.value(28).toDouble());
    ui->doubleSpinBox_foglio2_lastreavviamenti_prime->setValue(campo.value(29).toDouble());
    ui->doubleSpinBox_foglio2_lastreavviamenti_successive->setValue(campo.value(30).toDouble());
    ui->doubleSpinBox_foglio2_stampa_prime->setValue(campo.value(31).toDouble());
    ui->doubleSpinBox_foglio2_stampa_successive->setValue(campo.value(32).toDouble());
    ui->doubleSpinBox_foglio2_stampadigitale_prime->setValue(campo.value(33).toDouble());
    ui->doubleSpinBox_foglio2_stampadigitale_successive->setValue(campo.value(34).toDouble());
    ui->doubleSpinBox_foglio2_percentuale->setValue(campo.value(35).toDouble());

//foglio3
    caricaComboBox(ui->comboBox_foglio3_carta_tipo_1, campo.value(36));
    caricaComboBox(ui->comboBox_foglio3_carta_tipo_2, campo.value(37));
    caricaComboBox(ui->comboBox_foglio3_carta_tipo_3, campo.value(38));
    caricaComboBox(ui->comboBox_foglio3_carta_tipo_4, campo.value(39));
    caricaComboBox(ui->comboBox_foglio3_carta_tipo_5, campo.value(40));
    ui->lineEdit_foglio3_tipocarta_1->setText(campo.value(41).toString());
    ui->lineEdit_foglio3_tipocarta_2->setText(campo.value(42).toString());
    ui->lineEdit_foglio3_tipocarta_3->setText(campo.value(43).toString());
    caricaComboBox(ui->comboBox_foglio3_carta_formato_1, campo.value(44));
    caricaComboBox(ui->comboBox_foglio3_carta_formato_2, campo.value(45));
    caricaComboBox(ui->comboBox_foglio3_carta_formato_3, campo.value(46));
    caricaComboBox(ui->comboBox_foglio3_carta_formato_4, campo.value(47));
    caricaComboBox(ui->comboBox_foglio3_carta_formato_5, campo.value(48));
    caricaComboBox(ui->comboBox_foglio3_carta_grammatura_1, campo.value(49));
    caricaComboBox(ui->comboBox_foglio3_carta_grammatura_2, campo.value(50));
    caricaComboBox(ui->comboBox_foglio3_carta_grammatura_3, campo.value(51));
    caricaComboBox(ui->comboBox_foglio3_carta_grammatura_4, campo.value(52));
    caricaComboBox(ui->comboBox_foglio3_carta_grammatura_5, campo.value(53));
    ui->spinBox_foglio3_nfogli_1->setValue(campo.value(54).toInt());
    ui->spinBox_foglio3_nfogli_2->setValue(campo.value(55).toInt());
    ui->spinBox_foglio3_nfogli_3->setValue(campo.value(56).toInt());
    ui->spinBox_foglio3_nfogli_4->setValue(campo.value(57).toInt());
    ui->spinBox_foglio3_nfogli_5->setValue(campo.value(58).toInt());
    ui->doubleSpinBox_foglio3_euro_1->setValue(campo.value(59).toDouble());
    ui->doubleSpinBox_foglio3_euro_2->setValue(campo.value(60).toDouble());
    ui->doubleSpinBox_foglio3_euro_3->setValue(campo.value(61).toDouble());
    ui->doubleSpinBox_foglio3_euro_4->setValue(campo.value(62).toDouble());
    ui->doubleSpinBox_foglio3_euro_5->setValue(campo.value(63).toDouble());
    ui->doubleSpinBox_foglio3_primencopie_1->setValue(campo.value(64).toDouble());
    ui->doubleSpinBox_foglio3_primencopie_2->setValue(campo.value(65).toDouble());
    ui->doubleSpinBox_foglio3_primencopie_3->setValue(campo.value(66).toDouble());
    ui->doubleSpinBox_foglio3_successivencopie_1->setValue(campo.value(67).toDouble());
    ui->doubleSpinBox_foglio3_successivencopie_2->setValue(campo.value(68).toDouble());
    ui->doubleSpinBox_foglio3_successivencopie_3->setValue(campo.value(69).toDouble());
    ui->doubleSpinBox_foglio3_percentuale->setValue(campo.value(70).toDouble());

    //foglio4
    caricaComboBox(ui->comboBox_foglio4_plastificazione_opaca_bianca,campo.value(71));
    ui->spinBox_foglio4_plastificazione_opaca_bianca->setValue(campo.value(72).toInt());
    ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_avviamento->setValue(campo.value(73).toDouble());
    caricaComboBox(ui->comboBox_foglio4_plastificazione_opaca_bianca_volta,campo.value(74));
    ui->spinBox_foglio4_plastificazione_opaca_bianca_volta->setValue(campo.value(75).toInt());
    ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_volta_avviamento->setValue(campo.value(76).toDouble());
    caricaComboBox(ui->comboBox_foglio4_plastificazione_lucida_bianca,campo.value(77));
    ui->spinBox_foglio4_plastificazione_lucida_bianca->setValue(campo.value(78).toInt());
    ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_avviamento->setValue(campo.value(79).toInt());
    caricaComboBox(ui->comboBox_foglio4_plastificazione_lucida_bianca_volta,campo.value(80));
    ui->spinBox_foglio4_plastificazione_lucida_bianca_volta->setValue(campo.value(81).toInt());
    ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_volta_avviamento->setValue(campo.value(82).toDouble());
    caricaComboBox(ui->comboBox_foglio4_serigrafia,campo.value(83));
    ui->spinBox_foglio4_serigrafia->setValue(campo.value(84).toInt());
    ui->doubleSpinBox_foglio4_serigrafia_avviamento->setValue(campo.value(85).toDouble());
    ui->doubleSpinBox_foglio4_serigrafia_telaio->setValue(campo.value(86).toDouble());
    ui->doubleSpinBox_fustella_primencopie->setValue(campo.value(87).toDouble());
    ui->spinBox_foglio4_fustellatura_nfogli->setValue(campo.value(88).toInt());
    ui->doubleSpinBox_spinBox_foglio4_fustellatura_euro->setValue(campo.value(89).toDouble());
    ui->doubleSpinBox_label_spinBox_foglio4_fustellatura_avviamento->setValue(campo.value(90).toDouble());
    ui->doubleSpinBox_cordonatura_primencopie->setValue(campo.value(91).toDouble());
    ui->doubleSpinBox_cordonatura_successivencopie->setValue(campo.value(92).toDouble());
    ui->doubleSpinBox_cordonatura_avviamento->setValue(campo.value(93).toDouble());
    ui->doubleSpinBox_foglio4_accoppiatura_prime->setValue(campo.value(94).toInt());
    ui->doubleSpinBox_foglio4_accoppiatura_succ->setValue(campo.value(95).toDouble());
    ui->doubleSpinBox_foglio4_stampaacaldo_primencopie->setValue(campo.value(96).toDouble());
    ui->doubleSpinBox_foglio4_stampaacaldo_successivencopie->setValue(campo.value(97).toDouble());
    ui->doubleSpinBox_foglio4_cliche_primencopie->setValue(campo.value(98).toDouble());
    ui->spinBox_foglio4_piegacopie_numero->setValue(campo.value(99).toInt());
    ui->doubleSpinBox_foglio4_piegacopie_euro->setValue(campo.value(100).toDouble());
    ui->spinBox_foglio4_tagliocopie_numero->setValue(campo.value(101).toInt());
    ui->doubleSpinBox_foglio4_tagliocopie_euro->setValue(campo.value(102).toDouble());
    ui->spinBox_foglio4_puntometallico_numero->setValue(campo.value(103).toInt());
    ui->doubleSpinBox_foglio4_puntometallico_euro->setValue(campo.value(104).toDouble());
    ui->doubleSpinBox_foglio4_puntometallico_avviamento->setValue(campo.value(105).toDouble());
    ui->spinBox_foglio4_brosurafresata_numero->setValue(campo.value(106).toInt());
    ui->doubleSpinBox_foglio4_brosurafresata_euro->setValue(campo.value(107).toDouble());
    ui->doubleSpinBox_foglio4_brosurafresata_avviamento->setValue(campo.value(108).toDouble());
    ui->spinBox_foglio4_filo_numero->setValue(campo.value(109).toInt());
    ui->doubleSpinBox_foglio4_filo_euro->setValue(campo.value(110).toDouble());
    ui->doubleSpinBox_foglio4_filo_avviamento->setValue(campo.value(111).toDouble());
    ui->spinBox_foglio4_cartonato_numero->setValue(campo.value(112).toInt());
    ui->doubleSpinBox_foglio4_cartonato_euro->setValue(campo.value(113).toDouble());
    ui->doubleSpinBox_foglio4_cartonato_avviamento->setValue(campo.value(114).toDouble());
    ui->spinBox_foglio4_spiralatura_numero->setValue(campo.value(115).toInt());
    ui->doubleSpinBox_foglio4_spiralatura_euro->setValue(campo.value(116).toDouble());
    ui->spinBox_foglio4_pacchi_numero->setValue(campo.value(117).toInt());
    ui->doubleSpinBox_foglio4_pacchi_euro->setValue(campo.value(118).toInt());
    ui->doubleSpinBox_foglio4_trasporto->setValue(campo.value(119).toDouble());
    ui->lineEdit_foglio4_prima->setText(campo.value(120).toString());
    ui->lineEdit_seconda->setText(campo.value(121).toString());
    ui->lineEdit_foglio4_terza->setText(campo.value(122).toString());
    ui->lineEdit_foglio4_quarta->setText(campo.value(123).toString());
    ui->lineEdit_foglio4_quinta->setText(campo.value(124).toString());
    ui->doubleSpinBox_foglio4_prima_primencopie->setValue(campo.value(125).toDouble());
    ui->doubleSpinBox_foglio4_seconda_primencopie->setValue(campo.value(126).toDouble());
    ui->doubleSpinBox_foglio4_terza_primencopie->setValue(campo.value(127).toDouble());
    ui->doubleSpinBox_foglio4_quarta_primencopie->setValue(campo.value(128).toDouble());
    ui->doubleSpinBox_foglio4_quinta_primencopie->setValue(campo.value(129).toDouble());
    ui->doubleSpinBox_foglio4_prima_successivencopie->setValue(campo.value(130).toDouble());
    ui->doubleSpinBox_foglio4_seconda_successivencopie->setValue(campo.value(131).toDouble());
    ui->doubleSpinBox_foglio4_terza_successivencopie->setValue(campo.value(132).toDouble());
    ui->doubleSpinBox_foglio4_quarta_successivencopie->setValue(campo.value(133).toDouble());
    ui->doubleSpinBox_foglio4_quinta_successivencopie->setValue(campo.value(134).toDouble());
    ui->doubleSpinBox_foglio4_percentuale->setValue(campo.value(135).toDouble());

}

void MainWindow::apriDb(QString nome)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(nome);
    database.open();
}

void MainWindow::popolaComboBox()
{


    /*
    POSSIBILE OTTIMIZZAZIONE PRESTAZIONALE!!
    nel caso di riempimento di comboBox uguali non è necessario eseguire
    di ognuna il count ma basta di una sola e utilizzare nelle altre il valore
     */

    QSqlQuery query;
    QSqlRecord campo;

    query.prepare("SELECT nome FROM clienti");
    query.exec();
    campo= query.record();

    ui->comboBox_clienti_seleziona->clear();
    while ( query.next())
    {
        ui->comboBox_clienti_seleziona->insertItem(ui->comboBox_clienti_seleziona->count(),query.value(campo.indexOf("nome")).toString());
    }
    query.clear();
    campo.clear();

    query.prepare("SELECT descrizione FROM cartatipo");
    query.exec();
    campo= query.record();

    ui->comboBox_foglio3_carta_tipo_1->clear();
    ui->comboBox_foglio3_carta_tipo_2->clear();
    ui->comboBox_foglio3_carta_tipo_3->clear();
    ui->comboBox_foglio3_carta_tipo_4->clear();
    ui->comboBox_foglio3_carta_tipo_5->clear();

    while ( query.next())
    {
        ui->comboBox_foglio3_carta_tipo_1->insertItem(ui->comboBox_foglio3_carta_tipo_1->count(), query.value(campo.indexOf("descrizione")).toString());
        ui->comboBox_foglio3_carta_tipo_2->insertItem(ui->comboBox_foglio3_carta_tipo_2->count(), query.value(campo.indexOf("descrizione")).toString());
        ui->comboBox_foglio3_carta_tipo_3->insertItem(ui->comboBox_foglio3_carta_tipo_3->count(), query.value(campo.indexOf("descrizione")).toString());
        ui->comboBox_foglio3_carta_tipo_4->insertItem(ui->comboBox_foglio3_carta_tipo_4->count(), query.value(campo.indexOf("descrizione")).toString());
        ui->comboBox_foglio3_carta_tipo_5->insertItem(ui->comboBox_foglio3_carta_tipo_5->count(), query.value(campo.indexOf("descrizione")).toString());
    }
    query.clear();
    campo.clear();


    query.prepare("SELECT formato FROM cartaformato");
    query.exec();
    campo= query.record();

    ui->comboBox_foglio3_carta_formato_1->clear();
    ui->comboBox_foglio3_carta_formato_2->clear();
    ui->comboBox_foglio3_carta_formato_3->clear();
    ui->comboBox_foglio3_carta_formato_4->clear();
    ui->comboBox_foglio3_carta_formato_5->clear();

    while ( query.next())
    {
        ui->comboBox_foglio3_carta_formato_1->insertItem(ui->comboBox_foglio3_carta_formato_1->count(), query.value(campo.indexOf("formato")).toString());
        ui->comboBox_foglio3_carta_formato_2->insertItem(ui->comboBox_foglio3_carta_formato_2->count(), query.value(campo.indexOf("formato")).toString());
        ui->comboBox_foglio3_carta_formato_3->insertItem(ui->comboBox_foglio3_carta_formato_3->count(), query.value(campo.indexOf("formato")).toString());
        ui->comboBox_foglio3_carta_formato_4->insertItem(ui->comboBox_foglio3_carta_formato_4->count(), query.value(campo.indexOf("formato")).toString());
        ui->comboBox_foglio3_carta_formato_5->insertItem(ui->comboBox_foglio3_carta_formato_5->count(), query.value(campo.indexOf("formato")).toString());
    }
    query.clear();
    campo.clear();



    query.prepare("SELECT grammatura FROM cartagrammatura");
    query.exec();
    campo= query.record();

    ui->comboBox_foglio3_carta_grammatura_1->clear();
    ui->comboBox_foglio3_carta_grammatura_2->clear();
    ui->comboBox_foglio3_carta_grammatura_3->clear();
    ui->comboBox_foglio3_carta_grammatura_4->clear();
    ui->comboBox_foglio3_carta_grammatura_5->clear();

    while ( query.next())
    {
        ui->comboBox_foglio3_carta_grammatura_1->insertItem(ui->comboBox_foglio3_carta_grammatura_1->count(), query.value(campo.indexOf("grammatura")).toString());
        ui->comboBox_foglio3_carta_grammatura_2->insertItem(ui->comboBox_foglio3_carta_grammatura_2->count(), query.value(campo.indexOf("grammatura")).toString());
        ui->comboBox_foglio3_carta_grammatura_3->insertItem(ui->comboBox_foglio3_carta_grammatura_3->count(), query.value(campo.indexOf("grammatura")).toString());
        ui->comboBox_foglio3_carta_grammatura_4->insertItem(ui->comboBox_foglio3_carta_grammatura_4->count(), query.value(campo.indexOf("grammatura")).toString());
        ui->comboBox_foglio3_carta_grammatura_5->insertItem(ui->comboBox_foglio3_carta_grammatura_5->count(), query.value(campo.indexOf("grammatura")).toString());
    }
    query.clear();
    campo.clear();


    query.prepare("SELECT formato FROM plastificazione");
    query.exec();
    campo= query.record();

    ui->comboBox_foglio4_plastificazione_lucida_bianca->clear();
    ui->comboBox_foglio4_plastificazione_lucida_bianca_volta->clear();
    ui->comboBox_foglio4_plastificazione_opaca_bianca->clear();
    ui->comboBox_foglio4_plastificazione_opaca_bianca_volta->clear();

    while (query.next())
    {
        ui->comboBox_foglio4_plastificazione_lucida_bianca->insertItem(ui->comboBox_foglio4_plastificazione_lucida_bianca->count(), query.value(campo.indexOf("formato")).toString());
        ui->comboBox_foglio4_plastificazione_lucida_bianca_volta->insertItem(ui->comboBox_foglio4_plastificazione_lucida_bianca_volta->count(), query.value(campo.indexOf("formato")).toString());
        ui->comboBox_foglio4_plastificazione_opaca_bianca->insertItem(ui->comboBox_foglio4_plastificazione_opaca_bianca->count(), query.value(campo.indexOf("formato")).toString());
        ui->comboBox_foglio4_plastificazione_opaca_bianca_volta->insertItem(ui->comboBox_foglio4_plastificazione_opaca_bianca_volta->count(), query.value(campo.indexOf("formato")).toString());
    }
     query.clear();
     campo.clear();

    query.prepare("SELECT formato FROM serigrafia");
    query.exec();
    campo=query.record();

    ui->comboBox_foglio4_serigrafia->clear();
    while (query.next())
    {
        ui->comboBox_foglio4_serigrafia->insertItem(ui->comboBox_foglio4_serigrafia->count(), query.value(campo.indexOf("formato")).toString());
    }
    query.clear();
    campo.clear();

}

void MainWindow::pulisciPreventivo()
{
    //foglio 1
   ui->plainTextEdit_descrizione->clear();
   ui->spinBox_foglio1_ncopie->setValue(1);
   ui->dateEdit_foglio1->setDate(QDate::currentDate());

   //foglio 2
   ui->spinBox_foglio2_lastre_n_1->setValue(0);
   ui->spinBox_foglio2_lastre_n_2->setValue(0);
   ui->spinBox_foglio2_lastre_n_3->setValue(0);
   ui->spinBox_foglio2_lastre_n_4->setValue(0);
   ui->spinBox_foglio2_lastre_n_5->setValue(0);
   ui->spinBox_foglio2_lastre_n_6->setValue(0);

   ui->doubleSpinBox_foglio2_lastre_prezzo_1->setValue(0);
   ui->doubleSpinBox_foglio2_lastre_prezzo_2->setValue(0);
   ui->doubleSpinBox_foglio2_lastre_prezzo_3->setValue(0);
   ui->doubleSpinBox_foglio2_lastre_prezzo_4->setValue(0);
   ui->doubleSpinBox_foglio2_lastre_prezzo_5->setValue(0);
   ui->doubleSpinBox_foglio2_lastre_prezzo_6->setValue(0);

   ui->spinBox_foglio2_risme_n_1->setValue(0);
   ui->spinBox_foglio2_risme_n_2->setValue(0);
   ui->spinBox_foglio2_risme_n_3->setValue(0);
   ui->spinBox_foglio2_risme_n_4->setValue(0);
   ui->spinBox_foglio2_risme_n_5->setValue(0);
   ui->spinBox_foglio2_risme_n_6->setValue(0);

   ui->doubleSpinBox_foglio2_risme_prezzo_1->setValue(0);
   ui->doubleSpinBox_foglio2_risme_prezzo_2->setValue(0);
   ui->doubleSpinBox_foglio2_risme_prezzo_3->setValue(0);
   ui->doubleSpinBox_foglio2_risme_prezzo_4->setValue(0);
   ui->doubleSpinBox_foglio2_risme_prezzo_5->setValue(0);
   ui->doubleSpinBox_foglio2_risme_prezzo_6->setValue(0);

   ui->doubleSpinBox_foglio2_lastreavviamenti_prime->setValue(0);
   ui->doubleSpinBox_foglio2_lastreavviamenti_successive->setValue(0);
   ui->doubleSpinBox_foglio2_stampa_prime->setValue(0);
   ui->doubleSpinBox_foglio2_stampa_successive->setValue(0);
   ui->doubleSpinBox_foglio2_stampadigitale_prime->setValue(0);
   ui->doubleSpinBox_foglio2_stampadigitale_successive->setValue(0);
   ui->doubleSpinBox_foglio2_percentuale->setValue(0);

   //foglio3

   ui->comboBox_foglio3_carta_tipo_1->clear();
   ui->comboBox_foglio3_carta_tipo_2->clear();
   ui->comboBox_foglio3_carta_tipo_3->clear();
   ui->comboBox_foglio3_carta_tipo_4->clear();
   ui->comboBox_foglio3_carta_tipo_5->clear();
   ui->lineEdit_foglio3_tipocarta_1->clear();
   ui->lineEdit_foglio3_tipocarta_2->clear();
   ui->lineEdit_foglio3_tipocarta_3->clear();
   ui->comboBox_foglio3_carta_formato_1->clear();
   ui->comboBox_foglio3_carta_formato_2->clear();
   ui->comboBox_foglio3_carta_formato_3->clear();
   ui->comboBox_foglio3_carta_formato_4->clear();
   ui->comboBox_foglio3_carta_formato_5->clear();
   ui->comboBox_foglio3_carta_grammatura_1->clear();
   ui->comboBox_foglio3_carta_grammatura_2->clear();
   ui->comboBox_foglio3_carta_grammatura_3->clear();
   ui->comboBox_foglio3_carta_grammatura_4->clear();
   ui->comboBox_foglio3_carta_grammatura_5->clear();
   ui->spinBox_foglio3_nfogli_1->setValue(0);
   ui->spinBox_foglio3_nfogli_2->setValue(0);
   ui->spinBox_foglio3_nfogli_3->setValue(0);
   ui->spinBox_foglio3_nfogli_4->setValue(0);
   ui->spinBox_foglio3_nfogli_5->setValue(0);
   ui->doubleSpinBox_foglio3_euro_1->setValue(0);
   ui->doubleSpinBox_foglio3_euro_2->setValue(0);
   ui->doubleSpinBox_foglio3_euro_3->setValue(0);
   ui->doubleSpinBox_foglio3_euro_4->setValue(0);
   ui->doubleSpinBox_foglio3_euro_5->setValue(0);
   ui->doubleSpinBox_foglio3_primencopie_1->setValue(0);
   ui->doubleSpinBox_foglio3_primencopie_2->setValue(0);
   ui->doubleSpinBox_foglio3_primencopie_3->setValue(0);
   ui->doubleSpinBox_foglio3_successivencopie_1->setValue(0);
   ui->doubleSpinBox_foglio3_successivencopie_1->setValue(0);
   ui->doubleSpinBox_foglio3_successivencopie_1->setValue(0);
   ui->doubleSpinBox_foglio3_percentuale->setValue(0);

   ui->comboBox_foglio4_plastificazione_opaca_bianca->clear();
   ui->spinBox_foglio4_plastificazione_opaca_bianca->setValue(0);
   ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_avviamento->setValue(0);
   ui->comboBox_foglio4_plastificazione_opaca_bianca_volta->clear();
   ui->spinBox_foglio4_plastificazione_opaca_bianca_volta->setValue(0);
   ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_volta_avviamento->setValue(0);
   ui->comboBox_foglio4_plastificazione_lucida_bianca->clear();
   ui->spinBox_foglio4_plastificazione_lucida_bianca->setValue(0);
   ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_avviamento->setValue(0);
   ui->comboBox_foglio4_plastificazione_lucida_bianca_volta->clear();
   ui->spinBox_foglio4_plastificazione_lucida_bianca_volta->setValue(0);
   ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_volta_avviamento->setValue(0);
   ui->comboBox_foglio4_serigrafia->clear();

   ui->spinBox_foglio4_serigrafia->setValue(0);
   ui->doubleSpinBox_foglio4_serigrafia_avviamento->setValue(0);
   ui->doubleSpinBox_foglio4_serigrafia_telaio->setValue(0);
   ui->doubleSpinBox_fustella_primencopie->setValue(0);
   ui->spinBox_foglio4_fustellatura_nfogli->setValue(0);
   ui->doubleSpinBox_spinBox_foglio4_fustellatura_euro->setValue(0);
   ui->doubleSpinBox_label_spinBox_foglio4_fustellatura_avviamento->setValue(0);
   ui->doubleSpinBox_cordonatura_primencopie->setValue(0);
   ui->doubleSpinBox_cordonatura_successivencopie->setValue(0);
   ui->doubleSpinBox_cordonatura_avviamento->setValue(0);
   ui->doubleSpinBox_foglio4_accoppiatura_prime->setValue(0);
   ui->doubleSpinBox_foglio4_accoppiatura_succ->setValue(0);
   ui->doubleSpinBox_foglio4_stampaacaldo_primencopie->setValue(0);
   ui->doubleSpinBox_foglio4_stampaacaldo_successivencopie->setValue(0);
   ui->doubleSpinBox_foglio4_cliche_primencopie->setValue(0);
   ui->spinBox_foglio4_piegacopie_numero->setValue(0);
   ui->doubleSpinBox_foglio4_piegacopie_euro->setValue(0);
   ui->spinBox_foglio4_tagliocopie_numero->setValue(0);
   ui->doubleSpinBox_foglio4_tagliocopie_euro->setValue(0);
   ui->spinBox_foglio4_puntometallico_numero->setValue(0);
   ui->doubleSpinBox_foglio4_puntometallico_euro->setValue(0);
   ui->doubleSpinBox_foglio4_puntometallico_avviamento->setValue(0);
   ui->spinBox_foglio4_brosurafresata_numero->setValue(0);
   ui->doubleSpinBox_foglio4_brosurafresata_euro->setValue(0);
   ui->doubleSpinBox_foglio4_brosurafresata_avviamento->setValue(0);
   ui->spinBox_foglio4_filo_numero->setValue(0);
   ui->doubleSpinBox_foglio4_filo_euro->setValue(0);
   ui->doubleSpinBox_foglio4_filo_avviamento->setValue(0);
   ui->spinBox_foglio4_cartonato_numero->setValue(0);
   ui->doubleSpinBox_foglio4_cartonato_euro->setValue(0);
   ui->doubleSpinBox_foglio4_cartonato_avviamento->setValue(0);
   ui->spinBox_foglio4_spiralatura_numero->setValue(0);
   ui->doubleSpinBox_foglio4_spiralatura_euro->setValue(0);
   ui->spinBox_foglio4_pacchi_numero->setValue(0);
   ui->doubleSpinBox_foglio4_pacchi_euro->setValue(0);
   ui->doubleSpinBox_foglio4_trasporto->setValue(0);
   ui->lineEdit_foglio4_prima->clear();
   ui->lineEdit_seconda->clear();
   ui->lineEdit_foglio4_terza->clear();
   ui->lineEdit_foglio4_quarta->clear();
   ui->lineEdit_foglio4_quinta->clear();
   ui->doubleSpinBox_foglio4_prima_primencopie->setValue(0);
   ui->doubleSpinBox_foglio4_seconda_primencopie->setValue(0);
   ui->doubleSpinBox_foglio4_terza_primencopie->setValue(0);
   ui->doubleSpinBox_foglio4_quarta_primencopie->setValue(0);
   ui->doubleSpinBox_foglio4_quinta_primencopie->setValue(0);
   ui->doubleSpinBox_foglio4_prima_successivencopie->setValue(0);
   ui->doubleSpinBox_foglio4_seconda_successivencopie->setValue(0);
   ui->doubleSpinBox_foglio4_terza_successivencopie->setValue(0);
   ui->doubleSpinBox_foglio4_quarta_successivencopie->setValue(0);
   ui->doubleSpinBox_foglio4_quinta_successivencopie->setValue(0);
   ui->doubleSpinBox_foglio4_percentuale->setValue(0);

   popolaComboBox();
   refreshFoglio2();
   refreshFoglio3();
   refreshFoglio4();
   refreshFoglio5();
    }





double MainWindow::formatoASuperficie(QString formato)
{

    QString primoValore;
    QString secondoValore;
    primoValore = formato.section("x",0,0);
    secondoValore = formato.section("x",1,1);
    return ( ( primoValore.toDouble()*secondoValore.toDouble() ) /1000000);

}

void MainWindow::showHide(QString show)
{

    ui->widget_navigazione->show();

    //refresh di TUTTE le tabelle
    refreshTabelle();

    //nasconde tutto tranne la sezione voluta
    if ( show == "benvenuto" )
    {
        ui->bottone_salva_preventivo->hide();
        ui->widget_benvenuto->show();
        ui->widget_navigazione->hide(); //poco elegante il show/hide delle stesso widget ma molto più veloce nell'implementazione
    }
        else
        ui->widget_benvenuto->hide();
    if ( show == "preventivi" )
        {
        ui->widget_preventivi->show();
        ui->bottone_preventivi_nuovo->show();
        ui->label_preventiv_cerca->show();
        ui->lineEdit_preventivi_cerca->show();
        ui->tableView_preventivi->show();
        ui->tabWidget_preventivi->hide();
        ui->bottone_preventivi_elimina->show();
        ui->bottone_preventivi_modifica->show();
        ui->bottone_preventivi_usamodello->show();
        }
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
    {
        ui->widget_clienti->show();
        ui->bottone_salva_preventivo->hide();
    }
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


void MainWindow::refreshTabelle()
{
    /* Questa funzione fa ogni volta il refresh di TUTTE le tabelle.
       In futuro sarebbe meglio fare il refresh solo di quella necessaria */

    QSqlTableModel *tabella_plastificazione = new QSqlTableModel;
    tabella_plastificazione->setTable("plastificazione");
    tabella_plastificazione->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_plastificazione->select();
    tabella_plastificazione->setHeaderData(0, Qt::Horizontal, "Formato (mm)");
    tabella_plastificazione->setHeaderData(1, Qt::Horizontal, "Lucida Bianca Euro");
    tabella_plastificazione->setHeaderData(2, Qt::Horizontal, "Lucida Bianca/Volta Euro");
    tabella_plastificazione->setHeaderData(3, Qt::Horizontal, "Opaca Bianca Euro");
    tabella_plastificazione->setHeaderData(4, Qt::Horizontal, "Opaca Bianca/Volta Euro");
    ui->tableView_plastificazione->setModel(tabella_plastificazione);

    QSqlTableModel *tabella_clienti = new QSqlTableModel;
    tabella_clienti->setTable("clienti");
    tabella_clienti->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_clienti->select();
    tabella_clienti->setHeaderData(0, Qt::Horizontal, "Nome");
    ui->tableView_clienti->setModel(tabella_clienti);


    QSqlTableModel *tabella_carta_formato = new QSqlTableModel;
    tabella_carta_formato->setTable("cartaformato");
    tabella_carta_formato->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_carta_formato->select();
    tabella_carta_formato->setHeaderData(0, Qt::Horizontal, "Formato (mm)");
    ui->tableView_carta_formato->setModel(tabella_carta_formato);

    QSqlTableModel *tabella_carta_grammatura = new QSqlTableModel;
    tabella_carta_grammatura->setTable("cartagrammatura");
    tabella_carta_grammatura->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_carta_grammatura->select();
    tabella_carta_grammatura->setHeaderData(0, Qt::Horizontal, "Grammatura (g/m2)");
    ui->tableView_carta_grammatura->setModel(tabella_carta_grammatura);

    QSqlTableModel *tabella_serigrafia = new QSqlTableModel;
    tabella_serigrafia->setTable("serigrafia");
    tabella_serigrafia->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_serigrafia->select();
    tabella_serigrafia->setHeaderData(0, Qt::Horizontal, "Formato (mm)");
    tabella_serigrafia->setHeaderData(1, Qt::Horizontal, "Prezzo Euro");
    ui->tableView_serigrafia->setModel(tabella_serigrafia);

    QSqlTableModel *tabella_carta_tipo = new QSqlTableModel;
    tabella_carta_tipo->setTable("cartatipo");
    tabella_carta_tipo->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_carta_tipo->select();
    tabella_carta_tipo->setHeaderData(0, Qt::Horizontal, "Descrizione");

    ui->tableView_carta_tipo->setModel(tabella_carta_tipo);


    QSqlTableModel *tabella_preventivi = new QSqlTableModel;
    tabella_preventivi->setTable("preventivo");

    if (!ui->lineEdit_preventivi_cerca->text().isEmpty())
    {
        QString filtro;
        filtro = "numero ='";
        filtro.append(ui->lineEdit_preventivi_cerca->text());
        filtro.append("' OR cliente='");
        filtro.append(ui->lineEdit_preventivi_cerca->text());
        filtro.append("' OR descrizione='");
        filtro.append(ui->lineEdit_preventivi_cerca->text());
        filtro.append("' OR data ='");
        filtro.append(ui->lineEdit_preventivi_cerca->text());
        filtro.append("'");
        tabella_preventivi->setFilter(filtro);
    }
    tabella_preventivi->select();

    tabella_preventivi->setHeaderData(0, Qt::Horizontal, "Numero");
    tabella_preventivi->setHeaderData(1, Qt::Horizontal, "Data");
    tabella_preventivi->setHeaderData(2, Qt::Horizontal, "Cliente");
    tabella_preventivi->setHeaderData(3, Qt::Horizontal, "Descrizione lavoro");

    ui->tableView_preventivi->setModel(tabella_preventivi);

    /* nascondi altre colonne
    for (int i=4; i<136; i++)
        ui->tableView_preventivi->hideColumn(i);
*/


    popolaComboBox();
    //Aggiungere qui il refresh di altre tabelle
}

void MainWindow::on_bottone_plastificazione_aggiungi_clicked()
{
    QSqlQuery query;
    n=n+1;
    query.prepare("INSERT INTO plastificazione (formato, lucidabianca, lucidabiancavolta, opacabianca, opacabiancavolta)"
                  "VALUES(:formato, :lucidabianca, :lucidabiancavolta, :opacabianca, :opacabiancavolta) ") ;
    query.bindValue(":formato", n);
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

    QSqlQuery query;
    n=n+1.0;
    qDebug() << query.prepare("INSERT INTO serigrafia (formato, prezzo)"
                              "VALUES(:formato, :prezzo) ");
    query.bindValue(":formato", n);
    query.bindValue(":prezzo", n);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();
}


void MainWindow::on_bottone_clienti_aggiungi_clicked()
{

    QSqlQuery query;
    n=n+1;
    qDebug() << query.prepare("INSERT INTO clienti (nome)"
                              "VALUES(:nome) ");
    query.bindValue(":nome", n);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();
}

void MainWindow::on_bottone_carta_formato_aggiungi_clicked()
{

    QSqlQuery query;
    n=n+1;
    qDebug() << query.prepare("INSERT INTO cartaformato (formato)"
                              "VALUES(:formato) ");
    query.bindValue(":formato", n);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();
}

void MainWindow::on_bottone_carta_grammatura_aggiungi_clicked()
{

    QSqlQuery query;
    n=n+1;
    qDebug() << query.prepare("INSERT INTO cartagrammatura (grammatura)"
                              "VALUES(:grammatura) ");
    query.bindValue(":grammatura", n);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();
}

void MainWindow::on_bottone_carta_tipo_aggiungi_clicked()
{
    QSqlQuery query;
    n=n+1.0;
    qDebug() << query.prepare("INSERT INTO cartatipo (descrizione)"
                              "VALUES(:descrizione) ");
    query.bindValue(":descrizione", n);
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();
}

void MainWindow::on_bottone_salva_preventivo_clicked()
{


    //Ricordarsi che manca la data
    QSqlQuery query;
    QSqlRecord campo;

    query = "SELECT numero FROM preventivo WHERE numero = '"+ui->label_npreventivo->text()+"'";
    qDebug()<<query.exec();
    query.next();
    campo= query.record();

    if (!campo.value(0).isNull())
    {
        eliminaRiga("preventivo","numero",ui->label_npreventivo->text());
    }
    else
    {
        qDebug() << query.prepare("INSERT INTO npreventivo (numero)"
                                  "VALUES(:numero) ");
        query.bindValue(":numero", ui->label_npreventivo->text().toInt());
        qDebug() << query.exec();
        query.clear();
    }
        query.clear();

        qDebug() << query.prepare("INSERT INTO preventivo (numero, data, cliente, descrizione, ncopie, lastren1, lastren2, lastren3, lastren4, lastren5, lastren6, rismen1, rismen2, rismen3, rismen4, rismen5, rismen6, lastreeuro1, lastreeuro2, lastreeuro3, lastreeuro4, lastreeuro5, lastreeuro6, rismeeuro1, rismeeuro2, rismeeuro3, rismeeuro4, rismeeuro5, rismeeuro6, lastravvprime, lastravvsucc, stampaprime, stampasucc, stampadigprime, stampadigsucc, percf2, tipo1, tipo2, tipo3, tipo4, tipo5, tipo6, tipo7, tipo8, formato1, formato2, formato3, formato4, formato5, grammatura1, grammatura2, grammatura3, grammatura4, grammatura5, nfogli1, nfogli2, nfogli3, nfogli4, nfogli5, euro1, euro2, euro3, euro4, euro5, europrime1, europrime2, europrime3, eurosucc1, eurosucc2, eurosucc3, percf3, plopbformato, plopbnfogli, plopbavv, plopbvformato, plopbvnfogli, plopbvavv, pllubformato, pllubnfogli, pllubavv, pllubvformato, pllubvnfogli, pllubvavv, serformato, sernfogli, seravv, sertelaio, fustella, fustellaturanfogli, fustellaturaeuro, fustellaturaavv, cordonaturaprime, cordonaturasucc, cordonaturaavv, accoppiaturaprime, accoppiaturasucc, stampacaldoprime, stampacaldosucc, cliche, piegacopien, piegacopieeuro, tagliocopien, tagliocopieeuro, puntometncopie, puntometeuro, puntometavv, brosfresncopie, brosfreseuro, brosfresavv, brosfiloncopie, brosfiloeuro, brosfiloavv, cartncopie, carteuro, cartavv, spirncopie, spireuro, pacchipolincopie, pacchipolieuro, trasporto, riga1, riga2, riga3, riga4, riga5, riga1prime, riga2prime, riga3prime, riga4prime, riga5prime, riga1succ, riga2succ, riga3succ, riga4succ, riga5succ, percf4)"
                      "VALUES(:numero, :data, :cliente, :descrizione, :ncopie, :lastren1, :lastren2, :lastren3, :lastren4, :lastren5, :lastren6, :rismen1, :rismen2, :rismen3, :rismen4, :rismen5, :rismen6, :lastreeuro1, :lastreeuro2, :lastreeuro3, :lastreeuro4, :lastreeuro5, :lastreeuro6, :rismeeuro1, :rismeeuro2, :rismeeuro3, :rismeeuro4, :rismeeuro5, :rismeeuro6, :lastravvprime, :lastravvsucc, :stampaprime, :stampasucc, :stampadigprime, :stampadigsucc, :percf2, :tipo1, :tipo2, :tipo3, :tipo4, :tipo5, :tipo6, :tipo7, :tipo8, :formato1, :formato2, :formato3, :formato4, :formato5, :grammatura1, :grammatura2, :grammatura3, :grammatura4, :grammatura5, :nfogli1, :nfogli2, :nfogli3, :nfogli4, :nfogli5, :euro1, :euro2, :euro3, :euro4, :euro5, :europrime1, :europrime2, :europrime3, :eurosucc1, :eurosucc2, :eurosucc3, :percf3, :plopbformato, :plopbnfogli, :plopbavv, :plopbvformato, :plopbvnfogli, :plopbvavv, :pllubformato, :pllubnfogli, :pllubavv, :pllubvformato, :pllubvnfogli, :pllubvavv, :serformato, :sernfogli, :seravv, :sertelaio, :fustella, :fustellaturanfogli, :fustellaturaeuro, :fustellaturaavv, :cordonaturaprime, :cordonaturasucc, :cordonaturaavv, :accoppiaturaprime, :accoppiaturasucc, :stampacaldoprime, :stampacaldosucc, :cliche, :piegacopien, :piegacopieeuro, :tagliocopien, :tagliocopieeuro, :puntometncopie, :puntometeuro, :puntometavv, :brosfresncopie, :brosfreseuro, :brosfresavv, :brosfiloncopie, :brosfiloeuro, :brosfiloavv, :cartncopie, :carteuro, :cartavv, :spirncopie, :spireuro, :pacchipolincopie, :pacchipolieuro, :trasporto, :riga1, :riga2, :riga3, :riga4, :riga5, :riga1prime, :riga2prime, :riga3prime, :riga4prime, :riga5prime, :riga1succ, :riga2succ, :riga3succ, :riga4succ, :riga5succ, :percf4) ");
        query.bindValue(":numero", ui->label_npreventivo->text().toInt() );
        query.bindValue(":data", ui->dateEdit_foglio1->date().toString("dd/MM/yyyy") );
        query.bindValue(":cliente", ui->comboBox_clienti_seleziona->currentText() );
        query.bindValue(":descrizione", ui->plainTextEdit_descrizione->toPlainText() );
        query.bindValue(":ncopie", ui->spinBox_foglio1_ncopie->value());
        query.bindValue(":lastren1", ui->spinBox_foglio2_lastre_n_1->value() );
        query.bindValue(":lastren2", ui->spinBox_foglio2_lastre_n_2->value() );
        query.bindValue(":lastren3", ui->spinBox_foglio2_lastre_n_3->value() );
        query.bindValue(":lastren4", ui->spinBox_foglio2_lastre_n_4->value() );
        query.bindValue(":lastren5", ui->spinBox_foglio2_lastre_n_5->value() );
        query.bindValue(":lastren6", ui->spinBox_foglio2_lastre_n_6->value() );
        query.bindValue(":rismen1", ui->spinBox_foglio2_risme_n_1->value() );
        query.bindValue(":rismen2", ui->spinBox_foglio2_risme_n_2->value() );
        query.bindValue(":rismen3", ui->spinBox_foglio2_risme_n_3->value() );
        query.bindValue(":rismen4", ui->spinBox_foglio2_risme_n_4->value() );
        query.bindValue(":rismen5", ui->spinBox_foglio2_risme_n_5->value() );
        query.bindValue(":rismen6", ui->spinBox_foglio2_risme_n_6->value() );
        query.bindValue(":lastreeuro1", ui->doubleSpinBox_foglio2_lastre_prezzo_1->value() );
        query.bindValue(":lastreeuro2", ui->doubleSpinBox_foglio2_lastre_prezzo_2->value() );
        query.bindValue(":lastreeuro3", ui->doubleSpinBox_foglio2_lastre_prezzo_3->value() );
        query.bindValue(":lastreeuro4", ui->doubleSpinBox_foglio2_lastre_prezzo_4->value() );
        query.bindValue(":lastreeuro5", ui->doubleSpinBox_foglio2_lastre_prezzo_5->value() );
        query.bindValue(":lastreeuro6", ui->doubleSpinBox_foglio2_lastre_prezzo_6->value() );
        query.bindValue(":rismeeuro1", ui->doubleSpinBox_foglio2_risme_prezzo_1->value() );
        query.bindValue(":rismeeuro2", ui->doubleSpinBox_foglio2_risme_prezzo_2->value() );
        query.bindValue(":rismeeuro3", ui->doubleSpinBox_foglio2_risme_prezzo_3->value() );
        query.bindValue(":rismeeuro4", ui->doubleSpinBox_foglio2_risme_prezzo_4->value() );
        query.bindValue(":rismeeuro5", ui->doubleSpinBox_foglio2_risme_prezzo_5->value() );
        query.bindValue(":rismeeuro6", ui->doubleSpinBox_foglio2_risme_prezzo_6->value() );
        query.bindValue(":lastravvprime", ui->doubleSpinBox_foglio2_lastreavviamenti_prime->value() );
        query.bindValue(":lastravvsucc", ui->doubleSpinBox_foglio2_lastreavviamenti_successive->value() );
        query.bindValue(":stampaprime", ui->doubleSpinBox_foglio2_stampa_prime->value() );
        query.bindValue(":stampasucc", ui->doubleSpinBox_foglio2_stampa_successive->value() );
        query.bindValue(":stampadigprime", ui->doubleSpinBox_foglio2_stampadigitale_prime->value() );
        query.bindValue(":stampadigsucc", ui->doubleSpinBox_foglio2_stampadigitale_successive->value() );
        query.bindValue(":percf2", ui->doubleSpinBox_foglio2_percentuale->value() );
        query.bindValue(":tipo1", ui->comboBox_foglio3_carta_tipo_1->currentText() );
        query.bindValue(":tipo2", ui->comboBox_foglio3_carta_tipo_2->currentText() );
        query.bindValue(":tipo3", ui->comboBox_foglio3_carta_tipo_3->currentText() );
        query.bindValue(":tipo4", ui->comboBox_foglio3_carta_tipo_4->currentText() );
        query.bindValue(":tipo5", ui->comboBox_foglio3_carta_tipo_5->currentText() );
        query.bindValue(":tipo6", ui->lineEdit_foglio3_tipocarta_1->text() );
        query.bindValue(":tipo7", ui->lineEdit_foglio3_tipocarta_2->text() );
        query.bindValue(":tipo8", ui->lineEdit_foglio3_tipocarta_3->text() );
        query.bindValue(":formato1", ui->comboBox_foglio3_carta_formato_1->currentText() );
        query.bindValue(":formato2", ui->comboBox_foglio3_carta_formato_2->currentText() );
        query.bindValue(":formato3", ui->comboBox_foglio3_carta_formato_3->currentText() );
        query.bindValue(":formato4", ui->comboBox_foglio3_carta_formato_4->currentText() );
        query.bindValue(":formato5", ui->comboBox_foglio3_carta_formato_5->currentText() );
        query.bindValue(":grammatura1",ui->comboBox_foglio3_carta_grammatura_1->currentText().toDouble());
        query.bindValue(":grammatura2",ui->comboBox_foglio3_carta_grammatura_2->currentText().toDouble());
        query.bindValue(":grammatura3",ui->comboBox_foglio3_carta_grammatura_3->currentText().toDouble());
        query.bindValue(":grammatura4",ui->comboBox_foglio3_carta_grammatura_4->currentText().toDouble());
        query.bindValue(":grammatura5",ui->comboBox_foglio3_carta_grammatura_5->currentText().toDouble());
        query.bindValue(":nfogli1",ui->spinBox_foglio3_nfogli_1->value() );
        query.bindValue(":nfogli2",ui->spinBox_foglio3_nfogli_2->value() );
        query.bindValue(":nfogli3",ui->spinBox_foglio3_nfogli_3->value() );
        query.bindValue(":nfogli4",ui->spinBox_foglio3_nfogli_4->value() );
        query.bindValue(":nfogli5",ui->spinBox_foglio3_nfogli_5->value() );
        query.bindValue(":euro1", ui->doubleSpinBox_foglio3_euro_1->value() );
        query.bindValue(":euro2", ui->doubleSpinBox_foglio3_euro_2->value() );
        query.bindValue(":euro3", ui->doubleSpinBox_foglio3_euro_3->value() );
        query.bindValue(":euro4", ui->doubleSpinBox_foglio3_euro_4->value() );
        query.bindValue(":euro5", ui->doubleSpinBox_foglio3_euro_5->value() );
        query.bindValue(":europrime1", ui->doubleSpinBox_foglio3_primencopie_1->value() );
        query.bindValue(":europrime2", ui->doubleSpinBox_foglio3_primencopie_2->value() );
        query.bindValue(":europrime3", ui->doubleSpinBox_foglio3_primencopie_3->value() );
        query.bindValue(":eurosucc1", ui->doubleSpinBox_foglio3_successivencopie_1->value() );
        query.bindValue(":eurosucc2", ui->doubleSpinBox_foglio3_successivencopie_2->value() );
        query.bindValue(":eurosucc3", ui->doubleSpinBox_foglio3_successivencopie_3->value() );
        query.bindValue(":percf3", ui->doubleSpinBox_foglio3_percentuale->value() );
        query.bindValue(":plopbformato", ui->comboBox_foglio4_plastificazione_opaca_bianca->currentText() );
        query.bindValue(":plopbnfogli", ui->spinBox_foglio4_plastificazione_opaca_bianca->value() );
        query.bindValue(":plopbavv", ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_avviamento->value() );
        query.bindValue(":plopbvformato", ui->comboBox_foglio4_plastificazione_opaca_bianca_volta->currentText() );
        query.bindValue(":plopbvnfogli", ui->spinBox_foglio4_plastificazione_opaca_bianca_volta->value() );
        query.bindValue(":plopbvavv", ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_volta_avviamento->value() );
        query.bindValue(":pllubformato", ui->comboBox_foglio4_plastificazione_lucida_bianca->currentText() );
        query.bindValue(":pllubnfogli", ui->spinBox_foglio4_plastificazione_lucida_bianca->value() );
        query.bindValue(":pllubavv", ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_avviamento->value() );
        query.bindValue(":pllubvformato", ui->comboBox_foglio4_plastificazione_lucida_bianca_volta->currentText() );
        query.bindValue(":pllubvnfogli", ui->spinBox_foglio4_plastificazione_lucida_bianca_volta->value() );
        query.bindValue(":pllubvavv", ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_volta_avviamento->value() );
        query.bindValue(":serformato", ui->comboBox_foglio4_serigrafia->currentText() );
        query.bindValue(":sernfogli", ui->spinBox_foglio4_serigrafia->value() );
        query.bindValue(":seravv", ui->doubleSpinBox_foglio4_serigrafia_avviamento->value() );
        query.bindValue(":sertelaio", ui->doubleSpinBox_foglio4_serigrafia_telaio->value() );
        query.bindValue(":fustella", ui->doubleSpinBox_fustella_primencopie->value() );
        query.bindValue(":fustellaturanfogli", ui->spinBox_foglio4_fustellatura_nfogli->value() );
        query.bindValue(":fustellaturaeuro", ui->doubleSpinBox_spinBox_foglio4_fustellatura_euro->value() );
        query.bindValue(":fustellaturaavv", ui->doubleSpinBox_label_spinBox_foglio4_fustellatura_avviamento->value() );
        query.bindValue(":cordonaturaprime", ui->doubleSpinBox_cordonatura_primencopie->value() );
        query.bindValue(":cordonaturasucc", ui->doubleSpinBox_cordonatura_successivencopie->value() );
        query.bindValue(":cordonaturaavv", ui->doubleSpinBox_cordonatura_avviamento->value() );
        query.bindValue(":accoppiaturaprime", ui->doubleSpinBox_foglio4_accoppiatura_prime->value() );
        query.bindValue(":accoppiaturasucc", ui->doubleSpinBox_foglio4_accoppiatura_succ->value() );
        query.bindValue(":stampacaldoprime", ui->doubleSpinBox_foglio4_stampaacaldo_primencopie->value() );
        query.bindValue(":stampacaldosucc", ui->doubleSpinBox_foglio4_stampaacaldo_successivencopie->value() );
        query.bindValue(":cliche", ui->doubleSpinBox_foglio4_cliche_primencopie->value() );
        query.bindValue(":piegacopien", ui->spinBox_foglio4_piegacopie_numero->value() );
        query.bindValue(":piegacopieeuro", ui->doubleSpinBox_foglio4_piegacopie_euro->value() );
        query.bindValue(":tagliocopien", ui->spinBox_foglio4_tagliocopie_numero->value() );
        query.bindValue(":tagliocopieeuro", ui->doubleSpinBox_foglio4_tagliocopie_euro->value() );
        query.bindValue(":puntometncopie", ui->spinBox_foglio4_puntometallico_numero->value() );
        query.bindValue(":puntometeuro", ui->doubleSpinBox_foglio4_puntometallico_euro->value() );
        query.bindValue(":puntometavv", ui->doubleSpinBox_foglio4_puntometallico_avviamento->value() );
        query.bindValue(":brosfresncopie", ui->spinBox_foglio4_brosurafresata_numero->value() );
        query.bindValue(":brosfreseuro", ui->doubleSpinBox_foglio4_brosurafresata_euro->value() );
        query.bindValue(":brosfresavv", ui->doubleSpinBox_foglio4_brosurafresata_avviamento->value() );
        query.bindValue(":brosfiloncopie", ui->spinBox_foglio4_filo_numero->value() );
        query.bindValue(":brosfiloeuro", ui->doubleSpinBox_foglio4_filo_euro->value() );
        query.bindValue(":brosfiloavv", ui->doubleSpinBox_foglio4_filo_avviamento->value() );
        query.bindValue(":cartncopie", ui->spinBox_foglio4_cartonato_numero->value() );
        query.bindValue(":carteuro", ui->doubleSpinBox_foglio4_cartonato_euro->value() );
        query.bindValue(":cartavv", ui->doubleSpinBox_foglio4_cartonato_avviamento->value() );
        query.bindValue(":spirncopie", ui->spinBox_foglio4_spiralatura_numero->value() );
        query.bindValue(":spireuro", ui->doubleSpinBox_foglio4_spiralatura_euro->value() );
        query.bindValue(":pacchipolincopie", ui->spinBox_foglio4_pacchi_numero->value() );
        query.bindValue(":pacchipolieuro", ui->doubleSpinBox_foglio4_pacchi_euro->value() );
        query.bindValue(":trasporto", ui->doubleSpinBox_foglio4_trasporto->value() );
        query.bindValue(":riga1", ui->lineEdit_foglio4_prima->text() );
        query.bindValue(":riga2", ui->lineEdit_seconda->text() );
        query.bindValue(":riga3", ui->lineEdit_foglio4_terza->text() );
        query.bindValue(":riga4", ui->lineEdit_foglio4_quarta->text() );
        query.bindValue(":riga5", ui->lineEdit_foglio4_quinta->text() );
        query.bindValue(":riga1prime", ui->doubleSpinBox_foglio4_prima_primencopie->value() );
        query.bindValue(":riga2prime", ui->doubleSpinBox_foglio4_seconda_primencopie->value() );
        query.bindValue(":riga3prime", ui->doubleSpinBox_foglio4_terza_primencopie->value() );
        query.bindValue(":riga4prime", ui->doubleSpinBox_foglio4_quarta_primencopie->value() );
        query.bindValue(":riga5prime", ui->doubleSpinBox_foglio4_quinta_primencopie->value() );
        query.bindValue(":riga1succ", ui->doubleSpinBox_foglio4_prima_successivencopie->value() );
        query.bindValue(":riga2succ", ui->doubleSpinBox_foglio4_seconda_successivencopie->value() );
        query.bindValue(":riga3succ", ui->doubleSpinBox_foglio4_terza_successivencopie->value() );
        query.bindValue(":riga4succ", ui->doubleSpinBox_foglio4_quarta_successivencopie->value() );
        query.bindValue(":riga5succ", ui->doubleSpinBox_foglio4_quinta_successivencopie->value() );
        query.bindValue(":percf4", ui->doubleSpinBox_foglio4_percentuale->value() );


        qDebug() << query.exec();
        query.clear();
        refreshTabelle();

    /*
DA CANCELLARE QUANDO SARO' CERTO CHE L'ALTRA FUNZIONA BENE
QSqlQuery query;
    qDebug() << query.prepare("INSERT INTO preventivo (numero, cliente, descrizione, ncopie, lastren1, lastren2, lastren3, lastren4, lastren5, lastren6, rismen1, rismen2, rismen3, rismen4, rismen5, rismen6, lastreeuro1, lastreeuro2, lastreeuro3, lastreeuro4, lastreeuro5, lastreeuro6, rismeeuro1, rismeeuro2, rismeeuro3, rismeeuro4, rismeeuro5, rismeeuro6, lastravvprime, lastravvsucc, stampaprime, stampasucc, stampadigprime, stampadigsucc, percf2, tipo1, tipo2, tipo3, tipo4, tipo5, tipo6, tipo7, tipo8, formato1, formato2, formato3, formato4, formato5, euro1, euro2, euro3, euro4, euro5, europrime1, europrime2, europrime3, eurosucc1, eurosucc2, eurosucc3, percf3, plopbformato, plopbnfogli, plopbavv, plopbvformato, plopbvnfogli, plopbvavv, pllubformato, pllubnfogli, pllubavv, pllubvformato, pllubvnfogli, pllubvavv, serformato, sernfogli, seravv, sertelaio, fustella, fustellaturanfogli, fustellaturaeuro, fustellaturaavv, cordonaturaprime, cordonaturasucc, cordonaturaavv, accoppiaturanfogli, accoppiaturaeuro, stampacaldoprime, stampacaldosucc, cliche, piegacopien, piegacopieeuro, tagliocopien, tagliocopieeuro, puntometncopie, puntometeuro, puntometavv, brosfresncopie, brosfreseuro, brosfresavv, brosfiloncopie, brosfiloeuro, brosfiloavv, cartncopie, carteuro, cartavv, spirncopie, spireuro, pacchipolincopie, pacchipolieuro, trasporto, riga1, riga2, riga3, riga4, riga5, riga1prime, riga2prime, riga3prime, riga4prime, riga5prime, riga1succ, riga2succ, riga3succ, riga4succ, riga5succ, percf4)"
                  "VALUES(:numero, :cliente, :descrizione, :ncopie, :lastren1, :lastren2, :lastren3, :lastren4, :lastren5, :lastren6, :rismen1, :rismen2, :rismen3, :rismen4, :rismen5, :rismen6, :lastreeuro1, :lastreeuro2, :lastreeuro3, :lastreeuro4, :lastreeuro5, :lastreeuro6, :rismeeuro1, :rismeeuro2, :rismeeuro3, :rismeeuro4, :rismeeuro5, :rismeeuro6, :lastravvprime, :lastravvsucc, :stampaprime, :stampasucc, :stampadigprime, :stampadigsucc, :percf2, :tipo1, :tipo2, :tipo3, :tipo4, :tipo5, :tipo6, :tipo7, :tipo8, :formato1, :formato2, :formato3, :formato4, :formato5, :euro1, :euro2, :euro3, :euro4, :euro5, :europrime1, :europrime2, :europrime3, :eurosucc1, :eurosucc2, :eurosucc3, :percf3, :plopbformato, :plopbnfogli, :plopbavv, :plopbvformato, :plopbvnfogli, :plopbvavv, :pllubformato, :pllubnfogli, :pllubavv, :pllubvformato, :pllubvnfogli, :pllubvavv, :serformato, :sernfogli, :seravv, :sertelaio, :fustella, :fustellaturanfogli, :fustellaturaeuro, :fustellaturaavv, :cordonaturaprime, :cordonaturasucc, :cordonaturaavv, :accoppiaturanfogli, :accoppiaturaeuro, :stampacaldoprime, :stampacaldosucc, :cliche, :piegacopien, :piegacopieeuro, :tagliocopien, :tagliocopieeuro, :puntometncopie, :puntometeuro, :puntometavv, :brosfresncopie, :brosfreseuro, :brosfresavv, :brosfiloncopie, :brosfiloeuro, :brosfiloavv, :cartncopie, :carteuro, :cartavv, :spirncopie, :spireuro, :pacchipolincopie, :pacchipolieuro, :trasporto, :riga1, :riga2, :riga3, :riga4, :riga5, :riga1prime, :riga2prime, :riga3prime, :riga4prime, :riga5prime, :riga1succ, :riga2succ, :riga3succ, :riga4succ, :riga5succ, :percf4) ");
    query.bindValue(":numero", ui->label_npreventivo->text().toInt() );
    query.bindValue(":cliente", ui->comboBox_clienti_seleziona->currentText() );
    query.bindValue(":descrizione", ui->plainTextEdit_descrizione->toPlainText() );
    query.bindValue(":ncopie", ui->spinBox_foglio1_ncopie->value());
    query.bindValue(":lastren1", ui->spinBox_foglio2_lastre_n_1->value() );
    query.bindValue(":lastren2", ui->spinBox_foglio2_lastre_n_2->value() );
    query.bindValue(":lastren3", ui->spinBox_foglio2_lastre_n_3->value() );
    query.bindValue(":lastren4", ui->spinBox_foglio2_lastre_n_4->value() );
    query.bindValue(":lastren5", ui->spinBox_foglio2_lastre_n_5->value() );
    query.bindValue(":lastren6", ui->spinBox_foglio2_lastre_n_6->value() );
    query.bindValue(":rismen1", ui->spinBox_foglio2_risme_n_1->value() );
    query.bindValue(":rismen2", ui->spinBox_foglio2_risme_n_2->value() );
    query.bindValue(":rismen3", ui->spinBox_foglio2_risme_n_3->value() );
    query.bindValue(":rismen4", ui->spinBox_foglio2_risme_n_4->value() );
    query.bindValue(":rismen5", ui->spinBox_foglio2_risme_n_5->value() );
    query.bindValue(":rismen6", ui->spinBox_foglio2_risme_n_6->value() );
    query.bindValue(":lastreeuro1", ui->doubleSpinBox_foglio2_lastre_prezzo_1->value() );
    query.bindValue(":lastreeuro2", ui->doubleSpinBox_foglio2_lastre_prezzo_2->value() );
    query.bindValue(":lastreeuro3", ui->doubleSpinBox_foglio2_lastre_prezzo_3->value() );
    query.bindValue(":lastreeuro4", ui->doubleSpinBox_foglio2_lastre_prezzo_4->value() );
    query.bindValue(":lastreeuro5", ui->doubleSpinBox_foglio2_lastre_prezzo_5->value() );
    query.bindValue(":lastreeuro6", ui->doubleSpinBox_foglio2_lastre_prezzo_6->value() );
    query.bindValue(":rismeeuro1", ui->doubleSpinBox_foglio2_risme_prezzo_1->value() );
    query.bindValue(":rismeeuro2", ui->doubleSpinBox_foglio2_risme_prezzo_2->value() );
    query.bindValue(":rismeeuro3", ui->doubleSpinBox_foglio2_risme_prezzo_3->value() );
    query.bindValue(":rismeeuro4", ui->doubleSpinBox_foglio2_risme_prezzo_4->value() );
    query.bindValue(":rismeeuro5", ui->doubleSpinBox_foglio2_risme_prezzo_5->value() );
    query.bindValue(":rismeeuro6", ui->doubleSpinBox_foglio2_risme_prezzo_6->value() );
    query.bindValue(":lastravvprime", ui->doubleSpinBox_foglio2_lastreavviamenti_prime->value() );
    query.bindValue(":lastravvsucc", ui->doubleSpinBox_foglio2_lastreavviamenti_successive->value() );
    query.bindValue(":stampaprime", ui->doubleSpinBox_foglio2_stampa_prime->value() );
    query.bindValue(":stampasucc", ui->doubleSpinBox_foglio2_stampa_successive->value() );
    query.bindValue(":stampadigprime", ui->doubleSpinBox_foglio2_stampadigitale_prime->value() );
    query.bindValue(":stampadigsucc", ui->doubleSpinBox_foglio2_stampadigitale_successive->value() );
    query.bindValue(":percf2", ui->doubleSpinBox_foglio2_percentuale->value() );
    query.bindValue(":tipo1", ui->comboBox_foglio3_carta_tipo_1->currentText() );
    query.bindValue(":tipo2", ui->comboBox_foglio3_carta_tipo_2->currentText() );
    query.bindValue(":tipo3", ui->comboBox_foglio3_carta_tipo_3->currentText() );
    query.bindValue(":tipo4", ui->comboBox_foglio3_carta_tipo_4->currentText() );
    query.bindValue(":tipo5", ui->comboBox_foglio3_carta_tipo_5->currentText() );
    query.bindValue(":tipo6", ui->lineEdit_foglio3_tipocarta_1->text() );
    query.bindValue(":tipo7", ui->lineEdit_foglio3_tipocarta_2->text() );
    query.bindValue(":tipo8", ui->lineEdit_foglio3_tipocarta_3->text() );
    query.bindValue(":formato1", ui->comboBox_foglio3_carta_formato_1->currentText() );
    query.bindValue(":formato2", ui->comboBox_foglio3_carta_formato_2->currentText() );
    query.bindValue(":formato3", ui->comboBox_foglio3_carta_formato_3->currentText() );
    query.bindValue(":formato4", ui->comboBox_foglio3_carta_formato_4->currentText() );
    query.bindValue(":formato5", ui->comboBox_foglio3_carta_formato_5->currentText() );
    query.bindValue(":euro1", ui->comboBox_foglio3_carta_grammatura_1->currentText().toDouble() );
    query.bindValue(":euro2", ui->comboBox_foglio3_carta_grammatura_2->currentText().toDouble() );
    query.bindValue(":euro3", ui->comboBox_foglio3_carta_grammatura_3->currentText().toDouble() );
    query.bindValue(":euro4", ui->comboBox_foglio3_carta_grammatura_4->currentText().toDouble() );
    query.bindValue(":euro5", ui->comboBox_foglio3_carta_grammatura_5->currentText().toDouble() );
    query.bindValue(":europrime1", ui->doubleSpinBox_foglio3_primencopie_1->value() );
    query.bindValue(":europrime2", ui->doubleSpinBox_foglio3_primencopie_2->value() );
    query.bindValue(":europrime3", ui->doubleSpinBox_foglio3_primencopie_3->value() );
    query.bindValue(":eurosucc1", ui->doubleSpinBox_foglio3_successivencopie_1->value() );
    query.bindValue(":eurosucc2", ui->doubleSpinBox_foglio3_successivencopie_2->value() );
    query.bindValue(":eurosucc3", ui->doubleSpinBox_foglio3_successivencopie_3->value() );
    query.bindValue(":percf3", ui->doubleSpinBox_foglio3_percentuale->value() );
    query.bindValue(":plopbformato", ui->comboBox_foglio4_plastificazione_opaca_bianca->currentText() );
    query.bindValue(":plopbnfogli", ui->spinBox_foglio4_plastificazione_opaca_bianca->value() );
    query.bindValue(":plopbavv", ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_avviamento->value() );
    query.bindValue(":plopbvformato", ui->comboBox_foglio4_plastificazione_opaca_bianca_volta->currentText() );
    query.bindValue(":plopbvnfogli", ui->spinBox_foglio4_plastificazione_opaca_bianca_volta->value() );
    query.bindValue(":plopbvavv", ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_volta_avviamento->value() );
    query.bindValue(":pllubformato", ui->comboBox_foglio4_plastificazione_lucida_bianca->currentText() );
    query.bindValue(":pllubnfogli", ui->spinBox_foglio4_plastificazione_lucida_bianca->value() );
    query.bindValue(":pllubavv", ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_avviamento->value() );
    query.bindValue(":pllubvformato", ui->comboBox_foglio4_plastificazione_lucida_bianca_volta->currentText() );
    query.bindValue(":pllubvnfogli", ui->spinBox_foglio4_plastificazione_lucida_bianca_volta->value() );
    query.bindValue(":pllubvavv", ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_volta_avviamento->value() );
    query.bindValue(":serformato", ui->comboBox_foglio4_serigrafia->currentText() );
    query.bindValue(":sernfogli", ui->spinBox_foglio4_serigrafia->value() );
    query.bindValue(":seravv", ui->doubleSpinBox_foglio4_serigrafia_avviamento->value() );
    query.bindValue(":sertelaio", ui->doubleSpinBox_foglio4_serigrafia_telaio->value() );
    query.bindValue(":fustella", ui->doubleSpinBox_fustella_primencopie->value() );
    query.bindValue(":fustellaturanfogli", ui->spinBox_foglio4_fustellatura_nfogli->value() );
    query.bindValue(":fustellaturaeuro", ui->doubleSpinBox_spinBox_foglio4_fustellatura_euro->value() );
    query.bindValue(":fustellaturaavv", ui->doubleSpinBox_label_spinBox_foglio4_fustellatura_avviamento->value() );
    query.bindValue(":cordonaturaprime", ui->doubleSpinBox_cordonatura_primencopie->value() );
    query.bindValue(":cordonaturasucc", ui->doubleSpinBox_cordonatura_successivencopie->value() );
    query.bindValue(":cordonaturaavv", ui->doubleSpinBox_cordonatura_avviamento->value() );
    query.bindValue(":accoppiaturanfogli", ui->spinBox_foglio4_accoppiatura_fogli->value() );
    query.bindValue(":accoppiaturaeuro", ui->doubleSpinBox_foglio4_accoppiatura_euro->value() );
    query.bindValue(":stampacaldoprime", ui->doubleSpinBox_foglio4_stampaacaldo_primencopie->value() );
    query.bindValue(":stampacaldosucc", ui->doubleSpinBox_foglio4_stampaacaldo_successivencopie->value() );
    query.bindValue(":cliche", ui->doubleSpinBox_foglio4_cliche_primencopie->value() );
    query.bindValue(":piegacopien", ui->spinBox_foglio4_piegacopie_numero->value() );
    query.bindValue(":piegacopieeuro", ui->doubleSpinBox_foglio4_piegacopie_euro->value() );
    query.bindValue(":tagliocopien", ui->spinBox_foglio4_tagliocopie_numero->value() );
    query.bindValue(":tagliocopieeuro", ui->doubleSpinBox_foglio4_tagliocopie_euro->value() );
    query.bindValue(":puntometncopie", ui->spinBox_foglio4_puntometallico_numero->value() );
    query.bindValue(":puntometeuro", ui->doubleSpinBox_foglio4_puntometallico_euro->value() );
    query.bindValue(":puntometavv", ui->doubleSpinBox_foglio4_puntometallico_avviamento->value() );
    query.bindValue(":brosfresncopie", ui->spinBox_foglio4_brosurafresata_numero->value() );
    query.bindValue(":brosfreseuro", ui->doubleSpinBox_foglio4_brosurafresata_euro->value() );
    query.bindValue(":brosfresavv", ui->doubleSpinBox_foglio4_brosurafresata_avviamento->value() );
    query.bindValue(":brosfiloncopie", ui->spinBox_foglio4_filo_numero->value() );
    query.bindValue(":brosfiloeuro", ui->doubleSpinBox_foglio4_filo_euro->value() );
    query.bindValue(":brosfiloavv", ui->doubleSpinBox_foglio4_filo_avviamento->value() );
    query.bindValue(":cartncopie", ui->spinBox_foglio4_cartonato_numero->value() );
    query.bindValue(":carteuro", ui->doubleSpinBox_foglio4_cartonato_euro->value() );
    query.bindValue(":cartavv", ui->doubleSpinBox_foglio4_cartonato_avviamento->value() );
    query.bindValue(":spirncopie", ui->spinBox_foglio4_spiralatura_numero->value() );
    query.bindValue(":spireuro", ui->doubleSpinBox_foglio4_spiralatura_euro->value() );
    query.bindValue(":pacchipolincopie", ui->spinBox_foglio4_pacchi_numero->value() );
    query.bindValue(":pacchipolieuro", ui->doubleSpinBox_foglio4_pacchi_euro->value() );
    query.bindValue(":trasporto", ui->doubleSpinBox_foglio4_trasporto->value() );
    query.bindValue(":riga1", ui->lineEdit_foglio4_prima->text() );
    query.bindValue(":riga2", ui->lineEdit_seconda->text() );
    query.bindValue(":riga3", ui->lineEdit_foglio4_terza->text() );
    query.bindValue(":riga4", ui->lineEdit_foglio4_quarta->text() );
    query.bindValue(":riga5", ui->lineEdit_foglio4_quinta->text() );
    query.bindValue(":riga1prime", ui->doubleSpinBox_foglio4_prima_primencopie->value() );
    query.bindValue(":riga2prime", ui->doubleSpinBox_foglio4_seconda_primencopie->value() );
    query.bindValue(":riga3prime", ui->doubleSpinBox_foglio4_terza_primencopie->value() );
    query.bindValue(":riga4prime", ui->doubleSpinBox_foglio4_quarta_primencopie->value() );
    query.bindValue(":riga5prime", ui->doubleSpinBox_foglio4_quinta_primencopie->value() );
    query.bindValue(":riga1succ", ui->doubleSpinBox_foglio4_prima_successivencopie->value() );
    query.bindValue(":riga2succ", ui->doubleSpinBox_foglio4_seconda_successivencopie->value() );
    query.bindValue(":riga3succ", ui->doubleSpinBox_foglio4_terza_successivencopie->value() );
    query.bindValue(":riga4succ", ui->doubleSpinBox_foglio4_quarta_successivencopie->value() );
    query.bindValue(":riga5succ", ui->doubleSpinBox_foglio4_quinta_successivencopie->value() );
    query.bindValue(":percf4", ui->doubleSpinBox_foglio4_percentuale->value() );
    qDebug() << query.exec();
    query.clear();
    refreshTabelle();*/
}

void MainWindow::razionalizzaTabella(QString tabella, QString colonna, int nmancante)
{
    QSqlQuery query;
    QString stringa_query;
    QString str_numero;
    QString str_numero2;
    str_numero.setNum(nmancante);
    str_numero2.setNum(nmancante+1);

    int numtotale(0);
    //stringa_query = "SELECT rowid FROM "+tabella;
    stringa_query = "SELECT ";
    stringa_query.append(colonna);
    stringa_query.append(" FROM ");
    stringa_query.append(tabella);
    qDebug() << query.prepare(stringa_query);
    qDebug() << query.exec();

    while ( query.next())
    {
        numtotale++;
    }

    stringa_query.clear();
    query.clear();

    for ( ; str_numero.toInt() < numtotale; str_numero.setNum( str_numero.toInt()+1 ) )
     {
        str_numero2.setNum(str_numero.toInt()+1);
        //stringa_query= "UPDATE "+tabella+" SET rowid='"+str_numero+"'WHERE rowid='"+str_numero2+"'";
        stringa_query= "UPDATE "+tabella+" SET "+colonna+"='"+str_numero+"'WHERE "+colonna+"='"+str_numero2+"'";
        qDebug() << query.prepare(stringa_query);
        qDebug() << query.exec();
     }


}

void MainWindow::eliminaRiga(QString tabella, int numero)
{
    QSqlQuery query;
    QString stringa_query;
    QString str_numero;
    str_numero.setNum(numero);

    stringa_query = "DELETE FROM "+tabella+" WHERE rowid="+str_numero;
    qDebug() << query.prepare(stringa_query);
    qDebug() << query.exec();
    stringa_query.clear();
    query.clear();


}

void MainWindow::eliminaRiga(QString tabella, QString colonna, QString valore)
{

    QSqlQuery query;
    QString stringa_query;
    stringa_query = "DELETE FROM "+tabella+" WHERE "+colonna+"='"+valore+"'";
    qDebug() << query.prepare(stringa_query);
    qDebug() << query.exec();
    stringa_query.clear();
    query.clear();
}




// FUNZIONI PER I CALCOLI ( forse per tutta sta roba sarebbe utile un'altra classe..

//foglio 2

void MainWindow::refreshFoglio2()
{

    /*
Questa funzione fa svolgere ogni volta un sacco di calcoli inutili ma garantisce la certezza
che l'interfaccia sia sempre tutta aggiornata
*/

    ui->label_foglio2_lastre_prime_1->setNum( ui->spinBox_foglio2_lastre_n_1->value() * ui->doubleSpinBox_foglio2_lastre_prezzo_1->value());
    ui->label_foglio2_lastre_prime_2->setNum( ui->spinBox_foglio2_lastre_n_2->value() * ui->doubleSpinBox_foglio2_lastre_prezzo_2->value());
    ui->label_foglio2_lastre_prime_3->setNum( ui->spinBox_foglio2_lastre_n_3->value() * ui->doubleSpinBox_foglio2_lastre_prezzo_3->value());
    ui->label_foglio2_lastre_prime_4->setNum( ui->spinBox_foglio2_lastre_n_4->value() * ui->doubleSpinBox_foglio2_lastre_prezzo_4->value());
    ui->label_foglio2_lastre_prime_5->setNum( ui->spinBox_foglio2_lastre_n_5->value() * ui->doubleSpinBox_foglio2_lastre_prezzo_5->value());
    ui->label_foglio2_lastre_prime_6->setNum( ui->spinBox_foglio2_lastre_n_6->value() * ui->doubleSpinBox_foglio2_lastre_prezzo_6->value());

    ui->label_foglio2_risme_prime_1->setNum( ui->spinBox_foglio2_risme_n_1->value() * ui->doubleSpinBox_foglio2_risme_prezzo_1->value());
    ui->label_foglio2_risme_prime_2->setNum( ui->spinBox_foglio2_risme_n_2->value() * ui->doubleSpinBox_foglio2_risme_prezzo_2->value());
    ui->label_foglio2_risme_prime_3->setNum( ui->spinBox_foglio2_risme_n_3->value() * ui->doubleSpinBox_foglio2_risme_prezzo_3->value());
    ui->label_foglio2_risme_prime_4->setNum( ui->spinBox_foglio2_risme_n_4->value() * ui->doubleSpinBox_foglio2_risme_prezzo_4->value());
    ui->label_foglio2_risme_prime_5->setNum( ui->spinBox_foglio2_risme_n_5->value() * ui->doubleSpinBox_foglio2_risme_prezzo_5->value());
    ui->label_foglio2_risme_prime_6->setNum( ui->spinBox_foglio2_risme_n_6->value() * ui->doubleSpinBox_foglio2_risme_prezzo_6->value());

   ui->label_foglio2_risme_successive_1->setText(ui->label_foglio2_risme_prime_1->text());
   ui->label_foglio2_risme_successive_2->setText(ui->label_foglio2_risme_prime_2->text());
   ui->label_foglio2_risme_successive_3->setText(ui->label_foglio2_risme_prime_3->text());
   ui->label_foglio2_risme_successive_4->setText(ui->label_foglio2_risme_prime_4->text());
   ui->label_foglio2_risme_successive_5->setText(ui->label_foglio2_risme_prime_5->text());
   ui->label_foglio2_risme_successive_6->setText(ui->label_foglio2_risme_prime_6->text());

   ui->label_foglio2_pretotale_prime->setNum(  ui->label_foglio2_lastre_prime_1->text().toDouble()
                                             + ui->label_foglio2_lastre_prime_2->text().toDouble()
                                             + ui->label_foglio2_lastre_prime_3->text().toDouble()
                                             + ui->label_foglio2_lastre_prime_4->text().toDouble()
                                             + ui->label_foglio2_lastre_prime_5->text().toDouble()
                                             + ui->label_foglio2_lastre_prime_6->text().toDouble()
                                             + ui->label_foglio2_risme_prime_1->text().toDouble()
                                             + ui->label_foglio2_risme_prime_2->text().toDouble()
                                             + ui->label_foglio2_risme_prime_3->text().toDouble()
                                             + ui->label_foglio2_risme_prime_4->text().toDouble()
                                             + ui->label_foglio2_risme_prime_5->text().toDouble()
                                             + ui->label_foglio2_risme_prime_6->text().toDouble()
                                             + ui->doubleSpinBox_foglio2_lastreavviamenti_prime->value()
                                             + ui->doubleSpinBox_foglio2_stampadigitale_prime->value()
                                             + ui->doubleSpinBox_foglio2_stampa_prime->value()
                                             );


   ui->label_foglio2_pretotale_successive->setNum(  ui->label_foglio2_risme_successive_1->text().toDouble()
                                                  + ui->label_foglio2_risme_successive_2->text().toDouble()
                                                  + ui->label_foglio2_risme_successive_3->text().toDouble()
                                                  + ui->label_foglio2_risme_successive_4->text().toDouble()
                                                  + ui->label_foglio2_risme_successive_5->text().toDouble()
                                                  + ui->label_foglio2_risme_successive_6->text().toDouble()
                                                  + ui->doubleSpinBox_foglio2_lastreavviamenti_successive->value()
                                                  + ui->doubleSpinBox_foglio2_stampadigitale_successive->value()
                                                  + ui->doubleSpinBox_foglio2_stampa_successive->value()
                                                  );

   ui->label_foglio2_totale_prime->setNum(ui->label_foglio2_pretotale_prime->text().toDouble() + (ui->label_foglio2_pretotale_prime->text().toDouble()/100 * ui->doubleSpinBox_foglio2_percentuale->value()));
   ui->label_foglio2_totale_successive->setNum(ui->label_foglio2_pretotale_successive->text().toDouble() + (ui->label_foglio2_pretotale_successive->text().toDouble()/100 * ui->doubleSpinBox_foglio2_percentuale->value()));

}

void MainWindow::refreshFoglio3()
{
    //calcolo kg

    ui->label_foglio3_kg_1->setNum(((formatoASuperficie( ui->comboBox_foglio3_carta_formato_1->currentText() )) * ui->comboBox_foglio3_carta_grammatura_1->currentText().toDouble() /1000) );
    ui->label_foglio3_kg_2->setNum(((formatoASuperficie( ui->comboBox_foglio3_carta_formato_2->currentText() )) * ui->comboBox_foglio3_carta_grammatura_2->currentText().toDouble() /1000) );
    ui->label_foglio3_kg_3->setNum(((formatoASuperficie( ui->comboBox_foglio3_carta_formato_3->currentText() )) * ui->comboBox_foglio3_carta_grammatura_3->currentText().toDouble() /1000) );
    ui->label_foglio3_kg_4->setNum(((formatoASuperficie( ui->comboBox_foglio3_carta_formato_4->currentText() )) * ui->comboBox_foglio3_carta_grammatura_4->currentText().toDouble() /1000) );
    ui->label_foglio3_kg_5->setNum(((formatoASuperficie( ui->comboBox_foglio3_carta_formato_5->currentText() )) * ui->comboBox_foglio3_carta_grammatura_5->currentText().toDouble() /1000) );

    //aggiungere qui tutti gli altri calcoli

    //prime
    ui->label_foglio3_primencopie_1->setNum( ui->spinBox_foglio3_nfogli_1->value() * ui->label_foglio3_kg_1->text().toDouble() * ui->doubleSpinBox_foglio3_euro_1->value() );
    ui->label_foglio3_primencopie_2->setNum( ui->spinBox_foglio3_nfogli_2->value() * ui->label_foglio3_kg_2->text().toDouble() * ui->doubleSpinBox_foglio3_euro_2->value() );
    ui->label_foglio3_primencopie_3->setNum( ui->spinBox_foglio3_nfogli_3->value() * ui->label_foglio3_kg_3->text().toDouble() * ui->doubleSpinBox_foglio3_euro_3->value() );
    ui->label_foglio3_primencopie_4->setNum( ui->spinBox_foglio3_nfogli_4->value() * ui->label_foglio3_kg_4->text().toDouble() * ui->doubleSpinBox_foglio3_euro_4->value() );
    ui->label_foglio3_primencopie_5->setNum( ui->spinBox_foglio3_nfogli_5->value() * ui->label_foglio3_kg_5->text().toDouble() * ui->doubleSpinBox_foglio3_euro_5->value() );

    //successive
    ui->label_foglio3_successivencopie_1->setText( ui->label_foglio3_primencopie_1->text() );
    ui->label_foglio3_successivencopie_2->setText( ui->label_foglio3_primencopie_2->text() );
    ui->label_foglio3_successivencopie_3->setText( ui->label_foglio3_primencopie_3->text() );
    ui->label_foglio3_successivencopie_4->setText( ui->label_foglio3_primencopie_4->text() );
    ui->label_foglio3_successivencopie_5->setText( ui->label_foglio3_primencopie_5->text() );


    //pretotale prime
    ui->label_foglio3_pretotale_primencopie->setNum( ui->label_foglio3_primencopie_1->text().toDouble()
                                                     + ui->label_foglio3_primencopie_2->text().toDouble()
                                                     + ui->label_foglio3_primencopie_3->text().toDouble()
                                                     + ui->label_foglio3_primencopie_4->text().toDouble()
                                                     + ui->label_foglio3_primencopie_5->text().toDouble()
                                                     + ui->doubleSpinBox_foglio3_primencopie_1->value()
                                                     + ui->doubleSpinBox_foglio3_primencopie_2->value()
                                                     + ui->doubleSpinBox_foglio3_primencopie_3->value());

    ui->label_foglio3_pretotale_successivencopie->setNum( ui->label_foglio3_successivencopie_1->text().toDouble()
                                                     + ui->label_foglio3_successivencopie_2->text().toDouble()
                                                     + ui->label_foglio3_successivencopie_3->text().toDouble()
                                                     + ui->label_foglio3_successivencopie_4->text().toDouble()
                                                     + ui->label_foglio3_successivencopie_5->text().toDouble()
                                                     + ui->doubleSpinBox_foglio3_successivencopie_1->value()
                                                     + ui->doubleSpinBox_foglio3_successivencopie_2->value()
                                                     + ui->doubleSpinBox_foglio3_successivencopie_3->value());

    ui->label_foglio3_totale_primencopie->setNum(ui->label_foglio3_pretotale_primencopie->text().toDouble() + (ui->label_foglio3_pretotale_primencopie->text().toDouble()/100 * ui->doubleSpinBox_foglio3_percentuale->value()));
    ui->label_foglio3_totale_successivencopie->setNum(ui->label_foglio3_pretotale_successivencopie->text().toDouble() + (ui->label_foglio3_pretotale_successivencopie->text().toDouble()/100 * ui->doubleSpinBox_foglio3_percentuale->value()));




}


void MainWindow::refreshFoglio4()
{

    QSqlQuery query;

    //plastificazione

    //prime
    query = "SELECT opacabianca FROM plastificazione WHERE formato = '"+ui->comboBox_foglio4_plastificazione_opaca_bianca->currentText()+"'";
    query.exec();
    query.next();
    ui->label_foglio4_plastificazione_opaca_bianca_primencopie->setNum( query.value(0).toString().toDouble() * ui->spinBox_foglio4_plastificazione_opaca_bianca->value() );
    query.clear();

    query = "SELECT opacabiancavolta FROM plastificazione WHERE formato = '"+ui->comboBox_foglio4_plastificazione_opaca_bianca_volta->currentText()+"'";
    query.exec();
    query.next();
    ui->label_foglio4_plastificazione_opaca_bianca_volta_primencopie->setNum( query.value(0).toString().toDouble() * ui->spinBox_foglio4_plastificazione_opaca_bianca_volta->value() );
    query.clear();

    query = "SELECT lucidabianca FROM plastificazione WHERE formato = '"+ui->comboBox_foglio4_plastificazione_lucida_bianca->currentText()+"'";
    query.exec();
    query.next();
    ui->label_foglio4_plastificazione_lucida_bianca_primencopie->setNum( query.value(0).toString().toDouble() * ui->spinBox_foglio4_plastificazione_lucida_bianca->value() );
    query.clear();

    query = "SELECT lucidabiancavolta FROM plastificazione WHERE formato = '"+ui->comboBox_foglio4_plastificazione_lucida_bianca_volta->currentText()+"'";
    query.exec();
    query.next();
    ui->label_foglio4_plastificazione_lucida_bianca_volta_primencopie->setNum( query.value(0).toString().toDouble() * ui->spinBox_foglio4_plastificazione_lucida_bianca_volta->value() );
    query.clear();

    //successive
    ui->label_foglio4_plastificazione_opaca_bianca_volta_successivencopie->setText(ui->label_foglio4_plastificazione_opaca_bianca_volta_primencopie->text());
    ui->label_foglio4_plastificazione_opaca_bianca_successivencopie->setText(ui->label_foglio4_plastificazione_opaca_bianca_primencopie->text());
    ui->label_foglio4_plastificazione_lucida_bianca_volta_successivencopie->setText(ui->label_foglio4_plastificazione_lucida_bianca_volta_primencopie->text());
    ui->label_foglio4_plastificazione_lucida_bianca_successivencopie->setText(ui->label_foglio4_plastificazione_lucida_bianca_primencopie->text());

    //serigrafia
    query = "SELECT prezzo FROM serigrafia WHERE formato = '"+ui->comboBox_foglio4_serigrafia->currentText()+"'";
    query.exec();
    query.next();
    ui->label_foglio4_serigrafia_primencopie->setNum( query.value(0).toString().toDouble() * ui->spinBox_foglio4_serigrafia->value() );
    query.clear();

    ui->label_foglio4_serigrafia_successivencopie->setText(ui->label_foglio4_serigrafia_primencopie->text());


    ui->label_spinBox_foglio4_fustellatura_primencopie->setNum( ui->spinBox_foglio4_fustellatura_nfogli->value() * ui->doubleSpinBox_spinBox_foglio4_fustellatura_euro->value() );
    ui->label_spinBox_foglio4_fustellatura_successivencopie->setText(ui->label_spinBox_foglio4_fustellatura_primencopie->text());


    ui->label_foglio4_piegacopie_primencopie->setNum( ui->spinBox_foglio4_piegacopie_numero->value() * ui->doubleSpinBox_foglio4_piegacopie_euro->value());
    ui->label_foglio4_piegacopie_successivencopie->setText(  ui->label_foglio4_piegacopie_primencopie->text() );


    ui->label_foglio4_tagliocopie_primencopie->setNum( ui->spinBox_foglio4_tagliocopie_numero->value() * ui->doubleSpinBox_foglio4_tagliocopie_euro->value() );
    ui->label_foglio4_tagliocopie_successivencopie->setText(ui->label_foglio4_tagliocopie_primencopie->text());

    ui->label_foglio4_puntometallico_primencopie->setNum( ui->spinBox_foglio4_puntometallico_numero->value() * ui->doubleSpinBox_foglio4_puntometallico_euro->value());

    ui->label_foglio4_brosurafresata_primencopie->setNum( ui->spinBox_foglio4_brosurafresata_numero->value() * ui->doubleSpinBox_foglio4_brosurafresata_euro->value());
    ui->label_foglio4_brosurafresata_successivencopie->setText( ui->label_foglio4_brosurafresata_primencopie->text() );

    ui->label_foglio4_filo_primencopie->setNum( ui->spinBox_foglio4_filo_numero->value() * ui->doubleSpinBox_foglio4_filo_euro->value());
    ui->label_foglio4_filo_successivencopie->setText( ui->label_foglio4_filo_primencopie->text());

    ui->label_foglio4_cartonato_primencopie->setNum( ui->spinBox_foglio4_cartonato_numero->value() * ui->doubleSpinBox_foglio4_cartonato_euro->value());
    ui->label_foglio4_cartonato_successivencopie->setText(ui->label_foglio4_cartonato_primencopie->text());

    ui->label_foglio4_spiralatura_primencopie->setNum( ui->spinBox_foglio4_spiralatura_numero->value() * ui->doubleSpinBox_foglio4_spiralatura_euro->value());
    ui->label_foglio4_spiralatura_successivencopie->setText(ui->label_foglio4_spiralatura_primencopie->text());

    ui->label_foglio4_pacchi_primencopie->setNum( ui->spinBox_foglio4_pacchi_numero->value() * ui->doubleSpinBox_foglio4_pacchi_euro->value());
    ui->label_foglio4_pacchi_successivencopie->setText(ui->label_foglio4_pacchi_primencopie->text());

    ui->label_foglio4_pretotale_primencopie->setNum( ui->label_foglio4_plastificazione_opaca_bianca_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_avviamento->value()
                                                     + ui->label_foglio4_plastificazione_opaca_bianca_volta_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_plastificazione_opaca_bianca_volta_avviamento->value()
                                                     + ui->label_foglio4_plastificazione_lucida_bianca_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_avviamento->value()
                                                     + ui->label_foglio4_plastificazione_lucida_bianca_volta_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_plastificazione_lucida_bianca_volta_avviamento->value()
                                                     + ui->label_foglio4_serigrafia_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_serigrafia_avviamento->value()
                                                     + ui->doubleSpinBox_foglio4_serigrafia_telaio->value()
                                                     + ui->doubleSpinBox_fustella_primencopie->value()
                                                     + ui->label_spinBox_foglio4_fustellatura_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_label_spinBox_foglio4_fustellatura_avviamento->value()
                                                     + ui->doubleSpinBox_cordonatura_primencopie->value()
                                                     + ui->doubleSpinBox_cordonatura_avviamento->value()
                                                     + ui->doubleSpinBox_foglio4_accoppiatura_prime->value()
                                                     + ui->doubleSpinBox_foglio4_stampaacaldo_primencopie->value()
                                                     + ui->doubleSpinBox_foglio4_cliche_primencopie->value()
                                                     + ui->label_foglio4_piegacopie_primencopie->text().toDouble()
                                                     + ui->label_foglio4_tagliocopie_primencopie->text().toDouble()
                                                     + ui->label_foglio4_puntometallico_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_puntometallico_avviamento->value()
                                                     + ui->label_foglio4_brosurafresata_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_brosurafresata_avviamento->value()
                                                     + ui->label_foglio4_filo_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_filo_avviamento->value()
                                                     + ui->label_foglio4_cartonato_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_cartonato_avviamento->value()
                                                     + ui->label_foglio4_spiralatura_primencopie->text().toDouble()
                                                     + ui->label_foglio4_pacchi_primencopie->text().toDouble()
                                                     + ui->doubleSpinBox_foglio4_trasporto->value()
                                                     + ui->doubleSpinBox_foglio4_prima_primencopie->value()
                                                     + ui->doubleSpinBox_foglio4_seconda_primencopie->value()
                                                     + ui->doubleSpinBox_foglio4_terza_primencopie->value()
                                                     + ui->doubleSpinBox_foglio4_quarta_primencopie->value()
                                                     + ui->doubleSpinBox_foglio4_quinta_primencopie->value());


    ui->label_foglio4_pretotale_successivencopie->setNum( ui->label_foglio4_plastificazione_opaca_bianca_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_plastificazione_opaca_bianca_volta_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_plastificazione_lucida_bianca_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_plastificazione_lucida_bianca_volta_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_serigrafia_successivencopie->text().toDouble()
                                                          + ui->label_spinBox_foglio4_fustellatura_successivencopie->text().toDouble()
                                                          + ui->doubleSpinBox_cordonatura_successivencopie->value()
                                                          + ui->doubleSpinBox_foglio4_accoppiatura_succ->value()
                                                          + ui->doubleSpinBox_foglio4_stampaacaldo_successivencopie->value()
                                                          + ui->label_foglio4_piegacopie_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_tagliocopie_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_brosurafresata_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_filo_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_cartonato_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_spiralatura_successivencopie->text().toDouble()
                                                          + ui->label_foglio4_pacchi_successivencopie->text().toDouble()
                                                          + ui->doubleSpinBox_foglio4_prima_successivencopie->value()
                                                          + ui->doubleSpinBox_foglio4_seconda_successivencopie->value()
                                                          + ui->doubleSpinBox_foglio4_terza_successivencopie->value()
                                                          + ui->doubleSpinBox_foglio4_quarta_successivencopie->value()
                                                          + ui->doubleSpinBox_foglio4_quinta_successivencopie->value());

    ui->label_foglio4_totale_primencopie->setNum(ui->label_foglio4_pretotale_primencopie->text().toDouble() + (ui->label_foglio4_pretotale_primencopie->text().toDouble()/100 * ui->doubleSpinBox_foglio4_percentuale->value()));
    ui->label_foglio4_totale_successivencopie->setNum(ui->label_foglio4_pretotale_successivencopie->text().toDouble() + (ui->label_foglio4_pretotale_successivencopie->text().toDouble()/100 * ui->doubleSpinBox_foglio4_percentuale->value()));


}

void MainWindow::refreshFoglio5()
{
   ui->label_foglio5_stampa_primencopie->setText( ui->label_foglio2_totale_prime->text() );
   ui->label_foglio5_stampa_successivencopie->setText(ui->label_foglio2_totale_successive->text() );

   ui->label_foglio5_carta_primencopie->setNum( ui->label_foglio3_totale_primencopie->text().toDouble() * ui->spinBox_foglio1_ncopie->value());
   ui->label_foglio5_carta_successivencopie->setNum( ui->label_foglio3_totale_successivencopie->text().toDouble() * ui->spinBox_foglio1_ncopie->value());

   ui->label_foglio5_lavorazioni_primencopie->setText( ui->label_foglio4_totale_primencopie->text());
   ui->label_foglio5_lavorazioni_successivencopie->setText(ui->label_foglio4_totale_successivencopie->text());

   ui->label_foglio5_prezzoacopia_primencopie->setNum( (ui->label_foglio5_stampa_primencopie->text().toDouble()
                                                        + ui->label_foglio5_carta_primencopie->text().toDouble()
                                                        + ui->label_foglio5_lavorazioni_primencopie->text().toDouble())
                                                       / (ui->spinBox_foglio1_ncopie->value())
                                                       );

   ui->label_foglio5_prezzoacopia_successivencopie->setNum( (ui->label_foglio5_stampa_successivencopie->text().toDouble()
                                                        + ui->label_foglio5_carta_successivencopie->text().toDouble()
                                                        + ui->label_foglio5_lavorazioni_successivencopie->text().toDouble())
                                                       / (ui->spinBox_foglio1_ncopie->value())
                                                       );


/* IN CASO CHE VOGLIA I COSTI SOLO MODIFICANDO IL NUMERO DI COPIE
ui->label_foglio5_prime_500->setNum(ui->label_foglio5_prezzoacopia_primencopie->text().toDouble()*ui->spinBox_foglio5_500->value());
ui->label_foglio5_prime_1000->setNum(ui->label_foglio5_prezzoacopia_primencopie->text().toDouble()*ui->spinBox_foglio5_1000->value());
ui->label_foglio5_prime_1500->setNum(ui->label_foglio5_prezzoacopia_primencopie->text().toDouble()*ui->spinBox_foglio5_1500->value());
ui->label_foglio5_prime_2000->setNum(ui->label_foglio5_prezzoacopia_primencopie->text().toDouble()*ui->spinBox_foglio5_2000->value());
ui->label_foglio5_prime_2500->setNum(ui->label_foglio5_prezzoacopia_primencopie->text().toDouble()*ui->spinBox_foglio5_2500->value());
ui->label_foglio5_prime_3000->setNum(ui->label_foglio5_prezzoacopia_primencopie->text().toDouble()*ui->spinBox_foglio5_3000->value());

ui->label_foglio5_succ_500->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble()*ui->spinBox_foglio5_500->value());
ui->label_foglio5_succ_1000->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble()*ui->spinBox_foglio5_1000->value());
ui->label_foglio5_succ_1500->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble()*ui->spinBox_foglio5_1500->value());
ui->label_foglio5_succ_2000->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble()*ui->spinBox_foglio5_2000->value());
ui->label_foglio5_succ_2500->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble()*ui->spinBox_foglio5_2500->value());
ui->label_foglio5_succ_3000->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble()*ui->spinBox_foglio5_3000->value());
*/

   double valore, valore2;
   valore2 = ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble();
   valore = ( ui->label_foglio5_prezzoacopia_primencopie->text().toDouble() - valore2 ) * ui->spinBox_foglio1_ncopie->value();

   ui->label_foglio5_prime_500->setNum((valore/ui->spinBox_foglio5_500->value())+valore2);
   ui->label_foglio5_prime_1000->setNum((valore/ui->spinBox_foglio5_1000->value())+valore2);
   ui->label_foglio5_prime_1500->setNum((valore/ui->spinBox_foglio5_1500->value())+valore2);
   ui->label_foglio5_prime_2000->setNum((valore/ui->spinBox_foglio5_2000->value())+valore2);
   ui->label_foglio5_prime_2500->setNum((valore/ui->spinBox_foglio5_2500->value())+valore2);
   ui->label_foglio5_prime_3000->setNum((valore/ui->spinBox_foglio5_3000->value())+valore2);


   ui->label_foglio5_succ_500->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble());
   ui->label_foglio5_succ_1000->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble());
   ui->label_foglio5_succ_1500->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble());
   ui->label_foglio5_succ_2000->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble());
   ui->label_foglio5_succ_2500->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble());
   ui->label_foglio5_succ_3000->setNum(ui->label_foglio5_prezzoacopia_successivencopie->text().toDouble());




}




void MainWindow::on_bottone_clienti_rimuovi_clicked()
{
    //eliminaRiga("clienti", rigadacancellare+1);
    //razionalizzaTabella("clienti", rigadacancellare+1);
    eliminaRiga("clienti","nome",valoredacancellare);
    refreshTabelle();
}



void MainWindow::on_bottone_preventivi_nuovo_clicked()
{
    QString stringa_query;
    QSqlQuery query;
    //QSqlRecord campo;
    int numtotale(1);


    stringa_query = "SELECT numero FROM npreventivo";
    qDebug() << query.prepare(stringa_query);
    qDebug() << query.exec();

    while ( query.next())
    {
        numtotale++;
    }

    //numtotale = campo.value(0).toInt()+1;



    ui->label_npreventivo->setNum(numtotale);

    if (pulire)
       pulisciPreventivo();

    ui->label_preventiv_cerca->hide();
    ui->bottone_preventivi_nuovo->hide();
    ui->lineEdit_preventivi_cerca->hide();
    ui->bottone_salva_preventivo->show();
    ui->tableView_preventivi->hide();
    ui->bottone_preventivi_elimina->hide();
    ui->bottone_preventivi_modifica->hide();
    ui->bottone_preventivi_usamodello->hide();
    ui->tabWidget_preventivi->setCurrentIndex(0);
    ui->tabWidget_preventivi->show();



    pulire = true;


}

void MainWindow::on_bottone_tab1_aggiungi_clienti_clicked()
{
    this->showHide("clienti");
    this->on_bottone_clienti_aggiungi_clicked();
    ui->bottone_torna_preventivo->show();
}



void MainWindow::on_spinBox_foglio1_ncopie_valueChanged(QString valore)
{
    if (valore=="1") //if necessario in caso che cambia il numero di copie ma poi lo riporta ad 1
    {
        ui->label_foglio2_ncopie->setText("Prima copia          ");
        ui->label_foglio2_successivencopie->setText("Successiva copia");
        ui->label_foglio3_ncopie->setText("Prima copia          ");
        ui->label_foglio3_successivencopie->setText("Successiva copia");
        ui->label_foglio4_ncopie->setText("Prima copia          ");
        ui->label_foglio4_successivencopie->setText("Successiva copia");
        ui->label_foglio5_ncopie->setText("Prima copia          ");
        ui->label_foglio5_successivencopie->setText("Successiva copia");

    } else
    {
    ui->label_foglio2_ncopie->setText("Prime "+valore+" copie          ");
    ui->label_foglio2_successivencopie->setText("Successive "+valore+" copie");
    ui->label_foglio3_ncopie->setText("Prime "+valore+" copie          ");
    ui->label_foglio3_successivencopie->setText("Successive "+valore+" copie");
    ui->label_foglio4_ncopie->setText("Prime "+valore+" copie          ");
    ui->label_foglio4_successivencopie->setText("Successive "+valore+" copie");
    ui->label_foglio5_ncopie->setText("Prime "+valore+" copie          ");
    ui->label_foglio5_successivencopie->setText("Successive "+valore+" copie");
}
}


void MainWindow::on_bottone_torna_preventivo_clicked()
{
    this->on_pushButton_preventivi_clicked();
    this->on_bottone_preventivi_nuovo_clicked();
    ui->comboBox_clienti_seleziona->setCurrentIndex(ui->comboBox_clienti_seleziona->count()-1);
    ui->bottone_torna_preventivo->hide();
}

void MainWindow::on_bottone_benvenuto_clicked()
{

    this->showHide("benvenuto");
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
}

void MainWindow::on_actionPlastificazione_triggered()
{
   this->showHide("plastificazione");
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

//lastre
void MainWindow::on_spinBox_foglio2_lastre_n_1_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_1_valueChanged(double )
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_2_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_2_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_spinBox_foglio2_lastre_n_3_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_3_valueChanged(double )
{
   refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_4_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_4_valueChanged(double )
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_5_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_5_valueChanged(double )
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_6_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_6_valueChanged(double )
{
    refreshFoglio2();
}

//risme
void MainWindow::on_spinBox_foglio2_risme_n_1_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_1_valueChanged(double )
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_2_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_2_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_spinBox_foglio2_risme_n_3_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_3_valueChanged(double )
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_4_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_4_valueChanged(double )
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_5_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_5_valueChanged(double )
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_6_valueChanged(int )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_6_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastreavviamenti_prime_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastreavviamenti_successive_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_stampa_prime_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_stampa_successive_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_stampadigitale_prime_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_stampadigitale_successive_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_percentuale_valueChanged(double )
{
    refreshFoglio2();
}

void MainWindow::on_comboBox_foglio3_carta_formato_1_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_grammatura_1_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_formato_4_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_grammatura_4_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_formato_2_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_grammatura_2_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_formato_3_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_grammatura_3_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_formato_5_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio3_carta_grammatura_5_currentIndexChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_spinBox_foglio3_nfogli_2_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_euro_2_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_spinBox_foglio3_nfogli_3_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_euro_3_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_spinBox_foglio3_nfogli_4_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_euro_4_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_spinBox_foglio3_nfogli_5_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_euro_5_valueChanged(QString )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_primencopie_1_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_successivencopie_1_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_primencopie_2_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_successivencopie_2_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_primencopie_3_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_successivencopie_3_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_percentuale_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_spinBox_foglio3_nfogli_1_valueChanged(int )
{
    refreshFoglio3();
}

void MainWindow::on_doubleSpinBox_foglio3_euro_1_valueChanged(double )
{
    refreshFoglio3();
}

void MainWindow::on_comboBox_foglio4_plastificazione_opaca_bianca_currentIndexChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_comboBox_foglio4_plastificazione_opaca_bianca_volta_currentIndexChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_comboBox_foglio4_plastificazione_lucida_bianca_currentIndexChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_comboBox_foglio4_plastificazione_lucida_bianca_volta_currentIndexChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_comboBox_foglio4_serigrafia_currentIndexChanged(QString )
{
    refreshFoglio4();
}


void MainWindow::on_spinBox_foglio4_plastificazione_opaca_bianca_valueChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_plastificazione_opaca_bianca_volta_valueChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_plastificazione_lucida_bianca_valueChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_plastificazione_lucida_bianca_volta_valueChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_serigrafia_valueChanged(QString )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_plastificazione_opaca_bianca_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_plastificazione_opaca_bianca_volta_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_plastificazione_lucida_bianca_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_plastificazione_lucida_bianca_volta_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_serigrafia_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_serigrafia_telaio_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_fustella_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_fustellatura_nfogli_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_spinBox_foglio4_fustellatura_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_label_spinBox_foglio4_fustellatura_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_cordonatura_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_cordonatura_successivencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_cordonatura_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_stampaacaldo_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_stampaacaldo_successivencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_cliche_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_piegacopie_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_piegacopie_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_tagliocopie_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_tagliocopie_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_puntometallico_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_puntometallico_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_puntometallico_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_brosurafresata_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_brosurafresata_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_brosurafresata_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_filo_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_filo_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_filo_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_cartonato_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_cartonato_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_cartonato_avviamento_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_spiralatura_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_spiralatura_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio4_pacchi_numero_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_pacchi_euro_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_trasporto_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_prima_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_prima_successivencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_seconda_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_seconda_successivencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_terza_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_terza_successivencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_quarta_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_quarta_successivencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_quinta_primencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_quinta_successivencopie_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_percentuale_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_tabWidget_preventivi_currentChanged(int index)
{
    if ( index == 4)
    {
       refreshFoglio5();
    }
}




void MainWindow::on_tableView_clienti_clicked(QModelIndex index)
{
    rigadacancellare = index.row();
    valoredacancellare = index.data(0).toString();
}

void MainWindow::on_tableView_carta_tipo_clicked(QModelIndex index)
{
    rigadacancellare = index.row();
    valoredacancellare = index.data(0).toString();
}

void MainWindow::on_tableView_carta_formato_clicked(QModelIndex index)
{
    rigadacancellare = index.row();
    valoredacancellare = index.data(0).toString();
}

void MainWindow::on_tableView_carta_grammatura_clicked(QModelIndex index)
{
    rigadacancellare = index.row();
    valoredacancellare = index.data(0).toString();
}

void MainWindow::on_tableView_serigrafia_clicked(QModelIndex index)
{
    rigadacancellare = index.row();
    valoredacancellare = index.data(0).toString();
}

void MainWindow::on_tableView_plastificazione_clicked(QModelIndex index)
{
    rigadacancellare = index.row();
    valoredacancellare = index.data(0).toString();
}

void MainWindow::on_bottone_carta_formato_rimuovi_clicked()
{
    eliminaRiga("cartaformato","formato",valoredacancellare);
    refreshTabelle();
}

void MainWindow::on_bottone_carta_tipo_rimuovi_clicked()
{
    eliminaRiga("cartatipo","descrizione",valoredacancellare);
    refreshTabelle();
}

void MainWindow::on_bottone_carta_grammatura_rimuovi_clicked()
{
    eliminaRiga("cartagrammatura","grammatura",valoredacancellare);
    refreshTabelle();
}

void MainWindow::on_bottone_serigrafia_rimuovi_clicked()
{
    eliminaRiga("serigrafia","formato",valoredacancellare);
    refreshTabelle();
}

void MainWindow::on_bottone_plastificazione_rimuovi_clicked()
{
    eliminaRiga("plastificazione","formato",valoredacancellare);
    refreshTabelle();
}

void MainWindow::on_actionSalva_triggered()
{

}

void MainWindow::on_lineEdit_preventivi_cerca_textChanged(QString )
{
    refreshTabelle();
}

void MainWindow::on_tableView_preventivi_clicked(QModelIndex index)
{
    valoredacancellare = index.data(0).toString();
     ui->label_27->setText(valoredacancellare);
}

void MainWindow::on_bottone_preventivi_elimina_clicked()
{
    eliminaRiga("preventivo", "numero", valoredacancellare);
    //razionalizzaTabella("preventivo","numero",valoredacancellare.toInt());
    refreshTabelle();
}


void MainWindow::on_bottone_preventivi_usamodello_clicked()
{
    pulire = false;
    caricaPreventivo(valoredacancellare.toInt());
    this->on_bottone_preventivi_nuovo_clicked();
}

void MainWindow::on_bottone_preventivi_modifica_clicked()
{
    pulire = false;
    this->on_bottone_preventivi_nuovo_clicked();
    caricaPreventivo(valoredacancellare.toInt());
}

void MainWindow::on_doubleSpinBox_foglio4_accoppiatura_prime_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_accoppiatura_succ_valueChanged(double )
{
    refreshFoglio4();
}

void MainWindow::on_spinBox_foglio5_500_valueChanged(int )
{
    refreshFoglio5();
}

void MainWindow::on_spinBox_foglio5_1000_valueChanged(int )
{
    refreshFoglio5();
}

void MainWindow::on_spinBox_foglio5_1500_valueChanged(int )
{
    refreshFoglio5();
}

void MainWindow::on_spinBox_foglio5_2000_valueChanged(int )
{
    refreshFoglio5();
}

void MainWindow::on_spinBox_foglio5_2500_valueChanged(int )
{
    refreshFoglio5();
}

void MainWindow::on_spinBox_foglio5_3000_valueChanged(int )
{
    refreshFoglio5();
}
