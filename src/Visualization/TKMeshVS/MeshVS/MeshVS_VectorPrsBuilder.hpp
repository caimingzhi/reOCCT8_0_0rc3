#pragma once

#include <Standard_Integer.hpp>
#include <gp_Vec.hpp>
#include <NCollection_DataMap.hpp>
#include <MeshVS_PrsBuilder.hpp>
#include <MeshVS_DisplayModeFlags.hpp>
#include <MeshVS_BuilderPriority.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

class MeshVS_Mesh;
class Quantity_Color;
class MeshVS_DataSource;
class gp_Trsf;
class Graphic3d_ArrayOfPrimitives;
class gp_Vec;

//! This class provides methods to create vector data presentation.
//! It store map of vectors assigned with nodes or elements.
//! In simplified mode vectors draws with thickened ends instead of arrows
class MeshVS_VectorPrsBuilder : public MeshVS_PrsBuilder
{

public:
  Standard_EXPORT MeshVS_VectorPrsBuilder(
    const occ::handle<MeshVS_Mesh>&       Parent,
    const double                          MaxLength,
    const Quantity_Color&                 VectorColor,
    const MeshVS_DisplayModeFlags&        Flags       = MeshVS_DMF_VectorDataPrs,
    const occ::handle<MeshVS_DataSource>& DS          = nullptr,
    const int                             Id          = -1,
    const MeshVS_BuilderPriority&         Priority    = MeshVS_BP_Vector,
    const bool                            IsSimplePrs = false);

  //! Builds vector data presentation
  Standard_EXPORT void Build(const occ::handle<Prs3d_Presentation>& Prs,
                             const TColStd_PackedMapOfInteger&      IDs,
                             TColStd_PackedMapOfInteger&            IDsToExclude,
                             const bool                             IsElement,
                             const int                              theDisplayMode) const override;

  //! Adds to array of polygons and polylines some primitive representing single vector
  Standard_EXPORT void DrawVector(const gp_Trsf&                                  theTrsf,
                                  const double                                    Length,
                                  const double                                    MaxLength,
                                  const NCollection_Array1<gp_Pnt>&               ArrowPoints,
                                  const occ::handle<Graphic3d_ArrayOfPrimitives>& Lines,
                                  const occ::handle<Graphic3d_ArrayOfPrimitives>& ArrowLines,
                                  const occ::handle<Graphic3d_ArrayOfPrimitives>& Triangles) const;

  //! Calculates points of arrow presentation
  Standard_EXPORT static double calculateArrow(NCollection_Array1<gp_Pnt>& Points,
                                               const double                Length,
                                               const double                ArrowPart);

  //! Returns map of vectors assigned with nodes or elements
  Standard_EXPORT const NCollection_DataMap<int, gp_Vec>& GetVectors(const bool IsElement) const;

  //! Sets map of vectors assigned with nodes or elements
  Standard_EXPORT void SetVectors(const bool                              IsElement,
                                  const NCollection_DataMap<int, gp_Vec>& Map);

  //! Returns true, if map isn't empty
  Standard_EXPORT bool HasVectors(const bool IsElement) const;

  //! Returns vector assigned with certain node or element
  Standard_EXPORT bool GetVector(const bool IsElement, const int ID, gp_Vec& Vect) const;

  //! Sets vector assigned with certain node or element
  Standard_EXPORT void SetVector(const bool IsElement, const int ID, const gp_Vec& Vect);

  //! Calculates minimal and maximal length of vectors in map
  //! ( nodal, if IsElement = False or elemental, if IsElement = True )
  Standard_EXPORT void GetMinMaxVectorValue(const bool IsElement,
                                            double&    MinValue,
                                            double&    MaxValue) const;

  //! Sets flag that indicates is simple vector arrow mode uses or not
  //! default value is False
  Standard_EXPORT void SetSimplePrsMode(const bool IsSimpleArrow);

  //! Sets parameters of simple vector arrwo presentation
  //! theLineWidthParam - coefficient of vector line width (to draw line instead of arrow)
  //! theStartParam and theEndParam parameters of start and end of thickened ends
  //! position of thickening calculates according to parameters and maximum vector length
  //! default values are:
  //! theLineWidthParam = 2.5
  //! theStartParam     = 0.85
  //! theEndParam       = 0.95
  Standard_EXPORT void SetSimplePrsParams(const double theLineWidthParam,
                                          const double theStartParam,
                                          const double theEndParam);

  DEFINE_STANDARD_RTTIEXT(MeshVS_VectorPrsBuilder, MeshVS_PrsBuilder)

private:
  bool                             myIsSimplePrs;
  double                           mySimpleWidthPrm;
  double                           mySimpleStartPrm;
  double                           mySimpleEndPrm;
  NCollection_DataMap<int, gp_Vec> myNodeVectorMap;
  NCollection_DataMap<int, gp_Vec> myElemVectorMap;
};
