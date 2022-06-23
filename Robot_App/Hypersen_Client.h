/*************************************************************************************************************************************************
**Copyright(C), 2020-2025, bjtds.
**Version:2.0
**Author: dz
**Date:2021.2.1
**Description:
**Others:                         "Hypersen_Client"
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
using namespace std;
QT_END_NAMESPACE

class c_Hypersen_Client : public QObject
{
	Q_OBJECT

public:
	c_Hypersen_Client(QObject * parent = nullptr);
	~c_Hypersen_Client();

	public slots:
	void Init();//子线程初始化
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write(quint8 value); //写Json数据

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
	quint8 m_device_id = 99;
	uint8_t m_sdk_version[6] = { 0 };
	uint8_t m_device_version[6] = { 0 };
	char m_SN[64] = { 0 };
	quint8 m_group_id = 0;
	quint8 m_roi_number = 0;
	quint8 m_roi_id[8] = { 0 };
	quint8 m_roi_current_id = 0;
	quint16 m_roi_aver_distance = 0;
	quint16 m_roi_max_distance = 0;
	quint16 m_roi_min_distance = 0;
	quint16 m_roi_valid_aver_amp = 0;
	quint16 m_roi_all_aver_amp = 0;

	private slots:
	void Read_Json(quint8 id);//读Json数据
	void State_Changed(QString str);//状态改变
};