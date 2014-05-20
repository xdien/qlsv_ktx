#include "dialog_chitietsv.h"
#
#include "ui_dialog_chitietsv.h"

Dialog_chitietSV::Dialog_chitietSV(QWidget *parent, QString st) :
    QDialog(parent),
    ui(new Ui::Dialog_chitietSV)
{
    ui->setupUi(this);
    reciveString = "select * from SINH_VIEN where mssv='"+ st +"'";
    query.exec(reciveString);
    //if resut query return null show message box
    if(query.next())
    {
        temp = query.value(1).toString();//luu lop
        ui->lineEdit_hoten->setText(query.value(2).toString());//cot thu 3 trong SINH_VIEN chua "ho ten"
        ui->lineEdit_sdt->setText(query.value(3).toString());
        ui->lineEdit_mssv->setText(st);
        ui->radioButton->setChecked(query.value(4).toBool());
        ui->lineEdit_lop->setText(temp);
        ui->dateEdit->setDate(query.value(5).toDate());
        QPixmap pix(query.value(6).toString());
        ui->label_pic->setPixmap(pix.scaled(120,140,Qt::KeepAspectRatio));
        //tim ten dt
        reciveString = "select DOI_TUONG.ten_dt from SINH_VIEN " \
                "left join THUOC_DT " \
                "on SINH_VIEN.mssv = THUOC_DT.mssv " \
                "left join DOI_TUONG " \
                "on THUOC_DT.ma_dt = DOI_TUONG.ma_dt " \
                "where SINH_VIEN.mssv = '"+st+"'";

        query.clear();
        query.exec(reciveString);
        QString doituong;
        while(query.next())
        {
            doituong.append(query.value(0).toString()+",");
        }
        ui->lineEdit_doituong->setText(doituong);
        /*set thong tin dia chi*/
        query.exec("select * from DC_CUASV where mssv ='"+st+"'");
        if(query.next())//co ma gia tri va lay ra
        {
            diachi.append(query.value(1).toString() +" ");
            maxp = query.value(2).toString();
            maqh = query.value(3).toString();
            matp = query.value(4).toString();
        }
        //lay xa phuong
        query.exec("select * from ward where wardid = '"+maxp+"'");
        if(query.next())
        {
            diachi.append(query.value(2).toString()+": ");
            diachi.append(query.value(1).toString()+", ");
        }
        //lay qh
        query.exec("select * from district where districtid = '"+maqh+"'");
        if(query.next())
        {
            diachi.append(query.value(2).toString()+": ");
            diachi.append(query.value(1).toString()+", ");
        }
        //lay tp
        query.exec("select * from province where provinceid = '"+matp+"'");
        if(query.next())
        {
            diachi.append(query.value(2).toString()+": ");
            diachi.append(query.value(1).toString());
        }
        diachi.trimmed();
        ui->textEdit_diachi->append(diachi);
        //truy van hop dong
        query.exec("select * from HOP_DONG where mssv = '"+st+"'");
        if(query.next())
        {
            ui->label_stthd->setText(query.value(0).toString());
            ui->lineMsPhong->setText(query.value(1).toString());
            querymodelLTS = new QSqlQueryModel();
            querymodelLTS->setQuery("select TAI_SAN.ten_ts,CUA_PHONG.so_luong,TAI_SAN.gia_tri from PHONG,TAI_SAN,CUA_PHONG "\
                                    "where PHONG.ma_phong = CUA_PHONG.ma_phong and TAI_SAN.ma_ts = CUA_PHONG.ma_ts and PHONG.ma_phong = '"+ui->lineMsPhong->text()+"'");
            ui->treeView_ts->setModel(querymodelLTS);
            query.exec("select TAI_SAN.ten_ts,CUA_PHONG.so_luong,TAI_SAN.gia_tri from PHONG,TAI_SAN,CUA_PHONG "\
                       "where PHONG.ma_phong = CUA_PHONG.ma_phong and TAI_SAN.ma_ts = CUA_PHONG.ma_ts and PHONG.ma_phong = '"+ui->lineMsPhong->text()+"'");
            if(query.next())
            {
                giatri = query.value(1).toFloat();
                soluong = query.value(2).toInt();
                giatri = giatri*soluong;
                while(query.next())
                {
                    soluong = query.value(1).toInt();
                    giatri = query.value(2).toFloat()*soluong + giatri;
                }
                ui->label_giatri->setText(QString::number(giatri));
            }
            //truy van so luong nguoi trong phong
            reciveString = "select distinct HOP_DONG.mssv from HOP_DONG where ma_phong='"+ui->lineMsPhong->text()+"'";
            query.exec(reciveString);
            int i;
            i= 0;
            while (query.next()) {
                i++;
            }
            querymodel1 = new QSqlQueryModel();
            querymodel1->setQuery(query);
            ui->listView_hopdong->setModel(querymodel1);
            ui->label_soluongnguoi->setText(QString::number(i));
        }
        else
        {
            ui->label_thongbao->setText(QString::fromUtf8("Sinh viên này chưa đăng ký́"));
        }
    }
    else
    {
        QMessageBox thongbao;
        thongbao.setText(QString::fromUtf8("Sinh viên này chưa có trong hệ thống, xin hãy kiểm tra lại MSSV!"));
        thongbao.exec();
    }
}

Dialog_chitietSV::~Dialog_chitietSV()
{
    delete ui;
}
void Dialog_chitietSV::setvalue(QString st)
{
    reciveString = st;
}
