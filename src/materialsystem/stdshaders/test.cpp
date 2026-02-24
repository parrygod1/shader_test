// Includes for all shaders
#include "BaseVSShader.h"
#include "cpp_shader_constant_register_map.h"
#include "shaderapi/ishaderapi.h"
#include "vtf/vtf.h"

// Includes for PS30
#include "test_ps30.inc"
#include "test_vs30.inc"

// Define the shader name as it appears in the .vmt
BEGIN_VS_SHADER(TestShader, "Helpful description of my shader")

// 1. Setup Parameters (Variables the .vmt can use)

BEGIN_SHADER_PARAMS;
SHADER_PARAM(BASETEXTURE, SHADER_PARAM_TYPE_TEXTURE, "shadertest/BaseTexture", "The base texture")

// This creates $color in the .vmt
SHADER_PARAM(COLOR, SHADER_PARAM_TYPE_COLOR, "[1 1 1 1]", "The tint color")

// This creates $is_active in the .vmt (Integers are often used as booleans)
SHADER_PARAM(IS_ACTIVE, SHADER_PARAM_TYPE_INTEGER, "1", "Toggle the pulse effect")

END_SHADER_PARAMS;
// 2. Initialize Parameters
SHADER_INIT_PARAMS()
{
    // Set default values or handle missing parameters here
}

// 3. Initialize Shader
SHADER_INIT
{
    // Tell the engine to load the texture into memory
    if (params[BASETEXTURE]->IsDefined())
    {
        LoadTexture(BASETEXTURE);
    }

    if (!params[COLOR]->IsDefined())
    {
        // Set to black error color.
        params[COLOR]->SetVecValue(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

bool NeedsFullFrameBufferTexture(IMaterialVar **params, bool bCheckSpecificToThisFrame /* = true */) const
{
    return true;
}

// 4. Draw the Shader
SHADER_DRAW
{
    // Define the "Pass"
    SHADOW_STATE
    {
        int flags = VERTEX_POSITION | VERTEX_TEXCOORD_SIZE(0, 2);
        pShaderShadow->VertexShaderVertexFormat(flags, 1, 0, 0);

        // We don't need to write to the depth buffer.
        pShaderShadow->EnableDepthWrites(false);

        // Enable the base texture sampler
        pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);

        // Standard vertex format (Position and TexCoord)

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

        // 2. Handle the $color parameter
        float color[4] = {1.0, 1.0, 1.0, 1.0};        // Default
        params[COLOR]->GetLinearVecValue(color, 3);   // Pull RGB from the VMT $color
        pShaderAPI->SetPixelShaderConstant(1, color); // Send to register c2

        /*
        // 3. Handle $is_active
        // We check the VMT value and send a 1 or 0 to Pixel Shader Register 1 (c1)
        float isActive = params[IS_ACTIVE]->GetStringValue()[0] ? 1.0f : 0.0f;
        float activeVec[4] = {isActive, 0, 0, 0};
        pShaderAPI->SetPixelShaderConstant(1, activeVec);
*/
        /*
        *
        // 4. Send Time to Register 0 (c0)
        float timeVec[4] = {pShaderAPI->CurrentTime(), 0, 0, 0};
        pShaderAPI->SetPixelShaderConstant(0, timeVec);
        */

        DECLARE_DYNAMIC_PIXEL_SHADER(test_ps30);
        SET_DYNAMIC_PIXEL_SHADER(test_ps30);
    }

    Draw();
}

END_SHADER