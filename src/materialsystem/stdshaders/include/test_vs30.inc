// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH

#pragma once
#include "shaderlib/cshader.h"
class test_vs30_Static_Index
{
public:
	test_vs30_Static_Index(  )
	{
	}

	int GetIndex() const
	{
		return 0;
	}
};

#define shaderStaticTest_test_vs30 1


class test_vs30_Dynamic_Index
{
public:
	test_vs30_Dynamic_Index(  )
	{
	}

	int GetIndex() const
	{
		return 0;
	}
};

#define shaderDynamicTest_test_vs30 1

