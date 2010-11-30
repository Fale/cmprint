void MainWindow::on_bottone_clienti_rimuovi_clicked()
{
    eliminaRiga("clienti",ui->line_edit_clienti->text());
    refreshTabelle();
}


void MainWindow::on_line_edit_clienti_returnPressed()
{
    this->on_bottone_clienti_rimuovi_clicked();
}

void MainWindow::on_bottone_preventivi_nuovo_clicked()
{
    ui->bottone_preventivi_cerca->hide();
    ui->bottone_preventivi_nuovo->hide();
    ui->lineEdit_preventivi_cerca->hide();
    ui->tableView_preventivi->hide();
    ui->tabWidget_preventivi->show();
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
void MainWindow::on_spinBox_foglio2_lastre_n_1_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_1_valueChanged(double valore)
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_2_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_2_valueChanged(double valore)
{
    refreshFoglio2();
}

void MainWindow::on_spinBox_foglio2_lastre_n_3_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_3_valueChanged(double valore)
{
   refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_4_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_4_valueChanged(double valore)
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_5_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_5_valueChanged(double valore)
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_lastre_n_6_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_lastre_prezzo_6_valueChanged(double valore)
{
    refreshFoglio2();
}

//risme
void MainWindow::on_spinBox_foglio2_risme_n_1_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_1_valueChanged(double valore)
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_2_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_2_valueChanged(double valore)
{
    refreshFoglio2();
}

void MainWindow::on_spinBox_foglio2_risme_n_3_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_3_valueChanged(double valore)
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_4_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_4_valueChanged(double valore)
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_5_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_5_valueChanged(double valore)
{
    refreshFoglio2();
}


void MainWindow::on_spinBox_foglio2_risme_n_6_valueChanged(int valore)
{
    refreshFoglio2();
}

void MainWindow::on_doubleSpinBox_foglio2_risme_prezzo_6_valueChanged(double valore)
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

void MainWindow::on_comboBox_foglio3_carta_formato_1_currentIndexChanged(QString formato)
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

void MainWindow::on_spinBox_foglio4_accoppiatura_fogli_valueChanged(int )
{
    refreshFoglio4();
}

void MainWindow::on_doubleSpinBox_foglio4_accoppiatura_euro_valueChanged(double )
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
