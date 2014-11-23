 playSweep(20, 20000, 1);

% fs = 48000
% SIGNAL_TIME = 3;
% 
% fftSize = 2.^(floor(log2(48000*SIGNAL_TIME)));
% 
% %ramp
% fmin = 10;
% fmax = 20000;
% t = 0:(1./fs):(fftSize-1)/fs;
% x = chirp(t,fmin,fftSize/fs,fmax);%, 'logarithmic');
% 
% figure(1);
% plot(x);
% 
% figure(2);
% H = fft(x);
% fftrange = 1:fftSize;
% loglog((fftrange./fftSize).*fs,abs(H));
% axis([10 24000 1e-1 1e4]);



%soundsc(x,fs);

% firstIndex = 0;
% 
% for i = 1:size(myHello)
%     if myHello(i) > 0.1
%         firstIndex = i;
%         break;
%     end
% end
% 
% STARTOFFSET = 100;
% 
% if(firstIndex-STARTOFFSET < 0)
%     STARTOFFSET = -1;
% end
% 
% fftSize = 2.^(floor(log2(length(myHello) - firstIndex)));
% 
% range = firstIndex-STARTOFFSET:(firstIndex+fftSize-1-STARTOFFSET);
% 
% figure(1);
% clf;
% plot(t(range)./fs,myHello(range));
% ylim([-0.8 0.6])
% figure(2)
% 
% H = fft(myHello(range));
% 
% fftrange = 1:fftSize;
% 
% figure(2);
% clf;
% semilogy((fftrange./fftSize).*fs,abs(H));
% axis([0 fs/2 1e-4 1e2]);