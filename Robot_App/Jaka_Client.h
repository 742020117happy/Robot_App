/*************************************************************************************************************************************************
**Copyright(C), 2020-2025, bjtds.
**Version:2.0
**Author: dz
**Date:2021.2.1
**Description:
**Others:                              "TcpClient"
							  ____________________________
			   connectDevice->|REQ          |        DONE|->Done
			disconnectDevice->|DISCONNECT   |       ERROR|->Error
				  read/write->|MB_MODE      |      STATUS|->status
					 ip,port->|CONNECT      |            |
					  value ->|DATA         |            |
							  ----------------------------
*************************************************************************************************************************************************/
#pragma once
#include "Public_Header.h"

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
QT_END_NAMESPACE

class c_Jaka_Client : public QObject
{
	Q_OBJECT
public:
	explicit c_Jaka_Client(QObject *parent = nullptr);
	~c_Jaka_Client();

	public slots:
	void Init();//子线程初始化
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Json(QJsonObject value); //写Json数据

signals:
	void Connect_Done();//连接到服务器完成
	void Disconnect_Done();//断开连接完成
	void Read_Json_Done(QJsonObject value);//读Json完成
	void Write_Json_Done(); //写完成
	void Read_Json_Error();//读错误
	void Write_Json_Error(); //写错误
	void Status(int state);//通讯状态

private:
	QTcpSocket *m_Socket;//通讯对象

	private slots:
	void Read_Json();//读Json数据
	void State_Changed();//状态改变
};

