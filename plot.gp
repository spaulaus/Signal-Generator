reset
set terminal wxt enhanced

name="triangle-sine"

fileName(val)=sprintf("pictures/%s.eps", val)
sourceName(val)=sprintf("generatedSignals/%s.dat", val)
noiseSource(val)=sprintf("generatedSignals/%s-wNoise.dat",val)
graphTitle(val)=sprintf("%s",val)

unset key

set title graphTitle(name)
plot sourceName(name) w linespoints,\
     noiseSource(name) w linespoints,\
     0

set terminal postscript eps enhanced color "Helvetica, 24"
set output fileName(name)
replot