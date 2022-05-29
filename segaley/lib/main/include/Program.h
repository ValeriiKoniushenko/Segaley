#pragma once

#include "MainShader.h"

class Program final
{
public:
	Program() = default;
	~Program() = default;
	Program( const Program& ) = delete;
	Program( Program&& ) = delete;
	Program& operator=( const Program& ) = delete;
	Program& operator=( Program&& ) = delete;

	void launch();

private:
	void preDraw();
	void draw();
	void postDraw();
	void setUpShaders();

private:
	MainShader program_;
	MainShader textProgram_;
};
