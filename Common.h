#pragma once

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <vector>
#include <random>
#include <typeinfo>
#include <stdlib.h>
#include <crtdbg.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3d10.lib")

//Œx”ñ•\Ž¦
#pragma warning(disable : 4305)

#define SAFE_RELEASE(x) if(x){x->Release(); x = nullptr;}
#define SAFE_DELETE_ARRAY(x) if(x){delete[] x; x = nullptr;}
#define SAFE_DELETE(x) if(x) {delete x; x = nullptr;}
#define SAFE_FREE(x) if(x) {free(x); x = nullptr;}