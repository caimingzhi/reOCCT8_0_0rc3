#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Transformer.hpp>
class Interface_CopyControl;
class Interface_Graph;
class Interface_Protocol;
class Interface_CheckIterator;
class Interface_InterfaceModel;
class Standard_Transient;
class TCollection_AsciiString;

class IGESSelect_SplineToBSpline : public IFSelect_Transformer
{

public:
  Standard_EXPORT IGESSelect_SplineToBSpline(const bool tryC2);

  Standard_EXPORT bool OptionTryC2() const;

  Standard_EXPORT bool Perform(const Interface_Graph&                 G,
                               const occ::handle<Interface_Protocol>& protocol,
                               Interface_CheckIterator&               checks,
                               occ::handle<Interface_InterfaceModel>& newmod) override;

  Standard_EXPORT bool Updated(const occ::handle<Standard_Transient>& entfrom,
                               occ::handle<Standard_Transient>&       entto) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SplineToBSpline, IFSelect_Transformer)

private:
  bool                               thetryc2;
  bool                               thefound;
  occ::handle<Interface_CopyControl> themap;
};
