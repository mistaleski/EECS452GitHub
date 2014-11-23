function [ index ] = getFFTIndex( N, fs, f )

    index = round((f/fs)*N);

end

