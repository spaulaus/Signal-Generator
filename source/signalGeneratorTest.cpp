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

TEST_FIXTURE(SignalGenerator, TestGaussian) {
    vector<double> expected = {3.726653172078671e-06, 4.006529739295107e-05, 0.00033546262790251185, 
                               0.002187491118182885, 0.011108996538242306, 0.04393693362340742, 0.1353352832366127, 
                               0.32465246735834974, 0.6065306597126334, 0.8824969025845955, 1.0, 0.8824969025845955,
                               0.6065306597126334, 0.32465246735834974, 0.1353352832366127, 0.04393693362340742,
                               0.011108996538242306, 0.002187491118182885, 0.00033546262790251185, 
                               4.006529739295107e-05, 3.726653172078671e-06};

    CHECK_ARRAY_CLOSE(expected, GenerateGaussian(2.0, 5.01, 20, 1.0), expected.size(), 0.1);
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