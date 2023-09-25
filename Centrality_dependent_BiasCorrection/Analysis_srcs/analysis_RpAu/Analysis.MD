<Analysis method>

#input
../analysis_scaled-dNdpT/pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_byCentrality #for all pT
../analysis_scaled-dNdpT/pAu200GeV_p8303ver4_option3_yieldOfgammaApion0_bypT_byCentrality #for high-pT

../analysis_scaled-dNdpT/pAu200GeV_p8303ver3_option3_Ncoll_MBevents.root # of event of Ncoll=1 events, ver3
../analysis_scaled-dNdpT/pAu200GeV_p8303ver4_option3_Ncoll_MBevents.root # of event of Ncoll=1 events, ver4

-> take YavgNcollPion0pT_cent1~5, YavgNcollDirpT_cent1~5: numerator
-> take 'ncoll_mb -> GetBinContent(2)' to get number of events of Ncoll=1 events

*assume Ncoll=1 event as pp event

TH2DpTeta_pion0dir_Ncoll1 -> # of event by pT
						  -> scale as number of event
						  -> pT rebin
					      -> 'Make it as additional analysis code'
						  -> denominator
