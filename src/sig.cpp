/* 
 * Copyright S.V. Paulauskas 2012
 * stanpaulauskas@gmail.com
 * Distributed under GNU General Public Licence v3
 */

/** \example sig.cpp
 * \brief A simple example.
 * 
 * The example generates a simple function, a compound function, 
 * and finally a custom function.  It will then output these 
 * functions into separate data files.  
 */
#include <iostream>
#include "SignalGenerator.hpp"

using namespace std;

/// The main function, to set/get the different stuff for the example.
int main(int argc, char* argv[])
{
   string signalType = argv[1];
   string fileName;
   if(argc == 3)
      fileName = argv[2];

   double res = 0.01;
   
   SignalGenerator sig;

   //Set Signal Information
   sig.SetSignalLength(10);
   sig.SetSignalResolution(res);
   sig.SetPeriod(1.);
   sig.SetAmplitude(5.);
   sig.SetSigma(1.);
   sig.SetDelay(5.);
   sig.SetSignalType(signalType);

   //Set Noise Information
   sig.SetNoise(true);
   sig.SetNoiseAmplitude(0.5);

   //Generate and Get Signal
   sig.GenerateSignal();
   vector<double> *signal = sig.GetSignal();

   for(unsigned int i = 0; i < signal->size(); i++)
      cout << i*res << " " << signal->at(i) << endl;
}
