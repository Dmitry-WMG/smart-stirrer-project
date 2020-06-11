% This code reads the data from the Smart Stirrer device using
% Bluetooth UART

clf
clc
clear all

list = blelist;
devices = table2cell(list);
stirrer_name = '';
for i = 1:height(list)
    name = string(devices(i, 2));
    if contains(name, 'Smart') == 1
        stirrer_name = name;
        fprintf('Discovered device: %s \n',stirrer_name)
    end
end
clear i list devices

if strcmp(stirrer_name, '') == 1
    fprintf('Smart Stirrer is not detected.\n');
    return
end

% Establish connection with the Smart Stirrer
stirrer = ble(stirrer_name);
ch = table2cell(stirrer.Characteristics);
tx = characteristic(stirrer, string(ch(1, 2)), string(ch(1, 4)));
rx = characteristic(stirrer, string(ch(2, 2)), string(ch(2, 4)));

global start_time t Tab;
start_time = rem(now, 1);
t = 1;
rx.DataAvailableFcn = @handleData;

% Set up the plot window
figure_data = figure(1);
subplot(3, 2, 1);
ylabel('Colour, a.u.');
subplot(3, 2, 2);
ylabel('Temperature, ^\circC');
subplot(3, 2, 3);
ylabel('Accelerometer, \it{g}');
subplot(3, 2, 4);
ylabel('Conductivity, au');
subplot(3, 2, 5);
ylabel('Gyroscop, ds^{-1}');
xlabel('Time, sec');
subplot(3, 2, 6);
ylabel('Magnetometer, gauss');
xlabel('Time, sec');
hold all

global rRaw t colour adc accel gyro magn temp time Thermistor;
% Only subscribe to notifications once the plot window is set up.
subscribe(rx, 'notification');
fprintf('Collecting data ....\n')

function handleData(src, ~)
    dt = 10; % this parameter corresponds to the x-axis lenghts update in seconds 
    global t rRaw;
    raw = read(src, 'oldest');
    data = zeros(1, 11); % depending on how Smart Stirrer is programmed,
  
    rRaw(t,:) = raw;
    
    for i = 1:2:21
        data((i+1)/2) = swapbytes(typecast(uint8([raw(i) raw(i+1)]),'int16'));
    end
    
    save_data(data);
    plot_data();
    t = t + 1;
    
end

function save_data(data)
    global Tab start_time colour adc accel gyro magn temp time t Thermistor;
    time(t)      = 86400 * (rem(now, 1) - start_time);
    colour(t, :) = data(1:4);
    adc(t, :)    = data(5:7);
    accel(t,:)   = data(8:10)/2^12;
    temp(t)      = 27.97+0.0625*data(11);
    %gyro(t, :)   = data(11:13)*2000/2^15;
    %magn(t, :)   = data(14:16)*16/2^15;
    Thermistor(t) = (3000*adc(t,3)/2^14-500)/10;
    colour(t,1) = 1.39.*colour(t,1);
    colour(t,3) = 1.79.*colour(t,3);
    Tab(t,:) = [time(t), colour(t,:), adc(t,:), accel(t,:), temp(t)];
    writematrix(Tab,'Experiment.txt','Delimiter','tab')
    
end

function plot_data()
    dt = 30;
    global colour adc accel time t Thermistor temp;
    subplot(3, 2, 1);
    plot(time, colour(:, 1), 'r', time, colour(:, 2), 'g', time, colour(:, 3), 'b', time, colour(:, 4), 'k')
    %legend('Red', 'Green', 'Blue', 'Clear');
    ylabel('Colour, a.u.');
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    % ADC Values
    subplot(3, 2, 2);
    plot(time, temp, time, 69.6+Thermistor );
    ylabel('Temperature, ^\circC');
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    subplot(3, 2, 3);
    plot(time, accel(:,1),time, accel(:,2), time, accel(:,3));
    ylabel('Accelerometer, \it{g}');
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    subplot(3, 2, 4);
    plot(time, 0.01*adc(:,2));
    ylabel('Conductivity, a.u.');
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    % Other devices plotted in same way.

    drawnow;
end

