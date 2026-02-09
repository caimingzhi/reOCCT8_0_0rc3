#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Ax1.hpp>

enum BRepFeat_Status
{
  BRepFeat_NoError,
  BRepFeat_InvalidPlacement,
  BRepFeat_HoleTooLong
};

#include <TopoDS_Face.hpp>
#include <BRepFeat_Builder.hpp>

#ifdef Status
  #undef Status
#endif

class BRepFeat_MakeCylindricalHole : public BRepFeat_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_MakeCylindricalHole();

  void Init(const gp_Ax1& Axis);

  void Init(const TopoDS_Shape& S, const gp_Ax1& Axis);

  Standard_EXPORT void Perform(const double Radius);

  Standard_EXPORT void Perform(const double Radius,
                               const double PFrom,
                               const double PTo,
                               const bool   WithControl = true);

  Standard_EXPORT void PerformThruNext(const double Radius, const bool WithControl = true);

  Standard_EXPORT void PerformUntilEnd(const double Radius, const bool WithControl = true);

  Standard_EXPORT void PerformBlind(const double Radius,
                                    const double Length,
                                    const bool   WithControl = true);

  BRepFeat_Status Status() const;

  Standard_EXPORT void Build();

protected:
  using BRepFeat_Builder::Perform;

private:
  Standard_EXPORT BRepFeat_Status Validate();

  gp_Ax1          myAxis;
  bool            myAxDef;
  BRepFeat_Status myStatus;
  bool            myIsBlind;
  bool            myValidate;
  TopoDS_Face     myTopFace;
  TopoDS_Face     myBotFace;
};

inline BRepFeat_MakeCylindricalHole::BRepFeat_MakeCylindricalHole()
    : myAxDef(false),
      myStatus(BRepFeat_NoError),
      myIsBlind(false),
      myValidate(false)
{
}

inline void BRepFeat_MakeCylindricalHole::Init(const gp_Ax1& Axis)
{
  myAxis  = Axis;
  myAxDef = true;
}

inline void BRepFeat_MakeCylindricalHole::Init(const TopoDS_Shape& S, const gp_Ax1& Axis)
{
  BRepFeat_Builder::Init(S);
  myAxis  = Axis;
  myAxDef = true;
}

inline BRepFeat_Status BRepFeat_MakeCylindricalHole::Status() const
{
  return myStatus;
}
