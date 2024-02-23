#!/bin/bash

# correlation of charge with pion0
root -l -b -q analysis_correlations_withPion0_charge.cpp

# correlation of charge with DirPhoton
root -l -b -q analysis_correlations_withDirPhoton_charge.cpp
