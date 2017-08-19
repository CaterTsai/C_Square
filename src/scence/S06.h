#pragma once

#include "SBase.h"


class S06 : public SBase
{
public:
	S06();

	inline string getScenceName() override { return "S06"; };
#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion


};