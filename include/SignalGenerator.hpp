/*
 * Copyright S.V. Paulauskas 2012
 * stanpaulauskas@gmail.com 
 * Distributed under GNU General Public Licence v3
 */

/** \file SignalGenerator.hpp
 * Class for generating different kinds of signals;
 *   also allows for one to add random noise.
 * \author S.V. Paulauskas
 * \date 15 March 2012
 */
#include <string>
#include <vector>

#include <cstdlib>

#include "time.h"

class SignalGenerator {
 public:
   SignalGenerator() {srand(time(NULL));};
   ~SignalGenerator() {};

   /*! Returns the values of the generated signal */
   /*! If a custom function is specified this will return the y values */
   /*! Remember: The size of the vector will be length * resolution */
   std::vector<double>* GetSignal() {return &signal_;};
   /*! Returns the x values of a custom function. */  
   std::vector<double>* GetSignalX() {return &signalA_;};

   /*! Generate a signal */
   void GenerateSignal(void); 

   /*! Set the amplitude of the generated signal */
   void SetAmplitude(const double &amplitude) {amp_ = amplitude;};  
   
   /*! Set the decay constant for an exponential decay. (not implemented) */
   void SetDecayConstant(const double &decay) {decay_ = decay;}; 
   
   /*! Set the delay for the signal */
   void SetDelay(const double &delay) {mu_ = delay;}; 
   
   /*! Set the file name to read the custom function. */
   /*! The file should contain a series of xy pairs */
   void SetFileName(const std::string &fileName) {fileName_ = fileName;};
   
   /*! Set the flattop for the trapezoidal signal (not implemented)   */
   void SetFlattop(const double &flattop) {flattop_ = flattop;};
   
   /*! Set to true to give the signal some white noise   */
   void SetNoise(const bool &noise) {hasNoise_ = noise;} 
   
   /*! Set the amplitude of the noise   */
   void SetNoiseAmplitude(const double &amplitude) {noiseAmp_ = amplitude;}; 
   
   /*! Set the periodicity of the signal (if periodic).   */
   void SetPeriod(const double &period) {period_ = period;}; 
   
   /*! Set the risetime for a trapezoidal signal (not implemented)   */
   void SetRisetime(const double &risetime) {risetime_ = risetime;};
   
   /*! Set the sigma for the gaussian signal   */
   void SetSigma(const double &sigma) {sigma_ = sigma;}; 
   
   /*! Set the length of the generated signal   */
   void SetSignalLength(const unsigned int &sigLength) {length_ = sigLength;} 
   
   /*! Set the resolution for the generated signal   */
   void SetSignalResolution(const double &sigRes) {res_ = sigRes;}
   
   /*! Set the type of signal to generate */
   /*! Available types: sine, cosine, gaussian, sawtooth, square, triangle, 
    *  custom, composite. */
   void SetSignalType (const std::string &sigType) {type_ = sigType;}
   
   /*! Set the types of signals to generate for a composite signal   */
   void SetSignalType (const std::string &sigTypeA, const std::string &sigTypeB)
      {type_ = sigTypeA; typeA_ = sigTypeB;};
private:
   bool hasNoise_;
   double amp_, decay_, mu_, sigma_, period_, risetime_, flattop_, res_;
   double noiseAmp_;
   std::string type_, typeA_, fileName_;
   std::vector<double> signal_, signalA_;
   unsigned int length_;
      
   double Gaussian(const double &t);
   double Noise(void);
   double NonStationarySine(const double &t);
   double SawtoothWave(const double &t);
   double SineWave(const double &t);
   double Sign(const double &t);
   double SquareWave(const double &t);
   //double Trapezoidal();

   void CompositeFunction();
   void CustomFunction(void);
   void FillVector(std::vector<double> &vec, 
		   const std::string &type);
}; //class SignalGenerator
