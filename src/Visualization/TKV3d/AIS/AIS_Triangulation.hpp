#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <AIS_InteractiveObject.hpp>

class Poly_Triangulation;

class AIS_Triangulation : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Triangulation, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Triangulation(const occ::handle<Poly_Triangulation>& aTriangulation);

  Standard_EXPORT void SetColors(const occ::handle<NCollection_HArray1<int>>& aColor);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> GetColors() const;

  bool HasVertexColors() const { return (myFlagColor == 1); }

  Standard_EXPORT void SetTriangulation(const occ::handle<Poly_Triangulation>& aTriangulation);

  Standard_EXPORT occ::handle<Poly_Triangulation> GetTriangulation() const;

  Standard_EXPORT void SetTransparency(const double aValue = 0.6) override;

  Standard_EXPORT void UnsetTransparency() override;

protected:
  Standard_EXPORT void updatePresentation();

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT NCollection_Vec4<uint8_t> attenuateColor(const int    theColor,
                                                           const double theComponent);

  occ::handle<Poly_Triangulation>       myTriangulation;
  occ::handle<NCollection_HArray1<int>> myColor;
  int                                   myFlagColor;
  int                                   myNbNodes;
  int                                   myNbTriangles;
};
