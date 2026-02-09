#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <gp_Vec.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <gp_Pnt.hpp>

class LocOpe_LinearForm
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_LinearForm();

  LocOpe_LinearForm(const TopoDS_Shape& Base,
                    const gp_Vec&       V,
                    const gp_Pnt&       Pnt1,
                    const gp_Pnt&       Pnt2);

  LocOpe_LinearForm(const TopoDS_Shape& Base,
                    const gp_Vec&       V,
                    const gp_Vec&       Vectra,
                    const gp_Pnt&       Pnt1,
                    const gp_Pnt&       Pnt2);

  Standard_EXPORT void Perform(const TopoDS_Shape& Base,
                               const gp_Vec&       V,
                               const gp_Pnt&       Pnt1,
                               const gp_Pnt&       Pnt2);

  Standard_EXPORT void Perform(const TopoDS_Shape& Base,
                               const gp_Vec&       V,
                               const gp_Vec&       Vectra,
                               const gp_Pnt&       Pnt1,
                               const gp_Pnt&       Pnt2);

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shapes(const TopoDS_Shape& S) const;

private:
  Standard_EXPORT void IntPerf();

  TopoDS_Shape myBase;
  gp_Vec       myVec;
  gp_Vec       myTra;
  bool         myDone;
  bool         myIsTrans;
  TopoDS_Shape myRes;
  TopoDS_Shape myFirstShape;
  TopoDS_Shape myLastShape;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  gp_Pnt                                                                                     myPnt1;
  gp_Pnt                                                                                     myPnt2;
};

inline LocOpe_LinearForm::LocOpe_LinearForm()
    : myDone(false),
      myIsTrans(false)
{
}

inline LocOpe_LinearForm::LocOpe_LinearForm(const TopoDS_Shape& Base,
                                            const gp_Vec&       V,
                                            const gp_Pnt&       Pnt1,
                                            const gp_Pnt&       Pnt2)

{
  Perform(Base, V, Pnt1, Pnt2);
}

inline LocOpe_LinearForm::LocOpe_LinearForm(const TopoDS_Shape& Base,
                                            const gp_Vec&       V,
                                            const gp_Vec&       Vectra,
                                            const gp_Pnt&       Pnt1,
                                            const gp_Pnt&       Pnt2)

{
  Perform(Base, V, Vectra, Pnt1, Pnt2);
}
