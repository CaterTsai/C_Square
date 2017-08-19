#pragma once

#include "SBase.h"


class S01 : public SBase
{
public:
	S01();

	inline string getScenceName() override{ return "S01"; };

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion

};