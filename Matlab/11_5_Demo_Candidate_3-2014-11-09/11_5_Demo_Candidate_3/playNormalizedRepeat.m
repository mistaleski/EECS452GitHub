function [ ] = playNormalizedRepeat( x, fs )

while 1
    playNormalized(x, fs);
    blah = input('Press enter to play again, or input C to continue', 's');
    if blah == 'C'
        break
    end
end

end

