#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntSurf_PathPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <math_Vector.hpp>
#include <IntWalk_VectorOfWalkingData.hpp>
#include <IntWalk_VectorOfInteger.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir2d.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <IntPatch_TheIWLineOfTheIWalking.hpp>
#include <IntSurf_InteriorPoint.hpp>
#include <IntWalk_StatusDeflection.hpp>
#include <Bnd_Range.hpp>

class IntSurf_PathPoint;
class IntSurf_PathPointTool;
class IntSurf_InteriorPoint;
class IntSurf_InteriorPointTool;
class Adaptor3d_HSurfaceTool;
class IntPatch_TheSurfFunction;
class IntPatch_TheIWLineOfTheIWalking;
class IntSurf_PntOn2S;
class math_FunctionSetRoot;

class IntPatch_TheIWalking
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_TheIWalking(const double Epsilon,
                                       const double Deflection,
                                       const double Step,
                                       const bool   theToFillHoles = false);

  void SetTolerance(const double Epsilon, const double Deflection, const double Step);

  Standard_EXPORT void Perform(const NCollection_Sequence<IntSurf_PathPoint>&     Pnts1,
                               const NCollection_Sequence<IntSurf_InteriorPoint>& Pnts2,
                               IntPatch_TheSurfFunction&                          Func,
                               const occ::handle<Adaptor3d_Surface>&              S,
                               const bool                                         Reversed = false);

  Standard_EXPORT void Perform(const NCollection_Sequence<IntSurf_PathPoint>& Pnts1,
                               IntPatch_TheSurfFunction&                      Func,
                               const occ::handle<Adaptor3d_Surface>&          S,
                               const bool                                     Reversed = false);

  bool IsDone() const;

  int NbLines() const;

  const occ::handle<IntPatch_TheIWLineOfTheIWalking>& Value(const int Index) const;

  int NbSinglePnts() const;

  const IntSurf_PathPoint& SinglePnt(const int Index) const;

protected:
  Standard_EXPORT bool Cadrage(math_Vector& BornInf,
                               math_Vector& BornSup,
                               math_Vector& UVap,
                               double&      Step,
                               const int    StepSign) const;

  Standard_EXPORT bool TestArretPassage(const NCollection_Sequence<double>& Umult,
                                        const NCollection_Sequence<double>& Vmult,
                                        IntPatch_TheSurfFunction&           Section,
                                        math_Vector&                        UV,
                                        int&                                Irang);

  Standard_EXPORT bool TestArretPassage(const NCollection_Sequence<double>& Umult,
                                        const NCollection_Sequence<double>& Vmult,
                                        const math_Vector&                  UV,
                                        const int                           Index,
                                        int&                                Irang);

  Standard_EXPORT bool TestArretAjout(IntPatch_TheSurfFunction& Section,
                                      math_Vector&              UV,
                                      int&                      Irang,
                                      IntSurf_PntOn2S&          PSol);

  Standard_EXPORT void FillPntsInHoles(IntPatch_TheSurfFunction&                    Section,
                                       NCollection_Sequence<int>&                   CopySeqAlone,
                                       NCollection_Sequence<IntSurf_InteriorPoint>& PntsInHoles);

  Standard_EXPORT void TestArretCadre(const NCollection_Sequence<double>&                 Umult,
                                      const NCollection_Sequence<double>&                 Vmult,
                                      const occ::handle<IntPatch_TheIWLineOfTheIWalking>& Line,
                                      IntPatch_TheSurfFunction&                           Section,
                                      math_Vector&                                        UV,
                                      int&                                                Irang);

  Standard_EXPORT IntWalk_StatusDeflection
    TestDeflection(IntPatch_TheSurfFunction&      Section,
                   const bool                     Finished,
                   const math_Vector&             UV,
                   const IntWalk_StatusDeflection StatusPrecedent,
                   int&                           NbDivision,
                   double&                        Step,
                   const int                      StepSign);

  Standard_EXPORT void ComputeOpenLine(const NCollection_Sequence<double>&            Umult,
                                       const NCollection_Sequence<double>&            Vmult,
                                       const NCollection_Sequence<IntSurf_PathPoint>& Pnts1,
                                       IntPatch_TheSurfFunction&                      Section,
                                       bool&                                          Rajout);

  Standard_EXPORT void OpenLine(const int                                           N,
                                const IntSurf_PntOn2S&                              Psol,
                                const NCollection_Sequence<IntSurf_PathPoint>&      Pnts1,
                                IntPatch_TheSurfFunction&                           Section,
                                const occ::handle<IntPatch_TheIWLineOfTheIWalking>& Line);

  Standard_EXPORT bool IsValidEndPoint(const int IndOfPoint, const int IndOfLine);

  Standard_EXPORT void RemoveTwoEndPoints(const int IndOfPoint);

  Standard_EXPORT bool IsPointOnLine(const gp_Pnt2d& theP2d, const int Irang);

  Standard_EXPORT void ComputeCloseLine(const NCollection_Sequence<double>&                Umult,
                                        const NCollection_Sequence<double>&                Vmult,
                                        const NCollection_Sequence<IntSurf_PathPoint>&     Pnts1,
                                        const NCollection_Sequence<IntSurf_InteriorPoint>& Pnts2,
                                        IntPatch_TheSurfFunction&                          Section,
                                        bool&                                              Rajout);

  Standard_EXPORT void AddPointInCurrentLine(
    const int                                           N,
    const IntSurf_PathPoint&                            PathPnt,
    const occ::handle<IntPatch_TheIWLineOfTheIWalking>& CurrentLine) const;

  Standard_EXPORT void MakeWalkingPoint(const int                 Case,
                                        const double              U,
                                        const double              V,
                                        IntPatch_TheSurfFunction& Section,
                                        IntSurf_PntOn2S&          Psol);

  Standard_EXPORT void Clear();

  Standard_EXPORT bool IsPointOnLine(const IntSurf_PntOn2S&    thePOn2S,
                                     const math_Vector&        theInfBounds,
                                     const math_Vector&        theSupBounds,
                                     math_FunctionSetRoot&     theSolver,
                                     IntPatch_TheSurfFunction& theFunc);

private:
  bool                                                               done;
  NCollection_Sequence<IntSurf_PathPoint>                            seqSingle;
  double                                                             fleche;
  double                                                             pas;
  math_Vector                                                        tolerance;
  double                                                             epsilon;
  bool                                                               reversed;
  IntWalk_VectorOfWalkingData                                        wd1;
  IntWalk_VectorOfWalkingData                                        wd2;
  IntWalk_VectorOfInteger                                            nbMultiplicities;
  Bnd_Range                                                          mySRangeU;
  Bnd_Range                                                          mySRangeV;
  double                                                             Um;
  double                                                             UM;
  double                                                             Vm;
  double                                                             VM;
  IntSurf_PntOn2S                                                    previousPoint;
  gp_Vec                                                             previousd3d;
  gp_Dir2d                                                           previousd2d;
  NCollection_Sequence<int>                                          seqAjout;
  NCollection_Sequence<int>                                          seqAlone;
  NCollection_DataMap<int, NCollection_List<int>>                    PointLineLine;
  NCollection_Sequence<occ::handle<IntPatch_TheIWLineOfTheIWalking>> lines;
  bool                                                               ToFillHoles;
};

#define ThePointOfPath IntSurf_PathPoint
#define ThePointOfPath_hxx <IntSurf_PathPoint.hpp>
#define ThePointOfPathTool IntSurf_PathPointTool
#define ThePointOfPathTool_hxx <IntSurf_PathPointTool.hpp>
#define ThePOPIterator NCollection_Sequence<IntSurf_PathPoint>
#define ThePOPIterator_hxx <NCollection_Sequence<IntSurf_PathPoint>.hxx>
#define ThePointOfLoop IntSurf_InteriorPoint
#define ThePointOfLoop_hxx <IntSurf_InteriorPoint.hpp>
#define ThePointOfLoopTool IntSurf_InteriorPointTool
#define ThePointOfLoopTool_hxx <IntSurf_InteriorPointTool.hpp>
#define ThePOLIterator NCollection_Sequence<IntSurf_InteriorPoint>
#define ThePOLIterator_hxx <NCollection_Sequence<IntSurf_InteriorPoint>.hxx>
#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheIWFunction IntPatch_TheSurfFunction
#define TheIWFunction_hxx <IntPatch_TheSurfFunction.hpp>
#define IntWalk_TheIWLine IntPatch_TheIWLineOfTheIWalking
#define IntWalk_TheIWLine_hxx <IntPatch_TheIWLineOfTheIWalking.hpp>
#define IntWalk_SequenceOfIWLine NCollection_Sequence<occ::handle<IntPatch_TheIWLineOfTheIWalking>>
#define IntWalk_SequenceOfIWLine_hxx                                                               \
  <NCollection_Sequence<occ::handle<IntPatch_TheIWLineOfTheIWalking>>.hxx>
#define Handle_IntWalk_TheIWLine occ::handle<IntPatch_TheIWLineOfTheIWalking>
#define IntWalk_IWalking IntPatch_TheIWalking
#define IntWalk_IWalking_hxx <IntPatch_TheIWalking.hpp>

#include <IntWalk_IWalking_1.hpp>

#undef ThePointOfPath
#undef ThePointOfPath_hxx
#undef ThePointOfPathTool
#undef ThePointOfPathTool_hxx
#undef ThePOPIterator
#undef ThePOPIterator_hxx
#undef ThePointOfLoop
#undef ThePointOfLoop_hxx
#undef ThePointOfLoopTool
#undef ThePointOfLoopTool_hxx
#undef ThePOLIterator
#undef ThePOLIterator_hxx
#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef TheIWFunction
#undef TheIWFunction_hxx
#undef IntWalk_TheIWLine
#undef IntWalk_TheIWLine_hxx
#undef IntWalk_SequenceOfIWLine
#undef IntWalk_SequenceOfIWLine_hxx
#undef Handle_IntWalk_TheIWLine
#undef IntWalk_IWalking
#undef IntWalk_IWalking_hxx
