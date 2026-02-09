#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
class gp_Pln;

class IntAna_Int3Pln
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_Int3Pln();

  Standard_EXPORT IntAna_Int3Pln(const gp_Pln& P1, const gp_Pln& P2, const gp_Pln& P3);

  Standard_EXPORT void Perform(const gp_Pln& P1, const gp_Pln& P2, const gp_Pln& P3);

  bool IsDone() const;

  bool IsEmpty() const;

  const gp_Pnt& Value() const;

private:
  bool   done;
  bool   empt;
  gp_Pnt pnt;
};

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>

inline bool IntAna_Int3Pln::IsDone() const
{

  return done;
}

inline bool IntAna_Int3Pln::IsEmpty() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return empt;
}

inline const gp_Pnt& IntAna_Int3Pln::Value() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (empt)
  {
    throw Standard_DomainError();
  }
  return pnt;
}
