#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class IGESData_ParamCursor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_ParamCursor(const int num);

  Standard_EXPORT IGESData_ParamCursor(const int num, const int nb, const int size = 1);

  Standard_EXPORT void SetTerm(const int size, const bool autoadv = true);

  Standard_EXPORT void SetOne(const bool autoadv = true);

  Standard_EXPORT void SetXY(const bool autoadv = true);

  Standard_EXPORT void SetXYZ(const bool autoadv = true);

  Standard_EXPORT void SetAdvance(const bool advance);

  int Start() const;

  int Limit() const;

  int Count() const;

  int ItemSize() const;

  int TermSize() const;

  int Offset() const;

  bool Advance() const;

private:
  int  thestart;
  int  thelimit;
  int  thecount;
  int  theisize;
  int  theoffst;
  int  thetsize;
  bool theadv;
};

inline int IGESData_ParamCursor::Start() const
{
  return thestart;
}

inline int IGESData_ParamCursor::Limit() const
{
  return thelimit;
}

inline int IGESData_ParamCursor::Count() const
{
  return thecount;
}

inline int IGESData_ParamCursor::ItemSize() const
{
  return theisize;
}

inline int IGESData_ParamCursor::TermSize() const
{
  return thetsize;
}

inline int IGESData_ParamCursor::Offset() const
{
  return theoffst;
}

inline bool IGESData_ParamCursor::Advance() const
{
  return theadv;
}
