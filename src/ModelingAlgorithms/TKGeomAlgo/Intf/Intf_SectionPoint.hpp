#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <Intf_PIType.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt2d;

class Intf_SectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT const gp_Pnt& Pnt() const;

  double ParamOnFirst() const;

  double ParamOnSecond() const;

  Intf_PIType TypeOnFirst() const;

  Intf_PIType TypeOnSecond() const;

  Standard_EXPORT void InfoFirst(Intf_PIType& Dim, int& Add1, int& Add2, double& Param) const;

  Standard_EXPORT void InfoFirst(Intf_PIType& Dim, int& Addr, double& Param) const;

  Standard_EXPORT void InfoSecond(Intf_PIType& Dim, int& Add1, int& Add2, double& Param) const;

  Standard_EXPORT void InfoSecond(Intf_PIType& Dim, int& Addr, double& Param) const;

  Standard_EXPORT double Incidence() const;

  bool IsEqual(const Intf_SectionPoint& Other) const;

  bool operator==(const Intf_SectionPoint& Other) const { return IsEqual(Other); }

  Standard_EXPORT bool IsOnSameEdge(const Intf_SectionPoint& Other) const;

  Standard_EXPORT Intf_SectionPoint();

  Standard_EXPORT Intf_SectionPoint(const gp_Pnt&     Where,
                                    const Intf_PIType DimeO,
                                    const int         AddrO1,
                                    const int         AddrO2,
                                    const double      ParamO,
                                    const Intf_PIType DimeT,
                                    const int         AddrT1,
                                    const int         AddrT2,
                                    const double      ParamT,
                                    const double      Incid);

  Standard_EXPORT Intf_SectionPoint(const gp_Pnt2d&   Where,
                                    const Intf_PIType DimeO,
                                    const int         AddrO1,
                                    const double      ParamO,
                                    const Intf_PIType DimeT,
                                    const int         AddrT1,
                                    const double      ParamT,
                                    const double      Incid);

  Standard_EXPORT void Merge(Intf_SectionPoint& Other);

  Standard_EXPORT void Dump(const int Indent) const;

private:
  gp_Pnt      myPnt;
  Intf_PIType DimenObje;
  int         IndexO1;
  int         IndexO2;
  double      ParamObje;
  Intf_PIType DimenTool;
  int         IndexT1;
  int         IndexT2;
  double      ParamTool;
  double      Incide;
};

inline double Intf_SectionPoint::ParamOnFirst() const
{
  return (IndexO2 - 1) + ParamObje;
}

inline double Intf_SectionPoint::ParamOnSecond() const
{
  return (IndexT2 - 1) + ParamTool;
}

inline Intf_PIType Intf_SectionPoint::TypeOnFirst() const
{
  return DimenObje;
}

inline Intf_PIType Intf_SectionPoint::TypeOnSecond() const
{
  return DimenTool;
}

inline bool Intf_SectionPoint::IsEqual(const Intf_SectionPoint& Other) const
{
  return (DimenObje == Other.DimenObje && IndexO1 == Other.IndexO1 && IndexO2 == Other.IndexO2
          && DimenTool == Other.DimenTool && IndexT1 == Other.IndexT1 && IndexT2 == Other.IndexT2);
}
