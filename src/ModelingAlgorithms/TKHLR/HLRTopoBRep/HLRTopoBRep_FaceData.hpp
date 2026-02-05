#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

//! Contains the 3 ListOfShape of a Face
//! (Internal OutLines, OutLines on restriction and IsoLines).
class HLRTopoBRep_FaceData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRTopoBRep_FaceData();

  const NCollection_List<TopoDS_Shape>& FaceIntL() const;

  const NCollection_List<TopoDS_Shape>& FaceOutL() const;

  const NCollection_List<TopoDS_Shape>& FaceIsoL() const;

  NCollection_List<TopoDS_Shape>& AddIntL();

  NCollection_List<TopoDS_Shape>& AddOutL();

  NCollection_List<TopoDS_Shape>& AddIsoL();

private:
  NCollection_List<TopoDS_Shape> myIntL;
  NCollection_List<TopoDS_Shape> myOutL;
  NCollection_List<TopoDS_Shape> myIsoL;
};

inline const NCollection_List<TopoDS_Shape>& HLRTopoBRep_FaceData::FaceIntL() const
{
  return myIntL;
}

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& HLRTopoBRep_FaceData::FaceOutL() const
{
  return myOutL;
}

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& HLRTopoBRep_FaceData::FaceIsoL() const
{
  return myIsoL;
}

//=================================================================================================

inline NCollection_List<TopoDS_Shape>& HLRTopoBRep_FaceData::AddIntL()
{
  return myIntL;
}

//=================================================================================================

inline NCollection_List<TopoDS_Shape>& HLRTopoBRep_FaceData::AddOutL()
{
  return myOutL;
}

//=================================================================================================

inline NCollection_List<TopoDS_Shape>& HLRTopoBRep_FaceData::AddIsoL()
{
  return myIsoL;
}
