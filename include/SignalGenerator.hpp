/// @file SignalGenerator.hpp
/// @brief Class for generating different kinds of signals, with random noise
/// @author S. V. Paulauskas
/// @date March 15, 2012
/// @copyright Copyright (c) 2012 - 2018 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#ifndef SIGNAL_GENERATOR
#define SIGNAL_GENERATOR
#include <string>
#include <vector>

class SignalGenerator {
public:
    /// Default Constructor 
    SignalGenerator();
    /// Default Destructor 
    ~SignalGenerator();

    /// Get the amplitude of the generated signal 
    double GetAmplitude();
   
    /// Get the decay constant for an exponential decay. (not implemented) 
    double GetDecayConstant();
    
    /// Get the delay for the signal 
    double GetDelay();
    
    /// Get the file name to read the custom function. 
    /// The file should contain a series of xy pairs 
    std::string GetFileName();
    
    /// Get the flattop for the trapezoidal signal (not implemented)
    double GetFlattop();

    /// Get to true to give the signal some white noise
    double GetNoise();
    
    /// Get the amplitude of the noise
    double GetNoiseAmplitude();
    
    /// Get the periodicity of the signal (if periodic).
    double GetPeriod();
    
    /// Get the risetime for a trapezoidal signal (not implemented)
    double GetRisetime();
    
    /// Get the sigma for the gaussian signal
    double GetSigma();
    
    /// Get the length of the generated signal
    unsigned int GetSignalLength();
    
    /// Get the resolution for the generated signal
    double GetSignalResolution();
    
    /// Returns a single value from the function, can be used to generate 
    /// your own resolutions and vectors if wanted 
    double GetSignalValue(const double &x);

    /// Returns the vectors of the generated signal
    /// If a custom function is specified this will return the y values 
    /// Remember: The size of the vector will be length * resolution 
    std::vector<double>* GetSignal();

    /// Returns the x values of a custom function.
    std::vector<double>* GetSignalX();
    
    /// Generate a signal 
    void GenerateSignal(); 
    
    /// Set the amplitude of the generated signal 
    void SetAmplitude(const double &a);
   
    /// Set the baseline value for the generated signal 
    void SetBaseline(const double &a);

    /// Set the decay constant for an exponential decay. (not implemented) 
    void SetDecayConstant(const double &a);
    
    /// Set the delay for the signal 
    void SetDelay(const double &a);
    
    /// Set the file name to read the custom function. 
    /// The file should contain a series of xy pairs
    void SetFileName(const std::string &a);
    
    /// Set the flattop for the trapezoidal signal (not implemented)
    void SetFlattop(const double &a);

    /// Set the sigma using FWHM for a gaussian signal 
    void SetFwhm(const double &fwhm);

    /// Set to true to give the signal some white noise
    void SetNoise(const bool &a);
    
    /// Set the amplitude of the noise
    void SetNoiseAmplitude(const double &a);
    
    /// Set the periodicity of the signal (if periodic).
    void SetPeriod(const double &a);
    
    /// Set the risetime for a trapezoidal signal (not implemented)
    void SetRisetime(const double &a);
    
    /// Set the sigma for the gaussian signal
    void SetSigma(const double &a);

    /// Set the length of the generated signal
    void SetSignalLength(const unsigned int &a);
    
    /// Set the resolution for the generated signal
    void SetSignalResolution(const double &a);
    
    /// Set the type of signal to generate 
    /// Available types: sine, cosine, gaussian, sawtooth, square, triangle, custom, composite.
    void SetSignalType (const std::string &a);
    
    /// Set the types of signals to generate for a composite signal
    void SetSignalType (const std::string &a, const std::string &b);
private:
    bool hasNoise_;
    double amp_, baseline_, decay_, mu_, sigma_, period_, risetime_, flattop_, res_;
    double noiseAmp_;
    std::string type_, typeA_, fileName_;
    std::vector<double> signal_, signalA_;
    unsigned int length_;
    
    double Gaussian(const double &t);
    double PixieFunc(const double &t);
    double Noise();
    double NonStationarySine(const double &t);
    double SawtoothWave(const double &t);
    double SineWave(const double &t);
    double Sign(const double &t);
    double SquareWave(const double &t);
    //double Trapezoidal();
    
    void CompositeFunction();
    void CustomFunction();
    void FillVector(std::vector<double> &vec, const std::string &type);
}; //class SignalGenerator

#endif