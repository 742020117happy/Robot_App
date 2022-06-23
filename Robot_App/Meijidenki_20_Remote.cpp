﻿#pragma execution_character_set("utf-8")
#include "Meijidenki_20_Remote.h"

/*************************************************************************************************************************************************
**Function:    构造函数
**Others:      构造函数初始化在主线程实例化中完成，故在子线程中运行时，成员函数的初始化不能在构造函数中完成
*************************************************************************************************************************************************/
c_Meijidenki_20_Remote::c_Meijidenki_20_Remote(c_Meijidenki_Remote *parent) : c_Meijidenki_Remote(parent)
{

}
/*************************************************************************************************************************************************
**Function:    析构函数
*************************************************************************************************************************************************/
c_Meijidenki_20_Remote::~c_Meijidenki_20_Remote()
{
}
/*************************************************************************************************************************************************
**Function:    操作接口
*************************************************************************************************************************************************/
void c_Meijidenki_20_Remote::Connect()
{
	int id = c_Variable::g_Communicate_DB.value("Meijidenki_20_Id").toInt();
	QString ip = c_Variable::g_Communicate_DB.value("Meijidenki_20_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Meijidenki_20_Port").toInt();
	emit Connect_Device(id, ip, port);
}