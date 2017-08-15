#pragma once

#include "SBase.h"


class S06 : public SBase
{
public:
	S06();

	void update(float delta) override;
	void draw() override;
	void start() override;
	void stop() override;
	
	void control(eCtrlType ctrl, int value = 0) override;

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;
#pragma endregion


};