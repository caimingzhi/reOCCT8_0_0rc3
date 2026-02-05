#pragma once

#include <IVtk_Types.hpp>
#include <vtkSmartPointer.h>

#include <limits>

class vtkLookupTable;
class vtkMapper;

//! Helper methods to facilitate usage of VIS classes in an application.
namespace IVtkTools
{

  //! Returns vtkLookupTable instance initialized by standrad OCCT colors used
  //! in wireframe mode for different kinds of sub-shapes (free/boundary/shared
  //! edges, isolines,...)
  Standard_EXPORT vtkSmartPointer<vtkLookupTable> InitLookupTable();

  //! Set a color for given type of sub-shapes.
  //! @param [in,out] theColorTable vtkLookupTable to set the color.
  //! @param[in]   theColorRole type of sub-shapes to set the color.
  //! @param[in]   theR red color component. Use [0,1] double values.
  //! @param[in]   theG green color component. Use [0,1] double values.
  //! @param[in]   theB blue color component. Use [0,1] double values.
  //! @param[in]   theA the alpha value (the opacity) as a double between 0 and 1.
  Standard_EXPORT void SetLookupTableColor(vtkLookupTable*     theColorTable,
                                           const IVtk_MeshType theColorRole,
                                           const double        theR,
                                           const double        theG,
                                           const double        theB,
                                           const double        theA = 1);

  //! Get a color for given type of sub-shapes.
  //! @param[in]   theColorTable vtkLookupTable to set the color.
  //! @param[in]   theColorRole type of sub-shapes to set the color.
  //! @param[out]  theR red color component as a double between 0 and 1.
  //! @param[out]  theG green color component as a double between 0 and 1.
  //! @param[out]  theB blue color component as a double between 0 and 1.
  Standard_EXPORT void GetLookupTableColor(vtkLookupTable*     theColorTable,
                                           const IVtk_MeshType theColorRole,
                                           double&             theR,
                                           double&             theG,
                                           double&             theB);

  //! Get a color for given type of sub-shapes.
  //! @param[in]   theColorTable vtkLookupTable to set the color.
  //! @param[in]   theColorRole type of sub-shapes to set the color.
  //! @param[out]  theR red color component as a double between 0 and 1.
  //! @param[out]  theG green color component as a double between 0 and 1.
  //! @param[out]  theB blue color component as a double between 0 and 1.
  //! @param[out]  theA the alpha value (the opacity) as a double between 0 and 1.
  Standard_EXPORT void GetLookupTableColor(vtkLookupTable*     theColorTable,
                                           const IVtk_MeshType theColorRole,
                                           double&             theR,
                                           double&             theG,
                                           double&             theB,
                                           double&             theA);

  //! Set up the initial shape mapper parameters with default OCC colors.
  Standard_EXPORT void InitShapeMapper(vtkMapper* theMapper);

  //! Set up the initial shape mapper parameters with user colors.
  //! @param [in,out] theMapper mapper to initialize
  //! @param[in]  theColorTable a table with user's colors definition
  Standard_EXPORT void InitShapeMapper(vtkMapper* theMapper, vtkLookupTable* theColorTable);

} // namespace IVtkTools
