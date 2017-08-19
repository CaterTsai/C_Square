#pragma once

#include "SBase.h"


class SIdle : public SBase
{
public:
	SIdle();

	inline string getScenceName() override { return "SIdle"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};