

#include <StdObjMgt_ReadData.hpp>
#include <ShapePersistent_HSequence.hpp>

template <class SequenceClass>
void ShapePersistent_HSequence::node<SequenceClass>::Read(StdObjMgt_ReadData& theReadData)
{
  theReadData >> myPreviuos >> myItem >> myNext;
}

template <class SequenceClass>
void ShapePersistent_HSequence::node<SequenceClass>::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myPreviuos << myItem << myNext;
}

template <class SequenceClass>
void ShapePersistent_HSequence::instance<SequenceClass>::Read(StdObjMgt_ReadData& theReadData)
{
  theReadData >> myFirst >> myLast >> mySize;
}

template <class SequenceClass>
void ShapePersistent_HSequence::instance<SequenceClass>::Write(
  StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myFirst << myLast << mySize;
}

template <class SequenceClass>
occ::handle<SequenceClass> ShapePersistent_HSequence::instance<SequenceClass>::Import() const
{
  occ::handle<SequenceClass> aSequence = new SequenceClass;

  for (occ::handle<Node> aNode = myFirst; aNode; aNode = aNode->Next())
    aSequence->Append(aNode->Item());

  return aSequence;
}

template class ShapePersistent_HSequence::node<NCollection_HSequence<gp_XYZ>>;
template class ShapePersistent_HSequence::node<NCollection_HSequence<gp_Pnt>>;
template class ShapePersistent_HSequence::node<NCollection_HSequence<gp_Dir>>;
template class ShapePersistent_HSequence::node<NCollection_HSequence<gp_Vec>>;

template class ShapePersistent_HSequence::instance<NCollection_HSequence<gp_XYZ>>;
template class ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Pnt>>;
template class ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Dir>>;
template class ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Vec>>;

template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_XYZ>>::PName() const
{
  return "PColgp_HSequenceOfXYZ";
}

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_XYZ>>::PName() const
{
  return "PColgp_SeqNodeOfHSequenceOfXYZ";
}

template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Pnt>>::PName() const
{
  return "PColgp_HSequenceOfPnt";
}

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_Pnt>>::PName() const
{
  return "PColgp_SeqNodeOfHSequenceOfPnt";
}

template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Dir>>::PName() const
{
  return "PColgp_HSequenceOfDir";
}

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_Dir>>::PName() const
{
  return "PColgp_SeqNodeOfHSequenceOffDir";
}

template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Vec>>::PName() const
{
  return "PColgp_HSequenceOfVec";
}

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_Vec>>::PName() const
{
  return "PColgp_SeqNodeOfHSequenceOfVec";
}
