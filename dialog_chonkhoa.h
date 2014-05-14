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

#ifndef DIALOG_CHONKHOA_H
#define DIALOG_CHONKHOA_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include "ncreport.h"
#include "ncreportpreviewwindow.h"

namespace Ui {
class dialog_chonKhoa;
}

class dialog_chonKhoa : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_chonKhoa(QWidget *parent = 0);
    ~dialog_chonKhoa();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dialog_chonKhoa *ui;
};

#endif // DIALOG_CHONKHOA_H
