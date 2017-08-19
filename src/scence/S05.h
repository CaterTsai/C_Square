#pragma once

#include "SBase.h"


class S05 : public SBase
{
public:
	S05();

	inline string getScenceName() override { return "S05"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion


};