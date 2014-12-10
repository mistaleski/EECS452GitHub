close all    

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
            fprintf(1,'%d,\n %d,\n %d,\n %d,\n %d,\n %d,\n\n', ...
                B0_Q13, B1_Q13, B2_Q13, A0_Q13, A1_Q13, A2_Q13);
            fprintf(1,'%d,\n %d,\n %d,\n %d,\n %d,\n %d,\n\n', ...
                D0_Q13, D1_Q13, D2_Q13, C0_Q13, C1_Q13, C2_Q13);
        elseif i == xsize-1
            fprintf(1,'%d,\n %d,\n %d,\n %d,\n %d,\n %d,\n\n', ...
                B0_Q13, B1_Q13, B2_Q13, A0_Q13, A1_Q13, A2_Q13);
            fprintf(1,'%d,\n %d,\n %d,\n %d,\n %d,\n %d\n};\n', ...
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