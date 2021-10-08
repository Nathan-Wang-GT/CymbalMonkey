
clc
clear
[dataC, fs] = audioread('CMajor.wav');
[dataD, fs2] = audioread('DMajor.wav');
[dataE, fs3] = audioread('EMajor.wav');
[dataF, fs4] = audioread('FMajor.wav');
[dataG, fs5] = audioread('GMajor.wav');

x = 1:size(dataG);
plot(x, dataG);
%x = 1:size(y);

%plot(x, dataC);

C = dataC(1:10000);
D = dataD(1:10000);
E = dataE(1:10000);
F = dataF(1:10000);
G = dataG(1:10000);

data = [C, D, E, F, G];
%sampleF = 10:10:1000; %523.2511;
%bins = 2 * (sampleF./fs) * 10000;
%sampleF = 523.2511;
sampleF = 659.2551; % F 698.4565; % G 783.9909; 	
bin = 2 * sampleF / fs * 10000;

powerArr = [0,0,0,0,0];%zeros(5);

for i = 1:size(data.')
    power = goertzel_FFT(data(:,i), bin, 10000);
    disp([num2str(sampleF) ' - ' num2str(power)]);
    powerArr(i) = power;
end

x = categorical({'C', 'D', 'E', 'F', 'G'});
x = reordercats(x, {'C', 'D', 'E', 'F', 'G'});
b = bar(x, powerArr);
title(['\fontsize{16}Testing notes to \color{red}' num2str(sampleF) '(E Note)']);
xlabel('Note');
ylabel('Power');



