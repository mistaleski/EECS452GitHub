clear;
clc;
close all;

FS = 48e3; % Hz
N = 512; % (number of points in FFT)
Q = 15;

fout = fopen('filters.h', 'w');
if fout == -1
    disp('File failed to open!');
    return
end

fprintf(fout, '#ifndef FILTERS_H_\n');
fprintf(fout, '#define FILTERS_H_\n');
fprintf(fout, '\n');

fprintf(fout, 'static const Int32 filters[%d] = {\n', N*6);

for i=1:511

      
    BW = 400/512;%400/512;%1/512;
    w0 = (2*pi*i)/512;

    p = BW;
    a = -2*cos(w0);

    B0 = 1;
    B1 = a;
    B2 = 1;
    A0 = 1;
    A1 = a*p;
    A2 = p^2;
    
    normalize_coeff = (1/(10^(3/20)));%
    
    B0 = B0 * normalize_coeff;
    B1 = B1 * normalize_coeff;
    B2 = B2 * normalize_coeff;
    
    
    B0_Q13 = round(((2^Q) * B0));
    B1_Q13 = round(((2^Q) * B1));
    B2_Q13 = round(((2^Q) * B2));
    A0_Q13 = round(((2^Q) * A0));
    A1_Q13 = round(((2^Q) * A1));
    A2_Q13 = round(((2^Q) * A2));
    
    
    fprintf(fout,'\n// f = %0.2e Hz\n', w0 * FS);
    fprintf(fout, '%d, // B0\n', B0_Q13);
    fprintf(fout, '%d, // B1\n', B1_Q13);
    fprintf(fout, '%d, // B2\n', B2_Q13);
    fprintf(fout, '%d, // A0\n', A0_Q13);
    fprintf(fout, '%d, // A1\n', A1_Q13);
    fprintf(fout, '%d ', A2_Q13);
    if i ~= 511
        fprintf(fout, ',// A2\n');
    end
    
    if mod(i,32) == 0
        % figure(round(i/32) + 1);
        [b,a] = sos2tf([ B0 B1 B2 A0 A1 A2 ]);
        [h,w] = freqz(b,a,2001);
        
        [b2,a2] = sos2tf([ B0_Q13/2^Q B1_Q13/2^Q ...
            B2_Q13/2^Q A0_Q13/2^Q ...
            A1_Q13/2^Q A2_Q13/2^Q ]);
        [h2,w2] = freqz(b2,a2,2001);
               
        %plot(w/pi,20*log10(abs(h)));
        plot(w/pi,h2);
        hold on;
        %plot(w2/pi,20*log10(abs(h2)), 'r');
        plot(w2/pi,h, 'r');
        ax = gca;
        ax.YLim = [-100 20];
        ax.XTick = 0:.5:2;
        xlabel('Normalized Frequency (\times\pi rad/sample)')
        %ylabel('Magnitude (dB)')
    end
end

fprintf(fout, '\n};\n');
fprintf(fout, '#endif /* FILTERS_H_ */');
fclose(fout);