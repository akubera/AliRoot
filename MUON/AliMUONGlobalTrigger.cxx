/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/ 
 

/* $Id$ */


#include "AliMUONGlobalTrigger.h"
#include <assert.h>
#include "AliLog.h"
#include "AliMUONLocalStruct.h"

/// \class AliMUONGlobalTrigger
/// Global Trigger algorithm data output.
/// Built from Local and Regional algorithms.                          \n 
/// Update for copy & assigment operator,
/// add SetGlobalPattern and GetGlobalPattern method for rawdata 
/// (Ch. Finck)
/// \author Ph. Crochet

/// \cond CLASSIMP
ClassImp(AliMUONGlobalTrigger)
/// \endcond

//----------------------------------------------------------------------
AliMUONGlobalTrigger::AliMUONGlobalTrigger()
  : TObject(),
    fSingleLpt(0),
    fSingleHpt(0),
      
    fPairUnlikeLpt(0),
    fPairUnlikeHpt(0),
    
    fPairLikeLpt(0),
    fPairLikeHpt(0)
{ 
  /// Default constructor 
}

//----------------------------------------------------------------------
AliMUONGlobalTrigger::AliMUONGlobalTrigger(const AliMUONGlobalTrigger& theMUONGlobalTrig)
  : TObject(theMUONGlobalTrig),
  
    fSingleLpt(theMUONGlobalTrig.fSingleLpt),
    fSingleHpt(theMUONGlobalTrig.fSingleHpt),
    
    fPairUnlikeLpt(theMUONGlobalTrig.fPairUnlikeLpt),
    fPairUnlikeHpt(theMUONGlobalTrig.fPairUnlikeHpt),
    
    fPairLikeLpt(theMUONGlobalTrig.fPairLikeLpt),
    fPairLikeHpt(theMUONGlobalTrig.fPairLikeHpt)
{
  /// Copy constructor
}

//----------------------------------------------------------------------
AliMUONGlobalTrigger::~AliMUONGlobalTrigger()
{
  /// Destructor
}

//----------------------------------------------------------------------
AliMUONGlobalTrigger& AliMUONGlobalTrigger::operator=(const AliMUONGlobalTrigger& theMUONGlobalTrig)
{
  /// Assignement operator;
  /// equal operator (useful for non-pointer member in TClonesArray)

  if (this == &theMUONGlobalTrig)
    return *this;
    
  // base class assignement
  TObject::operator=(theMUONGlobalTrig);

  fSingleLpt  = theMUONGlobalTrig.fSingleLpt;
  fSingleHpt  = theMUONGlobalTrig.fSingleHpt;
  
  fPairUnlikeLpt  = theMUONGlobalTrig.fPairUnlikeLpt;
  fPairUnlikeHpt  = theMUONGlobalTrig.fPairUnlikeHpt;
  
  fPairLikeLpt    = theMUONGlobalTrig.fPairLikeLpt;
  fPairLikeHpt    = theMUONGlobalTrig.fPairLikeHpt;

  return *this;
}

//-----------------------------------------------------------
void AliMUONGlobalTrigger::SetFromGlobalResponse(UShort_t globalResponse)
{
  /// Set class members from global response
  /// coming from rawdata & global trigger board
  /// [US:2, LS:2, Single:2] with [Hpt, Lpt]
  /// remove Apt

  // don't have the information anymore of the sign
  fSingleLpt = globalResponse & 0x1;
  fSingleHpt = (globalResponse >> 1) & 0x1;

  fPairUnlikeLpt = (globalResponse >> 4)  & 0x1;
  fPairUnlikeHpt = (globalResponse >> 5)  & 0x1;
  
  fPairLikeLpt = (globalResponse >> 2)  & 0x1;
  fPairLikeHpt = (globalResponse >> 3)  & 0x1;
  
}

//-----------------------------------------------------------
UChar_t AliMUONGlobalTrigger::GetGlobalResponse() const
{
  /// Global trigger response
  /// from class member values
  /// [US:2, LS:2, Single:2] with [Hpt, Lpt]

  Int_t response = 0;

  if (SingleLpt())     response|= 0x1;
  if (SingleHpt())     response|= 0x2;

  if (PairLikeLpt())   response|= 0x4;
  if (PairLikeHpt())   response|= 0x8;
 
  if (PairUnlikeLpt()) response|= 0x10;
  if (PairUnlikeHpt()) response|= 0x20;

  return response;
}
//----------------------------------------------------------------------
void AliMUONGlobalTrigger::Print(Option_t* opt) const
{
  //
  // Printing Global Trigger information
  //
  TString sopt(opt);
  sopt.ToUpper();
  if ( sopt.Contains("FULL") ) { 

      printf("=============================================\n");
      printf(" Global Trigger output       Low pt  High pt\n");
      printf(" Single                    :\t");
      printf("%i\t%i\t",SingleLpt(),SingleHpt());
      printf("\n");
      
      printf(" UnlikeSign pair           :\t"); 
      printf("%i\t%i\t",PairUnlikeLpt(),PairUnlikeHpt());
      printf("\n");
      
      printf(" LikeSign pair             :\t");  
      printf("%i\t%i\t",PairLikeLpt(),PairLikeHpt());
      printf("\n");
      
      printf("=============================================\n");
  }  
}


