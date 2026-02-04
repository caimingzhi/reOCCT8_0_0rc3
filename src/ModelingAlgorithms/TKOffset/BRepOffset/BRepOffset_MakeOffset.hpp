#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopoDS_Compound.hpp>
#include <BRepOffset_Mode.hpp>
#include <GeomAbs_JoinType.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <BRepOffset_Analyse.hpp>
#include <BRepAlgo_Image.hpp>
#include <NCollection_List.hpp>
#include <BRepOffset_Error.hpp>
#include <BRepOffset_MakeLoops.hpp>
#include <NCollection_Map.hpp>
#include <BRepOffset_Offset.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Array1.hpp>

#include <Message_ProgressRange.hpp>
class BRepAlgo_AsDes;
class TopoDS_Face;
class BRepOffset_Inter3d;

class BRepOffset_MakeOffset
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffset_MakeOffset();

  Standard_EXPORT BRepOffset_MakeOffset(
    const TopoDS_Shape&          S,
    const double                 Offset,
    const double                 Tol,
    const BRepOffset_Mode        Mode           = BRepOffset_Skin,
    const bool                   Intersection   = false,
    const bool                   SelfInter      = false,
    const GeomAbs_JoinType       Join           = GeomAbs_Arc,
    const bool                   Thickening     = false,
    const bool                   RemoveIntEdges = false,
    const Message_ProgressRange& theRange       = Message_ProgressRange());

  Standard_EXPORT void Initialize(const TopoDS_Shape&    S,
                                  const double           Offset,
                                  const double           Tol,
                                  const BRepOffset_Mode  Mode           = BRepOffset_Skin,
                                  const bool             Intersection   = false,
                                  const bool             SelfInter      = false,
                                  const GeomAbs_JoinType Join           = GeomAbs_Arc,
                                  const bool             Thickening     = false,
                                  const bool             RemoveIntEdges = false);

  Standard_EXPORT void Clear();

  //! Changes the flag allowing the linearization
  Standard_EXPORT void AllowLinearization(const bool theIsAllowed);

  //! Add Closing Faces, <F> has to be in the initial
  //! shape S.
  Standard_EXPORT void AddFace(const TopoDS_Face& F);

  //! set the offset <Off> on the Face <F>
  Standard_EXPORT void SetOffsetOnFace(const TopoDS_Face& F, const double Off);

  Standard_EXPORT void MakeOffsetShape(
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT void MakeThickSolid(
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT const BRepOffset_Analyse& GetAnalyse() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  const TopoDS_Shape& InitShape() const { return myInitialShape; }

  //! returns information about offset state.
  Standard_EXPORT BRepOffset_Error Error() const;

  //! Returns <Image> containing links between initials
  //! shapes and offset faces.
  Standard_EXPORT const BRepAlgo_Image& OffsetFacesFromShapes() const;

  //! Returns myJoin.
  Standard_EXPORT GeomAbs_JoinType GetJoinType() const;

  //! Returns <Image> containing links between initials
  //! shapes and offset edges.
  Standard_EXPORT const BRepAlgo_Image& OffsetEdgesFromShapes() const;

  //! Returns the list of closing faces stores by AddFace
  Standard_EXPORT const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&
                        ClosingFaces() const;

  //! Makes pre analysis of possibility offset perform. Use method Error() to get more information.
  //! Finds first error. List of checks:
  //! 1) Check for existence object with non-null offset.
  //! 2) Check for connectivity in offset shell.
  //! 3) Check continuity of input surfaces.
  //! 4) Check for normals existence on grid.
  //! @return True if possible make computations and false otherwise.
  Standard_EXPORT bool CheckInputData(const Message_ProgressRange& theRange);

  //! Return bad shape, which obtained in CheckInputData.
  Standard_EXPORT const TopoDS_Shape& GetBadShape() const;

public: //! @name History methods
  //! Returns the list of shapes generated from the shape <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& theS);

  //! Returns the list of shapes modified from the shape <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& theS);

  //! Returns true if the shape S has been deleted.
  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S);

protected:
  //! Analyze progress steps of the whole operation.
  //! @param theWhole - sum of progress of all operations.
  //! @param theSteps - steps of the operations supported by PI
  Standard_EXPORT void analyzeProgress(const double                theWhole,
                                       NCollection_Array1<double>& theSteps) const;

private:
  //! Check if shape consists of only planar faces
  //! If <myIsLinearizationAllowed> is TRUE, try to approximate images of faces
  //! by planar faces
  Standard_EXPORT bool IsPlanar();

  //! Set the faces that are to be removed
  Standard_EXPORT void SetFaces();

  //! Set the faces with special value of offset
  Standard_EXPORT void SetFacesWithOffset();

  Standard_EXPORT void BuildFaceComp();

  Standard_EXPORT void BuildOffsetByArc(const Message_ProgressRange& theRange);

  Standard_EXPORT void BuildOffsetByInter(const Message_ProgressRange& theRange);

  //! Make Offset faces
  Standard_EXPORT void MakeOffsetFaces(
    NCollection_DataMap<TopoDS_Shape, BRepOffset_Offset, TopTools_ShapeMapHasher>& theMapSF,
    const Message_ProgressRange&                                                   theRange);

  Standard_EXPORT void SelfInter(NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& Modif);

  Standard_EXPORT void Intersection3D(BRepOffset_Inter3d&          Inter,
                                      const Message_ProgressRange& theRange);

  Standard_EXPORT void Intersection2D(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& Modif,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& NewEdges,
    const Message_ProgressRange&                                         theRange);

  Standard_EXPORT void MakeLoops(
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& Modif,
    const Message_ProgressRange&                                   theRange);

  Standard_EXPORT void MakeLoopsOnContext(
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& Modif);

  Standard_EXPORT void MakeFaces(
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& Modif,
    const Message_ProgressRange&                                   theRange);

  Standard_EXPORT void MakeShells(const Message_ProgressRange& theRange);

  Standard_EXPORT void SelectShells();

  Standard_EXPORT void EncodeRegularity();

  //! Replace roots in history maps
  Standard_EXPORT void ReplaceRoots();

  Standard_EXPORT void MakeSolid(const Message_ProgressRange& theRange);

  Standard_EXPORT void ToContext(
    NCollection_DataMap<TopoDS_Shape, BRepOffset_Offset, TopTools_ShapeMapHasher>& MapSF);

  //! Private method use to update the map face<->offset
  Standard_EXPORT void UpdateFaceOffset();

  //! Private method used to correct degenerated edges on conical faces
  Standard_EXPORT void CorrectConicalFaces();

  //! Private method used to build walls for thickening the shell
  Standard_EXPORT void MakeMissingWalls(const Message_ProgressRange& theRange);

  //! Removes INTERNAL edges from the result
  Standard_EXPORT void RemoveInternalEdges();

  //! Intersects edges
  Standard_EXPORT void IntersectEdges(
    const NCollection_List<TopoDS_Shape>&                                          theFaces,
    NCollection_DataMap<TopoDS_Shape, BRepOffset_Offset, TopTools_ShapeMapHasher>& theMapSF,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&      theMES,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&      theBuild,
    occ::handle<BRepAlgo_AsDes>&                                                   theAsDes,
    occ::handle<BRepAlgo_AsDes>&                                                   theAsDes2d,
    const Message_ProgressRange&                                                   theRange);

  //! Building of the splits of the offset faces for mode Complete
  //! and joint type Intersection. This method is an advanced alternative
  //! for BRepOffset_MakeLoops::Build method.
  //! Currently the Complete intersection mode is limited to work only on planar cases.
  Standard_EXPORT void BuildSplitsOfExtendedFaces(
    const NCollection_List<TopoDS_Shape>& theLF,
    const BRepOffset_Analyse&             theAnalyse,
    const occ::handle<BRepAlgo_AsDes>&    theAsDes,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                                              theEdgesOrigins,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theFacesOrigins,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theETrimEInf,
    BRepAlgo_Image&                                                           theImage,
    const Message_ProgressRange&                                              theRange);

  //! Building of the splits of the already trimmed offset faces for mode Complete
  //! and joint type Intersection.
  Standard_EXPORT void BuildSplitsOfTrimmedFaces(const NCollection_List<TopoDS_Shape>& theLF,
                                                 const occ::handle<BRepAlgo_AsDes>&    theAsDes,
                                                 BRepAlgo_Image&                       theImage,
                                                 const Message_ProgressRange&          theRange);

  double                                                             myOffset;
  double                                                             myTol;
  TopoDS_Shape                                                       myInitialShape;
  TopoDS_Shape                                                       myShape;
  TopoDS_Compound                                                    myFaceComp;
  BRepOffset_Mode                                                    myMode;
  bool                                                               myIsLinearizationAllowed;
  bool                                                               myInter;
  bool                                                               mySelfInter;
  GeomAbs_JoinType                                                   myJoin;
  bool                                                               myThickening;
  bool                                                               myRemoveIntEdges;
  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> myFaceOffset;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>      myFaces;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>      myOriginalFaces;
  BRepOffset_Analyse                                                 myAnalyse;
  TopoDS_Shape                                                       myOffsetShape;
  BRepAlgo_Image                                                     myInitOffsetFace;
  BRepAlgo_Image                                                     myInitOffsetEdge;
  BRepAlgo_Image                                                     myImageOffset;
  BRepAlgo_Image                                                     myImageVV;
  NCollection_List<TopoDS_Shape>                                     myWalls;
  occ::handle<BRepAlgo_AsDes>                                        myAsDes;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                       myEdgeIntEdges;
  bool                 myDone;
  BRepOffset_Error     myError;
  BRepOffset_MakeLoops myMakeLoops;
  bool                 myIsPerformSewing; // Handle bad walls in thicksolid mode.
  bool                 myIsPlanar;
  TopoDS_Shape         myBadShape;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myFacePlanfaceMap;
  NCollection_List<TopoDS_Shape>                                           myGenerated;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                   myResMap;
};

