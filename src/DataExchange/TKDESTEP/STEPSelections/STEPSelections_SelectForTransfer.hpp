#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XSControl_SelectForTransfer.hpp>
class XSControl_TransferReader;
class Interface_EntityIterator;
class Interface_Graph;

class STEPSelections_SelectForTransfer : public XSControl_SelectForTransfer
{

public:
  Standard_EXPORT STEPSelections_SelectForTransfer();

  Standard_EXPORT STEPSelections_SelectForTransfer(const occ::handle<XSControl_TransferReader>& TR);

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  DEFINE_STANDARD_RTTIEXT(STEPSelections_SelectForTransfer, XSControl_SelectForTransfer)
};

