#include "GuiShader.h"

namespace gui
{

GuiShader::GuiShader(bool isCreate/* = false*/ ) :
	ShaderProgram( isCreate )
{
}

void GuiShader::use() const
{
	ShaderProgram::use();
	glDisable( GL_CULL_FACE );
}

} // gui