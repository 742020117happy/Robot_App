#pragma once
#include "Public_Header.h"

QT_BEGIN_NAMESPACE
class c_Meijidenki_Remote;
QT_END_NAMESPACE

class c_Meijidenki_21_Remote : public c_Meijidenki_Remote
{
	Q_OBJECT
public:
	explicit c_Meijidenki_21_Remote(c_Meijidenki_Remote *parent = nullptr);
	~c_Meijidenki_21_Remote();
	public slots:
	//虚函数的多态
	virtual void Connect();
};

