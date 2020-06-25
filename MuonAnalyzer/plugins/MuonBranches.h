//
// Original Author:
//                george karathanasis
//         Created:  Thu, 23 Mar 2019 17:40:23 GMT
//
// filling functions for aod and miniaod tag/probe


#ifndef MuonAnalysis_MuonAnalyzer_MuonBranches
#define MuonAnalysis_MuonAnalyzer_MuonBranches

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "helper.h"
#include "NtupleContent.h"
#include <type_traits>

template<typename MUON>
inline void FillTagBranches( const MUON & muon, NtupleContent & nt){
  nt.tag_pt=muon.pt();
  nt.tag_eta=muon.eta();
  nt.tag_phi=muon.phi();
  nt.tag_isLoose=muon.passed(reco::Muon::CutBasedIdLoose);
  nt.tag_isMedium=muon.passed(reco::Muon::CutBasedIdMedium);
  nt.tag_isTight=muon.passed(reco::Muon::CutBasedIdTight);
  nt.tag_isSoft=muon.passed(reco::Muon::SoftCutBasedId);
  nt.tag_isHighPt=muon.passed(reco::Muon::CutBasedIdTrkHighPt);
}

template<typename MUON>
inline void FillSuccessProbeBranches( const MUON & muon, NtupleContent & nt){
 nt.probe_isLoose=muon.passed(reco::Muon::CutBasedIdLoose);
 // nt.probe_isMedium=muon.passed(reco::Muon::CutBasedIdMedium);
 // nt.probe_isTight=muon.passed(reco::Muon::CutBasedIdTight);
 // nt.probe_isSoft=muon.passed(reco::Muon::SoftCutBasedId);
 // nt.probe_isHighPt=muon.passed(reco::Muon::CutBasedIdTrkHighPt);
}

template<typename TRK>
inline void FillProbeBranches( const TRK & trk, NtupleContent & nt, bool success){
  nt.probe_pt=trk.pt();
  nt.probe_eta=trk.eta();
  nt.probe_phi=trk.phi();
  if (success){
     //FillSuccessProbeBranches<reco::Muon>(trk,nt);
     nt.probe_isLoose=trk.passed(reco::Muon::CutBasedIdLoose);
     nt.probe_isMedium=trk.passed(reco::Muon::CutBasedIdMedium);
     nt.probe_isTight=trk.passed(reco::Muon::CutBasedIdTight);
     nt.probe_isSoft=trk.passed(reco::Muon::SoftCutBasedId);
     nt.probe_isHighPt=trk.passed(reco::Muon::CutBasedIdTrkHighPt);
     nt.probe_isPF=trk.isPFMuon();
     nt.probe_isGlobal=trk.isGlobalMuon();
     if ( trk.globalTrack().isNonnull() )
        nt.probe_trkChi2=trk.globalTrack()->normalizedChi2();
     else
        nt.probe_trkChi2=-99;
     if ( trk.innerTrack().isNonnull() &&  trk.innerTrack().isAvailable() ){
        nt.probe_validFraction=trk.innerTrack()->validFraction();
        nt.probe_trackerLayers=trk.innerTrack()->hitPattern().trackerLayersWithMeasurement();
        nt.probe_pixelLayers=trk.innerTrack()->hitPattern().pixelLayersWithMeasurement();
        nt.probe_dxy=trk.innerTrack()->dxy(reco::TrackBase::Point(nt.pv_x,nt.pv_y,nt.pv_z));
        nt.probe_dz=trk.innerTrack()->dz(reco::TrackBase::Point(nt.pv_x,nt.pv_y,nt.pv_z));
    } else{
        nt.probe_validFraction=-99;   nt.probe_trackerLayers=-99;   
        nt.probe_pixelLayers=-99;     nt.probe_dxy=-99;  
        nt.probe_dz=-99;
    }
     nt.probe_positionChi2=trk.combinedQuality().chi2LocalPosition;
     nt.probe_trkKink=trk.combinedQuality().trkKink;
//     nt.probe_segmentCompatibility= 
     nt.probe_isMuMatched=true;
  }
   else{
     
     nt.probe_isLoose=false;        nt.probe_isMedium=false;
     nt.probe_isTight=false;        nt.probe_isSoft=false;
     nt.probe_isHighPt=false;       nt.probe_isMuMatched=false;
     nt.probe_isPF=false;           nt.probe_isGlobal=false;
     nt.probe_validFraction=-99;    nt.probe_trkChi2=-99;
     nt.probe_positionChi2=-99;     nt.probe_trkKink=-99;
     nt. probe_trackerLayers=-99;   nt. probe_pixelLayers=-99;
     nt.probe_dxy=-99;              nt.probe_dz=-99;
  }
}

template<typename MUO, typename TRK>
inline void FillPairBranches( const MUO & muon, const TRK & trk, NtupleContent & nt){
   math::PtEtaPhiMLorentzVector mu1(muon.pt(), muon.eta(), muon.phi(), MU_MASS);
   math::PtEtaPhiMLorentzVector mu2(trk.pt(), trk.eta(), trk.phi(), MU_MASS); 
   nt.pair_pt=(mu1+mu2).pt();   
   nt.pair_mass=(mu1+mu2).mass();        
   nt.pair_eta=(mu1+mu2).eta();
   nt.pair_phi=(mu1+mu2).phi();   
   nt.pair_dz=muon.vz()-trk.vz();
}


#endif
