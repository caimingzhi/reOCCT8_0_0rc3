#pragma once

#include <IVtkTools.hpp>

#include <Standard_WarningsDisable.hpp>
#include <vtkPolyDataAlgorithm.h>
#include <Standard_WarningsRestore.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4251) // avoid warning C4251: "class needs to have dll-interface..."
#endif

//! @class IVtkTools_SubPolyDataFilter
//! @brief Cells filter according to the given set of cells ids.
class Standard_EXPORT IVtkTools_SubPolyDataFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(IVtkTools_SubPolyDataFilter, vtkPolyDataAlgorithm)

    static IVtkTools_SubPolyDataFilter* New();
  void PrintSelf(std::ostream& theOs, vtkIndent theIndent) override;

  //! Set ids to be passed through this filter.
  void SetData(const NCollection_Map<IVtk_IdType>& theSet);

  //! Add ids to be passed through this filter.
  void AddData(const NCollection_Map<IVtk_IdType>& theSet);

  //! Set ids to be passed through this filter.
  void SetData(const NCollection_List<IVtk_IdType>& theIds);

  //! Add ids to be passed through this filter.
  void AddData(const NCollection_List<IVtk_IdType>& theIds);

  //! Clear ids set to be passed through this filter.
  void Clear();

  //! Set ids array name.
  void SetIdsArrayName(const char* theArrayName);

  void SetDoFiltering(const bool theDoFiltering);

protected:
  //! @brief Filter cells according to the given set of ids.
  //! Note: Data arrays are not passed through if filtering is turned on.
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  IVtkTools_SubPolyDataFilter();
  ~IVtkTools_SubPolyDataFilter() override;

protected:
  //! Set of ids to be passed through this filter.
  NCollection_Map<IVtk_IdType> myIdsSet;
  const char*                  myIdsArrayName;
  bool                         myDoFiltering;
  bool                         myToCopyNormals;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif
