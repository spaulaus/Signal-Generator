double MotherWavelet(const double &t, const double &scale, const double &tau)
{
   double psi = 0;
   double transVar = (t-tau)/scale;
   switch(waveletType) {
   case 0: // Book Example
      psi = sin(8*transVar) * exp(-transVar*transVar/2);
      break;
   case 1: {// Hermitian wavelet 
      psi = -1/(pow(2*M_PI, 2)*pow(scale,3))*transVar * 
	 exp(-transVar*transVar/2);
      break;
   }
   case 2: {//Mexican Hat
      psi = (2/(sqrt(3*scale)*pow(M_PI, 0.25)))*
      (1-(transVar*transVar))* 
      exp(-transVar*transVar/2);
      break;
   }
   case 3: //Morlet
      psi = cos(2*M_PI*transVar)*exp(-transVar*transVar/2);
      break;
   }
   return(psi);
}

