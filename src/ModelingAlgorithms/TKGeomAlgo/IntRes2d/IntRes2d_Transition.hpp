#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <IntRes2d_Position.hpp>
#include <IntRes2d_TypeTrans.hpp>

enum IntRes2d_Situation
{
  IntRes2d_Inside,
  IntRes2d_Outside,
  IntRes2d_Unknown
};

class IntRes2d_Transition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntRes2d_Transition();

  IntRes2d_Transition(const bool               Tangent,
                      const IntRes2d_Position  Pos,
                      const IntRes2d_TypeTrans Type);

  IntRes2d_Transition(const bool               Tangent,
                      const IntRes2d_Position  Pos,
                      const IntRes2d_Situation Situ,
                      const bool               Oppos);

  IntRes2d_Transition(const IntRes2d_Position Pos);

  void SetValue(const bool Tangent, const IntRes2d_Position Pos, const IntRes2d_TypeTrans Type);

  void SetValue(const bool               Tangent,
                const IntRes2d_Position  Pos,
                const IntRes2d_Situation Situ,
                const bool               Oppos);

  void SetValue(const IntRes2d_Position Pos);

  void SetPosition(const IntRes2d_Position Pos);

  IntRes2d_Position PositionOnCurve() const;

  IntRes2d_TypeTrans TransitionType() const;

  bool IsTangent() const;

  IntRes2d_Situation Situation() const;

  bool IsOpposite() const;

private:
  bool               tangent;
  IntRes2d_Position  posit;
  IntRes2d_TypeTrans typetra;
  IntRes2d_Situation situat;
  bool               oppos;
};

#include <Standard_DomainError.hpp>

std::ostream& operator<<(std::ostream&, IntRes2d_Transition&);

inline IntRes2d_Transition::IntRes2d_Transition(const bool               Tangent,
                                                const IntRes2d_Position  Pos,
                                                const IntRes2d_TypeTrans Type)
    :

      tangent(Tangent),
      posit(Pos),
      typetra(Type),
      situat(IntRes2d_Unknown),
      oppos(false)

{
}

inline IntRes2d_Transition::IntRes2d_Transition(const bool               Tangent,
                                                const IntRes2d_Position  Pos,
                                                const IntRes2d_Situation Situ,
                                                const bool               Oppos)
    : tangent(Tangent),
      posit(Pos),
      typetra(IntRes2d_Touch),
      situat(Situ),
      oppos(Oppos)
{
}

inline IntRes2d_Transition::IntRes2d_Transition(const IntRes2d_Position Pos)
    :

      tangent(true),
      posit(Pos),
      typetra(IntRes2d_Undecided),
      situat(IntRes2d_Unknown),
      oppos(false)
{
}

inline void IntRes2d_Transition::SetValue(const bool               Tangent,
                                          const IntRes2d_Position  Pos,
                                          const IntRes2d_TypeTrans Type)
{

  tangent = Tangent;
  posit   = Pos;
  typetra = Type;
}

inline void IntRes2d_Transition::SetValue(const bool               Tangent,
                                          const IntRes2d_Position  Pos,
                                          const IntRes2d_Situation Situ,
                                          const bool               Oppos)
{

  tangent = Tangent;
  posit   = Pos;
  typetra = IntRes2d_Touch;
  situat  = Situ;
  oppos   = Oppos;
}

inline void IntRes2d_Transition::SetValue(const IntRes2d_Position Pos)
{

  posit   = Pos;
  typetra = IntRes2d_Undecided;
}

inline void IntRes2d_Transition::SetPosition(const IntRes2d_Position Pos)
{

  posit = Pos;
}

inline IntRes2d_Position IntRes2d_Transition::PositionOnCurve() const
{

  return posit;
}

inline IntRes2d_TypeTrans IntRes2d_Transition::TransitionType() const
{

  return typetra;
}

inline bool IntRes2d_Transition::IsTangent() const
{

  if (typetra == IntRes2d_Undecided)
  {
    throw Standard_DomainError();
  }
  return tangent;
}

inline IntRes2d_Situation IntRes2d_Transition::Situation() const
{

  if (typetra != IntRes2d_Touch)
  {
    throw Standard_DomainError();
  }
  return situat;
}

inline bool IntRes2d_Transition::IsOpposite() const
{

  if (typetra != IntRes2d_Touch)
  {
    throw Standard_DomainError();
  }
  return oppos;
}
