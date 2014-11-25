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

numBQ = 2;
[mySOS] = MakeSOS(numBQ);

figure(1)
[b2,a2] = sos2tf(mySOS);
       [h2,w2] = freqz(b2,a2,2001);
plot(w2/pi,20.*log10(h2));
%[h,w] = freqz(mySOS(1,:),2001);
%plot(w,h);

scale = ones(1,NUMFILTERS);
figure(2);

for i = 1:NUMFILTERS
     y(i,:) = ApplySOS(mySOS((i-1)*numBQ+1,:), sweep, scale);
     for j = 1:1:numBQ-1
        y(i,:) = ApplySOS(mySOS((i-1)*(numBQ)+1+j,:),y(i,:),scale);
     end
     blah = abs(fft(y(i,1:round(length(y(1,:)/2.2)))));
     maxfoo(i) = max(blah)/250;
     loglog(blah);
     hold on
end

figure(3);
colorHolder = ['k'; 'g'; 'r';  'b'; 'c';  'm'; 'o'];
for i = 1:NUMFILTERS
     y(i,:) = ApplySOS(mySOS((i-1)*numBQ+1,:), sweep, scale);
     for j = 1:1:numBQ-1
        y(i,:) = ApplySOS(mySOS((i-1)*(numBQ)+1+j,:),y(i,:),scale);
     end
     y(i,:) = y(i,:)./maxfoo(i)./Ave;
    
     theFFT = 20.*log10(abs(fft(y(i,:))));
     indices = 1:(length(theFFT)/2);
     semilogx( ((indices-1)/length(theFFT))*FS, theFFT(1:(length(theFFT)/2)), colorHolder(i));
     if i == 1
         hold on
     end
     %loglog(Ave*ones((length(theFFT)/2),1), 'r')
end

axis([20 20e3 -20 1])
xlabel('frequency (20Hz-20kHz)');
ylabel('magnitude (dB)');
title('7 Band Frequency Room Characterization');



figure(4);

colorHolder = ['k'; 'g'; 'r';  'b'; 'c';  'm'; 'o' ];
colorHolderdash = ['--k'; '--g'; '--r'; '--b';'--c';'--m';'--b'];
Plus20dBlin = 10^(7/20);
Minus20dBlin = 10^(-7/20);

for i = 1:1:NUMFILTERS
     y(i,:) = ApplySOS(mySOS((i-1)*numBQ+1,:), sweep, scale);
     for j = 1:1:numBQ-1
        y(i,:) = ApplySOS(mySOS((i-1)*(numBQ)+1+j,:),y(i,:),scale);
     end
     xMax = y(i,:)./maxfoo(i)./Ave.*Plus20dBlin;
     xMin = y(i,:)./maxfoo(i)./Ave.*Minus20dBlin;
     theFFTMax = abs(fft(xMax));
     theFFTMin = abs(fft(xMin));
     
     indices = 1:(length(theFFTMax)/2);
     semilogx( ((indices-1)/length(theFFTMax))*FS, 20.*log10(theFFTMax(1:(length(theFFTMax)/2))), colorHolder(i));
     if i ==1
        hold on 
     end
     semilogx( ((indices-1)/length(theFFTMin))*FS, 20.*log10(theFFTMin(1:(length(theFFTMin)/2))), colorHolderdash(i,:));
     
end
%loglog(Ave*ones((length(theFFTMax)/2),1), 'r')

axis([20 20e3 -20 10])
xlabel('frequency (20Hz-20kHz)');
ylabel('magnitude (dB)');
title('7 Band Frequency EQ +/-7dB');