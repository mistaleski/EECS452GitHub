
num = 512;
t = 0:2*pi/num:2*pi-(2*pi/num);
y = round(32767*sin(t));
for (k < 100)
    soundsc(y, 48000);
    k=k+1;
end