/**********************************************
 * Class for generating different signals;
 *  also allows for one to add random noise.
 *  Written : S.V. Paulauskas - 15 March 2012
 */
#include <fstream>
#include <iostream>

#include <cmath>

#include "SignalGenerator.h"

using namespace std;

//********** GenerateSignal **********
void SignalGenerator::GenerateSignal(void) {
   for(double i = 0; i < length_; i += res_) {
      if(type_ == "sin") {
	 signal_.push_back(SineWave(i));
      } else if(type_ == "cos") { 
	 mu_ += M_PI;
	 signal_.push_back(SineWave(i));
      } else if (type_ == "gaussian") {
	 signal_.push_back(Gaussian(i));
      }else if (type_ == "nonstationarysine") {
	 signal_.push_back(NonStationarySine(i));
      } else if (type_ == "square") {
	 signal_.push_back(SquareWave(i));
      } else if (type_ == "sawtooth") {
	 signal_.push_back(SawtoothWave(i));
      } else if (type_ == "triangle") {
	 signal_.push_back(2.*fabs(SawtoothWave(i)));
      }
   }

   if(hasNoise_) 
      for(unsigned int i = 0; i < signal_.size(); i++) 
	 signal_[i] += amp_*Noise();
}

//********** CompositeFunction **********

//********** CustomFunction **********
void SignalGenerator::CustomFunction(void) {
   ifstream readData("dataFiles/realData.dat");
   if(readData.is_open()) {
      while(readData.good()) {
	 double junk0, junk1, junk2;
	 readData >> junk0 >> junk1 >> junk2;
	 signal_.push_back(junk1);
      }
      readData.close();
   }
}
//********** Gaussian **********
double SignalGenerator::Gaussian(const double &t) {
   double coeff = amp_/(sigma_*sqrt(2*M_PI));
   double exponent = -pow((t-mu_)/sigma_,2)*0.5;
   return( coeff * exp(exponent) );
}
//********** Noise **********
double SignalGenerator::Noise(void) {
   return ( (rand() / double(RAND_MAX))*2 -1 );
}
//********** NonStationarySine **********
double SignalGenerator::NonStationarySine(const double &t) {
   double t1 = sigma_/6., t2 = 4.*sigma_/6.;       
   if (t >= 0 && t <= t1) 
      return(sin(2*M_PI*t));
   else if ( t >= t1 && t<=t2 ) 
      return(5.*sin(2*M_PI*t) + 10.*sin(4*M_PI*t));
   else if ( t >= t2 && t <= sigma_ )
      return(2.5*sin(2*M_PI*t)+6.*sin(4*M_PI*t)+
	     10*sin(6*M_PI*t));
   else
      return(0.0);
}
//********** SawtoothWave **********
double SignalGenerator::SawtoothWave(const double &t) {
   return (amp_ * (t/period_ - floor(t/period_ + 0.5)));
}
//********** Sign **********
double SignalGenerator::Sign(const double &t) {
   return ( (t<0) ? -1 : (t>0) );
}
//********** SineWave **********
double SignalGenerator::SineWave(const double &t) {
   return( sin(period_*t + mu_) );
}
//********** SquareWave **********
double SignalGenerator::SquareWave(const double &t) {
   return (amp_ * Sign(SineWave(t)) );
}
