/** \file SignalGenertator.h
 * Class for generating different kinds of signals;
 *   also allows for one to add random noise.
 * Written: S.V. Paulauskas - 15 March 2012
 */
#include <string>
#include <vector>

#include <cstdlib>

#include "time.h"

class SignalGenerator {
 public:
   SignalGenerator() {srand(time(NULL));};
   ~SignalGenerator() {};

   void GenerateSignal(void); 
   ///< Method to generate the signals.
   void SetAmplitude(const double &amplitude) {amp_ = amplitude;};
   ///< Set the amplitude of the signal.
   void SetDecayConstant(const double &decay) {decay_ = decay;}; 
   ///< Set the decay constant for exponential decays.
   void SetDelay(const double &delay) {mu_ = delay;}; 
   ///< Set the signal delay.
   void SetFlattop(const double &flattop) {flattop_ = flattop;};
   ///< Set flattop for trapezoidal signal (not implemented yet).
   void SetNoise(const bool &noise) {hasNoise_ = noise;} 
   ///< Set to true if the signal has noise
   void SetNoiseAmplitude(const double &amplitude) {noiseAmp_ = amplitude;}; 
   ///< Set the amplitude of the noise
   void SetPeriod(const double &period) {period_ = period;}; 
   ///< Set the period of the signal
   void SetRisetime(const double &risetime) {risetime_ = risetime;};
   ///< Set the risetime for a trapezoidal signal (not implemented yet).
   void SetSigma(const double &sigma) {sigma_ = sigma;}; 
   ///< Set the sigma for the signal
   void SetSignalLength(const unsigned int &sigLength) {length_ = sigLength;} 
   ///< Set the Length of the generated signal
   void SetSignalResolution(const double &sigRes) {res_ = sigRes;}
   void SetSignalType (const std::string &sigType) {type_ = sigType;}
   void SetSignalType (const std::string &sigTypeA, const std::string &sigTypeB)
      {type_ = sigTypeA; typeA_ = sigTypeB;};

   std::vector<double>* GetSignal() {return &signal_;};
 private:
   bool hasNoise_;
   double amp_, decay_, mu_, sigma_, period_, risetime_, flattop_, res_;
   double noiseAmp_;
   std::string type_, typeA_;
   std::vector<double> signal_;
   unsigned int length_;
      
   //double CompositeFunction();
   double Gaussian(const double &t);
   double Noise(void);
   double NonStationarySine(const double &t);
   double SawtoothWave(const double &t);
   double SineWave(const double &t);
   double Sign(const double &t);
   double SquareWave(const double &t);
   //double Trapezoidal();

   void CustomFunction(void);
}; //class SignalGenerator
