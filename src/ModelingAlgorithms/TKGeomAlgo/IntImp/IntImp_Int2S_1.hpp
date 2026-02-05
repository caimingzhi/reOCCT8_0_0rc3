#include <StdFail_NotDone.hpp>
#include <StdFail_UndefinedDerivative.hpp>
#include <Standard_DomainError.hpp>

inline bool IntImp_Int2S::IsDone() const
{
  return done;
}

inline bool IntImp_Int2S::IsEmpty() const
{
  if (!done)
    throw StdFail_NotDone(" IntImp_Int2S::IsEmpty() ");
  return empty;
}

inline const IntSurf_PntOn2S& IntImp_Int2S::Point() const
{
  if (!done)
    throw StdFail_NotDone(" IntImp_Int2S::Point() ");
  if (empty)
    throw Standard_DomainError(" IntImp_Int2S::Point() ");
  return pint;
}

inline bool IntImp_Int2S::IsTangent() const
{

  if (!done)
    throw StdFail_NotDone(" IntImp_Int2S::IsTangent () ");
  if (empty)
    throw Standard_DomainError(" IntImp_Int2S::IsTangent () ");
  return tangent;
}

inline const gp_Dir& IntImp_Int2S::Direction() const
{

  if (!done)
    throw StdFail_NotDone(" IntImp_Int2S::Direction () ");
  if (empty)
    throw Standard_DomainError(" IntImp_Int2S::Direction () ");
  if (tangent)
    throw StdFail_UndefinedDerivative(" IntImp_Int2S::Direction () ");
  return d3d;
}

inline const gp_Dir2d& IntImp_Int2S::DirectionOnS1() const
{

  if (!done)
    throw StdFail_NotDone(" IntImp_Int2S::DirectionOnS1 () ");
  if (empty)
    throw Standard_DomainError(" IntImp_Int2S::DirectionOnS1 () ");
  if (tangent)
    throw StdFail_UndefinedDerivative(" IntImp_Int2S::DirectionOnS1 () ");
  return d2d1;
}

inline const gp_Dir2d& IntImp_Int2S::DirectionOnS2() const
{

  if (!done)
    throw StdFail_NotDone(" IntImp_Int2S::DirectionOnS2 () ");
  if (empty)
    throw Standard_DomainError(" IntImp_Int2S::DirectionOnS2 () ");
  if (tangent)
    throw StdFail_UndefinedDerivative(" IntImp_Int2S::DirectionOnS2 () ");
  return d2d2;
}

inline IntImp_TheFunction& IntImp_Int2S::Function()
{
  return myZerParFunc;
}

inline IntSurf_PntOn2S& IntImp_Int2S::ChangePoint()
{
  return pint;
}
