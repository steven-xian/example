﻿// lib_add.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

extern "C" {
	__declspec(dllexport)  int /*__cdecl*/ add(int a, int b);
}