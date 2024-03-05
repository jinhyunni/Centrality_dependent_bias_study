#!/bin/bash

# correlation of charge with pion0
root -l -b -q analysis_correlations_charge_withMidPion0.cpp
root -l -b -q analysis_correlations_ratioOfChargeEta_pTClass2MB_withMidPion0.cpp

# correlation of charge with DirPhoton
root -l -b -q analysis_correlations_charge_withMidDirPhoton.cpp
root -l -b -q analysis_correlations_ratioOfChargeEta_pTClass2MB_withMidDirPhoton.cpp

# ratio of correlations
root -l -b -q analysis_correlations_ratioOfRatioPtClass2MB_pion0toDirPhoton.cpp

# ratio of correlations of charge by pTClass
root -l -b -q analysis_correlations_charge_bypTClass_withMidPion0.cpp
root -l -b -q analysis_correlations_ratioOfChargeEta_bypTClass_pTClass2MB_withMidPion0.cpp
