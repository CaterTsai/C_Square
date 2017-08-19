#pragma once

#include "SBase.h"


class S11 : public SBase
{
public:
	S11();

	inline string getScenceName() override { return "S11"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};