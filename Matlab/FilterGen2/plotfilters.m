clear;
clc;
close all;
FS = 48000;
FMIN = 0.2; % Hz
FMAX = 20e3; % Hz
SWEEPTIME = 5;

[t, sweep] = makeSweep( FS, FMIN, FMAX, 0, SWEEPTIME );
figure(1);
tempFoo = abs(fft(sweep));
tempFooLength = length(tempFoo);
loglog(tempFoo(1,1:tempFooLength/2))
Ave = mean(tempFoo(1,1:tempFooLength/2));
% Constants
NUMFILTERS = 7;

mySOS = MakeSOS();

scale = ones(1,NUMFILTERS);
figure(2);

for i = 1:NUMFILTERS
     y(i,:) = ApplySOS(mySOS(i,:), sweep, scale);
     blah = abs(fft(y(i,:)));
     maxfoo(i) = max(blah)/250;
     loglog(blah);
     hold on
end

figure(3);
for i = 1:NUMFILTERS
    x = ApplySOS(mySOS(i,:), sweep, scale)./maxfoo(i);
     theFFT = abs(fft(x));
     indices = 1:(length(theFFT)/2);
     loglog( ((indices-1)/length(theFFT))*FS, theFFT(1:(length(theFFT)/2)));
     if i == 1
         hold on
     end
     loglog(Ave*ones((length(theFFT)/2),1), 'r')
end

axis([20 20e3 1e-1 3e2])