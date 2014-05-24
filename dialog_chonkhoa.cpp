/****************************************************************************
 *   Copyright 2014 Unknown <bdienw@gmail.com>								*
 * 																			*
 * This program is free software; you can redistribute it and/or modify		*
 * it under the terms of the GNU General Public License as published by		*
 * the Free Software Foundation; either version 2 of the License, or		*
 * (at your option) any later version.										*
 * 																			*
 * This program is distributed in the hope that it will be useful,			*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of			*
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			*
 * GNU General Public License for more details.								*
 * 																			*
 * You should have received a copy of the GNU General Public License		*
 * along with this program; if not, write to the Free Software				*
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,				*
 * MA 02110-1301, USA.                  		                            *
 *                                                                    		*
 ***************************************************************************/

#include "dialog_chonkhoa.h"
#include "ui_dialog_chonkhoa.h"

dialog_chonKhoa::dialog_chonKhoa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_chonKhoa)
{
    ui->setupUi(this);
    QSqlQuery newq;
    newq.exec("select * from KHOA");
    while (newq.next()) {
        ui->comboBox->addItem(newq.value(1).toString(),newq.value(0).toString());
    }
}

dialog_chonKhoa::~dialog_chonKhoa()
{
    delete ui;
}

void dialog_chonKhoa::on_buttonBox_accepted()
{

    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/lietkeTheoKhoa.ncr"); //set the report filename fullpath or relative to di
    QString  query,htmlText;
    query = "select distinct SINH_VIEN.ho_ten,SINH_VIEN.mssv,HOP_DONG.tg_toi_da,HOP_DONG.tg_toi_da,HOP_DONG.ngay_den,HOP_DONG.ngay_di from KHOA "\
            "right join NGANH "\
            "on NGANH.ma_khoa = KHOA.ma_khoa "\
            "right join LOP "\
            "on LOP.ma_nganh = NGANH.ma_nganh "\
            "right join SINH_VIEN "\
            "on SINH_VIEN.ten_lop = LOP.ten_lop "\
            "right join HOP_DONG "\
            "on HOP_DONG.mssv = SINH_VIEN.mssv where KHOA.ma_khoa ='"+ui->comboBox->itemData(ui->comboBox->currentIndex()).toString()+"' and ngay_di in ('0000-00-00') and HOP_DONG.ngay_den between '"+QString::number(ui->dateEdit->date().year())+"-01-01' and '"+QString::number(ui->dateEdit->date().year())+"-12-31'";
    htmlText = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n "\
            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n "\
            "p, li { white-space: pre-wrap; }\n "\
            "</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\"> \n"\
            "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Arial'; font-size:18pt; font-weight:600;\"> \n"\
            +QString::fromUtf8("Danh Sách Sinh Viên Theo Khoa ")+"<br />"+ui->comboBox->currentText()+QString::fromUtf8(" Năm ")+" "+QString::number(ui->dateEdit->date().year())+"</span></p></body></html>";
    report->addParameter("header",htmlText);
    report->addParameter("query",query);//set val query for report;
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
