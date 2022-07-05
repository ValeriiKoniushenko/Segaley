#pragma once

#include "ShaderProgram.h"

namespace gui
{

class GuiShader final : public ShaderProgram
{
public:
	GuiShader(bool isCreate = false );
	void use() const;
};

} // gui