#pragma once

#include "BasicShader.h"

class LineShader : public BasicShader
{
public :
	LineShader();
private:
	void getUniforms() override;
};