#pragma once

#include "SBase.h"


class S08 : public SBase
{
public:
	S08();

	inline string getScenceName() override { return "S08"; };
#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion


private:
	ofImage _img;

};