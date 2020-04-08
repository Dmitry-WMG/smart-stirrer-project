% This code reads the data from the Smart Stirrer device using
% Bluetooth UART


list = blelist;
devices = table2cell(list);
stirrer_name = '';
for i = 1:height(list)
    name = string(devices(i, 2));
    if contains(name, 'Smart Stirrer') == 1
        stirrer_name = name;
    end
end

if strcmp(stirrer_name, '') == 1
    fprintf('Smart Stirrer is not detected.\n');
    return
end

% Establish connection with the Smart Stirrer
stirrer = ble(stirrer_name);
ch = table2cell(stirrer.Characteristics);
tx = characteristic(stirrer, string(ch(1, 2)), string(ch(1, 4)));
rx = characteristic(stirrer, string(ch(2, 2)), string(ch(2, 4)));

global start_time t;
start_time = rem(now, 1);
t = 1;
rx.DataAvailableFcn = @handleData;

% Set up the plot window
figure_data = figure(1);
subplot(4, 2, 1);
ylabel('Colour, a.u.');
subplot(4, 2, 2);
ylabel('Temperature, ^circC');
subplot(4, 2, 3);
ylabel('Conductivity, a.u.');
subplot(4, 2, 4);
ylabel('Accelerometer, g');
subplot(4, 2, 5);
ylabel('Gyroscop, ds^{-1}');
xlabel('Time, sec');
subplot(4, 2, 6);
ylabel('Magnetometer, gauss');
xlabel('Time, sec');
hold all

global colour adc accel gyro magn temp time Thermistor;
% Only subscribe to notifications once the plot window is set up.
subscribe(rx, 'notification');

function handleData(src, ~)
    dt = 10;
    raw = read(src, 'oldest');
    data = zeros(1, 17); % depending on how Smart Stirrer is programmed,
    % change the lenght of the data accordingly 
    for i = 1:2:33
        data((i+1)/2) = get_value(raw(i), raw(i+1));
        % uncomment this line for accel gyro and magn
        % data((i+1)/2) = swapbytes(typecast(uint8([raw(i) raw(i+1)]),'int16'));
    end
    save_data(data);
    global t rRaw; 
    plot_data();
    t = t + 1;
    rRaw(t,:) = raw;
end

function save_data(data)
    global start_time colour adc accel gyro magn temp time t Thermistor;
    colour(t, :) = data(1:4);
    adc(t, :)    = data(5:7);
    accel(t ,:)  = data(8:10)*8/2^15;
    gyro(t, :)   = data(11:13)*2000/2^15;
    magn(t, :)   = data(14:16)*16/2^15;
    temp(t)      = 27.97+0.0625*data(17);
    time(t)      = 86400 * (rem(now, 1) - start_time);
    Thermistor(t) = (3000*adc(t,3)/2^14-500)/10;
    colour(t,1) = 1.39.*colour(t,1);
    colour(t,3) = 1.79.*colour(t,3);
end

function plot_data()
    dt = 30;
    global colour adc time t Thermistor;
    subplot(4, 2, 1);
    plot(time, colour(:, 1), 'r', time, colour(:, 2), 'g', time, colour(:, 3), 'b', time, colour(:, 4), 'k')
    %legend('Red', 'Green', 'Blue', 'Clear');
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    % ADC Values
    subplot(4, 2, 2);
    plot(time, adc(:, 1));
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    subplot(4, 2, 3);
    plot(time, adc(:, 2));
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    subplot(4, 2, 4);
    %plot(time, adc(:, 3));
    plot(time, Thermistor);
    if time(t)>=dt
        xlim([time(t)-dt time(t)]);
        axis 'auto y'
     end
    % Other devices plotted in same way.

    drawnow;
end

% Linear bit-shift algorithm, should grow ~O(1)
% NOTE: More efficient than converting to binary then concatenating
function val = get_value(x1, x2)
    val = 0;
    y1 = x1;
    for j = 15:-1:8
        k = 2^(j-8);
        if y1 >= k
            val = val + (256 * k);
            y1 = y1 - k;
        end
    end
    y2 = x2;
    for j = 7:-1:0
        k = 2^(j);
        if y2 >= k
            val = val + k;
            y2 = y2 - k;
        end
    end
end
    
%typecast(uint16(sscanf('FFDF', '%x')), 'int16')