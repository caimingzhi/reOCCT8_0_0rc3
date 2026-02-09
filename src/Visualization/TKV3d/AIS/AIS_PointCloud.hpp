#pragma once

#include <Prs3d_Presentation.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class AIS
{
public:
  DEFINE_STANDARD_ALLOC
};

#include <AIS_InteractiveObject.hpp>
#include <Bnd_Box.hpp>
#include <Graphic3d_ArrayOfPoints.hpp>
#include <Quantity_Color.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>

class TColStd_HPackedMapOfInteger;

class AIS_PointCloud : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_PointCloud, AIS_InteractiveObject)
public:
  enum DisplayMode
  {
    DM_Points = 0,
    DM_BndBox = 2
  };

  enum SelectionMode
  {
    SM_Points         = 0,
    SM_SubsetOfPoints = 1,
    SM_BndBox         = 2,
  };

public:
  Standard_EXPORT AIS_PointCloud();

  Standard_EXPORT virtual void SetPoints(const occ::handle<Graphic3d_ArrayOfPoints>& thePoints);

  Standard_EXPORT virtual void SetPoints(
    const occ::handle<NCollection_HArray1<gp_Pnt>>&         theCoords,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& theColors  = nullptr,
    const occ::handle<NCollection_HArray1<gp_Dir>>&         theNormals = nullptr);

public:
  Standard_EXPORT virtual const occ::handle<Graphic3d_ArrayOfPoints> GetPoints() const;

  Standard_EXPORT virtual Bnd_Box GetBoundingBox() const;

public:
  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& theMat) override;

  Standard_EXPORT void UnsetMaterial() override;

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

private:
  occ::handle<Graphic3d_ArrayOfPoints> myPoints;
  Bnd_Box                              myBndBox;
};

class AIS_PointCloudOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(AIS_PointCloudOwner, SelectMgr_EntityOwner)
public:
  Standard_EXPORT AIS_PointCloudOwner(const occ::handle<AIS_PointCloud>& theOrigin);

  Standard_EXPORT ~AIS_PointCloudOwner() override;

  const occ::handle<TColStd_HPackedMapOfInteger>& SelectedPoints() const { return mySelPoints; }

  const occ::handle<TColStd_HPackedMapOfInteger>& DetectedPoints() const { return myDetPoints; }

  Standard_EXPORT bool IsForcedHilight() const override;

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                 const int                                      theMode) override;

  Standard_EXPORT void Clear(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                             const int                                      theMode) override;

protected:
  occ::handle<TColStd_HPackedMapOfInteger> myDetPoints;
  occ::handle<TColStd_HPackedMapOfInteger> mySelPoints;
};
