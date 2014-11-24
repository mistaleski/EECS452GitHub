% NUMFILTERS = 8;
% 
% mySOS = MakeSOS(NUMFILTERS);
% 
% for i = 1:NUMFILTERS
%     figure(i)
%     [h, w] = freqz(mySOS(i),1e10);
%     clf
%     if i==1 
%         hold on
%     end
%     plot(w/pi,20*log10(abs(h)))
%     ax = gca;
%     ax.YLim = [-100 20];
%     ax.XTick = 0:.5:2;
%     xlabel('Normalized Frequency (\times\pi rad/sample)')
%     ylabel('Magnitude (dB)')
%         
% end


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
loglog(tempFoo(1,1:length(tempFoo')/2))
% Constants
NUMFILTERS = 7;

mySOS = MakeSOS();

scale = ones(1,NUMFILTERS);
figure(3);
hold on
for i = 1:NUMFILTERS
     y(i,:) = ApplySOS(mySOS(i,:), sweep, scale).*NUMFILTERS;
%      if i == 1
%          hold on
%      end
     blah = abs(fft(y(i,:)));
     maxfoo(i) = max(blah);
     plot(blah);
end

figure(2);
for i = 1:NUMFILTERS
    x = (ApplySOS(mySOS(i,:), sweep, scale)*NUMFILTERS);%./maxfoo(i);
     %plotFFT( fft(x), 1, 1, 1, 1, 'comparison', FS );
     theFFT = abs(fft(x));
     indices = 1:(length(theFFT)/2);
     loglog( ((indices-1)/length(theFFT))*FS, theFFT(1:(length(theFFT)/2)));
     if i == 1
         hold on
     end
     loglog((1/sqrt(2))*ones((length(theFFT)/2),1), 'r')
end

%axis([20 20e3 1e-1 0.2e1])