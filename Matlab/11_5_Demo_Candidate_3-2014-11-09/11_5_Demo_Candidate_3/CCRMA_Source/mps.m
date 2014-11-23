function [sm] = mps(s) 
% Converts a system to minimum phase
% Uses the cepstrum method
% Source: https://ccrma.stanford.edu/~jos/fp/Matlab_listing_mps_m.html

% [sm] = mps(s) 
% create minimum-phase spectrum sm from complex spectrum s 
   sm = exp( fft( fold( ifft( log( clipdb(s,-100) )))));
   
end
