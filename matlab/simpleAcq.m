%==================================================================================================
% simpleAcq.m - A simple Matlab script for ultrasound data acquisition with the ARIUS platform.
%--------------------------------------------------------------------------------------------------
% Copyright (c) 2019 us4us Ltd. / MIT License
%==================================================================================================
%% Setup the Arius platform.
json = fileread('PA-BFR.json'); % load TX/RX JSON config file

hal = MockHAL(rand(32, 512, 32, 3)); 
% MockHAL's constructor can take one optional argument 'data':
% - 3-D matrix with dimensions: (x, y, z) - single 'RF frame'
% - 4-D matrix with dimensions: (x, y, z, n) - collection of RF frames to cycle 
%   through; the last dimension corresponds to the RF frame number. 
%  When no argument is provided: three random RF frames (32, 512, 32) are 
%  generated.

hal.configure(json);    % init HAL with the TX/RX JSON
hal.start();            % start TX/RX

[B,A] = butter(5, 1/25, 'high');    % define a RF high-pass filter

%% Acquire ultrasound data Frame-by-Frame
for i = 1:3
    signal = single(hal.getData());
    hal.sync();
    %figure(1);     % show raw RF data
    %signal_filt = filter(B, A, signal, [], 2); % filter raw RF with HP filter

    % plot(signal(:,:)'); % plot RF signal
    %drawnow;
    %pause(0.1);
    % disp(signal);
end
