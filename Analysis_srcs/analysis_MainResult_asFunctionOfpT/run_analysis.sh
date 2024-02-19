#!/bin/bash

# analyzing dirPhoton
root -l -b -q analysis_dirPhoton_dNdpT_MBevents.cpp
root -l -b -q analysis_dirPhoton_dNdpT_allEvents.cpp
root -l -b -q analysis_dirPhoton_ratio_dNdpT_highpT_cent2mb.cpp

# analyzing pion0
root -l -b -q analysis_pion0_dNdpT_MBevents.cpp
root -l -b -q analysis_pion0_dNdpT_allEvents.cpp
root -l -b -q analysis_pion0_ratio_dNdpT_highpT_cent2mb.cpp

# analyzing centBias ratio
root -l -b -q analysis_ratio_ratioCent2MB_highpT_dir2pion0_bypT.cpp
