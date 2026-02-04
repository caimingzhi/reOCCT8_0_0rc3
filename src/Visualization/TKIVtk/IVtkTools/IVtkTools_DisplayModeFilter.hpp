#pragma once


#include <IVtkTools.hpp>
#include <IVtkTools_SubPolyDataFilter.hpp>
#include <NCollection_DataMap.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4251) // avoid warning C4251: "class needs to have dll-interface..."
#endif

//! @class IVtkTools_DisplayModeFilter
//! @brief Cells filter according to the selected display mode by mesh parts types.
//! This filter is used to get parts of a shape according to different
//! display modes.
class Standard_EXPORT IVtkTools_DisplayModeFilter : public IVtkTools_SubPolyDataFilter
{
public:
  vtkTypeMacro(IVtkTools_DisplayModeFilter, IVtkTools_SubPolyDataFilter)

    static IVtkTools_DisplayModeFilter* New();
  void PrintSelf(std::ostream& os, vtkIndent indent) override;

  //! Set display mode to define cells types to be passed through this filter.
  void SetDisplayMode(const IVtk_DisplayMode aMode);

  //! Display or not shared vertices.
  void SetDisplaySharedVertices(const bool doDisplay);

  //! Get current display mode.
  IVtk_DisplayMode GetDisplayMode() const;

  //! Returns list of displaying mesh element types for the given display mode
  const NCollection_Map<IVtk_IdType>& MeshTypesForMode(IVtk_DisplayMode theMode) const;

  //! Set a list of displaying mesh element types for the given display mode
  void SetMeshTypesForMode(IVtk_DisplayMode                    theMode,
                           const NCollection_Map<IVtk_IdType>& theMeshTypes);

  //! Draw Boundary of faces for shading mode
  void SetFaceBoundaryDraw(bool theToDraw);

  //! Returns True if drawing Boundary of faces for shading mode is defined.
  bool FaceBoundaryDraw() const { return myDrawFaceBoundaries; }

  //! Returns TRUE if vertex normals should be included for smooth shading within DM_Shading mode or
  //! not.
  bool IsSmoothShading() const { return myIsSmoothShading; }

  //! Set if vertex normals should be included for smooth shading or not.
  void SetSmoothShading(bool theIsSmooth);

protected:
  //! Filter cells according to the given set of ids.
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  IVtkTools_DisplayModeFilter();
  ~IVtkTools_DisplayModeFilter() override;

protected:
  // clang-format off
  IVtk_DisplayMode      myDisplayMode;             //!< Display mode defining mesh types to pass through this filter
  NCollection_Map<IVtk_IdType>        myModesDefinition[2];
  bool                  myDoDisplaySharedVertices;

  bool                  myDrawFaceBoundaries;      //!< Draw Face boundaries within shading display mode
  bool                  myIsSmoothShading;         //!< include vertex normals for smooth shading or not
  // clang-format on
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

