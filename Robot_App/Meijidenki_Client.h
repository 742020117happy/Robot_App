/*************************************************************************************************************************************************
**Copyright(C), 2020-2025, bjtds.
**Version:2.0
**Author: dz
**Date:2021.2.1
**Description:
**Others:                         "Meijidenki_Client"
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

class c_Meijidenki_Client : public QObject
{
	Q_OBJECT

public:
	c_Meijidenki_Client(QObject * parent = nullptr);
	~c_Meijidenki_Client();

	public slots:
	void Init();//子线程初始化
	void Connect_Device(int id, QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write(quint32 value); //写Json数据

signals:
	void Connect_Done();//连接到服务器完成
	void Disconnect_Done();//断开连接完成
	void Connect_Error();//连接到服务器失败
	void Disconnect_Error();//断开连接失败
	void Read_Json_Done(QJsonObject value);//读Json完成
	void Write_Done(); //写完成
	void Read_Json_Error();//读错误
	void Write_Error(); //写错误
	void Status(QString state);//通讯状态

private:
	int m_device_id = 99;
	QJsonObject m_Value;

	private slots :
	void Read_Json(QVariant db);//读Json数据
	void State_Changed(qint32 _cid, quint32 _state_code);//状态改变
	QJsonObject Meijidenki_LDBCONFIG_Decoding(LIM_HEAD *lim);
	QJsonObject Meijidenki_LMD_Decoding(LIM_HEAD *lim);
	QJsonObject Meijidenki_LMD_RSSI_Decoding(LIM_HEAD *lim);
	QJsonObject Meijidenki_FMSIG_Decoding(LIM_HEAD *lim);
	QJsonObject Meijidenki_IOSTATUS_Decoding(LIM_HEAD *lim);
	QString Meijidenki_ALARM_Decoding(LIM_HEAD *lim);
	QString Meijidenki_DISALARM_Decoding(LIM_HEAD *lim);
};