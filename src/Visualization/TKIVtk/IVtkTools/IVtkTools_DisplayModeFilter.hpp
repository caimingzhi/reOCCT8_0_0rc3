#pragma once

#include <IVtkTools.hpp>
#include <IVtkTools_SubPolyDataFilter.hpp>
#include <NCollection_DataMap.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4251)
#endif

class Standard_EXPORT IVtkTools_DisplayModeFilter : public IVtkTools_SubPolyDataFilter
{
public:
  vtkTypeMacro(IVtkTools_DisplayModeFilter, IVtkTools_SubPolyDataFilter)

    static IVtkTools_DisplayModeFilter* New();
  void PrintSelf(std::ostream& os, vtkIndent indent) override;

  void SetDisplayMode(const IVtk_DisplayMode aMode);

  void SetDisplaySharedVertices(const bool doDisplay);

  IVtk_DisplayMode GetDisplayMode() const;

  const NCollection_Map<IVtk_IdType>& MeshTypesForMode(IVtk_DisplayMode theMode) const;

  void SetMeshTypesForMode(IVtk_DisplayMode                    theMode,
                           const NCollection_Map<IVtk_IdType>& theMeshTypes);

  void SetFaceBoundaryDraw(bool theToDraw);

  bool FaceBoundaryDraw() const { return myDrawFaceBoundaries; }

  bool IsSmoothShading() const { return myIsSmoothShading; }

  void SetSmoothShading(bool theIsSmooth);

protected:
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  IVtkTools_DisplayModeFilter();
  ~IVtkTools_DisplayModeFilter() override;

protected:
  IVtk_DisplayMode             myDisplayMode;
  NCollection_Map<IVtk_IdType> myModesDefinition[2];
  bool                         myDoDisplaySharedVertices;

  bool myDrawFaceBoundaries;
  bool myIsSmoothShading;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif
