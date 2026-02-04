#pragma once


#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <RWObj_Material.hpp>
#include <NCollection_DataMap.hpp>

//! Reader of mtl files.
class RWObj_MtlReader
{
public:
  //! Main constructor.
  RWObj_MtlReader(NCollection_DataMap<TCollection_AsciiString, RWObj_Material>& theMaterials);

  //! Destructor.
  ~RWObj_MtlReader();

  //! Read the file.
  bool Read(const TCollection_AsciiString& theFolder, const TCollection_AsciiString& theFile);

private:
  //! Validate scalar value
  bool validateScalar(const double theValue);

  //! Validate RGB color
  bool validateColor(const NCollection_Vec3<float>& theVec);

  //! Process texture path.
  void processTexturePath(TCollection_AsciiString&       theTexturePath,
                          const TCollection_AsciiString& theFolder);

private:
  FILE*                                                         myFile;
  TCollection_AsciiString                                       myPath;
  NCollection_DataMap<TCollection_AsciiString, RWObj_Material>* myMaterials;
  int                                                           myNbLines;
};

