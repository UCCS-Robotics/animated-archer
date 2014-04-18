clc, clear, close all

sensorID = 1;
filename='D:\Users\Chris\Documents\GitHub\animated-archer\Sensor Profiles\UltraSonicSensors.xlsx';
sheet = 1;

% Distance (in)
xlRange = 'A3:A50';
distanceIn = xlsread(filename, sheet, xlRange);
xlRange = 'B3:B50';
distanceCm = xlsread(filename, sheet, xlRange);
xlRange = 'C3:C50';
distancem = xlsread(filename, sheet, xlRange);

% Measurements
xlRange = 'D3:D50';
measV1 = xlsread(filename, sheet, xlRange);
xlRange = 'H3:H50';
measV2 = xlsread(filename, sheet, xlRange);
xlRange = 'L3:L50';
measV3 = xlsread(filename, sheet, xlRange);
xlRange = 'P3:P50';
averageV = xlsread(filename, sheet, xlRange);
xlRange = 'T3:T50';
IdealV = xlsread(filename, sheet, xlRange);

% errors
measError1=abs(IdealV-measV1)./measV1;
measError2=abs(IdealV-measV2)./measV2;
measError3=abs(IdealV-measV3)./measV3;
measErrorAvg=abs(IdealV-averageV)./averageV;

plot(distanceCm,IdealV,'.-',distanceCm,measV1,'.-',distanceCm,measV2,'.-',distanceCm,measV3,'.-');
title('Distance vs Raw Output Voltage');
xlabel('Distance (cm)');
ylabel('Voltage (V)');
legend('Ideal', 'Measurement 1', 'Measurement 2', 'Measurement 3');
figure
plot(distanceCm,IdealV,'.-',distanceCm,averageV,'.-');
title('Distance vs Average Output Voltage');
xlabel('Distance (cm)');
ylabel('Voltage (V)');
legend('Ideal', 'Average Measurement');
figure
semilogy(distanceCm,measError1,'.-',distanceCm,measError2,'.-',distanceCm,measError3,'.-');
title('Distance vs Raw Output Error');
xlabel('Distance (cm)');
ylabel('Voltage (V)');
legend('Measurement 1', 'Measurement 2', 'Measurement 3');
figure
semilogy(distanceCm,measErrorAvg,'.-');
title('Distance vs Average Output Error');
xlabel('Distance (cm)');
ylabel('Voltage (V)');