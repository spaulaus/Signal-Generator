/// @file sig.cpp
/// @brief Runs unit tests on the signal generator methods
/// @author S. V. Paulauskas
/// @date March 15, 2012
/// @copyright Copyright (c) 2012 - 2018 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include "SignalGenerator.hpp"

#include <UnitTest++/UnitTest++.h>

#include <fstream>
#include <iostream>

using namespace std;

double res = 0.01, length = 10., period = 1., amp = 5.;

TEST (TestSignalGeneration) {
    SignalGenerator standard;
    standard.SetSignalLength(length);
    standard.SetSignalResolution(res);
    standard.SetPeriod(period);
    standard.SetAmplitude(amp);
    standard.SetSignalType("triangle");

    //Set Noise Information
    standard.SetNoise(false);
    standard.SetNoiseAmplitude(0.5);

    //Generate and Get Signal
    standard.GenerateSignal();
    vector<double> *stdSignal = standard.GetSignal();
}

TEST_FIXTURE(SignalGenerator, TestCompoundSignal) {
    //Set a compound signal
    SignalGenerator compound;
    compound.SetSignalLength(length);
    compound.SetSignalResolution(res);
    compound.SetPeriod(period);
    compound.SetAmplitude(amp);
    compound.SetSignalType("sawtooth", "cosine");

    //Set Noise Information
    compound.SetNoise(false);
    compound.SetNoiseAmplitude(0.5);

    //Generate and Get Signal
    compound.GenerateSignal();
    vector<double> *compSignal = compound.GetSignal();
}

TEST_FIXTURE(SignalGenerator, TestCustomFunction) {
    //Set a custom signal
    SignalGenerator custom;
    custom.SetSignalType("custom");
    custom.SetFileName("example-input.dat");

    //Generate and Get Signal
    custom.GenerateSignal();
    vector<double> *customSignal = GetSignal();
}

int main(int argv, char *argc[]) {
    return (UnitTest::RunAllTests());
}