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

#include "dialog_chontp.h"
#include "ui_dialog_chontp.h"
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#include <QMessageBox>

dialog_chonTP::dialog_chonTP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_chonTP)
{
    ui->setupUi(this);
    QSqlQuery newq;
    newq.exec("select * from province");
    while(newq.next())
    {
        ui->comboBox->addItem(newq.value(1).toString(),newq.value(0).toString());
    }
}

dialog_chonTP::~dialog_chonTP()
{
    delete ui;
}

void dialog_chonTP::on_buttonBox_accepted()
{
    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/lietkeTheoTP.ncr"); //set the report filename fullpath or relative to di
    QString  query;
    query = "select SINH_VIEN.ho_ten,SINH_VIEN.mssv,HOP_DONG.tg_toi_da from KHOA "\
            "right join NGANH "\
            "on NGANH.ma_khoa = KHOA.ma_khoa "\
            "right join LOP "\
            "on LOP.ma_nganh = NGANH.ma_nganh "\
            "right join SINH_VIEN "\
            "on SINH_VIEN.ten_lop = LOP.ten_lop "\
            "right join HOP_DONG "\
            "on HOP_DONG.mssv = SINH_VIEN.mssv where KHO";
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
