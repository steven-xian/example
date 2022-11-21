// lib_add.cpp: 定义应用程序的入口点。
//

#include "lib_add.h"

extern "C" __declspec(dllexport) int /*__cdecl*/ add(int a, int b)
{
	return (a + b);
}