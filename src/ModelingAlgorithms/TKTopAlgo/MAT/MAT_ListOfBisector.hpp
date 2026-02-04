#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class MAT_TListNodeOfListOfBisector;
class MAT_Bisector;

class MAT_ListOfBisector : public Standard_Transient
{

public:
  Standard_EXPORT MAT_ListOfBisector();

  Standard_EXPORT ~MAT_ListOfBisector() override;

  Standard_EXPORT void First();

  Standard_EXPORT void Last();

  Standard_EXPORT void Init(const occ::handle<MAT_Bisector>& aniten);

  Standard_EXPORT void Next();

  Standard_EXPORT void Previous();

  Standard_EXPORT bool More() const;

  Standard_EXPORT occ::handle<MAT_Bisector> Current() const;

  Standard_EXPORT void Current(const occ::handle<MAT_Bisector>& anitem) const;

  Standard_EXPORT occ::handle<MAT_Bisector> FirstItem() const;

  Standard_EXPORT occ::handle<MAT_Bisector> LastItem() const;

  Standard_EXPORT occ::handle<MAT_Bisector> PreviousItem() const;

  Standard_EXPORT occ::handle<MAT_Bisector> NextItem() const;

  int Number() const;

  int Index() const;

  Standard_EXPORT occ::handle<MAT_Bisector> Brackets(const int anindex);

  occ::handle<MAT_Bisector> operator()(const int anindex) { return Brackets(anindex); }

  Standard_EXPORT void Unlink();

  Standard_EXPORT void LinkBefore(const occ::handle<MAT_Bisector>& anitem);

  Standard_EXPORT void LinkAfter(const occ::handle<MAT_Bisector>& anitem);

  Standard_EXPORT void FrontAdd(const occ::handle<MAT_Bisector>& anitem);

  Standard_EXPORT void BackAdd(const occ::handle<MAT_Bisector>& anitem);

  Standard_EXPORT void Permute();

  Standard_EXPORT void Loop() const;

  bool IsEmpty() const;

  Standard_EXPORT void Dump(const int ashift, const int alevel);

  DEFINE_STANDARD_RTTI_INLINE(MAT_ListOfBisector, Standard_Transient)

private:
  occ::handle<MAT_TListNodeOfListOfBisector> thefirstnode;
  occ::handle<MAT_TListNodeOfListOfBisector> thelastnode;
  occ::handle<MAT_TListNodeOfListOfBisector> thecurrentnode;
  int                                        thecurrentindex;
  int                                        thenumberofitems;
};

#define Item occ::handle<MAT_Bisector>
#define Item_hxx <MAT_Bisector.hpp>
#define MAT_TListNode MAT_TListNodeOfListOfBisector
#define MAT_TListNode_hxx <MAT_TListNodeOfListOfBisector.hpp>
#define Handle_MAT_TListNode occ::handle<MAT_TListNodeOfListOfBisector>
#define MAT_TList MAT_ListOfBisector
#define MAT_TList_hxx <MAT_ListOfBisector.hpp>
#define Handle_MAT_TList occ::handle<MAT_ListOfBisector>

#include <MAT_TList_1.hpp>

#undef Item
#undef Item_hxx
#undef MAT_TListNode
#undef MAT_TListNode_hxx
#undef Handle_MAT_TListNode
#undef MAT_TList
#undef MAT_TList_hxx
#undef Handle_MAT_TList

