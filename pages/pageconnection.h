/*
    Copyright 2016 - 2017 Benjamin Vedder	benjamin@vedder.se

    This file is part of VESC Tool.

    VESC Tool is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    VESC Tool is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#ifndef PAGECONNECTION_H
#define PAGECONNECTION_H

#include <QWidget>
#include <QTimer>
#include "vescinterface.h"

namespace Ui {
class PageConnection;
}

class PageConnection : public QWidget
{
    Q_OBJECT

public:
    explicit PageConnection(QWidget *parent = 0);
    ~PageConnection();

    VescInterface *vesc() const;
    void setVesc(VescInterface *vesc);

private slots:
    void timerSlot();
    void bleScanDone(QVariantMap devs, bool done);

    void on_serialRefreshButton_clicked();
    void on_serialDisconnectButton_clicked();
    void on_serialConnectButton_clicked();
    void on_tcpDisconnectButton_clicked();
    void on_tcpConnectButton_clicked();
    void on_canFwdBox_valueChanged(int arg1);
    void on_helpButton_clicked();
    void on_canFwdButton_toggled(bool checked);
    void on_autoConnectButton_clicked();
    void on_bleScanButton_clicked();
    void on_bleDisconnectButton_clicked();
    void on_bleConnectButton_clicked();

private:
    Ui::PageConnection *ui;
    VescInterface *mVesc;
    QTimer *mTimer;

};

#endif // PAGECONNECTION_H
