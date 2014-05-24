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

#include "dialog_chonquy.h"
#include "ui_dialog_chonquy.h"
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#include <QMessageBox>
#include <QDebug>

dialog_chonquy::dialog_chonquy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_chonquy)
{
    ui->setupUi(this);
    ui->comboBox->addItem("1");
    ui->comboBox->addItem("2");
    ui->comboBox->addItem("3");
    ui->comboBox->addItem("4");
}

dialog_chonquy::~dialog_chonquy()
{
    delete ui;
}

void dialog_chonquy::on_buttonBox_accepted()
{
    if(ui->radioButton->isChecked() || ui->radioButton_2->isChecked())
    {
        NCReport *report = new NCReport();
        report->setReportSource( NCReportSource::File ); // set report source type
        report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/lietkeTheoKhoa.ncr"); //set the report filename fullpath or relative to di
        QString  query,htmlText;
        if(ui->radioButton->isChecked())
        {
            switch (ui->comboBox->currentText().toInt()) {
            case 1:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where ngay_di in ('0000-00-00') and HOP_DONG.ngay_den between '"+QString::number(ui->dateEdit->date().year())+"-01-01' and '"+QString::number(ui->dateEdit->date().year())+"-03-30'";
                break;
            case 2:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where ngay_di in ('0000-00-00') and HOP_DONG.ngay_den between '"+QString::number(ui->dateEdit->date().year())+"-04-01' and '"+QString::number(ui->dateEdit->date().year())+"-06-30'";
                break;
            case 3:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where ngay_di in ('0000-00-00') and HOP_DONG.ngay_den between '"+QString::number(ui->dateEdit->date().year())+"-07-01' and '"+QString::number(ui->dateEdit->date().year())+"-09-30'";
                break;
            case 4:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where ngay_di in ('0000-00-00') and HOP_DONG.ngay_den between '"+QString::number(ui->dateEdit->date().year())+"-10-01' and '"+QString::number(ui->dateEdit->date().year())+"-12-31'";
                break;
            default:
                break;
            }
        }
        else
        {
            switch (ui->comboBox->currentText().toInt()) {
            case 1:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where HOP_DONG.ngay_di between '"+QString::number(ui->dateEdit->date().year())+"-01-01' and '"+QString::number(ui->dateEdit->date().year())+"-03-30' and  HOP_DONG.mssv not in (select mssv from HOP_DONG where ngay_di in ('0000-00-00'))";
                break;
            case 2:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where HOP_DONG.ngay_di between '"+QString::number(ui->dateEdit->date().year())+"-04-01' and '"+QString::number(ui->dateEdit->date().year())+"-06-30' and  HOP_DONG.mssv not in (select mssv from HOP_DONG where ngay_di in ('0000-00-00'))";
                break;
            case 3:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where HOP_DONG.ngay_di between '"+QString::number(ui->dateEdit->date().year())+"-07-01' and '"+QString::number(ui->dateEdit->date().year())+"-09-30' and  HOP_DONG.mssv not in (select mssv from HOP_DONG where ngay_di in ('0000-00-00'))";
                break;
            case 4:
                query = "select * from HOP_DONG "\
                        "left join SINH_VIEN "\
                        "on SINH_VIEN.mssv = HOP_DONG.mssv "\
                        "where HOP_DONG.ngay_di between '"+QString::number(ui->dateEdit->date().year())+"-10-01' and '"+QString::number(ui->dateEdit->date().year())+"-12-31' and  HOP_DONG.mssv not in (select mssv from HOP_DONG where ngay_di in ('0000-00-00'))";
                break;
            default:
                break;
            }
        }
        qDebug()<<query;
        htmlText = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n "\
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n "\
                "p, li { white-space: pre-wrap; }\n "\
                "</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\"> \n"\
                "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Arial'; font-size:18pt; font-weight:600;\"> \n"\
                +QString::fromUtf8("THỐNG KÊ QUÝ ")+ui->comboBox->currentText()+"<br />"+QString::fromUtf8("Năm ")+" "+QString::number(ui->dateEdit->date().year())+"</span></p></body></html>";
        report->addParameter("header",htmlText);
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
    else
    {
        QMessageBox chuaChon;
        chuaChon.setText(QString::fromUtf8("Hay chon mot kieu!"));
        chuaChon.exec();
    }
}
