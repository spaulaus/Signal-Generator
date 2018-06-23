/// @file SignalGenerator.cpp
/// @brief Implementation of methods used to generate signals to study
/// @author S. V. Paulauskas
/// @date Jun 23, 2018
/// @copyright Copyright (c) 2012 - 2018 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include "SignalGenerator.hpp"

#include <fstream>
#include <iostream>
#include <limits>

SignalGenerator::SignalGenerator() {
    srand(time(NULL));
}

SignalGenerator::~SignalGenerator() = default;

void SignalGenerator::GenerateSignal() {
    if(type_ == "custom") {
        CustomFunction();
    }else if(typeA_ != "") {
        FillVector(signal_, type_);
        FillVector(signalA_, typeA_);
        CompositeFunction();
    }else {
        FillVector(signal_, type_);
    }
    
    if(hasNoise_) 
        for(unsigned int i = 0; i < signal_.size(); i++) 
            signal_[i] += noiseAmp_*Noise();
}

void SignalGenerator::CompositeFunction() {
    for(unsigned int i = 0; i < signal_.size(); i++) {
        signal_[i] += signalA_[i];
    }
}

void SignalGenerator::CustomFunction() {
    double junk0, junk1, junk2;
    if(fileName_ == "") {
        std::cerr << std::endl << "A file name must be specified to use a custom function."
             << std::endl << "This is a fatal error. Exiting." << std::endl;
        exit(2);
    }else {
        std::ifstream readData(fileName_.c_str());
        if(readData.is_open()) {
            while(readData.good()) {
                readData >> junk0 >> junk1 >> junk2;
                signalA_.push_back(junk0);
                signal_.push_back(junk1);
            }
            readData.close();
        } else {
            std::cerr << "Unable to open the requested file. Exiting..." << std::endl;
            exit(2);
        }
    }
}

void SignalGenerator::FillVector(std::vector<double> &vec, const std::string &type) {
    if(type == "cosine")
        mu_ += M_PI*0.5;
    
    for(double i = 0; i < length_; i += res_) {
        if(type == "sine") {
            vec.push_back(SineWave(i));
        }else if(type == "cosine") { 
            vec.push_back(SineWave(i));
        }else if (type == "gaussian") {
            vec.push_back(Gaussian(i));
        }else if (type == "nonstationarysine") {
            vec.push_back(NonStationarySine(i));
        }else if (type == "square") {
            vec.push_back(SquareWave(i));
        }else if (type == "sawtooth") {
            vec.push_back(SawtoothWave(i));
        }else if (type == "triangle") {
            vec.push_back(2.*fabs(SawtoothWave(i)));
        }
    }
}
   
double SignalGenerator::GetSignalValue(const double &x) {
    if(type_ == "sine")
        return(SineWave(x));
    else if(type_ == "cosine")
        return(SineWave(x+M_PI*0.5));
    else if (type_ == "gaussian") 
        return(Gaussian(x));
    else if (type_ == "nonstationarysine") 
        return(NonStationarySine(x));
    else if (type_ == "square") 
        return(SquareWave(x));
    else if (type_ == "sawtooth") 
        return(SawtoothWave(x));
    else if (type_ == "triangle") 
        return(2.*fabs(SawtoothWave(x)));
    else if (type_ == "pixie")
        return(PixieFunc(x));
    else 
        return(std::numeric_limits<double>::quiet_NaN());
}

double SignalGenerator::Gaussian(const double &t) {
    double coeff = amp_/(sigma_*sqrt(2*M_PI));
    double exponent = -pow((t-mu_)/sigma_,2)*0.5;
    return( coeff * exp(exponent) );
}

double SignalGenerator::PixieFunc(const double &t) {
    if(t < mu_)
        return(baseline_);
    else
        return(baseline_+amp_*(1-exp(-(t-mu_)*(t-mu_)/sigma_))*
               exp(-(t-mu_)/decay_));
}

double SignalGenerator::Noise() {
    return ( (rand() / double(RAND_MAX))*2 -1 );
}

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

double SignalGenerator::SawtoothWave(const double &t) {
    return (amp_ * (t/period_ - floor(t/period_ + 0.5)));
}

double SignalGenerator::Sign(const double &t) {
    return ( (t<0) ? -1 : (t>0) );
}

double SignalGenerator::SineWave(const double &t) {
    return( amp_ * sin(period_*t + mu_) );
}

double SignalGenerator::SquareWave(const double &t) {
    return ( amp_ * Sign(SineWave(t)) );
}
