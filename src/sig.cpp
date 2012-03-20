#include <iostream>

#include <cmath>

#include "SignalGenerator.hpp"

using namespace std;

int main(int argc, char* argv[])
{
   string signalType = argv[1];
   double res = 0.01;
   
   SignalGenerator gen;

   //Set Signal Information
   gen.SetSignalLength(10);
   gen.SetSignalResolution(res);
   gen.SetPeriod(1.);
   gen.SetAmplitude(5.);
   gen.SetSigma(1.);
   gen.SetDelay(0.);
   gen.SetSignalType(signalType);
  
   //Set Noise Information
   gen.SetNoise(true);
   gen.SetNoiseAmplitude(0.5);

   //Generate and Get Signal
   gen.GenerateSignal();
   vector<double> *signal = gen.GetSignal();

   for(unsigned int i = 0; i < signal->size(); i++)
      cout << i*res << " " << signal->at(i) << endl;
}
