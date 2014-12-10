count = 0;
for i = 0:-.5:-14
   value =  10^(i/20);
   fprintf('dBValue[%f] = %f //dB value %f\n', count,value, i);
   count = count +1;
    
end