#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_GeneralModifier.hpp>
#include <NCollection_Sequence.hpp>
#include <IFSelect_Transformer.hpp>
#include <Standard_Integer.hpp>
class IFSelect_Selection;
class Interface_CopyControl;
class IFSelect_Modifier;
class Interface_Graph;
class Interface_Protocol;
class Interface_CheckIterator;
class Interface_InterfaceModel;
class Interface_CopyTool;
class Standard_Transient;
class TCollection_AsciiString;

class IFSelect_TransformStandard : public IFSelect_Transformer
{

public:
  Standard_EXPORT IFSelect_TransformStandard();

  Standard_EXPORT void SetCopyOption(const bool option);

  Standard_EXPORT bool CopyOption() const;

  Standard_EXPORT void SetSelection(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT occ::handle<IFSelect_Selection> Selection() const;

  Standard_EXPORT int NbModifiers() const;

  Standard_EXPORT occ::handle<IFSelect_Modifier> Modifier(const int num) const;

  Standard_EXPORT int ModifierRank(const occ::handle<IFSelect_Modifier>& modif) const;

  Standard_EXPORT bool AddModifier(const occ::handle<IFSelect_Modifier>& modif,
                                   const int                             atnum = 0);

  Standard_EXPORT bool RemoveModifier(const occ::handle<IFSelect_Modifier>& modif);

  Standard_EXPORT bool RemoveModifier(const int num);

  Standard_EXPORT bool Perform(const Interface_Graph&                 G,
                               const occ::handle<Interface_Protocol>& protocol,
                               Interface_CheckIterator&               checks,
                               occ::handle<Interface_InterfaceModel>& newmod) override;

  Standard_EXPORT void Copy(const Interface_Graph&                 G,
                            Interface_CopyTool&                    TC,
                            occ::handle<Interface_InterfaceModel>& newmod) const;

  Standard_EXPORT void StandardCopy(const Interface_Graph&                 G,
                                    Interface_CopyTool&                    TC,
                                    occ::handle<Interface_InterfaceModel>& newmod) const;

  Standard_EXPORT void OnTheSpot(const Interface_Graph&                 G,
                                 Interface_CopyTool&                    TC,
                                 occ::handle<Interface_InterfaceModel>& newmod) const;

  Standard_EXPORT bool ApplyModifiers(const Interface_Graph&                 G,
                                      const occ::handle<Interface_Protocol>& protocol,
                                      Interface_CopyTool&                    TC,
                                      Interface_CheckIterator&               checks,
                                      occ::handle<Interface_InterfaceModel>& newmod) const;

  Standard_EXPORT bool Updated(const occ::handle<Standard_Transient>& entfrom,
                               occ::handle<Standard_Transient>&       entto) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_TransformStandard, IFSelect_Transformer)

private:
  bool                                                        thecopy;
  occ::handle<IFSelect_Selection>                             thesel;
  NCollection_Sequence<occ::handle<IFSelect_GeneralModifier>> themodifs;
  occ::handle<Interface_CopyControl>                          themap;
};
