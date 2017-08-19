#pragma once

#include "SBase.h"


class S10 : public SBase
{
public:
	S10();

	inline string getScenceName() override { return "S10"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};