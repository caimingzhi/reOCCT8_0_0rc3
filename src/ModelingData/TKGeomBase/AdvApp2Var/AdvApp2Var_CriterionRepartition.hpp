#pragma once

//! way of cutting process//! all new cutting points at each step of cutting
//! process : (a+i(b-a)/N)i at step N,
//! (a+i(b-a)/(N+1))i at step N+1,...
//! where (a,b) is the global interval//! add one new cutting point at each step
//! of cutting process
enum AdvApp2Var_CriterionRepartition
{
  AdvApp2Var_Regular,
  AdvApp2Var_Incremental
};
