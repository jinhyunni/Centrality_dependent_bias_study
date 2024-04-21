#!/usr/bin/perl -w

print "Input simulation version to analyze: ";
$version = <STDIN>;
chomp($version);

# run BBCs charged particle pTsum correlated with mid-pion0
system "root -l -b -q 'analysis_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0.cpp(\"${version}\")'";
system "root -l -b -q 'analysis_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0_broaderCut.cpp(\"${version}\")'";

# run BBCs charged particle pTsum correlated with mid-dirPhoton
system "root -l -b -q 'analysis_correlations_BBCsMultiplicity_chargepTsum_corrWithMidDirPhoton.cpp(\"${version}\")'";
system "root -l -b -q 'analysis_correlations_BBCsMultiplicity_chargepTsum_corrWithMidDirPhoton_broaderCut.cpp(\"${version}\")'";
