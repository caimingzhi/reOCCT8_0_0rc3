#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Path.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class StepShape_EdgeLoop;
class TCollection_HAsciiString;
class StepShape_OrientedEdge;

class StepShape_OrientedPath : public StepShape_Path
{

public:
  //! Returns a OrientedPath
  Standard_EXPORT StepShape_OrientedPath();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_EdgeLoop>&       aPathElement,
                            const bool                                   aOrientation);

  Standard_EXPORT void SetPathElement(const occ::handle<StepShape_EdgeLoop>& aPathElement);

  Standard_EXPORT occ::handle<StepShape_EdgeLoop> PathElement() const;

  Standard_EXPORT void SetOrientation(const bool aOrientation);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetEdgeList(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList)
    override;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> EdgeList()
    const override;

  Standard_EXPORT occ::handle<StepShape_OrientedEdge> EdgeListValue(const int num) const override;

  Standard_EXPORT int NbEdgeList() const override;

  DEFINE_STANDARD_RTTIEXT(StepShape_OrientedPath, StepShape_Path)

private:
  occ::handle<StepShape_EdgeLoop> pathElement;
  bool                            orientation;
};

