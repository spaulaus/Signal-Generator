#include <iostream>

#include <cmath>

#include "SignalGenerator.h"

using namespace std;

double MotherWavelet(const double &t, const double &scale, const double &tau);

/*
double iTime = 0.0, fTime = 2000.0, width = fTime - iTime;   //i,f times
int noPoints = 2000; double h = width/noPoints;            //Steps
int noPtsSignal = noPoints, noScale = 10, noTau = 1e5;    //# of pts
double iTau = 0., iScale = 0.00001, tau = iTau, scale = iScale;
// Need *very* small s steps for high-frequency, but only if s is small
// Thus increment s by multiplying by number close enough to 1 
//double dTau = width/noTau, dScale = pow(width/iScale, 1./noScale);
double dTau = width/noTau, dScale = (1e-4-iScale)/noScale;
*/

int main(void)
{
   //double transform [noScale][noTau];
   
   SignalGenerator gen;
   gen.SetSignalLength(5);
   gen.SetSignalResolution(0.01);
   gen.SetPeriod(1.);
   gen.SetNoise(true);
   gen.SetAmplitude(5.);
   gen.SetSigma(1.);
   gen.SetDelay(0.);
   gen.SetSignalType("triangle");
   gen.GenerateSignal();

   vector<double> *signal = gen.GetSignal();

   for(unsigned int i = 0; i < signal->size(); i++)
      cout << i*0.01 << " " << signal->at(i) << endl;
   
   // //Do the loop for the transformation.
   // for (int i = 0; i < noScale; i++, scale += dScale) { // Scaling
   //    tau = iTime;
   //    for (int j = 0; j < noTau; j++, tau+=dTau) { // Translation
   // 	 transform[i][j] = DoTransform(scale, tau);
   //    }
   // }

   // //Find the maximum value of the transformation
   // //for normalization
   // double maximum = 0.001;
   // for (int i = 0; i < noScale; i++) { // Scaling
   //    for (int j = 0; j < noTau; j++) { // Translation
   // 	 if(transform[i][j] > maximum || transform[i][j] < -1*maximum)
   // 	    maximum = fabs(transform[i][j]);
   //    }
   // }
   
   // //Output either the signal or the source 
   // if(outputSignal) {
   //    for(vector<double>::iterator it = signal.begin(); 
   // 	  it!= signal.end(); it++){
   // 	 cout << it - signal.begin() << " " << *it << endl;
   //    }
   // }else {
   //    tau = iTime;
   //    scale = iScale;
   //    for (int i = 0; i < noScale; i++, scale += dScale) { // Scaling
   // 	 tau = iTime;
   // 	 for (int j = 0; j < noTau; j++, tau+=dTau) { // Translation
   // 	    cout << scale << " " << tau << " " 
   // 		 << fabs(transform[i][j]/maximum) << endl;
   // 	 }
   // 	 cout << endl;
   //    }
   // }// if(outputSignal)

   //Project out the Scale parameter
   // double tauSum[noTau];
   // for (int j = 0; j < noTau; j++) { // Translation
   //    scale = iScale;
   //    for (int i = 0; i < noScale; i++) { // Scaling
   // 	 if(i < 10)
   // 	    tauSum[j] += fabs(transform[i][j]/maximum);
   //    }
   // }
   
   // tau = iTau;
   // for (int j = 0; j < noTau; j++, tau+=dTau) { // Translation
   //    cout << tau << " " << tauSum[j] << endl;
   // }
}

// double DoTransform(double &scale, double &tau)  
// {
//    double integral = 0., t = iTime;
//    for (vector<double>::iterator it = signal.begin();
// 	it != signal.end(); it++, t += h)
//       integral += (*it)*MotherWavelet(t,scale,tau)*h;
//    return (integral / sqrt(scale));
// }
