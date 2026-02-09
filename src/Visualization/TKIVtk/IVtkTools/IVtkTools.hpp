#pragma once

#include <IVtk_Types.hpp>
#include <vtkSmartPointer.h>

#include <limits>

class vtkLookupTable;
class vtkMapper;

namespace IVtkTools
{

  Standard_EXPORT vtkSmartPointer<vtkLookupTable> InitLookupTable();

  Standard_EXPORT void SetLookupTableColor(vtkLookupTable*     theColorTable,
                                           const IVtk_MeshType theColorRole,
                                           const double        theR,
                                           const double        theG,
                                           const double        theB,
                                           const double        theA = 1);

  Standard_EXPORT void GetLookupTableColor(vtkLookupTable*     theColorTable,
                                           const IVtk_MeshType theColorRole,
                                           double&             theR,
                                           double&             theG,
                                           double&             theB);

  Standard_EXPORT void GetLookupTableColor(vtkLookupTable*     theColorTable,
                                           const IVtk_MeshType theColorRole,
                                           double&             theR,
                                           double&             theG,
                                           double&             theB,
                                           double&             theA);

  Standard_EXPORT void InitShapeMapper(vtkMapper* theMapper);

  Standard_EXPORT void InitShapeMapper(vtkMapper* theMapper, vtkLookupTable* theColorTable);

} // namespace IVtkTools
