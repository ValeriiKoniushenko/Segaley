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
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

} // gui