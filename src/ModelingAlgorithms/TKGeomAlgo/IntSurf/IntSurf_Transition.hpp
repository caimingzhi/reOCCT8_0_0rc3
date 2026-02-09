#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <IntSurf_TypeTrans.hpp>
#include <IntSurf_Situation.hpp>

class IntSurf_Transition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntSurf_Transition();

  Standard_EXPORT IntSurf_Transition(const bool Tangent, const IntSurf_TypeTrans Type);

  Standard_EXPORT IntSurf_Transition(const bool              Tangent,
                                     const IntSurf_Situation Situ,
                                     const bool              Oppos);

  void SetValue(const bool Tangent, const IntSurf_TypeTrans Type);

  void SetValue(const bool Tangent, const IntSurf_Situation Situ, const bool Oppos);

  void SetValue();

  IntSurf_TypeTrans TransitionType() const;

  bool IsTangent() const;

  IntSurf_Situation Situation() const;

  bool IsOpposite() const;

private:
  bool              tangent;
  IntSurf_TypeTrans typetra;
  IntSurf_Situation situat;
  bool              oppos;
};

#include <Standard_DomainError.hpp>

inline void IntSurf_Transition::SetValue(const bool Tangent, const IntSurf_TypeTrans Type)
{
  tangent = Tangent;
  typetra = Type;
}

inline void IntSurf_Transition::SetValue(const bool              Tangent,
                                         const IntSurf_Situation Situ,
                                         const bool              Oppos)
{

  tangent = Tangent;
  typetra = IntSurf_Touch;
  situat  = Situ;
  oppos   = Oppos;
}

inline void IntSurf_Transition::SetValue()
{

  typetra = IntSurf_Undecided;
}

inline IntSurf_TypeTrans IntSurf_Transition::TransitionType() const
{

  return typetra;
}

inline bool IntSurf_Transition::IsTangent() const
{

  if (typetra == IntSurf_Undecided)
  {
    throw Standard_DomainError();
  }
  return tangent;
}

inline IntSurf_Situation IntSurf_Transition::Situation() const
{

  if (typetra != IntSurf_Touch)
  {
    throw Standard_DomainError();
  }
  return situat;
}

inline bool IntSurf_Transition::IsOpposite() const
{

  if (typetra != IntSurf_Touch)
  {
    throw Standard_DomainError();
  }
  return oppos;
}
