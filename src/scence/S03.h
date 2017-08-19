#pragma once

#include "SBase.h"


class S03 : public SBase
{
public:
	S03();

	inline string getScenceName() override { return "S03"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};