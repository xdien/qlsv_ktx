#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "dialog_setting.h"
#include <QMessageBox>
#include "dialog_chitietsv.h"
#include <dialogform.h>
#include "editdatatable.h"
#include "form_liststbyphong.h"
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#include "dialog_suadt.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->loadpage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit_mssvSV->text() == "" || ui->lineEdit_hotenSV->text() == "")
    {
        QMessageBox thongbaorong;
        thongbaorong.setText(QString::fromUtf8("Ban phai dien day du thong tin, xin kiem tra lai!"));
        thongbaorong.exec();
    }
    else {
        QSqlQuery truyvanmoi;
        if(ui->checkBox_gt->isChecked())
            tempint = 1;
        else
           tempint = 0;
        tempst = ui->lineEdit_mssvSV->text();
        truyvanmoi.exec("select * from SINH_VIEN where mssv= '"+tempst+"'");
        if(truyvanmoi.next())
        {
            //tao button moi voi 2 nut
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Da ton tai", "Sinh vien nay ton tai, ban muon cap nhat?",
                                            QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                tempst1 = "update SINH_VIEN set ten_lop = '"+ui->comboBox_lopSv->itemText(ui->comboBox_lopSv->currentIndex())+"',ho_ten = '"+ui->lineEdit_hotenSV->text()+"', sdt='" \
                        +ui->lineEdit_sdtSV->text()+"', gioi_tinh = '"+QString::number(tempint)+"', img_path ='"+linkimg+"' where " \
                        "mssv='"+tempst+"'";
                if(!truyvanmoi.exec(tempst1))
                    qDebug()<<truyvanmoi.lastError().text();
                //cap nhat lai dia chi
                newq.exec("delete from DC_CUASV where mssv = '"+tempst+"'");
                tempst1 = "insert into DC_CUASV(`mssv`,`ma` ,`chitiet`) values ('"+tempst+"', '"+this->gomdiachi(ui->comboBox_tp,ui->comboBox_qh,ui->comboBox_xp)+"', '"+ui->lineEdit_diachi->text()+"')";
                newq.exec(tempst1);
            }
        }
        else{
            tempst1 = "insert into SINH_VIEN values ('" +ui->lineEdit_mssvSV->text()+"','"+ui->comboBox_lopSv->itemText(ui->comboBox_lopSv->currentIndex())+"','"+ui->lineEdit_hotenSV->text()+"','" \
                    +ui->lineEdit_sdtSV->text()+"', '"+QString::number(tempint)+"','"+ui->dateEdit_ngaysinh->date().toString("yyyy-MM-dd")+"','"+linkimg+"')";
            qDebug()<<"them sv moi"<<tempst1;
            if(truyvanmoi.exec(tempst1))
                qDebug()<< truyvanmoi.lastError().text();
            tempst1 = "insert into DC_CUASV(`mssv`,`ma` ,`chitiet`) values ('"+tempst+"', '"+this->gomdiachi(ui->comboBox_tp,ui->comboBox_qh,ui->comboBox_xp)+"', '"+ui->lineEdit_diachi->text()+"')";
            newq.exec(tempst1);
            qDebug()<< newq.lastError().text();
            qDebug()<<newq.lastQuery();
            table1.model->select();
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    table1.model->select();
}

void MainWindow::on_actionThoat_triggered()
{
    this->close();
}



void MainWindow::on_comboxLop_tabHopdong_activated(int index)
{
    //query lop roi dua vao combox
    QSqlQuery query;
    QString text;
    ui->comboBoxSV_tabHD->clear();
    text = ui->comboxLop_tabHopdong->itemText(index);
    qDebug() << query.exec("select mssv,ho_ten from SINH_VIEN where ten_lop='"+text+"'");
    while (query.next()) {
        ui->comboBoxSV_tabHD->addItem(query.value(1).toString(),query.value(0));
    }
}


void MainWindow::on_actionCai_dat_triggered()
{
    //hien thi form cai dat
    Dialog_setting mois;
    mois.exec();
}

void MainWindow::on_actionTim_kiem_triggered()
{
    //tao new dialog moi
    DialogForm formseach;
    formseach.exec();
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Delete)
    {
        qDebug()<< table1.model->removeRow(clickidxSV.row());
        table1.model->select();
    }

    // if(e->key() == QKeySequence::fromString("`"))
     if(e->matches(QKeySequence::Italic))
     {
         int rowCount;
         table1.model->setEditStrategy(QSqlTableModel::OnManualSubmit);
          rowCount = table1.model->rowCount();
          if(!table1.model->insertRow(rowCount))
          {
              qDebug()<<"Inserows for recoder table: "<<table1.model->lastError().text();
          }
          else
          {

          }
      }
     if(e->matches(QKeySequence::Save))
     {
         if(table1.model->submitAll())
         {
             table1.model->database().commit();
         }
     }
     if(e->matches(QKeySequence::Find))
     {
         //tao new dialog moi
         DialogForm formseach;
         formseach.exec();
     }
}


void MainWindow::on_tableView_listtable_doubleClicked(const QModelIndex &index)
{
    QString table_name;
    table_name = listmoi.model->data(index).toString();
    editDatatable tabblenew(NULL,table_name);
    tabblenew.exec();
}

//tao ham loadpage
void MainWindow::loadpage()
{
    //table1.model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->listView_sv->setModel(table1.model);
    ui->tableView_listtable->setModel(listmoi.model);
    QSqlQuery query;
    QString val1, val2;
    query.exec("select * from DOI_TUONG");
    while (query.next()) {
        //doi tuong
        val1 = query.value(0).toString();
        val2 = query.value(1).toString();
        //ui->comboBox_dtSV->addItem(val2,val1);
    }
    query.clear();
    query.exec("select ten_lop from LOP");
    while (query.next()) {
        //lop
        val1 = query.value(0).toString();
        //ui->comboBox->addItem(val1);
        ui->comboxLop_tabHopdong->addItem(val1);
        ui->comboBox_lopSv->addItem(val1);
    }
    /*day nha va phong*/
    query.clear();
    query.exec("select * from province");
    while(query.next())
    {
        ui->comboBox_tp->addItem(query.value(1).toString(),query.value(0).toString());
    }
}

void MainWindow::on_actionRefesh_triggered()
{
    this->loadpage();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString newstring;
    newstring =  "INSERT INTO `HOP_DONG`(`mssv`, `ma_phong`, `tg_hd`, `ngay_dk`) "\
            "VALUES ('"+ui->comboBoxSV_tabHD->itemData(ui->comboBoxSV_tabHD->currentIndex()).toString()+"','"\
            /*+ui->lineEdit_mahd->text()+"','"\*/
            +ui->comboBoxPhong_tabHD->currentText()+"','"\
            +ui->dateEdit_thoihan->date().toString("yyyy-MM-dd")+"','"\
            +ui->dateEdit_ngadk->date().toString("yyyy-MM-dd")+"')";
    newq.exec(newstring);
    qDebug()<<newq.lastError().text();
    //modelHopdong.setQuery("select HOP_DONG.ma_hd as '"+QString::fromUtf8("Ma HD")+"',SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten SV")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv");
    modelHopdong.setQuery("select SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten")+"',HOP_DONG.tg_hd as '"+QString::fromUtf8("Thoi hang")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv");
    ui->treeView->setModel(&modelHopdong);

}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Down || e->key() == Qt::Key_Up)
    {
        this->loadtabSV(ui->listView_sv->currentIndex());
    }
}

void MainWindow::on_comboBox_tp_currentIndexChanged(int index)
{
    newq.clear();
    ui->comboBox_qh->clear();
    newq.exec("select * from district where provinceid = '"+ui->comboBox_tp->itemData(index).toString()+"'");
    while (newq.next()) {
        ui->comboBox_qh->addItem(newq.value(1).toString(),newq.value(0).toString());
    }
    //them gia tri rong
    ui->comboBox_qh->addItem("");
}

void MainWindow::on_comboBox_qh_currentIndexChanged(int index)
{
    QSqlQuery xaphuong;
    ui->comboBox_xp->clear();
    xaphuong.exec("SELECT * FROM `ward` where districtid = '"+ui->comboBox_qh->itemData(index).toString()+"'");
    while(xaphuong.next())
    {
        ui->comboBox_xp->addItem(xaphuong.value(1).toString(),xaphuong.value(0).toString());
    }
    //them fia tri rong
    ui->comboBox_xp->addItem("");
}

void MainWindow::on_listView_sv_clicked(const QModelIndex &index)
{
    this->loadtabSV(index);
   //
    //QPixmap pix("/home/xdien/ProjectsQT/qlsv_ktx/the_1.jpg");
    //ui->label_pic->setPixmap(pix.scaled(120,160,Qt::KeepAspectRatio));
}


QString MainWindow::thuocdiachi(QString nhapvao)
{
    int len_address;
    len_address = nhapvao.length();
    switch (len_address) {
    case 2:
        return "province";
        break;
    case 3:
        return "district";
        break;
    case 5:
        return "ward";
        break;
    default:
        return "provice";
        break;
    }
}
//ham tra ve ma dia chi
QString MainWindow::gomdiachi(QComboBox *b1, QComboBox *b2, QComboBox *b3)
{
    if(b3->currentText().isEmpty())
    {
        if(b2->currentText().isEmpty())
        {
            return b1->itemData(b1->currentIndex()).toString();
        }
        else {
            return b2->itemData(b2->currentIndex()).toString();
        }
    }
    else {
        return b3->itemData(b3->currentIndex()).toString();
    }
}


void MainWindow::on_action_i_t_ng_triggered()
{
    Dialog_suaDT suadt;
    suadt.exec();
}

void MainWindow::on_pushButton_dlsv_clicked()
{
    qDebug()<< table1.model->removeRow(clickidxSV.row());
    table1.model->select();
}
void MainWindow::setcombobox(QString madc)
{
    int lent;
    lent = madc.length();
    QString luu, disid;
    switch (lent) {
    case 2:
    {
        ui->comboBox_tp->setCurrentIndex(ui->comboBox_tp->findData(madc));
        ui->comboBox_qh->setCurrentIndex(-1);
        ui->comboBox_xp->setCurrentIndex(-1);
        break;
    }
    case 3:
    {
        newq.exec("SELECT * FROM `district` where districtid = '"+madc+"'");
        while(newq.next())
        {
            ui->comboBox_qh->addItem(newq.value(1).toString(), newq.value(0).toString());
            luu = newq.value(4).toString();//luu gia ma tinh thanh
        }

        newq.exec("select * from provice where provinceid = '"+luu+"'");
        ui->comboBox_tp->setCurrentIndex(ui->comboBox_tp->findData(luu));
        ui->comboBox_qh->setCurrentIndex(ui->comboBox_qh->findData(madc));
        ui->comboBox_xp->setCurrentIndex(-1);
        break;
    }
    default:
    {
        newq.exec("SELECT * FROM `ward` where wardid = '"+madc+"'");
        while(newq.next())
        {
            ui->comboBox_xp->addItem(newq.value(1).toString(), newq.value(0).toString());
            disid = newq.value(4).toString();
        }
        //set gia tri cho qh
        newq.exec("select * from district where districtid = '"+disid+"'");
        if(newq.next())
        {
            luu = newq.value(4).toString();//luu gia ma tinh thanh
        }
        ui->comboBox_tp->setCurrentIndex(ui->comboBox_tp->findData(luu));
        ui->comboBox_qh->setCurrentIndex(ui->comboBox_qh->findData(disid));
        ui->comboBox_xp->setCurrentIndex(ui->comboBox_xp->findData(madc));
        break;
    }
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    //neu index thay doi bang = 1 thi chon load lop + ten sv vao combobx
    if(index ==1 )
    {
        modelHopdong.setQuery("select SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten")+"',HOP_DONG.tg_hd as '"+QString::fromUtf8("Thoi hang")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv");
        //modelHopdong.setQuery("select HOP_DONG.ma_hd as '"+QString::fromUtf8("Ma HD")+"', SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten SV")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv");
        ui->treeView->setModel(&modelHopdong);
        ui->comboxLop_tabHopdong->clear();
        newq.exec("select * from LOP");
        while(newq.next())
        {
            ui->comboxLop_tabHopdong->addItem(newq.value(0).toString());
        }
        //lay thong tin phong
        ui->comboBoxPhong_tabHD->clear();
        newq.exec("select * from PHONG");
        while (newq.next()) {
            ui->comboBoxPhong_tabHD->addItem(newq.value(0).toString());
        }
    }
}

void MainWindow::on_comboxLop_tabHopdong_activated(const QString &arg1)
{
    //neu click vao combobox thi load sinh vien thuoc lop do
    newq.clear();
    ui->comboBoxSV_tabHD->clear();
    newq.exec("select * from SINH_VIEN where ten_lop ='"+arg1+"'");
    while (newq.next()) {
        ui->comboBoxSV_tabHD->addItem(newq.value(2).toString(),newq.value(0).toString());
    }
}

void MainWindow::loadtabSV(const QModelIndex &index)
{
    newq.exec("select * from SINH_VIEN where mssv = '"+table1.model->data(index).toString()+"'");
    if(newq.next())
    {
        tempst = newq.value(1).toString();
        ui->lineEdit_hotenSV->setText(newq.value(2).toString());
        ui->lineEdit_mssvSV->setText(newq.value(0).toString());
        ui->checkBox_gt->setChecked(newq.value(4).toBool());
        ui->dateEdit_ngaysinh->setDate(QDate::fromString(newq.value(5).toString(),"yyyy-MM-dd"));
        if(newq.value(6).toString().isEmpty() || newq.value(6).toString().isNull())
        {
            ui->label_pic->setText("Khong co");
        }
        else
        {
        pix.load(newq.value(6).toString());
        ui->label_pic->setPixmap(pix.scaled(120,140,Qt::KeepAspectRatio));
        }
        //truy van lop va set no thanh active
        newq.exec("SELECT * FROM `LOP`");
        ui->comboBox_lopSv->clear();
        while(newq.next())
        {
            ui->comboBox_lopSv->addItem(newq.value(0).toString());
        }
        ui->comboBox_lopSv->setCurrentIndex(ui->comboBox_lopSv->findText(tempst));
        //truy van dia chi
        newq.exec("select * from DC_CUASV where mssv = '"+table1.model->data(index).toString()+"'");
        if(newq.next())
        {
            ui->lineEdit_diachi->clear();
            ui->lineEdit_diachi->setText(newq.value(2).toString());
            setcombobox(newq.value(1).toString());
        }
    }
    clickidxSV = index;
}


void MainWindow::on_toolButton_clicked()
{
    linkimg = QFileDialog::getOpenFileName(this,tr("Open jpg file"),"/home/xdien/ProjectsQT/qlsv_ktx/hinhThe/",tr("IMG file (*.jpg *.png)"));
    if(!linkimg.isNull())
    {
        pix.load(linkimg);
        ui->label_pic->setPixmap(pix.scaled(120,140,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_actionXemtheophong_triggered()
{
    Form_listSTbyPhong *xemmoi = new Form_listSTbyPhong();
    xemmoi->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/printHD.ncr"); //set the report filename fullpath or relative to dir
    report->addParameter("ten", ui->comboBoxSV_tabHD->currentText());
    report->addParameter("mssv",ui->comboBoxSV_tabHD->itemData(ui->comboBoxSV_tabHD->currentIndex()));
    qDebug()<< newq.exec("select * from SINH_VIEN where mssv = '"+ui->comboBoxSV_tabHD->itemData(ui->comboBoxSV_tabHD->currentIndex()).toString()+"'");
    if(newq.next())
    {
        report->addParameter("img_path",newq.value(6));
        report->addParameter("lop",newq.value(1));
        report->addParameter("phong",ui->comboBoxPhong_tabHD->currentText());
        report->addParameter("thoihan",ui->dateEdit_thoihan->date().toString("dd/MM/yyyy"));
    }
    report->runReportToPreview(); // run to preview output
    //report->dataSource()

    // error handling
    if( report->hasError())
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Report error: ") + report->lastErrorMsg());
        msgBox.exec();
    }
    else
    {
        // show preview
        NCReportPreviewWindow *pv = new NCReportPreviewWindow();    // create preview window
        pv->setOutput( (NCReportPreviewOutput*)report->output() );  // add output to the window
        pv->setReport(report);
        pv->setWindowModality(Qt::ApplicationModal );    // set modality
        pv->setAttribute( Qt::WA_DeleteOnClose );    // set attrib
        pv->exec();  // run like modal dialog
    }
    delete report;
}
