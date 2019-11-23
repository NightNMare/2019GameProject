#include "stdafx.h"
#include "SaveObject.h"


SaveObject::SaveObject():GameObject(L"save.png"), col(*transform, 32.0f, 32.0f)
{
}


SaveObject::~SaveObject()
{
}
