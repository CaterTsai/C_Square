#pragma once

#include "SBase.h"


class S04 : public SBase
{
public:
	S04();

	inline string getScenceName() override { return "S04"; };
#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};