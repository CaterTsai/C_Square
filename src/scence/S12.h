#pragma once

#include "SBase.h"


class S12 : public SBase
{
public:
	S12();

	inline string getScenceName() override { return "S12"; };

#pragma region View
	//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};