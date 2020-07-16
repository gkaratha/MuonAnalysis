Package to run tag/probe ntuples for Muon POG
Runs on bot AOD and miniAOD format

Main code under plugins directory

runs with cmsRun run_muonAnalizer_cfg.py option1=val1
run_muonAnalizer_cfg.py is located under the "test" directory

Instructions:
cmsrel CMSSW_10_5_0 
cd CMSSW_10_5_0/src
cmsenv
git cms-init
git clone https://github.com/gkaratha/MuonAnalysis
scram b -j 8
