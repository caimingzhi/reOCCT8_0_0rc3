# Source files for TDF package
set(OCCT_TDF_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_TDF_FILES
  TDF.cxx
  TDF.hpp
  TDF_Attribute.cxx
  TDF_Attribute.hpp

  TDF_AttributeDelta.cxx
  TDF_AttributeDelta.hpp

  TDF_AttributeIterator.cxx
  TDF_AttributeIterator.hpp

  TDF_ChildIDIterator.cxx
  TDF_ChildIDIterator.hpp
  TDF_ChildIterator.cxx
  TDF_ChildIterator.hpp
  TDF_ClosureMode.cxx
  TDF_ClosureMode.hpp
  TDF_ClosureTool.cxx
  TDF_ClosureTool.hpp
  TDF_ComparisonTool.cxx
  TDF_ComparisonTool.hpp
  TDF_CopyLabel.cxx
  TDF_CopyLabel.hpp
  TDF_CopyTool.cxx
  TDF_CopyTool.hpp
  TDF_Data.cxx
  TDF_Data.hpp

  TDF_DataSet.cxx
  TDF_DataSet.hpp
  TDF_DefaultDeltaOnModification.cxx
  TDF_DefaultDeltaOnModification.hpp
  TDF_DefaultDeltaOnRemoval.cxx
  TDF_DefaultDeltaOnRemoval.hpp
  TDF_Delta.cxx
  TDF_Delta.hpp

  TDF_DeltaOnAddition.cxx
  TDF_DeltaOnAddition.hpp
  TDF_DeltaOnForget.cxx
  TDF_DeltaOnForget.hpp
  TDF_DeltaOnModification.cxx
  TDF_DeltaOnModification.hpp
  TDF_DeltaOnRemoval.cxx
  TDF_DeltaOnRemoval.hpp
  TDF_DeltaOnResume.cxx
  TDF_DeltaOnResume.hpp
  TDF_DerivedAttribute.cxx
  TDF_DerivedAttribute.hpp

  TDF_HAllocator.hpp

  TDF_IDFilter.cxx
  TDF_IDFilter.hpp

  TDF_Label.cxx
  TDF_Label.hpp

  TDF_LabelNode.cxx
  TDF_LabelNode.hpp
  TDF_LabelNodePtr.hpp

  TDF_Reference.cxx
  TDF_Reference.hpp
  TDF_RelocationTable.cxx
  TDF_RelocationTable.hpp
  TDF_TagSource.cxx
  TDF_TagSource.hpp
  TDF_Tool.cxx
  TDF_Tool.hpp
  TDF_Transaction.cxx
  TDF_Transaction.hpp
)
