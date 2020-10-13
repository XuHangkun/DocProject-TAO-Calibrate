#!/bin/bash
#source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/setup.sh
MAINPROPATH=/dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build
export PATH=${MAINPROPATH}:$PATH
export LD_LIBRARY_PATH=${MAINPROPATH}:$LD_LIBRARY_PATH
#radioSource=(AmBe AmBeN1)
#radioSource=(Cs137 Mn54 Ge68 Co60)
#radioSource=(Gamma_0.511MeV Gamma_4.43MeV Gamma_6.13MeV)
#radioSource=(AmCN0 AmCN1 AmCN2  Gamma_0.511MeV)
#hep_sub ./main -o log -e log 
