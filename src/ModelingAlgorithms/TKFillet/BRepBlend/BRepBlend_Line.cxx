

#include <BRepBlend_Line.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepBlend_Line, Standard_Transient)

BRepBlend_Line::BRepBlend_Line()
    : tras1(IntSurf_Undecided),
      tras2(IntSurf_Undecided),
      hass1(false),
      hass2(false)
{
}

void BRepBlend_Line::Clear()
{
  seqpt.Clear();
  hass1 = false;
  hass2 = false;
  tras1 = IntSurf_Undecided;
  tras2 = IntSurf_Undecided;
}

void BRepBlend_Line::Set(const IntSurf_TypeTrans TranS1, const IntSurf_TypeTrans TranS2)
{
  hass1 = true;
  hass2 = true;
  tras1 = TranS1;
  tras2 = TranS2;
}

void BRepBlend_Line::Set(const IntSurf_TypeTrans Trans)
{
  hass1 = true;
  hass2 = false;
  tras1 = Trans;
}
