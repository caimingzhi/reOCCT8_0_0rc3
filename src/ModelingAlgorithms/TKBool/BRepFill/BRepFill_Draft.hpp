#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Dir.hpp>
#include <Standard_Real.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Wire.hpp>
#include <GeomAbs_Shape.hpp>
#include <BRepFill_TransitionStyle.hpp>
#include <Standard_Boolean.hpp>
class BRepFill_DraftLaw;
class BRepFill_SectionLaw;
class Geom_Surface;
class Bnd_Box;

class BRepFill_Draft
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Draft(const TopoDS_Shape& Shape, const gp_Dir& Dir, const double Angle);

  Standard_EXPORT void SetOptions(const BRepFill_TransitionStyle Style    = BRepFill_Right,
                                  const double                   AngleMin = 0.01,
                                  const double                   AngleMax = 3.0);

  Standard_EXPORT void SetDraft(const bool IsInternal = false);

  Standard_EXPORT void Perform(const double LengthMax);

  Standard_EXPORT void Perform(const occ::handle<Geom_Surface>& Surface,
                               const bool                       KeepInsideSurface = true);

  Standard_EXPORT void Perform(const TopoDS_Shape& StopShape, const bool KeepOutSide = true);

  Standard_EXPORT bool IsDone() const;

  //! Returns the draft surface
  //! To have the complete shape
  //! you have to use the Shape() methode.
  Standard_EXPORT TopoDS_Shell Shell() const;

  //! Returns the list of shapes generated from the
  //! shape <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S);

  Standard_EXPORT TopoDS_Shape Shape() const;

private:
  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& Surf,
                            const double                     Length,
                            const Bnd_Box&                   Box);

  Standard_EXPORT void BuildShell(const occ::handle<Geom_Surface>& Surf,
                                  const bool                       KeepOutSide = false);

  Standard_EXPORT bool Fuse(const TopoDS_Shape& S, const bool KeepOutSide);

  Standard_EXPORT bool Sewing();

  gp_Dir                                         myDir;
  double                                         myAngle;
  double                                         angmin;
  double                                         angmax;
  double                                         myTol;
  occ::handle<BRepFill_DraftLaw>                 myLoc;
  occ::handle<BRepFill_SectionLaw>               mySec;
  occ::handle<NCollection_HArray2<TopoDS_Shape>> mySections;
  occ::handle<NCollection_HArray2<TopoDS_Shape>> myFaces;
  NCollection_List<TopoDS_Shape>                 myGenerated;
  TopoDS_Shape                                   myShape;
  TopoDS_Shape                                   myTop;
  TopoDS_Shell                                   myShell;
  TopoDS_Wire                                    myWire;
  GeomAbs_Shape                                  myCont;
  BRepFill_TransitionStyle                       myStyle;
  bool                                           IsInternal;
  bool                                           myDone;
};

