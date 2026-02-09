#pragma once

#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <RWObj_Material.hpp>
#include <NCollection_DataMap.hpp>

class RWObj_MtlReader
{
public:
  RWObj_MtlReader(NCollection_DataMap<TCollection_AsciiString, RWObj_Material>& theMaterials);

  ~RWObj_MtlReader();

  bool Read(const TCollection_AsciiString& theFolder, const TCollection_AsciiString& theFile);

private:
  bool validateScalar(const double theValue);

  bool validateColor(const NCollection_Vec3<float>& theVec);

  void processTexturePath(TCollection_AsciiString&       theTexturePath,
                          const TCollection_AsciiString& theFolder);

private:
  FILE*                                                         myFile;
  TCollection_AsciiString                                       myPath;
  NCollection_DataMap<TCollection_AsciiString, RWObj_Material>* myMaterials;
  int                                                           myNbLines;
};
