fs = 44100;;
t = (0:1/fs:1-1/fs);
signal = cos(2*pi*50*t);
%plot(signal);
surf(signal)