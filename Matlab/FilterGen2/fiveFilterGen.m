%clear
%close all
clf
clc;

SOS =  MakeSOS_ThreeBand( );

[xsize ysize] = size(SOS);

dB = [35, 13.5, 12.7, 8, 10];

fd = fopen('filters.h', 'w');
fprintf(fd, '#ifndef THREEBANDFILTERS_H_\n');
fprintf(fd, '#define THREEBANDFILTERS_H_\n');

fprintf(fd, 'static const Int32 ThreeBandfilters[%d] = {\n\n', xsize*ysize);




for i = 1:xsize
        Q = 15;

        B0 = SOS(i,1);
        B1 = SOS(i,2);
        B2 = SOS(i,3);
        A0 = SOS(i,4);
        A1 = SOS(i,5);
        A2 = SOS(i,6);
    
    
    if i == 1
        normalize_coeff = (A0 + A1 + A2) / (B0 + B1 + B2);

        B0 = B0 * normalize_coeff;
        B1 = B1 * normalize_coeff;
        B2 = B2 * normalize_coeff;


    else
        normalize_coeff = (1./(10.^(dB(i-1)./20)));

        B0 = B0 * normalize_coeff;
        B1 = B1 * normalize_coeff;
        B2 = B2 * normalize_coeff;
        
        % figure(round(i/32) + 1);
        [b,a] = sos2tf([ B0 B1 B2 A0 A1 A2 ]);
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
    
        if i ~= xsize
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d,\n\n', ...
                B0_Q13, B1_Q13, B2_Q13, A0_Q13, A1_Q13, A2_Q13);
        else
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d\n};\n', ...
                B0_Q13, B1_Q13, B2_Q13, A0_Q13, A1_Q13, A2_Q13);
        end
        
end

fprintf(fd, '#endif //THREEBANDFILTERS_H_\n');
    