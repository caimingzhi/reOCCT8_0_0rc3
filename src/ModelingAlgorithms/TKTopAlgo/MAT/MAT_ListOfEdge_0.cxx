#include <MAT_ListOfEdge.hpp>

#include <Standard_Type.hpp>

#include <MAT_TListNodeOfListOfEdge.hpp>
#include <MAT_Edge.hpp>

#define Item occ::handle<MAT_Edge>
#define Item_hxx <MAT_Edge.hpp>
#define MAT_TListNode MAT_TListNodeOfListOfEdge
#define MAT_TListNode_hxx <MAT_TListNodeOfListOfEdge.hpp>
#define Handle_MAT_TListNode occ::handle<MAT_TListNodeOfListOfEdge>
#define MAT_TList MAT_ListOfEdge
#define MAT_TList_hxx <MAT_ListOfEdge.hpp>
#define Handle_MAT_TList occ::handle<MAT_ListOfEdge>
#include <MAT_TList.hpp>
