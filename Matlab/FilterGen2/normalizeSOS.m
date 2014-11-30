    

    Q = 15;

    B0 = SOS(1);
    B1 = SOS(2);
    B2 = SOS(3);
    A0 = SOS(4);
    A1 = SOS(5);
    A2 = SOS(6);
    
    normalize_coeff = (A0 + A1 + A2) / (B0 + B1 + B2);
    
    B0 = B0 * normalize_coeff;
    B1 = B1 * normalize_coeff;
    B2 = B2 * normalize_coeff;
    
    
    B0_Q13 = round(((2^Q) * B0) - 1);
    B1_Q13 = round(((2^Q) * B1) - 1);
    B2_Q13 = round(((2^Q) * B2) - 1);
    A0_Q13 = round(((2^Q) * A0) - 1);
    A1_Q13 = round(((2^Q) * A1) - 1);
    A2_Q13 = round(((2^Q) * A2) - 1);
    
    fprintf(1,'{%d, %d, %d, %d, %d, %d}', B0_Q13, B1_Q13, ...
        B2_Q13, A0_Q13, A1_Q13, A2_Q13);
    
    figure(1);
    [b,a] = sos2tf([ B0 B1 B2 A0 A1 A2 ]);
    [h,w] = freqz(b,a,2001);

    [b2,a2] = sos2tf([ B0_Q13/2^Q B1_Q13/2^Q ...
        B2_Q13/2^Q A0_Q13/2^Q ...
        A1_Q13/2^Q A2_Q13/2^Q ]);
    [h2,w2] = freqz(b2,a2,2001);

    plot(w/pi,20*log10(abs(h)));
    hold on;
    plot(w2/pi,20*log10(abs(h2)), 'r');
    ax = gca;
    ax.YLim = [-100 20];
    ax.XTick = 0:.5:2;
    xlabel('Normalized Frequency (\times\pi rad/sample)')
    ylabel('Magnitude (dB)')