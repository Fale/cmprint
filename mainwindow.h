#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QComboBox>
#include <QDebug>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>

//#include <QtSql>
#include <QFile>
#include <QTextDocument>
#include <QPixmap>
#include <QString>
#include <QPrinter>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>

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
    bool pulire;
    bool bomb();
    void scriviBomb(QString valore);
    int rigadacancellare;
    QString valoredacancellare;
    QTextDocument documento;
    QPrinter stampante;
    void caricaDb(QString nome);
    void creaTabelle();
    void apriDb(QString nome);
    void refreshTabelle();
    void showHide(QString show);
    void eliminaRiga(QString tabella, int numero);
    void eliminaRiga(QString tabella, QString colonna, QString valore);
    void razionalizzaTabella(QString tabella, QString colonna, int nmancante);
    void pulisciPreventivo();
    void caricaPreventivo(int numero);
    QString creaHtml(int numero);
    void caricaComboBox( QComboBox *comboBox, QVariant valore);
    void popolaComboBox();
    void refreshFoglio2();
    void refreshFoglio3();
    void refreshFoglio4();
    void refreshFoglio5();
    double formatoASuperficie(QString formato);


private slots:


    void on_bottone_pdf_clicked();
    void on_spinBox_foglio5_500_valueChanged(int );
    void on_spinBox_foglio5_1000_valueChanged(int );
    void on_spinBox_foglio5_1500_valueChanged(int );
    void on_spinBox_foglio5_2000_valueChanged(int );
    void on_spinBox_foglio5_2500_valueChanged(int );
    void on_spinBox_foglio5_3000_valueChanged(int );
    void on_spinBox_foglio5_3500_valueChanged(int );
    void on_spinBox_foglio5_4000_valueChanged(int );
    void on_spinBox_foglio5_4500_valueChanged(int );
    void on_spinBox_foglio5_5000_valueChanged(int );
    void on_spinBox_foglio5_5500_valueChanged(int );
    void on_spinBox_foglio5_6000_valueChanged(int );
    void on_spinBox_foglio5_6500_valueChanged(int );
    void on_spinBox_foglio5_7000_valueChanged(int );
    void on_doubleSpinBox_foglio4_accoppiatura_succ_valueChanged(double );
    void on_doubleSpinBox_foglio4_accoppiatura_prime_valueChanged(double );
    void on_bottone_preventivi_modifica_clicked();
    void on_bottone_preventivi_usamodello_clicked();
    void on_tableView_preventivi_clicked(QModelIndex index);
    void on_bottone_preventivi_elimina_clicked();
    void on_lineEdit_preventivi_cerca_textChanged(QString );
    void on_actionSalva_triggered();
    void on_bottone_plastificazione_rimuovi_clicked();
    void on_bottone_serigrafia_rimuovi_clicked();
    void on_bottone_carta_grammatura_rimuovi_clicked();
    void on_bottone_carta_tipo_rimuovi_clicked();
    void on_bottone_carta_formato_rimuovi_clicked();
    void on_tableView_plastificazione_clicked(QModelIndex index);
    void on_tableView_serigrafia_clicked(QModelIndex index);
    void on_tableView_carta_grammatura_clicked(QModelIndex index);
    void on_tableView_carta_formato_clicked(QModelIndex index);
    void on_tableView_carta_tipo_clicked(QModelIndex index);
    void on_tableView_clienti_clicked(QModelIndex index);
    void on_bottone_salva_preventivo_clicked();
    void on_tabWidget_preventivi_currentChanged(int index);
    void on_doubleSpinBox_foglio4_percentuale_valueChanged(double );
    void on_doubleSpinBox_foglio4_quinta_successivencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_quinta_primencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_quarta_successivencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_quarta_primencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_terza_successivencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_terza_primencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_seconda_successivencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_seconda_primencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_prima_successivencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_prima_primencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_trasporto_valueChanged(double );
    void on_doubleSpinBox_foglio4_pacchi_euro_valueChanged(double );
    void on_spinBox_foglio4_pacchi_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_spiralatura_euro_valueChanged(double );
    void on_spinBox_foglio4_spiralatura_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_cartonato_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_cartonato_euro_valueChanged(double );
    void on_spinBox_foglio4_cartonato_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_filo_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_filo_euro_valueChanged(double );
    void on_spinBox_foglio4_filo_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_brosurafresata_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_brosurafresata_euro_valueChanged(double );
    void on_spinBox_foglio4_brosurafresata_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_puntometallico_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_puntometallico_euro_valueChanged(double );
    void on_spinBox_foglio4_puntometallico_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_tagliocopie_euro_valueChanged(double );
    void on_spinBox_foglio4_tagliocopie_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_piegacopie_euro_valueChanged(double );
    void on_spinBox_foglio4_piegacopie_numero_valueChanged(int );
    void on_doubleSpinBox_foglio4_cliche_primencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_stampaacaldo_successivencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_stampaacaldo_primencopie_valueChanged(double );
    void on_doubleSpinBox_cordonatura_avviamento_valueChanged(double );
    void on_doubleSpinBox_cordonatura_successivencopie_valueChanged(double );
    void on_doubleSpinBox_cordonatura_primencopie_valueChanged(double );
    void on_doubleSpinBox_label_spinBox_foglio4_fustellatura_avviamento_valueChanged(double );
    void on_doubleSpinBox_spinBox_foglio4_fustellatura_euro_valueChanged(double );
    void on_spinBox_foglio4_fustellatura_nfogli_valueChanged(int );
    void on_doubleSpinBox_fustella_primencopie_valueChanged(double );
    void on_doubleSpinBox_foglio4_serigrafia_telaio_valueChanged(double );
    void on_doubleSpinBox_foglio4_serigrafia_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_plastificazione_lucida_bianca_volta_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_plastificazione_lucida_bianca_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_plastificazione_opaca_bianca_volta_avviamento_valueChanged(double );
    void on_doubleSpinBox_foglio4_plastificazione_opaca_bianca_avviamento_valueChanged(double );
    void on_spinBox_foglio4_serigrafia_valueChanged(QString );
    void on_spinBox_foglio4_plastificazione_lucida_bianca_volta_valueChanged(QString );
    void on_spinBox_foglio4_plastificazione_lucida_bianca_valueChanged(QString );
    void on_spinBox_foglio4_plastificazione_opaca_bianca_volta_valueChanged(QString );
    void on_spinBox_foglio4_plastificazione_opaca_bianca_valueChanged(QString );
    void on_comboBox_foglio4_serigrafia_currentIndexChanged(QString );
    void on_comboBox_foglio4_plastificazione_lucida_bianca_volta_currentIndexChanged(QString );
    void on_comboBox_foglio4_plastificazione_lucida_bianca_currentIndexChanged(QString );
    void on_comboBox_foglio4_plastificazione_opaca_bianca_volta_currentIndexChanged(QString );
    void on_comboBox_foglio4_plastificazione_opaca_bianca_currentIndexChanged(QString );
    void on_doubleSpinBox_foglio3_euro_1_valueChanged(double );
    void on_spinBox_foglio3_nfogli_1_valueChanged(int );
    void on_doubleSpinBox_foglio3_percentuale_valueChanged(double );
    void on_doubleSpinBox_foglio3_successivencopie_3_valueChanged(double );
    void on_doubleSpinBox_foglio3_primencopie_3_valueChanged(double valore);
    void on_doubleSpinBox_foglio3_successivencopie_2_valueChanged(double );
    void on_doubleSpinBox_foglio3_primencopie_2_valueChanged(double valore);
    void on_doubleSpinBox_foglio3_successivencopie_1_valueChanged(double );
    void on_doubleSpinBox_foglio3_primencopie_1_valueChanged(double valore);
    void on_doubleSpinBox_foglio3_euro_5_valueChanged(QString );
    void on_spinBox_foglio3_nfogli_5_valueChanged(QString );
    void on_doubleSpinBox_foglio3_euro_4_valueChanged(QString );
    void on_spinBox_foglio3_nfogli_4_valueChanged(QString );
    void on_doubleSpinBox_foglio3_euro_3_valueChanged(QString );
    void on_spinBox_foglio3_nfogli_3_valueChanged(QString );
    void on_doubleSpinBox_foglio3_euro_2_valueChanged(QString );
    void on_spinBox_foglio3_nfogli_2_valueChanged(QString );
    void on_comboBox_foglio3_carta_grammatura_5_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_formato_5_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_grammatura_3_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_formato_3_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_grammatura_2_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_formato_2_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_grammatura_4_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_formato_4_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_grammatura_1_currentIndexChanged(QString );
    void on_comboBox_foglio3_carta_formato_1_currentIndexChanged(QString );
    void on_doubleSpinBox_foglio2_percentuale_valueChanged(double );
    void on_doubleSpinBox_foglio2_stampadigitale_successive_valueChanged(double );
    void on_doubleSpinBox_foglio2_stampadigitale_prime_valueChanged(double );
    void on_doubleSpinBox_foglio2_stampa_successive_valueChanged(double );
    void on_doubleSpinBox_foglio2_stampa_prime_valueChanged(double );
    void on_doubleSpinBox_foglio2_lastreavviamenti_successive_valueChanged(double );
    void on_doubleSpinBox_foglio2_lastreavviamenti_prime_valueChanged(double );
    void on_bottone_torna_preventivo_clicked();
    void on_spinBox_foglio1_ncopie_valueChanged(QString valore);
    void on_bottone_tab1_aggiungi_clienti_clicked();
    void on_bottone_preventivi_nuovo_clicked();
    void on_bottone_clienti_rimuovi_clicked();
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

    //FUNZIONI PER I CALCOLI:

    //secondo foglio
    //lastre
    void on_doubleSpinBox_foglio2_lastre_prezzo_1_valueChanged(double );
    void on_spinBox_foglio2_lastre_n_1_valueChanged(int );

    void on_doubleSpinBox_foglio2_lastre_prezzo_2_valueChanged(double );
    void on_spinBox_foglio2_lastre_n_2_valueChanged(int );

    void on_doubleSpinBox_foglio2_lastre_prezzo_3_valueChanged(double );
    void on_spinBox_foglio2_lastre_n_3_valueChanged(int );

    void on_doubleSpinBox_foglio2_lastre_prezzo_4_valueChanged(double );
    void on_spinBox_foglio2_lastre_n_4_valueChanged(int );

    void on_doubleSpinBox_foglio2_lastre_prezzo_5_valueChanged(double );
    void on_spinBox_foglio2_lastre_n_5_valueChanged(int );

    void on_doubleSpinBox_foglio2_lastre_prezzo_6_valueChanged(double );
    void on_spinBox_foglio2_lastre_n_6_valueChanged(int );


    //risme
    void on_doubleSpinBox_foglio2_risme_prezzo_1_valueChanged(double );
    void on_spinBox_foglio2_risme_n_1_valueChanged(int );

    void on_doubleSpinBox_foglio2_risme_prezzo_2_valueChanged(double );
    void on_spinBox_foglio2_risme_n_2_valueChanged(int );

    void on_doubleSpinBox_foglio2_risme_prezzo_3_valueChanged(double );
    void on_spinBox_foglio2_risme_n_3_valueChanged(int );

    void on_doubleSpinBox_foglio2_risme_prezzo_4_valueChanged(double );
    void on_spinBox_foglio2_risme_n_4_valueChanged(int );

    void on_doubleSpinBox_foglio2_risme_prezzo_5_valueChanged(double );
    void on_spinBox_foglio2_risme_n_5_valueChanged(int );

    void on_doubleSpinBox_foglio2_risme_prezzo_6_valueChanged(double );
    void on_spinBox_foglio2_risme_n_6_valueChanged(int );



};

#endif // MAINWINDOW_H
