#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRepBuild_LoopSet.hpp>
#include <TopOpeBRepBuild_BlockIterator.hpp>
#include <TopOpeBRepBuild_BlockBuilder.hpp>
#include <TopOpeBRepBuild_SolidAreaBuilder.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRepBuild_ShellFaceSet;
class TopoDS_Shape;
class TopOpeBRepBuild_ShapeSet;

class TopOpeBRepBuild_SolidBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_SolidBuilder();

  //! Create a SolidBuilder to build the areas on
  //! the shapes (shells, blocks of faces) described by <LS>.
  Standard_EXPORT TopOpeBRepBuild_SolidBuilder(TopOpeBRepBuild_ShellFaceSet& FS,
                                               const bool                    ForceClass = false);

  Standard_EXPORT void InitSolidBuilder(TopOpeBRepBuild_ShellFaceSet& FS, const bool ForceClass);

  Standard_EXPORT int InitSolid();

  Standard_EXPORT bool MoreSolid() const;

  Standard_EXPORT void NextSolid();

  Standard_EXPORT int InitShell();

  Standard_EXPORT bool MoreShell() const;

  Standard_EXPORT void NextShell();

  Standard_EXPORT bool IsOldShell() const;

  //! Returns current shell
  //! This shell may be :
  //! * an old shell OldShell(), which has not been reconstructed;
  //! * a new shell made of faces described by ...NewFace() methods.
  Standard_EXPORT const TopoDS_Shape& OldShell() const;

  Standard_EXPORT int InitFace();

  Standard_EXPORT bool MoreFace() const;

  Standard_EXPORT void NextFace();

  //! Returns current new face of current new shell.
  Standard_EXPORT const TopoDS_Shape& Face() const;

private:
  Standard_EXPORT void MakeLoops(TopOpeBRepBuild_ShapeSet& SS);

  TopOpeBRepBuild_LoopSet          myLoopSet;
  TopOpeBRepBuild_BlockIterator    myBlockIterator;
  TopOpeBRepBuild_BlockBuilder     myBlockBuilder;
  TopOpeBRepBuild_SolidAreaBuilder mySolidAreaBuilder;
};

