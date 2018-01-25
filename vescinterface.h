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

#ifndef VESCINTERFACE_H
#define VESCINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QByteArray>
#include <QList>
#include <QTcpSocket>

#ifdef HAS_SERIALPORT
#include <QSerialPort>
#endif

#include "datatypes.h"
#include "configparams.h"
#include "commands.h"
#include "packet.h"

class VescInterface : public QObject
{
    Q_OBJECT
public:
    explicit VescInterface(QObject *parent = 0);
    Commands *commands() const;
    ConfigParams *mcConfig();
    ConfigParams *appConfig();
    ConfigParams *infoConfig();
    QStringList getSupportedFirmwares();
    QList<QPair<int, int> > getSupportedFirmwarePairs();
    QString getFirmwareNow();
    void emitStatusMessage(const QString &msg, bool isGood);
    bool fwRx();


    // Connection
    bool isPortConnected();
    void disconnectPort();
    bool reconnectLastPort();
    bool autoconnect();
    QString getConnectedPortName();
    bool connectSerial(QString port, int baudrate = 115200);
    QList<VSerialInfo_t> listSerialPorts();
    void connectTcp(QString server, int port);
    bool isAutoconnectOngoing() const;
    double getAutoconnectProgress() const;

signals:
    void statusMessage(const QString &msg, bool isGood);
    void messageDialog(const QString &title, const QString &msg, bool isGood);
    void fwUploadStatus(const QString &status, double progress, bool isOngoing);
    void serialPortNotWritable(const QString &port);
    void fwRxChanged(bool rx, bool limited);
    void portConnectedChanged();
    void autoConnectProgressUpdated(double progress, bool isOngoing);
    void autoConnectFinished();

public slots:

private slots:
#ifdef HAS_SERIALPORT
    void serialDataAvailable();
    void serialPortError(QSerialPort::SerialPortError error);
#endif

    void tcpInputConnected();
    void tcpInputDisconnected();
    void tcpInputDataAvailable();
    void tcpInputError(QAbstractSocket::SocketError socketError);

    void timerSlot();
    void packetDataToSend(QByteArray &data);
    void packetReceived(QByteArray &data);
    void cmdDataToSend(QByteArray &data);
    void fwVersionReceived(int major, int minor, QString hw, QByteArray uuid);
    void appconfUpdated();
    void mcconfUpdated();
    void ackReceived(QString ackType);

private:
    typedef enum {
        CONN_NONE = 0,
        CONN_SERIAL,
        CONN_TCP
    } conn_t;

    ConfigParams *mMcConfig;
    ConfigParams *mAppConfig;
    ConfigParams *mInfoConfig;

    QTimer *mTimer;
    Packet *mPacket;
    Commands *mCommands;
    bool mFwVersionReceived;
    int mFwRetries;
    QString mFwTxt;
    QString mHwTxt;
    bool mIsUploadingFw;

    // Connections
    conn_t mLastConnType;

#ifdef HAS_SERIALPORT
    QSerialPort *mSerialPort;
    QString mLastSerialPort;
    int mLastSerialBaud;
#endif

    QTcpSocket *mTcpSocket;
    bool mTcpConnected;
    QString mLastTcpServer;
    int mLastTcpPort;

    bool mSendCanBefore = false;
    int mCanIdBefore = 0;
    bool mWasConnected;
    bool mAutoconnectOngoing;
    double mAutoconnectProgress;

    void updateFwRx(bool fwRx);

};

#endif // VESCINTERFACE_H
