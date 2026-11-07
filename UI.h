/*
* +-------------------------------------+
* File   : ‘SUI‚ÌŠî’êƒNƒ‰ƒX[UI.h]
* Author : ’¾„Œ«
* Date   : 2026/11/01
*
*
*
* +-------------------------------------+
*/
#pragma once

class UI
{
public:
	virtual void Initialize(void) = 0;
	virtual void Finalize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) const = 0;

private:

};
