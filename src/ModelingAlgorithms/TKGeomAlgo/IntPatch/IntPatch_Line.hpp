#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IntPatch_IType.hpp>
#include <IntSurf_TypeTrans.hpp>
#include <IntSurf_Situation.hpp>
#include <Standard_Transient.hpp>

class IntPatch_Line : public Standard_Transient
{

public:
  void SetValue(const bool Uiso1, const bool Viso1, const bool Uiso2, const bool Viso2);

  IntPatch_IType ArcType() const;

  bool IsTangent() const;

  IntSurf_TypeTrans TransitionOnS1() const;

  IntSurf_TypeTrans TransitionOnS2() const;

  IntSurf_Situation SituationS1() const;

  IntSurf_Situation SituationS2() const;

  bool IsUIsoOnS1() const;

  bool IsVIsoOnS1() const;

  bool IsUIsoOnS2() const;

  bool IsVIsoOnS2() const;

  DEFINE_STANDARD_RTTIEXT(IntPatch_Line, Standard_Transient)

protected:
  Standard_EXPORT IntPatch_Line(const bool              Tang,
                                const IntSurf_TypeTrans Trans1,
                                const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_Line(const bool              Tang,
                                const IntSurf_Situation Situ1,
                                const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_Line(const bool Tang);

  IntPatch_IType typ;

private:
  bool              tg;
  IntSurf_TypeTrans tS1;
  IntSurf_TypeTrans tS2;
  IntSurf_Situation sit1;
  IntSurf_Situation sit2;
  bool              uS1;
  bool              vS1;
  bool              uS2;
  bool              vS2;
};

#include <Standard_DomainError.hpp>

inline void IntPatch_Line::SetValue(const bool Uiso1,
                                    const bool Viso1,
                                    const bool Uiso2,
                                    const bool Viso2)
{
  uS1 = Uiso1;
  vS1 = Viso1;
  uS2 = Uiso2;
  vS2 = Viso2;
}

inline IntPatch_IType IntPatch_Line::ArcType() const
{
  return typ;
}

inline bool IntPatch_Line::IsTangent() const
{

  return tg;
}

inline IntSurf_TypeTrans IntPatch_Line::TransitionOnS1() const
{

  return tS1;
}

inline IntSurf_TypeTrans IntPatch_Line::TransitionOnS2() const
{

  return tS2;
}

inline IntSurf_Situation IntPatch_Line::SituationS1() const
{

  if (tS1 != IntSurf_Touch)
  {
    throw Standard_DomainError();
  }
  return sit1;
}

inline IntSurf_Situation IntPatch_Line::SituationS2() const
{

  if (tS2 != IntSurf_Touch)
  {
    throw Standard_DomainError();
  }
  return sit2;
}

inline bool IntPatch_Line::IsUIsoOnS1() const
{

  return uS1;
}

inline bool IntPatch_Line::IsVIsoOnS1() const
{

  return vS1;
}

inline bool IntPatch_Line::IsUIsoOnS2() const
{

  return uS2;
}

inline bool IntPatch_Line::IsVIsoOnS2() const
{

  return vS2;
}
