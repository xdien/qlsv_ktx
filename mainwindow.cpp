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
#include "dialog_chontp.h"
#include "dialog_chonkhoa.h"
#include "dialogchonnganh.h"
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
        if(ui->lineEdit_sdtSV->text().toInt() == 0 ||  ui->lineEdit_sdtSV->text().isEmpty())
        {
            QMessageBox laso;
            laso.setText("La so");
            laso.exec();
        }
        else
        {
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
                        +ui->lineEdit_sdtSV->text()+"', gioi_tinh = '"+QString::number(tempint)+"', ngay_sinh='"+ui->dateEdit_ngaysinh->date().toString("yyyy-MM-dd")+"', img_path ='"+linkimg+"' where " \
                        "mssv='"+tempst+"'";
                if(!truyvanmoi.exec(tempst1))
                    qDebug()<<truyvanmoi.lastError().text();
                //cap nhat lai dia chi
                newq.exec("delete from DC_CUASV where mssv = '"+tempst+"'");
                //neu ward rong
                if(ui->comboBox_xp->itemData(ui->comboBox_xp->currentIndex()).toString().isEmpty())
                {
                    //neu province rong
                    if(!ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString().isEmpty())
                    newq.exec("insert into DC_CUASV(`mssv`,`chitiet`,`wardid`,`districtid`,`provinceid`) values('"+tempst+"','"+ui->lineEdit_diachi->text()+"',NULL,'"\
                              +ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString()+"','"+ui->comboBox_tp->itemData(ui->comboBox_tp->currentIndex()).toString()+"')");
                    else
                        newq.exec("insert into DC_CUASV(`mssv`,`chitiet`,`wardid`,`districtid`,`provinceid`) values('"+tempst+"','"+ui->lineEdit_diachi->text()+"',NULL,NULL"\
                                 ",'"+ui->comboBox_tp->itemData(ui->comboBox_tp->currentIndex()).toString()+"')");
                }
                else
                    newq.exec("insert into DC_CUASV(`mssv`,`chitiet`,`wardid`,`districtid`,`provinceid`) values('"+tempst+"','"+ui->lineEdit_diachi->text()+"','"+ui->comboBox_xp->itemData(ui->comboBox_xp->currentIndex()).toString()+"','"\
                          +ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString()+"','"+ui->comboBox_tp->itemData(ui->comboBox_tp->currentIndex()).toString()+"')");
            }
        }
        else{
            tempst1 = "insert into SINH_VIEN values ('" +ui->lineEdit_mssvSV->text()+"','"+ui->comboBox_lopSv->itemText(ui->comboBox_lopSv->currentIndex())+"','"+ui->lineEdit_hotenSV->text()+"','" \
                    +ui->lineEdit_sdtSV->text()+"', '"+QString::number(tempint)+"','"+ui->dateEdit_ngaysinh->date().toString("yyyy-MM-dd")+"','"+linkimg+"')";
            if(truyvanmoi.exec(tempst1))
                qDebug()<< truyvanmoi.lastError().text();
            //
            if(ui->comboBox_xp->itemData(ui->comboBox_xp->currentIndex()).toString().isEmpty())
            {
                //neu province rong
                if(!ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString().isEmpty())
                newq.exec("insert into DC_CUASV(`mssv`,`chitiet`,`wardid`,`districtid`,`provinceid`) values('"+tempst+"','"+ui->lineEdit_diachi->text()+"',NULL,'"\
                          +ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString()+"','"+ui->comboBox_tp->itemData(ui->comboBox_tp->currentIndex()).toString()+"')");
                else
                    newq.exec("insert into DC_CUASV(`mssv`,`chitiet`,`wardid`,`districtid`,`provinceid`) values('"+tempst+"','"+ui->lineEdit_diachi->text()+"',NULL,NULL"\
                             ",'"+ui->comboBox_tp->itemData(ui->comboBox_tp->currentIndex()).toString()+"')");
            }
            else
                newq.exec("insert into DC_CUASV(`mssv`,`chitiet`,`wardid`,`districtid`,`provinceid`) values('"+tempst+"','"+ui->lineEdit_diachi->text()+"','"+ui->comboBox_xp->itemData(ui->comboBox_xp->currentIndex()).toString()+"',"\
                      +ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString()+"','"+ui->comboBox_tp->itemData(ui->comboBox_tp->currentIndex()).toString()+"')");
            p_display(ui->spinBox->value(),4,"SINH_VIEN");
        }
        }
    }

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


//tao ham loadpage
void MainWindow::loadpage()
{
    giatrispibox =0;
    //loaf gia tri spinbox cho display so dong cua ket qua
    QSettings giatr("connect.conf",QSettings::IniFormat);
    giatr.beginGroup("Settings");
    ui->spinBox->setValue(giatr.value("p_display").toInt());
    //hien thi danh sach sinh vien
    modelInfosv.setQuery("select * from SINH_VIEN limit "+QString::number(giatrispibox)+","+QString::number(ui->spinBox->value()));
    ui->listView_sv->setModel(&modelInfosv);
    //
    QSqlQuery query;
    QString val1;
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

void MainWindow::on_pushButton_3_clicked()
{
    QString newstring;
    newstring =  "INSERT INTO `HOP_DONG`(`stt_hd`, `ma_phong`, `mssv`, `ngay_den`, `ngay_di`,`tg_toi_da`) "\
            "VALUES ('','"+ui->comboBoxPhong_tabHD->currentText()+"','"\
            +ui->comboBoxSV_tabHD->itemData(ui->comboBoxSV_tabHD->currentIndex()).toString()+"','"\
            +ui->dateEdit_ngadk->date().toString("yyyy-MM-dd")+"','"\
            +ui->lineEdit_Ngaydi->text()+"','"+ui->dateEdit_thoihan->date().toString("yyyy-MM-dd")+"')";
    newq.exec(newstring);
    qDebug()<<newq.lastError().text();
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


void MainWindow::on_action_i_t_ng_triggered()
{
    Dialog_suaDT suadt;
    suadt.exec();
}

void MainWindow::on_pushButton_dlsv_clicked()
{
    //Ham xoa 1 sinh vien
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
        ui->spinBox_2->setValue(ui->spinBox->value());
        modelHopdong.setQuery("select SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten")+"',HOP_DONG.tg_toi_da as '"+QString::fromUtf8("Thoi hang")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv");

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
    //load tab xl thanh toan
    if(index == 2)
    {
        ui->spinBox_3->setValue(ui->spinBox->value());
        modelTT.setQuery("select HOP_DONG.mssv,HOP_DONG.tg_toi_da from PT_TIEN_TRO left join HOP_DONG on PT_TIEN_TRO.stt_hd = HOP_DONG.stt_hd limit 0,"+QString::number(ui->spinBox_3->value()));
        ui->treeView_thanhtoan->setModel(&modelTT);
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
    newq.exec("select * from SINH_VIEN where mssv = '"+ui->listView_sv->currentIndex().sibling(index.row(),0).data().toString()+"'");
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
        newq.exec("select * from DC_CUASV where mssv = '"+ui->listView_sv->currentIndex().sibling(index.row(),0).data().toString()+"'");
        if(newq.next())
        {
            ui->lineEdit_diachi->clear();
            ui->lineEdit_diachi->setText(newq.value(1).toString());
            if(newq.value(3).isNull())
            {
                setcombobox(newq.value(4).toString());
            }
            else
            {
                if(newq.value(2).isNull())
                {
                    setcombobox(newq.value(3).toString());
                }
                else
                {
                    setcombobox(newq.value(2).toString());
                }
            }
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

void MainWindow::on_action_i_t_ng_m_i_triggered()
{
    editDatatable dtmoi(this,"DOI_TUONG");
    dtmoi.exec();
}

void MainWindow::on_actionPh_ng_m_i_triggered()
{
    editDatatable phongmoi(this,"PHONG");
    phongmoi.exec();
}

void MainWindow::on_actionL_p_triggered()
{
    editDatatable lop(this,"LOP");
    lop.exec();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    modelTT.setQuery("select mssv,ngay from PT_TIEN_TRO " \
                    "where mssv like '%"+arg1+"%' order by ngay desc");
}


void MainWindow::on_treeView_thanhtoan_clicked(const QModelIndex &index)
{

    newq.exec("select * from PT_TIEN_TRO "\
              "left join HOP_DONG "\
              "on PT_TIEN_TRO.mssv = HOP_DONG.mssv "\
              "left join SINH_VIEN "\
              "on SINH_VIEN.mssv = PT_TIEN_TRO.mssv where PT_TIEN_TRO.mssv= '"+index.sibling(index.row(),0).data().toString()+"' "\
              "and PT_TIEN_TRO.ngay = '"+index.sibling(index.row(),1).data().toString()+"'");
    if(newq.next())
    {
        ui->label_ten->setText(newq.value(13).toString());
        ui->spinBox_PHONG->setValue(newq.value(7).toInt());
        //ui->spinBox_DIEN->setValue(newq.value(3).toInt());
        //ui->spinBox_NUOC->setValue(newq.value(4).toInt());
        ui->dateEdit_quy->setDate(newq.value(5).toDate());
        ui->label_tien->setText(QString::number(tempint));

    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(0==1){
    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/pttientro.ncr"); //set the report filename fullpath or relative to dir
    QString tam;
    tam = "select * from PT_TIEN_TRO "\
            "left join HOP_DONG "\
            "on PT_TIEN_TRO.mssv = HOP_DONG.mssv "\
            "left join SINH_VIEN "\
            "on SINH_VIEN.mssv = PT_TIEN_TRO.mssv where PT_TIEN_TRO.mssv= '"+ui->treeView_thanhtoan->currentIndex().sibling(ui->treeView_thanhtoan->currentIndex().row(),0).data().toString()+"' "\
            "and PT_TIEN_TRO.ngay = '"+ui->treeView_thanhtoan->currentIndex().sibling(ui->treeView_thanhtoan->currentIndex().row(),0).data().toString()+"'";

    report->runReportToPreview(); // run to preview output

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
    else
    {
        qDebug()<<ui->treeView_thanhtoan->currentIndex().sibling(ui->treeView_thanhtoan->currentIndex().row(),0).data().toString();
    }
}

void MainWindow::on_actionT_i_s_n_triggered()
{
    editDatatable tsmoi(this,"TAI_SAN");
    tsmoi.exec();
}

void MainWindow::on_actionDanh_s_ch_SV_theo_phong_triggered()
{
    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    //report->addItemModel(querymodel_room,"myModel");
    report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/lietkeDSSV.ncr"); //set the report filename fullpath or relative to dir
    report->runReportToPreview(); // run to preview output
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

void MainWindow::on_actionTh_ng_k_theo_ti_nh_tha_nh_triggered()
{
    dialog_chonTP tinhtp(this);
    tinhtp.exec();
}

void MainWindow::on_actionKhoa_triggered()
{
    dialog_chonKhoa chonkhoa(this);
    chonkhoa.exec();
}

void MainWindow::on_actionTheo_nga_nh_triggered()
{
    dialogChonNganh nganhmoi(this);
    nganhmoi.exec();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    QSettings p_display("connect.conf",QSettings::IniFormat);
    p_display.beginGroup("Settings");
    p_display.setValue("p_display",arg1);
}

void MainWindow::on_pushButton_7_clicked()
{
    p_display(ui->spinBox->value(),1,"SINH_VIEN");
}

void MainWindow::on_pushButton_6_clicked()
{
    if(giatrispibox >= 0)
    {
        qDebug()<<giatrispibox;
        p_display(ui->spinBox->value(),2,"SINH_VIEN");
    }
}
void MainWindow::p_display(const int donghienthi, int toantu, const QString tablename)
{
    switch (toantu) {
    case 1://gia tri tang len
    {
        giatrispibox = giatrispibox + donghienthi;
        modelInfosv.setQuery("select * from "+tablename+" limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
        break;
    case 2://giam gia tri
    {
        giatrispibox = giatrispibox - donghienthi;
        modelInfosv.setQuery("select * from "+tablename+" limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
        break;
    case 3://end
    {
        newq.exec("select count(*) from "+tablename+"");
        if(newq.next())
        {
            giatrispibox =  newq.value(0).toInt() - (newq.value(0).toInt() % donghienthi);
            qDebug()<<giatrispibox;
            modelInfosv.setQuery("select * from "+tablename+" limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
        }
    }
        break;
    case 4://start
    {
        giatrispibox = 0;
        modelInfosv.setQuery("select * from "+tablename+" limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
    default:
        break;
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    p_display(ui->spinBox->value(),3,"SINH_VIEN");
}

void MainWindow::on_pushButton_2_clicked()
{
    p_display(ui->spinBox->value(),4,"SINH_VIEN");
}
//p_displayHD
void MainWindow::p_displayHD(const int donghienthi, int toantu)
{
    switch (toantu) {
    case 1://gia tri tang len
    {
        giatrispibox = giatrispibox + donghienthi;
        modelHopdong.setQuery("select SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten")+"',HOP_DONG.tg_toi_da as '"+QString::fromUtf8("Thoi hang")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
        break;
    case 2://giam gia tri
    {
        giatrispibox = giatrispibox - donghienthi;
        modelHopdong.setQuery("select SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten")+"',HOP_DONG.tg_toi_da as '"+QString::fromUtf8("Thoi hang")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
        break;
    case 3://end
    {
        newq.exec("select count(*) from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv");
        if(newq.next())
        {
            giatrispibox =  newq.value(0).toInt() - (newq.value(0).toInt() % donghienthi);
            qDebug()<<giatrispibox;
            modelHopdong.setQuery("select SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten")+"',HOP_DONG.tg_toi_da as '"+QString::fromUtf8("Thoi hang")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
        }
    }
        break;
    case 4://start
    {
        giatrispibox = 0;
        modelHopdong.setQuery("select SINH_VIEN.ho_ten as '"+QString::fromUtf8("Ho ten")+"',HOP_DONG.tg_toi_da as '"+QString::fromUtf8("Thoi hang")+"' from SINH_VIEN, HOP_DONG where SINH_VIEN.mssv = HOP_DONG.mssv limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
    default:
        break;
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    p_displayHD(ui->spinBox_2->value(),4);
}


void MainWindow::on_pushButton_12_clicked()
{
    p_displayHD(ui->spinBox_2->value(),2);
}



void MainWindow::on_pushButton_9_clicked()
{
    p_displayHD(ui->spinBox_2->value(),1);
}



void MainWindow::on_pushButton_10_clicked()
{
    p_displayHD(ui->spinBox_2->value(),3);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    QSettings p_display("connect.conf",QSettings::IniFormat);
    p_display.beginGroup("Settings");
    p_display.setValue("p_display",arg1);
}

void MainWindow::p_displayTT(const int donghienthi, int toantu)
{
    switch (toantu) {
    case 1://gia tri tang len
    {
        giatrispibox = giatrispibox + donghienthi;
        modelTT.setQuery("select * from PT_TIEN_TRO left join HOP_DONG on PT_TIEN_TRO.stt_hd = HOP_DONG.stt_hd " \
                              " limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
        break;
    case 2://giam gia tri
    {
        giatrispibox = giatrispibox - donghienthi;
        modelTT.setQuery("select * from PT_TIEN_TRO left join HOP_DONG on PT_TIEN_TRO.stt_hd = HOP_DONG.stt_hd " \
                              " limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
        break;
    case 3://end
    {
        newq.exec("select count(*) from PT_TIEN_TRO left join HOP_DONG on PT_TIEN_TRO.stt_hd = HOP_DONG.stt_hd");
        if(newq.next())
        {
            giatrispibox =  newq.value(0).toInt() - (newq.value(0).toInt() % donghienthi);
            qDebug()<<giatrispibox;
            modelTT.setQuery("select * from PT_TIEN_TRO left join HOP_DONG on PT_TIEN_TRO.stt_hd = HOP_DONG.stt_hd " \
                                  " limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
        }
    }
        break;
    case 4://start
    {
        giatrispibox = 0;
        modelTT.setQuery("select * from PT_TIEN_TRO left join HOP_DONG on PT_TIEN_TRO.stt_hd = HOP_DONG.stt_hd " \
                              " limit "+QString::number(giatrispibox)+","+QString::number(donghienthi));
    }
    default:
        break;
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    p_displayTT(ui->spinBox_3->value(),1);
}

void MainWindow::on_pushButton_13_clicked()
{
    p_displayTT(ui->spinBox_3->value(),3);
}

void MainWindow::on_pushButton_15_clicked()
{
    p_displayTT(ui->spinBox_3->value(),2);
}

void MainWindow::on_pushButton_16_clicked()
{
    p_displayTT(ui->spinBox_3->value(),4);
}
