#pragma once
#include "Public_Header.h"

QT_BEGIN_NAMESPACE
class c_Hypersen_Remote;
QT_END_NAMESPACE

class c_Hypersen_30_Remote : public c_Hypersen_Remote
{
	Q_OBJECT
public:
	explicit c_Hypersen_30_Remote(c_Hypersen_Remote *parent = nullptr);
	~c_Hypersen_30_Remote();
	public slots:
	//虚函数的多态
	virtual void Connect();
};

