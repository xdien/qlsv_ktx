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
        if(query.next())
        {
            ui->lineEdit_doituong->setText(query.value(0).toString());
        }
        /*set thong tin dia chi*/
        //lay ma xp, qh, tp
        query.exec("select * from DC_CUASV where mssv = '"+st+"'");
        if(query.next())
        {
            QString ma_dc, values,stq;
            int lent;
            ma_dc = query.value(1).toString();
            lent = ma_dc.length();
            values.append(query.value(2).toString());//luu chi tiet
            values.append(", ");
            switch (lent) {
            case 2:
            {
                query.exec("select * from province where provinceid = '"+ma_dc+"'");
                query.next();//ket qua ke tiep
                values.append(query.value(2).toString());
                values.append("."+query.value(1).toString());
            }
                break;
            case 3:
            {
                query.exec("select district.name,district.type,province.name,province.type from district left join province on district.provinceid = province.provinceid where districtid ='"+ma_dc+"'");
                query.next();
                values.append(query.value(1).toString()+".");//kieu luu quan huyen;
                values.append(query.value(0).toString()+", "+query.value(3).toString()+"."+query.value(2).toString());
            }
                break;
            default:
            {
                stq = "select ward.type,ward.name,district.type,district.name,province.type,province.name from ward "\
                        "left join district "\
                        "on district.districtid = ward.districtid "\
                        "left join province "\
                        "on province.provinceid = district.provinceid where ward.wardid ='"+ma_dc+"'";
                query.exec(stq);
                query.next();
                values.append(query.value(0).toString()+"."+query.value(1).toString()+", "+query.value(2).toString()+"."+query.value(3).toString()+", ");
                values.append(query.value(4).toString()+"."+query.value(5).toString());
                qDebug()<<values;
            }
                break;
            }
            ui->textEdit_diachi->append(values);
        }
        //truy van hop dong
        reciveString = "select "\
                "distinct TAI_SAN.ten_ts,TAI_SAN.gia_tri, CUA_PHONG.so_luong,CUA_PHONG.ma_phong "\
            "FROM "\
                "HOP_DONG "\
                    "left join "\
                "CUA_PHONG ON HOP_DONG.ma_phong = CUA_PHONG.ma_phong "\
                    "LEFT JOIN "\
                "TAI_SAN ON CUA_PHONG.ma_ts = TAI_SAN.ma_ts "\
            "WHERE HOP_DONG.MSSV = '"+st+"'";
        query.clear();
        query.exec(reciveString);
        if(query.next())
        {
            ma_ssv = query.value(3).toString();//luu ma phong
            ui->lineMsPhong->setText(ma_ssv);
            /*Set listview_ts*/
            querymodel = new QSqlQueryModel;
            querymodel->setQuery(query);
            ui->treeView_ts->setModel(querymodel);
            /*Tinh tong so tai san*/
            giatri = query.value(1).toFloat();
            soluong = query.value(2).toInt();
            giatri = giatri*soluong;
            while(query.next())
            {
                soluong = query.value(2).toInt();
                giatri = query.value(1).toFloat()*soluong + giatri;

            }
            ui->label_giatri->setText(QString::number(giatri));
            //truy van hop dong lien qua
            query.clear();
            reciveString = "select distinct HOP_DONG.mssv from HOP_DONG where ma_phong='"+ma_ssv+"'";
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
            this->close();
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
