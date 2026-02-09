#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;
class IGESBasic_HArray1OfHArray1OfInteger;

class IGESGraph_TextFontDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_TextFontDef();

  Standard_EXPORT void Init(const int                                    aFontCode,
                            const occ::handle<TCollection_HAsciiString>& aFontName,
                            const int                                    aSupersededFont,
                            const occ::handle<IGESGraph_TextFontDef>&    aSupersededEntity,
                            const int                                    aScale,
                            const occ::handle<NCollection_HArray1<int>>& allASCIICodes,
                            const occ::handle<NCollection_HArray1<int>>& allNextCharX,
                            const occ::handle<NCollection_HArray1<int>>& allNextCharY,
                            const occ::handle<NCollection_HArray1<int>>& allPenMotions,
                            const occ::handle<IGESBasic_HArray1OfHArray1OfInteger>& allPenFlags,
                            const occ::handle<IGESBasic_HArray1OfHArray1OfInteger>& allMovePenToX,
                            const occ::handle<IGESBasic_HArray1OfHArray1OfInteger>& allMovePenToY);

  Standard_EXPORT int FontCode() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FontName() const;

  Standard_EXPORT bool IsSupersededFontEntity() const;

  Standard_EXPORT int SupersededFontCode() const;

  Standard_EXPORT occ::handle<IGESGraph_TextFontDef> SupersededFontEntity() const;

  Standard_EXPORT int Scale() const;

  Standard_EXPORT int NbCharacters() const;

  Standard_EXPORT int ASCIICode(const int Chnum) const;

  Standard_EXPORT void NextCharOrigin(const int Chnum, int& NX, int& NY) const;

  Standard_EXPORT int NbPenMotions(const int Chnum) const;

  Standard_EXPORT bool IsPenUp(const int Chnum, const int Motionnum) const;

  Standard_EXPORT void NextPenPosition(const int Chnum,
                                       const int Motionnum,
                                       int&      IX,
                                       int&      IY) const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_TextFontDef, IGESData_IGESEntity)

private:
  int                                              theFontCode;
  occ::handle<TCollection_HAsciiString>            theFontName;
  int                                              theSupersededFontCode;
  occ::handle<IGESGraph_TextFontDef>               theSupersededFontEntity;
  int                                              theScale;
  occ::handle<NCollection_HArray1<int>>            theASCIICodes;
  occ::handle<NCollection_HArray1<int>>            theNextCharOriginX;
  occ::handle<NCollection_HArray1<int>>            theNextCharOriginY;
  occ::handle<NCollection_HArray1<int>>            theNbPenMotions;
  occ::handle<IGESBasic_HArray1OfHArray1OfInteger> thePenMotions;
  occ::handle<IGESBasic_HArray1OfHArray1OfInteger> thePenMovesToX;
  occ::handle<IGESBasic_HArray1OfHArray1OfInteger> thePenMovesToY;
};
