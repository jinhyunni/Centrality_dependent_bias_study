#!/bin/bash

# correlation of charge with pion0
root -l -b -q analysis_correlations_charge_withMidPion0.cpp
root -l -b -q analysis_correlations_ratioOfChargeEta_pTClass2MB_withMidPion0.cpp

# correlation of charge with DirPhoton
root -l -b -q analysis_correlations_charge_withMidDirPhoton.cpp
root -l -b -q analysis_correlations_ratioOfChargeEta_pTClass2MB_withMidDirPhoton.cpp
