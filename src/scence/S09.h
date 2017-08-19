#pragma once

#include "SBase.h"


class S09 : public SBase
{
public:
	S09();

	inline string getScenceName() override { return "S09"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};