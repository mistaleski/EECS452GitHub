clear
close all
clf
clc;

SOS =  MakeSOS_SixBand( );

[xsize ysize] = size(SOS);

dB = [32.82, 38.73, 25.17, 30.91, 23.21, 17.93, 15.86, 12.29, 13.11, 9.50];
dB = dB+1;
fs = 48000;
htot = 0;
w4 = 0;

fd = fopen('SixBandfilters.h', 'w');
fprintf(fd, '#ifndef SIXBANDFILTERS_H_\n');
fprintf(fd, '#define SIXBANDFILTERS_H_\n');

fprintf(fd, 'static const Int32 SixBandfilters[%d] = {\n\n', xsize*ysize);


colorArray = ['b'; 'r'; 'k'; 'g'; 'm' ;'c'];
colorArray2 = ['--b'; '--r'; '--k'; '--g'; '--m'; '--c'];

for i = 1:2:xsize
        Q = 14;

        B0 = SOS(i,1);
        B1 = SOS(i,2);
        B2 = SOS(i,3);
        A0 = SOS(i,4);
        A1 = SOS(i,5);
        A2 = SOS(i,6);
        
        D0 = SOS(i+1,1);
        D1 = SOS(i+1,2);
        D2 = SOS(i+1,3);
        C0 = SOS(i+1,4);
        C1 = SOS(i+1,5);
        C2 = SOS(i+1,6);
    
    
    if i == -1
        normalize_coeff = (A0 + A1 + A2) / (B0 + B1 + B2);
        normalize_coeff2 = (C0 + C1 + C2)/ (D0 + D1 + D2);
        
        B0 = B0 * normalize_coeff;
        B1 = B1 * normalize_coeff;
        B2 = B2 * normalize_coeff;
       
        D0 = D0 * normalize_coeff2;
        D1 = D1 * normalize_coeff2;
        D2 = D2 * normalize_coeff2;
        
        [b,a] = sos2tf([ B0 B1 B2 A0 A1 A2; D0 D1 D2 C0 C1 C2 ]);
        [h,w] = freqz(b,a,2001);
        
        
        figure(2)
       semilogx(w/(2*pi)*fs,20*log10(abs(h))+7, colorArray(i), 'linewidth', 3);
       axis([20 20000 -20 7]);
       xlabel('Frequency (Hz)');
       ylabel('Magnitude (dB)');
       title('6 Band EQ Range (7dB Swing)');
       hold on
       semilogx(w/(2*pi)*fs,20*log10(abs(h))-7, colorArray2(i,:), 'linewidth', 3);  
       
        %figure(1);   
        

      %plot(w/pi,h);
       


    else
        %normalize_coeff = (1./(10.^(dB((i-2))./20)));
        %normalize_coeff2 = (1./(10.^(dB((i-1))./20)));

        
        %B0 = B0 * normalize_coeff;
        %B1 = B1 * normalize_coeff;
        %B2 = B2 * normalize_coeff;
        
        %D0 = D0 * normalize_coeff2;
        %D1 = D1 * normalize_coeff2;
        %D2 = D2 * normalize_coeff2;
        
        % figure(round(i/32) + 1);
        [b,a] = sos2tf([ B0 B1 B2 A0 A1 A2]);
        [d,c] = sos2tf([ D0 D1 D2 C0 C1 C2 ]);
        [h,w] = freqz(b,a,5001);
        [h2,w2] = freqz(d,c,5001);
        20*log10(real(max(h)));
        20*log10(real(max(h2)));
        
        
%         [ beta, alpha] = sos2tf([ B0 B1 B2 A0 A1 A2;D0 D1 D2 C0 C1 C2 ]);
%      
%         [h3, w3] = freqz(beta,alpha,5001);
%          boost = (1/max(abs(h3))) * ();
%           
%           
%         B0 = B0;
%         B1 = B1;
%         B2 = B2;
%         
%         D0 = D0 * boost;
%         D1 = D1 * boost;
%         D2 = D2 * boost;
%        
%         [ beta, alpha] = sos2tf([ B0 B1 B2 A0 A1 A2;D0 D1 D2 C0 C1 C2 ]);
%         [h3, w3] = freqz(beta,alpha,5001);

        [ beta, alpha] = sos2tf([ B0 B1 B2 A0 A1 A2]);     
        [h3, w3] = freqz(beta,alpha,5001);
         boost = (1/max(abs(h3)));
          
        B0 = B0 * boost;
        B1 = B1 * boost;
        B2 = B2 * boost;
        
        figure(3);
        [ beta, alpha] = sos2tf([ B0 B1 B2 A0 A1 A2]);
        [h3, w3] = freqz(beta,alpha,5001);
        if i == 1 
            hold on
        end
        semilogx(w3/(2*pi)*fs,20*log10(abs(h3))+7, colorArray((i+1)/2), 'linewidth', 3);
        hold on
        semilogx(w3/(2*pi)*fs,20*log10(abs(h3))-7, colorArray2((i+1)/2,:),'linewidth', 3); 
        
        
        [ beta, alpha] = sos2tf([ D0 D1 D2 C0 C1 C2]);     
        [h3, w3] = freqz(beta,alpha,5001);
         boost = (1/max(abs(h3)));
          
        D0 = D0 * boost;
        D1 = D1 * boost;
        D2 = D2 * boost;

        figure(4);
        [ beta, alpha] = sos2tf([ D0 D1 D2 C0 C1 C2]);
        [h3, w3] = freqz(beta,alpha,5001);
        if i == 1 
            hold on
        end
        semilogx(w3/(2*pi)*fs,20*log10(abs(h3))+7, colorArray((i+1)/2), 'linewidth', 3);
        hold on
        semilogx(w3/(2*pi)*fs,20*log10(abs(h3))-7, colorArray2((i+1)/2,:),'linewidth', 3);     
        
        
        [ beta, alpha] = sos2tf([ B0 B1 B2 A0 A1 A2;D0 D1 D2 C0 C1 C2 ]);
        [h3, w3] = freqz(beta,alpha,5001);
         boost = (1/max(abs(h3)));
         dummy = round(16384*boost);
         fprintf(1,'%d, ', dummy);
                
        
        

        %axis([20 60000 -20 0])
       % hold on
        %plot(w/pi,h2);
       % hold on;
        ax = gca;
        %ax.YLim = [-100 20];
        %ax.XTick = 0:.5:2;\
        %{
        figure(i);
        plot(w/pi,20*log10(abs(h)));
        hold on
        
        plot(w2/pi,20*log10(abs(h2)),'r');
      %}
        
        %xlabel('Normalized Frequency (\times\pi rad/sample)')
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
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d,\n\n', ...
                B0_Q13, B1_Q13, B2_Q13, A0_Q13, A1_Q13, A2_Q13);
            fprintf(fd,'%d,\n %d,\n %d,\n %d,\n %d,\n %d\n};\n', ...
                D0_Q13, D1_Q13, D2_Q13, C0_Q13, C1_Q13, C2_Q13);            
        end
        
       [ beta, alpha] = sos2tf((1/(2^Q)) * [ B0_Q13 B1_Q13 B2_Q13 A0_Q13 ...
           A1_Q13 A2_Q13;D0_Q13 D1_Q13 D2_Q13 C0_Q13 C1_Q13 C2_Q13 ]);
       [h3, w3] = freqz(beta,alpha,5001);
        figure(1)
       semilogx(w3/(2*pi)*fs,20*log10(abs(h3))+7, colorArray((i+1)/2), 'linewidth', 3);
       hold on
       semilogx(w3/(2*pi)*fs,20*log10(abs(h3))-7, colorArray2((i+1)/2,:),'linewidth', 3);
       
      [h4, w4] = freqz(beta,alpha,5001);
      htot = htot + abs(h4);
end


fprintf(fd, '#endif //SIXBANDFILTERS_H_\n');


        figure(42)
       semilogx(w4/(2*pi)*fs,htot, 'b', 'linewidth', 3);
       hold on
    