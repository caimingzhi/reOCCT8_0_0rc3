# Source files for Storage package
set(OCCT_Storage_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_Storage_FILES
  Storage.cxx
  Storage.hpp

  Storage_ArrayOfSchema.hpp
  Storage_BaseDriver.cxx
  Storage_BaseDriver.hpp
  Storage_BucketOfPersistent.hpp
  Storage_CallBack.cxx
  Storage_CallBack.hpp
  Storage_Data.cxx
  Storage_Data.hpp

  Storage_DefaultCallBack.cxx
  Storage_DefaultCallBack.hpp
  Storage_Error.hpp

  Storage_HeaderData.cxx
  Storage_HeaderData.hpp

  Storage_InternalData.cxx
  Storage_InternalData.hpp
  Storage_Macros.hpp

  Storage_OpenMode.hpp

  Storage_Position.hpp

  Storage_Root.cxx
  Storage_Root.hpp
  Storage_RootData.cxx
  Storage_RootData.hpp
  Storage_Schema.cxx
  Storage_Schema.hpp

  Storage_SolveMode.hpp
  Storage_StreamExtCharParityError.hpp
  Storage_StreamFormatError.hpp
  Storage_StreamModeError.hpp
  Storage_StreamReadError.hpp
  Storage_StreamTypeMismatchError.hpp
  Storage_StreamUnknownTypeError.hpp
  Storage_StreamWriteError.hpp
  Storage_TypeData.cxx
  Storage_TypeData.hpp
  Storage_TypedCallBack.cxx
  Storage_TypedCallBack.hpp
)
