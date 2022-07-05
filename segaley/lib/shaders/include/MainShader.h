#pragma once

#include "ShaderProgram.h"

class MainShader final : public ShaderProgram
{
public:
	MainShader( bool isCreate = false );
	void use() const;
};
