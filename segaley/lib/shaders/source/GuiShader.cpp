#include "GuiShader.h"

GuiShader::GuiShader( bool isCreate/* = false*/ ) :
	ShaderProgram( isCreate )
{
}

void GuiShader::use() const
{
	ShaderProgram::use();
	glDisable( GL_CULL_FACE );
}
