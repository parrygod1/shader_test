#pragma once

// ficool2: reversed private interface

#include "ishaderapi.h"

struct ShaderRenderState_t;

#define SHADERSYSTEM_INTERFACE_VERSION "ShaderSystem002"

abstract_class IShaderSystem
{
public:
	virtual ShaderAPITextureHandle_t GetShaderAPITextureBindHandle( ITexture*, int, int ) = 0;
	virtual void BindTexture( Sampler_t, ITexture, int ) = 0;
	virtual void BindTexture( Sampler_t, Sampler_t, ITexture, int ) = 0;
	virtual void TakeSnapshot( ) = 0;
	virtual void DrawSnapshot( bool ) = 0;
	virtual bool IsUsingGraphics() const = 0;
	virtual bool CanUseEditorMaterials() const = 0;
};

abstract_class IShaderSystemInternal : public IShaderInit, public IShaderSystem
{
public:
	virtual void Init() = 0;
	virtual void Shutdown() = 0;
	virtual void ModInit() = 0;
	virtual void ModShutdown() = 0;
	virtual bool LoadShaderDLL( const char* pFilePath ) = 0;
	virtual void UnloadShaderDLL( const char* pFilePath ) = 0;
	virtual IShader* FindShader( char const* pName ) = 0;
	virtual const char* ShaderStateString( int ) const = 0;
	virtual int ShaderStateCount() const = 0;
	virtual void CreateDebugMaterials() = 0;
	virtual void CleanUpDebugMaterials() = 0;
	virtual void InitShaderParameters( IShader*, IMaterialVar**, const char* ) = 0;
	virtual void InitShaderInstance( IShader*, IMaterialVar**, const char*, const char* ) = 0;
	virtual bool InitRenderState( IShader*, int, IMaterialVar**, ShaderRenderState_t*, char const* ) = 0;
	virtual void CleanupRenderState( ShaderRenderState_t* ) = 0;
	virtual void DrawElements( IShader*, IMaterialVar**, ShaderRenderState_t*, VertexCompressionType_t, uint32 ) = 0;
	virtual int	 ShaderCount() const = 0;
	virtual int  GetShaders( int, int, IShader** ) const = 0;
};