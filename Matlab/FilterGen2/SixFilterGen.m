%clear
%close all
clf
clc;

SOS =  MakeSOS_SixBand( );

[xsize ysize] = size(SOS);

dB = [16.8, 13, 12, 8.3, 7];

fd = fopen('SixBandfilters.h', 'w');
fprintf(fd, '#ifndef SIXBANDFILTERS_H_\n');
fprintf(fd, '#define SIXBANDFILTERS_H_\n');

fprintf(fd, 'static const Int32 SixBandfilters[%d] = {\n\n', xsize*ysize);




for i = 1:2:xsize
        Q = 15;

        B0 = SOS(i,1);
        B1 = SOS(i,2);
        B2 = SOS(i,3);
        A0 = SOS(i,4);
        A1 = SOS(i,5);
        A2 = SOS(i,6);
        
        D0 = SOS(i+1,1);
        D1 = SOS(i+1,1);
        D2 = SOS(i+1,1);
        C0 = SOS(i+1,1);
        C1 = SOS(i+1,1);
        C2 = SOS(i+1,1);
    
    
    if i == 1
        normalize_coeff = ((A0 + A1 + A2)*(C0 + C1 + C2)) / ((B0 + B1 + B2)*(D0 + D1 + D2));

        B0 = B0 * normalize_coeff;
        B1 = B1 * normalize_coeff;
        B2 = B2 * normalize_coeff;
        D0 = D0 * normalize_coeff;
        D1 = D1 * normalize_coeff;
        D2 = D2 * normalize_coeff;


    else
        normalize_coeff = (1./(10.^(dB((i-1)/2)./20)));

        B0 = B0 * normalize_coeff;
        B1 = B1 * normalize_coeff;
        B2 = B2 * normalize_coeff;
        
        D0 = D0 * normalize_coeff;
        D1 = D1 * normalize_coeff;
        D2 = D2 * normalize_coeff;
        
        % figure(round(i/32) + 1);
        [b,a] = sos2tf([ B0 B1 B2 A0 A1 A2; D0 D1 D2 C0 C1 C2 ]);
        [h,w] = freqz(b,a,2001);
        
               
        plot(w/pi,20*log10(abs(h)));
        %plot(w/pi,h2);
        hold on;
        ax = gca;
        %ax.YLim = [-100 20];
        %ax.XTick = 0:.5:2;
        xlabel('Normalized Frequency (\times\pi rad/sample)')
        %ylabel('Magnitude (dB)')
    end
    
        B0_Q13 = round(((2^Q) * B0) - 1);
        B1_Q13 = round(((2^Q) * B1) - 1);
        B2_Q13 = round(((2^Q) * B2) - 1);
        A0_Q13 = round(((2^Q) * A0) - 1);
        A1_Q13 = round(((2^Q) * A1) - 1);
        A2_Q13 = round(((2^Q) * A2) - 1);
        
        D0_Q13 = round(((2^Q) * D0) - 1);
        D1_Q13 = round(((2^Q) * D1) - 1);
        D2_Q13 = round(((2^Q) * D2) - 1);
        C0_Q13 = round(((2^Q) * C0) - 1);
        C1_Q13 = round(((2^Q) * C1) - 1);
        C2_Q13 = round(((2^Q) * C2) - 1);        
    
        if i ~= xsize && i ~= xsize-1
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d,\n\n', ...
                B0_Q13, B1_Q13, B2_Q13, A0_Q13, A1_Q13, A2_Q13);
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d,\n\n', ...
                D0_Q13, D1_Q13, D2_Q13, C0_Q13, C1_Q13, C2_Q13);
        elseif i == xsize-1
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d\n\n', ...
                B0_Q13, B1_Q13, B2_Q13, A0_Q13, A1_Q13, A2_Q13);
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d\n};\n', ...
                D0_Q13, D1_Q13, D2_Q13, C0_Q13, C1_Q13, C2_Q13);            
        end
        
end

fprintf(fd, '#endif //SIXBANDFILTERS_H_\n');
    