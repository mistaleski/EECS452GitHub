function [ ] = playNormalized( x , fs)

% Normalize
toPlay = (x./max(x(:,1)))*0.8;

% Play!
sound(toPlay, fs)

end

