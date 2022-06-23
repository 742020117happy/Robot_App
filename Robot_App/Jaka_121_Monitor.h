#pragma once
#include "Public_Header.h"

QT_BEGIN_NAMESPACE
class c_Jaka_Remote;
QT_END_NAMESPACE

class c_Jaka_121_Monitor : public c_Jaka_Remote
{
	Q_OBJECT
public:
	explicit c_Jaka_121_Monitor(c_Jaka_Remote *parent = nullptr);
	~c_Jaka_121_Monitor();
	public slots:
	//虚函数的多态
	virtual void Connect();
};
