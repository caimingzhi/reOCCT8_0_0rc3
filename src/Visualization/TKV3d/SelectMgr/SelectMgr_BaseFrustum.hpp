#pragma once

#include <SelectMgr_BaseIntersector.hpp>

class SelectMgr_BaseFrustum : public SelectMgr_BaseIntersector
{
public:
  Standard_EXPORT SelectMgr_BaseFrustum();

  ~SelectMgr_BaseFrustum() override = default;

  Standard_EXPORT void SetBuilder(const occ::handle<SelectMgr_FrustumBuilder>& theBuilder);

  Standard_EXPORT void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera) override;

  Standard_EXPORT void SetPixelTolerance(const int theTol) override;

  Standard_EXPORT void SetWindowSize(const int theWidth, const int theHeight) override;

  Standard_EXPORT void WindowSize(int& theWidth, int& theHeight) const override;

  Standard_EXPORT void SetViewport(const double theX,
                                   const double theY,
                                   const double theWidth,
                                   const double theHeight) override;

  Standard_EXPORT bool IsBoundaryIntersectSphere(const gp_Pnt&                     theCenter,
                                                 const double                      theRadius,
                                                 const gp_Dir&                     thePlaneNormal,
                                                 const NCollection_Array1<gp_Pnt>& theBoundaries,
                                                 bool& theBoundaryInside) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_BaseFrustum, SelectMgr_BaseIntersector)

protected:
  int myPixelTolerance;

  occ::handle<SelectMgr_FrustumBuilder> myBuilder;
};
