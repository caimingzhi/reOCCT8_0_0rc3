#pragma once

#include <IVtkTools.hpp>

#include <Standard_WarningsDisable.hpp>
#include <vtkPolyDataAlgorithm.h>
#include <Standard_WarningsRestore.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4251)
#endif

class Standard_EXPORT IVtkTools_SubPolyDataFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(IVtkTools_SubPolyDataFilter, vtkPolyDataAlgorithm)

    static IVtkTools_SubPolyDataFilter* New();
  void PrintSelf(std::ostream& theOs, vtkIndent theIndent) override;

  void SetData(const NCollection_Map<IVtk_IdType>& theSet);

  void AddData(const NCollection_Map<IVtk_IdType>& theSet);

  void SetData(const NCollection_List<IVtk_IdType>& theIds);

  void AddData(const NCollection_List<IVtk_IdType>& theIds);

  void Clear();

  void SetIdsArrayName(const char* theArrayName);

  void SetDoFiltering(const bool theDoFiltering);

protected:
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  IVtkTools_SubPolyDataFilter();
  ~IVtkTools_SubPolyDataFilter() override;

protected:
  NCollection_Map<IVtk_IdType> myIdsSet;
  const char*                  myIdsArrayName;
  bool                         myDoFiltering;
  bool                         myToCopyNormals;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif
