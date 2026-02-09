#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include <Interface_GTool.hpp>
class Interface_Protocol;
class Standard_Transient;
class Interface_ShareTool;
class Interface_InterfaceModel;

class Interface_Category
{
public:
  DEFINE_STANDARD_ALLOC

  Interface_Category()
      : myGTool(new Interface_GTool)
  {
    Init();
  }

  Interface_Category(const occ::handle<Interface_Protocol>& theProtocol)
      : myGTool(new Interface_GTool(theProtocol))
  {
    Init();
  }

  Interface_Category(const occ::handle<Interface_GTool>& theGTool)
      : myGTool(theGTool)
  {
    Init();
  }

  void SetProtocol(const occ::handle<Interface_Protocol>& theProtocol)
  {
    myGTool->SetProtocol(theProtocol);
  }

  Standard_EXPORT int CatNum(const occ::handle<Standard_Transient>& theEnt,
                             const Interface_ShareTool&             theShares);

  void ClearNums() { myNum.Nullify(); }

  Standard_EXPORT void Compute(const occ::handle<Interface_InterfaceModel>& theModel,
                               const Interface_ShareTool&                   theShares);

  Standard_EXPORT int Num(const int theNumEnt) const;

  Standard_EXPORT static int AddCategory(const char* theName);

  Standard_EXPORT static int NbCategories();

  Standard_EXPORT static const char* Name(const int theNum);

  Standard_EXPORT static int Number(const char* theName);

  Standard_EXPORT static void Init();

private:
  occ::handle<Interface_GTool>          myGTool;
  occ::handle<NCollection_HArray1<int>> myNum;
};
