#!/bin/bash

# analyze pion0
root -l -b -q analysis_pion0_dNdCent.cpp
root -l -b -q analysis_pion0_MB_pTClass.cpp


# analyze direct photon
root -l -b -q analysis_dirPhoton_dNdCent.cpp
root -l -b -q analysis_dirPhoton_MB_pTClass.cpp

# analyze centBias
root -l -b -q analysis_centBias_asFunctionOfCent_bypTClass.cpp
