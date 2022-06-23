#pragma once
#include "Public_Header.h"

QT_BEGIN_NAMESPACE
class c_Jaka_Monitor;
QT_END_NAMESPACE

class c_Jaka_120_Monitor : public c_Jaka_Monitor
{
	Q_OBJECT
public:
	explicit c_Jaka_120_Monitor(c_Jaka_Monitor *parent = nullptr);
	~c_Jaka_120_Monitor();
	public slots:
	//虚函数的多态
	virtual void Connect();
};
