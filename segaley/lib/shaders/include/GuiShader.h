#include "ShaderProgram.h"

class GuiShader final : public ShaderProgram
{
public:
	GuiShader( bool isCreate = false );
	void use() const;
};
