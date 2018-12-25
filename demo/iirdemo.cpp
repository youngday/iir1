// Usage Examples
//
// This shows you how to operate the filters
//

// This is the only include you need
#include "Iir.h"

#include <stdio.h>

int main (int,char**)
{
	// 4th order for all filters shown here
	const int order = 4;

	// sampling rate here 1kHz as an example
	const float samplingrate = 1000;

	FILE *fimpulse = NULL;

	// Bandstop filter
	// Here the "direct form I" is chosen for the number crunching
	Iir::Butterworth::BandStop<order,Iir::DirectFormI> bs;
	const float center_frequency = 100;
	const float frequency_width = 20;
	bs.setup (samplingrate, center_frequency, frequency_width);
	fimpulse = fopen("bs.dat","wt");
	for(int i=0;i<1000;i++) 
	{
		double a=0;
		if (i==10) a = 1;
		double b = bs.filter(a);
		fprintf(fimpulse,"%e\n",b);
	}
	fclose(fimpulse);
	
	// Butterworth lowpass with gain ("LowShelf" instead of "LowPass")
	Iir::Butterworth::LowShelf<order> f;
	const float cutoff_frequency = 100; // Hz
	const float passband_gain = 10; // db
	f.setup (samplingrate, cutoff_frequency,passband_gain);
	fimpulse = fopen("lp.dat","wt");
	for(int i=0;i<1000;i++) 
	{
		double a=0;
		if (i==10) a = 1;
		double b = f.filter(a);
		fprintf(fimpulse,"%e\n",b);
	}
	fclose(fimpulse);
	
	// RBJ highpass filter
	// The Q factor determines the resonance at the
	// cutoff frequency. If Q=1/sqrt(2) then the transition
	// has no resonance. The higher the Q-factor the higher
	// the resonance.
	Iir::RBJ::HighPass hp;
	const float hp_cutoff_frequency = 100;
	const float hp_qfactor = 5;
	hp.setup (samplingrate, hp_cutoff_frequency, hp_qfactor);
	fimpulse = fopen("hp_rbj.dat","wt");
	for(int i=0;i<1000;i++) 
	{
		double a=0;
		if (i==10) a = 1;
		double b = hp.filter(a);
		fprintf(fimpulse,"%e\n",b);
	}
	fclose(fimpulse);

	Iir::Elliptic::LowPass<order> lp_elliptic;
	const float pass_ripple_db = 5; // dB
	const float rolloff = 0.1;
	lp_elliptic.setup (samplingrate,
			   cutoff_frequency,
			   pass_ripple_db,
			   rolloff);
	fimpulse = fopen("lp_elliptic.dat","wt");
	for(int i=0;i<1000;i++) 
	{
		double a=0;
		if (i==10) a = 1;
		double b = lp_elliptic.filter(a);
		fprintf(fimpulse,"%e\n",b);
	}
	fclose(fimpulse);

	Iir::ChebyshevI::LowPass<order> lp_cheby1;
	lp_cheby1.setup (samplingrate,
			 cutoff_frequency,
			 pass_ripple_db);
	fimpulse = fopen("lp_cheby1.dat","wt");
	for(int i=0;i<1000;i++) 
	{
		double a=0;
		if (i==10) a = 1;
		double b = lp_cheby1.filter(a);
		fprintf(fimpulse,"%e\n",b);
	}
	fclose(fimpulse);

	Iir::ChebyshevII::LowPass<order> lp_cheby2;
	double stop_ripple_dB = 20;
	lp_cheby2.setup (samplingrate,
			 cutoff_frequency,
			 stop_ripple_dB);
	fimpulse = fopen("lp_cheby2.dat","wt");
	for(int i=0;i<1000;i++) 
	{
		double a=0;
		if (i==10) a = 1;
		double b = lp_cheby2.filter(a);
		fprintf(fimpulse,"%e\n",b);
	}
	fclose(fimpulse);

	Iir::Bessel::BandPass<order> bp_bessel;
	bp_bessel.setup (samplingrate,
			 center_frequency, frequency_width);
	fimpulse = fopen("bp_bessel.dat","wt");
	for(int i=0;i<1000;i++) 
	{
		double a=0;
		if (i==10) a = 1;
		double b = bp_bessel.filter(a);
		fprintf(fimpulse,"%e\n",b);
	}
	fclose(fimpulse);

	printf("finished!\n");
	printf("Now run `plot_impulse_fresponse.py` to display the impulse/frequency responses.\n");
}
