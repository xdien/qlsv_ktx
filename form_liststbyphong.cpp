#include "form_liststbyphong.h"
#include "ui_form_liststbyphong.h"
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#include <QMessageBox>

Form_listSTbyPhong::Form_listSTbyPhong(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_listSTbyPhong)
{
    ui->setupUi(this);
    querymodel_room = new QSqlQueryModel();
    querymodel_room->setQuery("select ma_phong from PHONG");
    ui->treeView_phong->setModel(querymodel_room);
    ui->tableView->setModel(querymodel_room);
}

Form_listSTbyPhong::~Form_listSTbyPhong()
{
    delete ui;
}

void Form_listSTbyPhong::on_treeView_phong_clicked(const QModelIndex &index)
{
    listsv = new QSqlQueryModel();
    listsv->setQuery("select distinct SINH_VIEN.mssv, SINH_VIEN.ho_ten from PHONG "\
                     "left join HOP_DONG on PHONG.ma_phong = HOP_DONG.ma_phong "\
                     "left join SINH_VIEN on SINH_VIEN.mssv = HOP_DONG.mssv where PHONG.ma_phong = '"+ index.sibling(index.row(),0).data().toString()+"'");
    ui->treeView_sv->setModel(listsv);
}

void Form_listSTbyPhong::on_pushButton_2_clicked()
{
    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    report->addItemModel(querymodel_room,"myModel");
    report->addTableView("myView",ui->tableView);
    report->setConnectionID("gentoo");
    report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/lietkeDSSV.ncr"); //set the report filename fullpath or relative to dir
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
