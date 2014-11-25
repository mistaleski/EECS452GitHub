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
NUMFILTERS = 5;

mySOS = MakeSOS_ThreeBand();

scale = ones(1,NUMFILTERS);
figure(2);
hold on

for i = 1:NUMFILTERS
     y(i,:) = ApplySOS(mySOS(i,:), sweep, scale);
     blah = abs(fft(y(i,:)));
     maxfoo(i) = max(blah)/250;
     [b2,a2] = sos2tf(mySOS(i,:));
     [h2,w2] = freqz(b2./maxfoo(i),a2,2001);
     plot(w2/pi,20.*log10(h2));
     %loglog(blah);
     hold on
end

figure(3);
colorHolder = ['k';  'r';  'b'; 'c';  'm'; ];
for i = 1:NUMFILTERS
    x = ApplySOS(mySOS(i,:), sweep, scale)./maxfoo(i)./Ave;
     theFFT = 20.*log10(abs(fft(x)));
     indices = 1:(length(theFFT)/2);
     semilogx( ((indices-1)/length(theFFT))*FS, theFFT(1:(length(theFFT)/2)), colorHolder(i));
     if i == 1
         hold on
     end
     %loglog(Ave*ones((length(theFFT)/2),1), 'r')
end

axis([20 20e3 -10 1])
xlabel('frequency (20Hz-20kHz)');
ylabel('magnitude (dB)');
title('3 Band Frequency EQ non adjust Middle Bands');

figure(4);

colorHolder = ['k';  'r';  'b'; 'c';  'm' ];
colorHolderdash = [':k';':r'; ':b';':c';':m'];
Plus20dBlin = 10^(8/20);
Minus20dBlin = 10^(-8/20);

for i = 1:2:NUMFILTERS
     xMax1 = ApplySOS(mySOS(i,:), sweep, scale)./maxfoo(i).*Plus20dBlin./Ave;
     xMin1 = ApplySOS(mySOS(i,:), sweep, scale)./maxfoo(i).*Minus20dBlin./Ave;
     theFFTMax = abs(fft(xMax1));
     theFFTMin = abs(fft(xMin1));
     
     indices = 1:(length(theFFTMax)/2);
     semilogx( ((indices-1)/length(theFFTMax))*FS, 20.*log10(theFFTMax(1:(length(theFFTMax)/2))), colorHolder(i));
     if i ==1
        hold on 
     end
     semilogx( ((indices-1)/length(theFFTMin))*FS, 20.*log10(theFFTMin(1:(length(theFFTMin)/2))), colorHolderdash(i,:));
     
end
%loglog(Ave*ones((length(theFFTMax)/2),1), 'r')

axis([20 20e3 -30 10])
xlabel('frequency (20Hz-20kHz)');
ylabel('magnitude (dB)');
title('3 Band Frequency EQ +/-8dB');