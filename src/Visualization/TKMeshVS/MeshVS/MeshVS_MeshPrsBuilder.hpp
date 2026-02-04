#pragma once


#include <MeshVS_PrsBuilder.hpp>
#include <MeshVS_DisplayModeFlags.hpp>
#include <MeshVS_BuilderPriority.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HArray1.hpp>

class MeshVS_Mesh;
class MeshVS_DataSource;
class Graphic3d_ArrayOfSegments;
class Graphic3d_ArrayOfTriangles;
class Graphic3d_ArrayOfPrimitives;
class Graphic3d_AspectFillArea3d;
class Graphic3d_AspectLine3d;

//! This class provides methods to compute base mesh presentation
class MeshVS_MeshPrsBuilder : public MeshVS_PrsBuilder
{

public:
  //! Creates builder with certain display mode flags, data source, ID and priority
  Standard_EXPORT MeshVS_MeshPrsBuilder(const occ::handle<MeshVS_Mesh>& Parent,
                                        const MeshVS_DisplayModeFlags&  Flags = MeshVS_DMF_OCCMask,
                                        const occ::handle<MeshVS_DataSource>& DS = nullptr,
                                        const int                             Id = -1,
                                        const MeshVS_BuilderPriority& Priority   = MeshVS_BP_Mesh);

  //! Builds base mesh presentation by calling the methods below
  Standard_EXPORT void Build(const occ::handle<Prs3d_Presentation>& Prs,
                             const TColStd_PackedMapOfInteger&      IDs,
                             TColStd_PackedMapOfInteger&            IDsToExclude,
                             const bool                             IsElement,
                             const int                              DisplayMode) const override;

  //! Builds nodes presentation
  Standard_EXPORT virtual void BuildNodes(const occ::handle<Prs3d_Presentation>& Prs,
                                          const TColStd_PackedMapOfInteger&      IDs,
                                          TColStd_PackedMapOfInteger&            IDsToExclude,
                                          const int                              DisplayMode) const;

  //! Builds elements presentation
  Standard_EXPORT virtual void BuildElements(const occ::handle<Prs3d_Presentation>& Prs,
                                             const TColStd_PackedMapOfInteger&      IDs,
                                             TColStd_PackedMapOfInteger&            IDsToExclude,
                                             const int DisplayMode) const;

  //! Builds presentation of hilighted entity
  Standard_EXPORT virtual void BuildHilightPrs(const occ::handle<Prs3d_Presentation>& Prs,
                                               const TColStd_PackedMapOfInteger&      IDs,
                                               const bool IsElement) const;

  //! Add to array polygons or polylines representing volume
  Standard_EXPORT static void AddVolumePrs(
    const occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& Topo,
    const NCollection_Array1<double>&                                  Nodes,
    const int                                                          NbNodes,
    const occ::handle<Graphic3d_ArrayOfPrimitives>&                    Array,
    const bool                                                         IsReflected,
    const bool                                                         IsShrinked,
    const bool                                                         IsSelect,
    const double                                                       ShrinkCoef);

  //! Calculate how many polygons or polylines are necessary to draw passed topology
  Standard_EXPORT static void HowManyPrimitives(
    const occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& Topo,
    const bool                                                         AsPolygons,
    const bool                                                         IsSelect,
    const int                                                          NbNodes,
    int&                                                               Vertices,
    int&                                                               Bounds);

  DEFINE_STANDARD_RTTIEXT(MeshVS_MeshPrsBuilder, MeshVS_PrsBuilder)

protected:
  //! Add to array of polylines some lines representing link
  Standard_EXPORT void AddLinkPrs(const NCollection_Array1<double>&             theCoords,
                                  const occ::handle<Graphic3d_ArrayOfSegments>& theLines,
                                  const bool                                    IsShrinked,
                                  const double                                  ShrinkCoef) const;

  //! Add to array of segments representing face's wire
  Standard_EXPORT void AddFaceWirePrs(const NCollection_Array1<double>&             theCoords,
                                      const int                                     theNbNodes,
                                      const occ::handle<Graphic3d_ArrayOfSegments>& theLines,
                                      const bool                                    theIsShrinked,
                                      const double theShrinkingCoef) const;

  //! Add to array of polygons a polygon representing face
  Standard_EXPORT void AddFaceSolidPrs(const int                                      ID,
                                       const NCollection_Array1<double>&              theCoords,
                                       const int                                      theNbNodes,
                                       const int                                      theMaxNodes,
                                       const occ::handle<Graphic3d_ArrayOfTriangles>& theTriangles,
                                       const bool   theIsReflected,
                                       const bool   theIsShrinked,
                                       const double theShrinkCoef,
                                       const bool   theIsMeshSmoothShading) const;

  //! Draw array of polygons and polylines in the certain order according to transparency
  Standard_EXPORT void DrawArrays(const occ::handle<Prs3d_Presentation>&          Prs,
                                  const occ::handle<Graphic3d_ArrayOfPrimitives>& thePolygons,
                                  const occ::handle<Graphic3d_ArrayOfPrimitives>& theLines,
                                  const occ::handle<Graphic3d_ArrayOfPrimitives>& theLinkLines,
                                  const occ::handle<Graphic3d_ArrayOfPrimitives>& theVolumesInShad,
                                  const bool                                     IsPolygonsEdgesOff,
                                  const bool                                     IsSelected,
                                  const occ::handle<Graphic3d_AspectFillArea3d>& theFillAsp,
                                  const occ::handle<Graphic3d_AspectLine3d>&     theLineAsp) const;

  //! Default calculation of center of face or link. This method if useful for shrink mode
  //! presentation theCoords is array of nodes coordinates in the strict order X1, Y1, Z1, X2...
  //! NbNodes is number of nodes an element consist of
  //! xG, yG, zG are coordinates of center whose will be returned
  Standard_EXPORT static void CalculateCenter(const NCollection_Array1<double>& theCoords,
                                              const int                         NbNodes,
                                              double&                           xG,
                                              double&                           yG,
                                              double&                           zG);
};

