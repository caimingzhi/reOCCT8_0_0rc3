#include <Standard_Boolean.hpp>

static bool Blend_traceDRAWSECT = false;

void Blend_SettraceDRAWSECT(const bool b)
{
  Blend_traceDRAWSECT = b;
}

bool Blend_GettraceDRAWSECT()
{
  return Blend_traceDRAWSECT;
}

static bool Blend_contextNOTESTDEFL = false;

void Blend_SetcontextNOTESTDEFL(const bool b)
{
  Blend_contextNOTESTDEFL = b;
}

bool Blend_GetcontextNOTESTDEFL()
{
  return Blend_contextNOTESTDEFL;
}
