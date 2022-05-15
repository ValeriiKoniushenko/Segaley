#include "MainShader.h"

MainShader::MainShader( bool isCreate/* = false*/ ) :
	ShaderProgram( isCreate )
{ }

void MainShader::use() const
{
	ShaderProgram::use();
	glEnable( GL_CULL_FACE );
	glCullFace( GL_FRONT );
}
