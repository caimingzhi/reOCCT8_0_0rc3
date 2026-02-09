#include <IVtkTools.hpp>
#include <IVtkVTK_ShapeData.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
#endif
#include <vtkLookupTable.h>
#include <vtkMapper.h>
#ifdef _MSC_VER
  #pragma warning(pop)
#endif

namespace IVtkTools
{

  vtkSmartPointer<vtkLookupTable> InitLookupTable()
  {
    vtkSmartPointer<vtkLookupTable> aColorTable = vtkSmartPointer<vtkLookupTable>::New();

    double aRange[2];
    aRange[0] = MT_Undefined;
    aRange[1] = MT_ShadedFace;
    aColorTable->Allocate(9);
    aColorTable->SetNumberOfTableValues(9);
    aColorTable->SetTableRange(aRange);
    aColorTable->SetValueRange(0, 1);

    aColorTable->SetTableValue(0, 0, 0, 0);
    aColorTable->SetTableValue(1, 0.5, 0.5, 0.5);
    aColorTable->SetTableValue(2, 1, 0, 0);
    aColorTable->SetTableValue(3, 1, 1, 0);
    aColorTable->SetTableValue(4, 1, 0, 0);
    aColorTable->SetTableValue(5, 0, 1, 0);
    aColorTable->SetTableValue(6, 1, 1, 0);
    aColorTable->SetTableValue(7, 1, 1, 0);
    aColorTable->SetTableValue(8, 1, 1, 0);
    return aColorTable;
  }

  void SetLookupTableColor(vtkLookupTable*     theColorTable,
                           const IVtk_MeshType theColorRole,
                           const double        theR,
                           const double        theG,
                           const double        theB,
                           const double)
  {
    theColorTable->SetTableValue(theColorRole + 1, theR, theG, theB);
  }

  void GetLookupTableColor(vtkLookupTable*     theColorTable,
                           const IVtk_MeshType theColorRole,
                           double&             theR,
                           double&             theG,
                           double&             theB)
  {
    double aRgb[3];
    theColorTable->GetColor(theColorRole + 1, aRgb);
    theR = aRgb[0];
    theG = aRgb[1];
    theB = aRgb[2];
  }

  void GetLookupTableColor(vtkLookupTable*     theColorTable,
                           const IVtk_MeshType theColorRole,
                           double&             theR,
                           double&             theG,
                           double&             theB,
                           double&             theA)
  {
    theA = theColorTable->GetOpacity(theColorRole + 1);
    GetLookupTableColor(theColorTable, theColorRole, theR, theG, theB);
  }

  void InitShapeMapper(vtkMapper* theMapper)
  {
    InitShapeMapper(theMapper, InitLookupTable());
  }

  void InitShapeMapper(vtkMapper* theMapper, vtkLookupTable* theColorTable)
  {
    theMapper->ScalarVisibilityOn();
    theMapper->SetScalarModeToUseCellFieldData();
    theMapper->SelectColorArray(IVtkVTK_ShapeData::ARRNAME_MESH_TYPES());
    theMapper->SetColorModeToMapScalars();
    theMapper->SetScalarRange(theColorTable->GetRange());
    theMapper->SetLookupTable(theColorTable);
    theMapper->Update();
  }

} // namespace IVtkTools
