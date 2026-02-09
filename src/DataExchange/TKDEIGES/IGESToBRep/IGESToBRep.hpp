#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class IGESToBRep_AlgoContainer;
class IGESData_IGESEntity;
class TopoDS_Edge;
class TopoDS_Face;

class IGESToBRep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static void SetAlgoContainer(
    const occ::handle<IGESToBRep_AlgoContainer>& aContainer);

  Standard_EXPORT static occ::handle<IGESToBRep_AlgoContainer> AlgoContainer();

  Standard_EXPORT static bool IsCurveAndSurface(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT static bool IsBasicCurve(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT static bool IsBasicSurface(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT static bool IsTopoCurve(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT static bool IsTopoSurface(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT static bool IsBRepEntity(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT static int IGESCurveToSequenceOfIGESCurve(
    const occ::handle<IGESData_IGESEntity>&                              curve,
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& sequence);

  Standard_EXPORT static bool TransferPCurve(const TopoDS_Edge& fromedge,
                                             const TopoDS_Edge& toedge,
                                             const TopoDS_Face& face);
};
