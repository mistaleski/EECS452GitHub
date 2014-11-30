Fc = 150;
Hd = LowPassCoeffGen(Fc);
values = coeffs(Hd);
SOS = values.SOSMatrix;



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
    
    fprintf(1,'{%d, %d, %d, %d, %d, %d}\n', B0_Q13, B1_Q13, ...
        B2_Q13, A0_Q13, A1_Q13, A2_Q13);