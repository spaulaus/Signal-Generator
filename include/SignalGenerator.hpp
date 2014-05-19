/***************************************************************************
  *  Copyright S. V. Paulauskas 2012-2014                                  *
  *                                                                        *
  *  This program is free software: you can redistribute it and/or modify  *
  *  it under the terms of the GNU General Public License as published by  *
  *  the Free Software Foundation, version 3.0 License.                    *
  *                                                                        *
  *  This program is distributed in the hope that it will be useful,       *
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
  *  GNU General Public License for more details.                          *
  *                                                                        *
  *  You should have received a copy of the GNU General Public License     *
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
  **************************************************************************
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
#include <cmath>

#include "time.h"

class SignalGenerator {
public:
    /*! Default Constructor */
    SignalGenerator() {srand(time(NULL));};
    /*! Default Destructor */
    ~SignalGenerator() {};

    /*! Get the amplitude of the generated signal */
    double GetAmplitude(void) {return(amp_);};  
   
    /*! Get the decay constant for an exponential decay. (not implemented) */
    double GetDecayConstant(void) {return(decay_);}; 
    
    /*! Get the delay for the signal */
    double GetDelay(void) {return(mu_);}; 
    
    /*! Get the file name to read the custom function. */
    /*! The file should contain a series of xy pairs */
    std::string GetFileName(void) {return(fileName_);};
    
    /*! Get the flattop for the trapezoidal signal (not implemented)   */
    double GetFlattop(void) {return(flattop_);};

    /*! Get to true to give the signal some white noise   */
    double GetNoise(void) {return(hasNoise_);} 
    
    /*! Get the amplitude of the noise   */
    double GetNoiseAmplitude(void) {return(noiseAmp_);}; 
    
    /*! Get the periodicity of the signal (if periodic).   */
    double GetPeriod(void) {return(period_);}; 
    
    /*! Get the risetime for a trapezoidal signal (not implemented)   */
    double GetRisetime(void) {return(risetime_);};
    
    /*! Get the sigma for the gaussian signal   */
    double GetSigma(void) {return(sigma_);}; 
    
    /*! Get the length of the generated signal   */
    unsigned int GetSignalLength(void) {return(length_);} 
    
    /*! Get the resolution for the generated signal   */
    double GetSignalResolution(void) {return(res_);}
    
    /*! Returns a single value from the function, can be used to generate */
    /*! your own resolutions and vectors if wanted */
    double GetSignalValue(const double &x);
    /*! Returns the vectors of the generated signal */
    /*! If a custom function is specified this will return the y values */
    /*! Remember: The size of the vector will be length * resolution */
    std::vector<double>* GetSignal() {return &signal_;};
    /*! Returns the x values of a custom function. */  
    std::vector<double>* GetSignalX() {return &signalA_;};
    
    /*! Generate a signal */
    void GenerateSignal(void); 
    
    /*! Set the amplitude of the generated signal */
    void SetAmplitude(const double &a) {amp_ = a;};  
   
    /*! Set the baseline value for the generated signal */
    void SetBaseline(const double &a) {baseline_ = a;};

    /*! Set the decay constant for an exponential decay. (not implemented) */
    void SetDecayConstant(const double &a) {decay_ = a;}; 
    
    /*! Set the delay for the signal */
    void SetDelay(const double &a) {mu_ = a;}; 
    
    /*! Set the file name to read the custom function. */
    /*! The file should contain a series of xy pairs */
    void SetFileName(const std::string &a) {fileName_ = a;};
    
    /*! Set the flattop for the trapezoidal signal (not implemented)   */
    void SetFlattop(const double &a) {flattop_ = a;};

    /*! Set the sigma using FWHM for a gaussian signal */
    void SetFwhm(const double &fwhm) {SetSigma(fwhm/(2*sqrt(2*log(2))));};

    /*! Set to true to give the signal some white noise   */
    void SetNoise(const bool &a) {hasNoise_ = a;} 
    
    /*! Set the amplitude of the noise   */
    void SetNoiseAmplitude(const double &a) {noiseAmp_ = a;}; 
    
    /*! Set the periodicity of the signal (if periodic).   */
    void SetPeriod(const double &a) {period_ = a;}; 
    
    /*! Set the risetime for a trapezoidal signal (not implemented)   */
    void SetRisetime(const double &a) {risetime_ = a;};
    
    /*! Set the sigma for the gaussian signal   */
    void SetSigma(const double &a) {sigma_ = a;}; 
    
    /*! Set the length of the generated signal   */
    void SetSignalLength(const unsigned int &a) {length_ = a;} 
    
    /*! Set the resolution for the generated signal   */
    void SetSignalResolution(const double &a) {res_ = a;}
    
    /*! Set the type of signal to generate */
    /*! Available types: sine, cosine, gaussian, sawtooth, square, triangle, 
     *  custom, composite. */
    void SetSignalType (const std::string &a) {type_ = a;}
    
    /*! Set the types of signals to generate for a composite signal   */
    void SetSignalType (const std::string &a, const std::string &b)
    {type_ = a; typeA_ = b;};
private:
    bool hasNoise_;
    double amp_, baseline_, decay_, mu_, sigma_, period_, 
        risetime_, flattop_, res_;
    double noiseAmp_;
    std::string type_, typeA_, fileName_;
    std::vector<double> signal_, signalA_;
    unsigned int length_;
    
    double Gaussian(const double &t);
    double PixieFunc(const double &t);
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
