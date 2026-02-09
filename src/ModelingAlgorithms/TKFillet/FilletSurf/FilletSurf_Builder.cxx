

#include <FilletSurf_Builder.hpp>
#include <FilletSurf_ErrorTypeStatus.hpp>
#include <FilletSurf_InternalBuilder.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

FilletSurf_Builder::FilletSurf_Builder(const TopoDS_Shape&                   S,
                                       const NCollection_List<TopoDS_Shape>& E,
                                       const double                          R,
                                       const double                          Ta,
                                       const double                          Tapp3d,
                                       const double                          Tapp2d)
    : myIntBuild(S, ChFi3d_Polynomial, Ta, Tapp3d, Tapp2d)
{
  myisdone      = FilletSurf_IsOk;
  myerrorstatus = FilletSurf_EmptyList;
  int add       = myIntBuild.Add(E, R);
  if (add != 0)
  {
    myisdone = FilletSurf_IsNotOk;
    if (add == 1)
      myerrorstatus = FilletSurf_EmptyList;
    else if (add == 2)
      myerrorstatus = FilletSurf_EdgeNotG1;
    else if (add == 3)
      myerrorstatus = FilletSurf_FacesNotG1;
    else if (add == 4)
      myerrorstatus = FilletSurf_EdgeNotOnShape;
    else if (add == 5)
      myerrorstatus = FilletSurf_NotSharpEdge;
  }
}

void FilletSurf_Builder::Perform()
{
  if (myisdone == FilletSurf_IsOk)
  {
    myIntBuild.Perform();
    if (myIntBuild.Done())
      myisdone = FilletSurf_IsOk;
    else if (myIntBuild.NbSurface() != 0)
    {
      myisdone      = FilletSurf_IsPartial;
      myerrorstatus = FilletSurf_PbFilletCompute;
    }
    else
    {
      myisdone      = FilletSurf_IsNotOk;
      myerrorstatus = FilletSurf_PbFilletCompute;
    }
  }
}

FilletSurf_StatusDone FilletSurf_Builder::IsDone() const
{
  return myisdone;
}

FilletSurf_ErrorTypeStatus FilletSurf_Builder::StatusError() const
{
  return myerrorstatus;
}

int FilletSurf_Builder::NbSurface() const
{
  if (IsDone() != FilletSurf_IsNotOk)
    return myIntBuild.NbSurface();
  throw StdFail_NotDone("FilletSurf_Builder::NbSurface");
}

const occ::handle<Geom_Surface>& FilletSurf_Builder::SurfaceFillet(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::SurfaceFillet");
  return myIntBuild.SurfaceFillet(Index);
}

double FilletSurf_Builder::TolApp3d(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::TolApp3d");
  return myIntBuild.TolApp3d(Index);
}

const TopoDS_Face& FilletSurf_Builder::SupportFace1(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::SupportFace1");
  return myIntBuild.SupportFace1(Index);
}

const TopoDS_Face& FilletSurf_Builder::SupportFace2(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::SupportFace2");
  return myIntBuild.SupportFace2(Index);
}

const occ::handle<Geom_Curve>& FilletSurf_Builder::CurveOnFace1(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::CurveOnFace1");
  return myIntBuild.CurveOnFace1(Index);
}

const occ::handle<Geom_Curve>& FilletSurf_Builder::CurveOnFace2(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::CurveOnFace2");
  return myIntBuild.CurveOnFace2(Index);
}

const occ::handle<Geom2d_Curve>& FilletSurf_Builder::PCurveOnFace1(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::PCurveOnFace1");
  return myIntBuild.PCurveOnFace1(Index);
}

const occ::handle<Geom2d_Curve>& FilletSurf_Builder::PCurve1OnFillet(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::PCurve1OnFillet");
  return myIntBuild.PCurve1OnFillet(Index);
}

const occ::handle<Geom2d_Curve>& FilletSurf_Builder::PCurveOnFace2(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::PCurveOnFace2");
  return myIntBuild.PCurveOnFace2(Index);
}

const occ::handle<Geom2d_Curve>& FilletSurf_Builder::PCurve2OnFillet(const int Index) const
{
  if ((Index < 1) || (Index > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::PCurve2OnFillet");
  return myIntBuild.PCurve2OnFillet(Index);
}

double FilletSurf_Builder::FirstParameter() const
{
  if (IsDone() == FilletSurf_IsNotOk)
    throw StdFail_NotDone("FilletSurf_Builder::FirstParameter");
  return myIntBuild.FirstParameter();
}

double FilletSurf_Builder::LastParameter() const
{
  if (IsDone() == FilletSurf_IsNotOk)
    throw StdFail_NotDone("FilletSurf_Builder::LastParameter");
  return myIntBuild.LastParameter();
}

FilletSurf_StatusType FilletSurf_Builder::StartSectionStatus() const
{
  if (IsDone() == FilletSurf_IsNotOk)
    throw StdFail_NotDone("FilletSurf_Builder::StartSectionStatus");
  return myIntBuild.StartSectionStatus();
}

FilletSurf_StatusType FilletSurf_Builder::EndSectionStatus() const
{
  if (IsDone() == FilletSurf_IsNotOk)
    throw StdFail_NotDone("FilletSurf_Builder::StartSectionStatus");
  return myIntBuild.EndSectionStatus();
}

void FilletSurf_Builder::Simulate()
{
  if (myisdone == FilletSurf_IsOk)
  {
    myIntBuild.Simulate();

    if (myIntBuild.Done())
      myisdone = FilletSurf_IsOk;
    else
    {
      myisdone      = FilletSurf_IsNotOk;
      myerrorstatus = FilletSurf_PbFilletCompute;
    }
  }
}

int FilletSurf_Builder::NbSection(const int IndexSurf) const
{
  if (IsDone() == FilletSurf_IsNotOk)
    throw StdFail_NotDone("FilletSurf_Builder::NbSection)");
  else if ((IndexSurf < 1) || (IndexSurf > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::NbSection");
  return myIntBuild.NbSection(IndexSurf);
}

void FilletSurf_Builder::Section(const int                       IndexSurf,
                                 const int                       IndexSec,
                                 occ::handle<Geom_TrimmedCurve>& Circ) const
{
  if ((IndexSurf < 1) || (IndexSurf > NbSurface()))
    throw Standard_OutOfRange("FilletSurf_Builder::Section NbSurface");

  else if ((IndexSec < 1) || (IndexSec > NbSection(IndexSurf)))
    throw Standard_OutOfRange("FilletSurf_Builder::Section NbSection");

  else
    myIntBuild.Section(IndexSurf, IndexSec, Circ);
}
