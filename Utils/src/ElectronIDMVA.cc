#include "MitPhysics/Utils/interface/ElectronIDMVA.h"
#include "MitPhysics/Utils/interface/ElectronTools.h"
#include "MitPhysics/Utils/interface/IsolationTools.h"
#include "MitAna/DataTree/interface/StableData.h"
#include <TFile.h>
#include <TRandom3.h>
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"


ClassImp(mithep::ElectronIDMVA)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
ElectronIDMVA::ElectronIDMVA() :
fMethodname("BDTG method"),
fIsInitialized(kFALSE)
{
  // Constructor.
  for(UInt_t i=0; i<6; ++i) {
    fTMVAReader[i] = 0;
  }
}


//--------------------------------------------------------------------------------------------------
ElectronIDMVA::~ElectronIDMVA()
{
  for(UInt_t i=0; i<6; ++i) {
    if (fTMVAReader[i]) delete fTMVAReader[i];
  }
}

//--------------------------------------------------------------------------------------------------
void ElectronIDMVA::Initialize( TString methodName,
                                TString Subdet0Pt10To20Weights , 
                                TString Subdet1Pt10To20Weights , 
                                TString Subdet2Pt10To20Weights,
                                TString Subdet0Pt20ToInfWeights,
                                TString Subdet1Pt20ToInfWeights, 
                                TString Subdet2Pt20ToInfWeights,
                                ElectronIDMVA::MVAType type) {

  fIsInitialized = kTRUE;
  
  fMethodname = methodName;
    
  for(UInt_t i=0; i<6; ++i) {
    if (fTMVAReader[i]) delete fTMVAReader[i];

    fTMVAReader[i] = new TMVA::Reader( "!Color:!Silent:Error" );  
    fTMVAReader[i]->SetVerbose(kTRUE);

    if (type == kBaseline) {
      fTMVAReader[i]->AddVariable( "SigmaIEtaIEta",         &fMVAVar_EleSigmaIEtaIEta         );
      fTMVAReader[i]->AddVariable( "DEtaIn",                &fMVAVar_EleDEtaIn                );
      fTMVAReader[i]->AddVariable( "DPhiIn",                &fMVAVar_EleDPhiIn                );
      fTMVAReader[i]->AddVariable( "FBrem",                 &fMVAVar_EleFBrem                 );
      fTMVAReader[i]->AddVariable( "SigmaIPhiIPhi",         &fMVAVar_EleSigmaIPhiIPhi         );
      fTMVAReader[i]->AddVariable( "NBrem",                 &fMVAVar_EleNBrem                 );
      fTMVAReader[i]->AddVariable( "OneOverEMinusOneOverP", &fMVAVar_EleOneOverEMinusOneOverP );      
    }
    
    if (type == kNoIPInfo) {
      fTMVAReader[i]->AddVariable( "SigmaIEtaIEta",         &fMVAVar_EleSigmaIEtaIEta         );
      fTMVAReader[i]->AddVariable( "DEtaIn",                &fMVAVar_EleDEtaIn                );
      fTMVAReader[i]->AddVariable( "DPhiIn",                &fMVAVar_EleDPhiIn                );
      fTMVAReader[i]->AddVariable( "FBrem",                 &fMVAVar_EleFBrem                 );
      fTMVAReader[i]->AddVariable( "EOverP",                &fMVAVar_EleEOverP                );
      fTMVAReader[i]->AddVariable( "ESeedClusterOverPout",  &fMVAVar_EleESeedClusterOverPout  );
      fTMVAReader[i]->AddVariable( "SigmaIPhiIPhi",         &fMVAVar_EleSigmaIPhiIPhi         );
      fTMVAReader[i]->AddVariable( "NBrem",                 &fMVAVar_EleNBrem                 );
      fTMVAReader[i]->AddVariable( "OneOverEMinusOneOverP", &fMVAVar_EleOneOverEMinusOneOverP );      
      fTMVAReader[i]->AddVariable( "ESeedClusterOverPIn",   &fMVAVar_EleESeedClusterOverPIn   );
    }
    if (type == kWithIPInfo) {
      fTMVAReader[i]->AddVariable( "SigmaIEtaIEta",         &fMVAVar_EleSigmaIEtaIEta         );
      fTMVAReader[i]->AddVariable( "DEtaIn",                &fMVAVar_EleDEtaIn                );
      fTMVAReader[i]->AddVariable( "DPhiIn",                &fMVAVar_EleDPhiIn                );
      fTMVAReader[i]->AddVariable( "D0",                    &fMVAVar_EleD0                    );
      fTMVAReader[i]->AddVariable( "FBrem",                 &fMVAVar_EleFBrem                 );
      fTMVAReader[i]->AddVariable( "EOverP",                &fMVAVar_EleEOverP                );
      fTMVAReader[i]->AddVariable( "ESeedClusterOverPout",  &fMVAVar_EleESeedClusterOverPout  );
      fTMVAReader[i]->AddVariable( "SigmaIPhiIPhi",         &fMVAVar_EleSigmaIPhiIPhi         );
      fTMVAReader[i]->AddVariable( "NBrem",                 &fMVAVar_EleNBrem                 );
      fTMVAReader[i]->AddVariable( "OneOverEMinusOneOverP", &fMVAVar_EleOneOverEMinusOneOverP );      
      fTMVAReader[i]->AddVariable( "ESeedClusterOverPIn",   &fMVAVar_EleESeedClusterOverPIn   );
      fTMVAReader[i]->AddVariable( "IP3d",                  &fMVAVar_EleIP3d                  );
      fTMVAReader[i]->AddVariable( "IP3dSig",               &fMVAVar_EleIP3dSig               );
    }

    if (i==0) fTMVAReader[i]->BookMVA(fMethodname , Subdet0Pt10To20Weights );
    if (i==1) fTMVAReader[i]->BookMVA(fMethodname , Subdet1Pt10To20Weights );
    if (i==2) fTMVAReader[i]->BookMVA(fMethodname , Subdet2Pt10To20Weights );
    if (i==3) fTMVAReader[i]->BookMVA(fMethodname , Subdet0Pt20ToInfWeights );
    if (i==4) fTMVAReader[i]->BookMVA(fMethodname , Subdet1Pt20ToInfWeights );
    if (i==5) fTMVAReader[i]->BookMVA(fMethodname , Subdet2Pt20ToInfWeights );

  }

  std::cout << "Electron ID MVA Initialization\n";
  std::cout << "MethodName : " << fMethodname << " , type == " << type << std::endl;
  std::cout << "Load weights file : " << Subdet0Pt10To20Weights << std::endl;
  std::cout << "Load weights file : " << Subdet1Pt10To20Weights << std::endl;
  std::cout << "Load weights file : " << Subdet2Pt10To20Weights << std::endl;
  std::cout << "Load weights file : " << Subdet0Pt20ToInfWeights << std::endl;
  std::cout << "Load weights file : " << Subdet1Pt20ToInfWeights << std::endl;
  std::cout << "Load weights file : " << Subdet2Pt20ToInfWeights << std::endl;

}

//--------------------------------------------------------------------------------------------------
Double_t ElectronIDMVA::MVAValue(Double_t ElePt , Double_t EleSCEta,
                                 Double_t EleSigmaIEtaIEta,
                                 Double_t EleDEtaIn,
                                 Double_t EleDPhiIn,
                                 Double_t EleHoverE,
                                 Double_t EleD0,
                                 Double_t EleDZ,
                                 Double_t EleFBrem,
                                 Double_t EleEOverP,
                                 Double_t EleESeedClusterOverPout,
                                 Double_t EleSigmaIPhiIPhi,
                                 Double_t EleNBrem,
                                 Double_t EleOneOverEMinusOneOverP,
                                 Double_t EleESeedClusterOverPIn,
                                 Double_t EleIP3d,
                                 Double_t EleIP3dSig
  ) {
  
  if (!fIsInitialized) { 
    std::cout << "Error: ElectronIDMVA not properly initialized.\n"; 
    return -9999;
  }

  Int_t subdet = 0;
  if (fabs(EleSCEta) < 1.0) subdet = 0;
  else if (fabs(EleSCEta) < 1.479) subdet = 1;
  else subdet = 2;
  Int_t ptBin = 0;
  if (ElePt > 20.0) ptBin = 1;
  
  //set all input variables
  fMVAVar_EleSigmaIEtaIEta = EleSigmaIEtaIEta;
  fMVAVar_EleDEtaIn = EleDEtaIn;
  fMVAVar_EleDPhiIn = EleDPhiIn;
  fMVAVar_EleHoverE = EleHoverE;
  fMVAVar_EleD0 = EleD0;
  fMVAVar_EleDZ = EleDZ;
  fMVAVar_EleFBrem = EleFBrem;
  fMVAVar_EleEOverP = EleEOverP;
  fMVAVar_EleESeedClusterOverPout = EleESeedClusterOverPout;
  fMVAVar_EleSigmaIPhiIPhi = EleSigmaIPhiIPhi;
  fMVAVar_EleNBrem = EleNBrem;
  fMVAVar_EleOneOverEMinusOneOverP = EleOneOverEMinusOneOverP;
  fMVAVar_EleESeedClusterOverPIn = EleESeedClusterOverPIn;
  fMVAVar_EleIP3d = EleIP3d;
  fMVAVar_EleIP3dSig = EleIP3dSig;

  Double_t mva = -9999;  
  TMVA::Reader *reader = 0;
  Int_t MVABin = -1;
  if (subdet == 0 && ptBin == 0) MVABin = 0;
  if (subdet == 1 && ptBin == 0) MVABin = 1;
  if (subdet == 2 && ptBin == 0) MVABin = 2;
  if (subdet == 0 && ptBin == 1) MVABin = 3;
  if (subdet == 1 && ptBin == 1) MVABin = 4;
  if (subdet == 2 && ptBin == 1) MVABin = 5;
  assert(MVABin >= 0 && MVABin <= 5);
  reader = fTMVAReader[MVABin];
                                                
  mva = reader->EvaluateMVA( fMethodname );

  return mva;
}



//--------------------------------------------------------------------------------------------------
Double_t ElectronIDMVA::MVAValue(const Electron *ele, const Vertex *vertex) {
  
  if (!fIsInitialized) { 
    std::cout << "Error: ElectronIDMVA not properly initialized.\n"; 
    return -9999;
  }

  Int_t subdet = 0;
  if (ele->SCluster()->AbsEta() < 1.0) subdet = 0;
  else if (ele->SCluster()->AbsEta() < 1.479) subdet = 1;
  else subdet = 2;
  Int_t ptBin = 0;
  if (ele->Pt() > 20.0) ptBin = 1;
  
  //set all input variables
  fMVAVar_EleSigmaIEtaIEta = ele->CoviEtaiEta() ; 
  fMVAVar_EleDEtaIn = ele->DeltaEtaSuperClusterTrackAtVtx(); 
  fMVAVar_EleDPhiIn = ele->DeltaPhiSuperClusterTrackAtVtx(); 
  fMVAVar_EleHoverE = ele->HadronicOverEm(); 
  fMVAVar_EleD0 = ele->BestTrk()->D0Corrected(*vertex); 
  fMVAVar_EleDZ = ele->BestTrk()->DzCorrected(*vertex); 
  fMVAVar_EleFBrem = ele->FBrem(); 
  fMVAVar_EleEOverP = ele->ESuperClusterOverP(); 
  fMVAVar_EleESeedClusterOverPout = ele->ESeedClusterOverPout(); 
  if (!TMath::IsNaN(ele->SCluster()->Seed()->CoviPhiiPhi())) fMVAVar_EleSigmaIPhiIPhi = TMath::Sqrt(ele->SCluster()->Seed()->CoviPhiiPhi()); 
  else fMVAVar_EleSigmaIPhiIPhi = ele->CoviEtaiEta();
  fMVAVar_EleNBrem = ele->NumberOfClusters() - 1; 
  fMVAVar_EleOneOverEMinusOneOverP = (1.0/(ele->SCluster()->Energy())) - 1.0 / ele->BestTrk()->P(); 
  fMVAVar_EleESeedClusterOverPIn = ele->ESeedClusterOverPIn(); 
  fMVAVar_EleIP3d = ele->Ip3dPV(); 
  fMVAVar_EleIP3dSig = ele->Ip3dPVSignificance(); 

  Double_t mva = -9999;  
  TMVA::Reader *reader = 0;
  Int_t MVABin = -1;
  if (subdet == 0 && ptBin == 0) MVABin = 0;
  if (subdet == 1 && ptBin == 0) MVABin = 1;
  if (subdet == 2 && ptBin == 0) MVABin = 2;
  if (subdet == 0 && ptBin == 1) MVABin = 3;
  if (subdet == 1 && ptBin == 1) MVABin = 4;
  if (subdet == 2 && ptBin == 1) MVABin = 5;
  assert(MVABin >= 0 && MVABin <= 5);
  reader = fTMVAReader[MVABin];
                                                
  mva = reader->EvaluateMVA( fMethodname );

  return mva;
}