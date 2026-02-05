#pragma once

//! Defines additional commands for XSDRAW to :
//! - control of initialisation (xinit, xnorm, newmodel)
//! - analyse of the result of a transfer (recorded in a
//! TransientProcess for Read, FinderProcess for Write) :
//! statistics, various lists (roots,complete,abnormal), what
//! about one specific entity, producing a model with the
//! abnormal result
//!
//! This appendix of XSDRAW is compiled separately to distinguish
//! basic features from user callable forms
class XSDRAW_Functions
{
public:
  //! Defines and loads all basic functions for XSDRAW (as ActFunc)
  Standard_EXPORT static void Init();
};
