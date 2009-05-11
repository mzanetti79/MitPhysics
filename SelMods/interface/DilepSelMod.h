//--------------------------------------------------------------------------------------------------
// $Id: DilepSelMod.h,v 1.3 2009/01/29 10:05:38 loizides Exp $
//
// DilepSelMod
// 
// This module will select a specific event if a dilepton pair can be formed among the
// possible combinations from the input collection that fulfills given criteria.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITPHYSICS_SELMODS_DILEPSELMOD_H
#define MITPHYSICS_SELMODS_DILEPSELMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

namespace mithep 
{
  class DilepSelMod : public BaseMod
  {
    public:
      DilepSelMod(const char *name="DilepSelMod", 
                  const char *title="Dilepton selection module");
      ~DilepSelMod() {}

      void         SetCleanLeptonsName(const char *n)  { fCleanLeptonsName = n; }
      void         SetIgnoreElCharge(Bool_t b)         { fIgnoreElCharge = b;   }
      void         SetMaxZMass(Double_t m)             { fMaxZMass = m;         }
      void         SetMinDilMass(Double_t m)           { fDilMinMass = m;       }
      void         SetMinPt(Double_t pt)               { fMinPt      = pt;      }
      void         SetMinZMass(Double_t m)             { fMinZMass = m;         }

    protected:
      void         Process();
      void         SlaveBegin();

      TString      fCleanLeptonsName;     //clean leptons name (input)
      Double_t     fMinPt;                //minimum pt for leptons
      Double_t     fDilMinMass;           //minimum dilepton mass
      Double_t     fMinZMass;             //minimum Z mass
      Double_t     fMaxZMass;             //maximum Z mass
      Bool_t       fIgnoreElCharge;       //=true then ignore electron charge for z mass cut
      TH1D        *fNAccCounters;         //!history of cuts
      TH1D        *fAllDiLepMass;         //!dilepton mass for all dilepton pairs
      TH1D        *fDiElMass;             //!dielectron mass 
      TH1D        *fDiMuMass;             //!dimuon mass
      TH1D        *fElMuMass;             //!electron-muon mass 
      TH1D        *fAllDiLepMassAcc;      //!accepted dilepton mass for all dilepton pairs
      TH1D        *fDiElMassAcc;          //!accepted dielectron mass 
      TH1D        *fDiMuMassAcc;          //!accepted dimuon mass
      TH1D        *fElMuMassAcc;          //!accepted electron-muon mass 
      TH1D        *fNLeptons;             //!number of leptons
      TH1D        *fNGPairs;              //!number of good pairs
      TH1D        *fNZPairs;              //!number of bad (Z) pairs
          
    ClassDef(DilepSelMod,1) // Dilepton selection module
  };
}
#endif