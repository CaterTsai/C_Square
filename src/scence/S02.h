#pragma once

#include "SBase.h"


class S02 : public SBase
{
public:
	S02();

	inline string getScenceName() override { return "S02"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};