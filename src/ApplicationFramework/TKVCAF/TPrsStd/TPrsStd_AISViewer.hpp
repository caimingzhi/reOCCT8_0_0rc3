#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_Attribute.hpp>
class AIS_InteractiveContext;
class Standard_GUID;
class TDF_Label;
class V3d_Viewer;
class TDF_RelocationTable;

class TPrsStd_AISViewer : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static bool Has(const TDF_Label& acces);

  Standard_EXPORT static occ::handle<TPrsStd_AISViewer> New(
    const TDF_Label&                           access,
    const occ::handle<AIS_InteractiveContext>& selector);

  Standard_EXPORT static occ::handle<TPrsStd_AISViewer> New(const TDF_Label&               acces,
                                                            const occ::handle<V3d_Viewer>& viewer);

  Standard_EXPORT static bool Find(const TDF_Label& acces, occ::handle<TPrsStd_AISViewer>& A);

  Standard_EXPORT static bool Find(const TDF_Label& acces, occ::handle<AIS_InteractiveContext>& IC);

  Standard_EXPORT static bool Find(const TDF_Label& acces, occ::handle<V3d_Viewer>& V);

  Standard_EXPORT static void Update(const TDF_Label& acces);

  Standard_EXPORT TPrsStd_AISViewer();

  Standard_EXPORT void Update() const;

  Standard_EXPORT void SetInteractiveContext(const occ::handle<AIS_InteractiveContext>& ctx);

  Standard_EXPORT occ::handle<AIS_InteractiveContext> GetInteractiveContext() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_AISViewer, TDF_Attribute)

private:
  occ::handle<AIS_InteractiveContext> myInteractiveContext;
};
