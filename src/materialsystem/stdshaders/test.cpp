#include "BaseVSShader.h"
#include "cpp_shader_constant_register_map.h"
#include "shaderapi/ishaderapi.h"
#include "vtf/vtf.h"

#include "test_ps30.inc"
#include "test_vs30.inc"

BEGIN_VS_SHADER(TestShader, "")

BEGIN_SHADER_PARAMS
SHADER_PARAM(BASETEXTURE, SHADER_PARAM_TYPE_TEXTURE, "shadertest/BaseTexture", "The base texture")
END_SHADER_PARAMS
SHADER_INIT_PARAMS()
{
}

SHADER_INIT
{
    if (params[BASETEXTURE]->IsDefined())
    {
        LoadTexture(BASETEXTURE);
    }
}

bool NeedsFullFrameBufferTexture(IMaterialVar **params, bool bCheckSpecificToThisFrame /* = true */) const
{
    return true;
}

SHADER_DRAW
{
    SHADOW_STATE
    {
        int flags = VERTEX_POSITION | VERTEX_TEXCOORD_SIZE(0, 2);
        pShaderShadow->VertexShaderVertexFormat(flags, 1, 0, 0);

        pShaderShadow->EnableDepthWrites(false);

        pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);

        DECLARE_STATIC_PIXEL_SHADER(test_ps30);
        SET_STATIC_PIXEL_SHADER(test_ps30);

        DECLARE_STATIC_VERTEX_SHADER(test_vs30);
        SET_STATIC_VERTEX_SHADER(test_vs30);
    }
    DYNAMIC_STATE
    {
        BindTexture(SHADER_SAMPLER0, BASETEXTURE, 0);
        SetVertexShaderTextureTransform(VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, BASETEXTURETRANSFORM);

        DECLARE_DYNAMIC_VERTEX_SHADER(test_vs30);
        SET_DYNAMIC_VERTEX_SHADER(test_vs30);

        DECLARE_DYNAMIC_PIXEL_SHADER(test_ps30);
        SET_DYNAMIC_PIXEL_SHADER(test_ps30);
    }

    Draw();
}

END_SHADER