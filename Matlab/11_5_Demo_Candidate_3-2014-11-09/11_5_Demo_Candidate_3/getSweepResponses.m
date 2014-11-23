function [ FFTresponse, FFTsweep, sweep ] = getSweepResponses(FS, FMIN, FMAX, ISLOG, SWEEPTIME, numRepeats)
% 
[t, sweep] = makeSweep(FS, FMIN, FMAX, ISLOG, SWEEPTIME);

% record
for i = 1:numRepeats
    response(i,:) = zeros(1,131072);
    [rTemp, timestamp(i,:)] = RecordReponse(FS, sweep);
    lTemp = length(rTemp);
    response(i,1:lTemp) = rTemp;
end

% pad
for i = 1:numRepeats
	[sweepPad reponsePad(i,:)] = fftPrep(sweep, response(i,:));
    length(reponsePad(i,:))
end

window = transpose(chebwin(length(reponsePad(1,:)),100));

FFTresponse = zeros(1,length(reponsePad(1,:)));
FFTDBresponse = zeros(1,length(reponsePad(1,:)));

figure(42);
clf;
for i = 1:numRepeats
    reponsePad(i,:) = window.*reponsePad(i,:);
    % Take FFT of data
    FFTtemp(i,:) = fft(reponsePad(i,:));
end

% Select reference FFT
FFTref = FFTtemp(round(numRepeats/2),:);

for i = 1:numRepeats
    FFTDBresponse = FFTDBresponse + 20*log10(abs(FFTtemp(i,:)));
end

% complete averaging process
FFTDBresponse = FFTDBresponse/numRepeats;
FFTMagresponse = 10.^(FFTDBresponse./20);

FFTresponse = (FFTref./abs(FFTref)) .* FFTMagresponse;

figure(42);
clf;
loglog(abs(FFTtemp(1,:)));
hold on;
loglog(abs(FFTtemp(2,:)), 'r');
loglog(abs(FFTtemp(3,:)), 'g');
loglog(abs(FFTresponse), 'k');

% Take FFT of sweep
FFTsweep = fft(sweepPad);


end

