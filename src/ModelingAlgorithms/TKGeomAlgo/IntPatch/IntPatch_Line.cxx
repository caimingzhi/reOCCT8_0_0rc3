

#include <IntPatch_Line.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IntPatch_Line, Standard_Transient)

IntPatch_Line::IntPatch_Line(const bool              Tang,
                             const IntSurf_TypeTrans Trans1,
                             const IntSurf_TypeTrans Trans2)
    : tg(Tang),
      tS1(Trans1),
      tS2(Trans2),
      sit1(IntSurf_Unknown),
      sit2(IntSurf_Unknown),
      uS1(false),
      vS1(false),
      uS2(false),
      vS2(false)
{
}

IntPatch_Line::IntPatch_Line(const bool              Tang,
                             const IntSurf_Situation Situ1,
                             const IntSurf_Situation Situ2)
    : tg(Tang),
      tS1(IntSurf_Touch),
      tS2(IntSurf_Touch),
      sit1(Situ1),
      sit2(Situ2),
      uS1(false),
      vS1(false),
      uS2(false),
      vS2(false)
{
}

IntPatch_Line::IntPatch_Line(const bool Tang)
    : tg(Tang),
      tS1(IntSurf_Undecided),
      tS2(IntSurf_Undecided),
      sit1(IntSurf_Unknown),
      sit2(IntSurf_Unknown),
      uS1(false),
      vS1(false),
      uS2(false),
      vS2(false)
{
}
