#pragma once


//! gives successive stages of reading an entity (see ParamReader)
enum IGESData_ReadStage
{
  IGESData_ReadDir,
  IGESData_ReadOwn,
  IGESData_ReadAssocs,
  IGESData_ReadProps,
  IGESData_ReadEnd
};

