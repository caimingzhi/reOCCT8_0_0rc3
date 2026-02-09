#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Vector.hpp>
#include <math_Matrix.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class math_Uzawa
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_Uzawa(const math_Matrix& Cont,
                             const math_Vector& Secont,
                             const math_Vector& StartingPoint,
                             const double       EpsLix       = 1.0e-06,
                             const double       EpsLic       = 1.0e-06,
                             const int          NbIterations = 500);

  Standard_EXPORT math_Uzawa(const math_Matrix& Cont,
                             const math_Vector& Secont,
                             const math_Vector& StartingPoint,
                             const int          Nci,
                             const int          Nce,
                             const double       EpsLix       = 1.0e-06,
                             const double       EpsLic       = 1.0e-06,
                             const int          NbIterations = 500);

  bool IsDone() const;

  const math_Vector& Value() const;

  const math_Vector& InitialError() const;

  Standard_EXPORT void Duale(math_Vector& V) const;

  const math_Vector& Error() const;

  int NbIterations() const;

  const math_Matrix& InverseCont() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  Standard_EXPORT void Perform(const math_Matrix& Cont,
                               const math_Vector& Secont,
                               const math_Vector& StartingPoint,
                               const int          Nci,
                               const int          Nce,
                               const double       EpsLix       = 1.0e-06,
                               const double       EpsLic       = 1.0e-06,
                               const int          NbIterations = 500);

private:
  math_Vector Resul;
  math_Vector Erruza;
  math_Vector Errinit;
  math_Vector Vardua;
  math_Matrix CTCinv;
  int         NbIter;
  bool        Done;
};

#include <StdFail_NotDone.hpp>

inline bool math_Uzawa::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Uzawa& U)
{
  U.Dump(o);
  return o;
}

inline const math_Vector& math_Uzawa::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Resul;
}

inline const math_Vector& math_Uzawa::InitialError() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Errinit;
}

inline const math_Vector& math_Uzawa::Error() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Erruza;
}

inline int math_Uzawa::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return NbIter;
}

inline const math_Matrix& math_Uzawa::InverseCont() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return CTCinv;
}
