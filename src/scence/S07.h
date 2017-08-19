#pragma once

#include "SBase.h"


class S07 : public SBase
{
public:
	S07();

	inline string getScenceName() override { return "S07"; };
#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion


};