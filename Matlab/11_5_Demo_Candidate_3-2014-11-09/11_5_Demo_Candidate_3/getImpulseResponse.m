function [ fullRespose, timestamp ] = getImpulseResponse( fs )

%intialize recorder
recorder = audiorecorder(fs, 16, 1);
timestamp = [];

%get user input
temp = input('Press enter, clap, then press enter again');
timestamp = clock;
record(recorder);

temp = input('Press enter when finished');
stop(recorder);

temp = input('Play back? (Y/n)','s');
if(temp == 'Y')
    play(recorder);
end

%finish and write data to file for later use
fullRespose = getaudiodata(recorder);

firstIndex = 0;

for i = 1:size(fullRespose)
    if fullRespose(i) > 0.1
        firstIndex = i;
        break;
    end
end

STARTOFFSET = 100;

if(firstIndex-STARTOFFSET < 0)
    STARTOFFSET = -1;
end

fftSize = (2.^(floor(log2(length(fullRespose) - firstIndex))))/2;

range = firstIndex-STARTOFFSET:(firstIndex+fftSize-1-STARTOFFSET);

response = fullRespose(range);

end

