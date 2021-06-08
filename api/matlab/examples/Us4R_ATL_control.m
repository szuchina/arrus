
% path to the MATLAB API files
addpath('../arrus');

txFrequency = 5e6;
samplingFrequency = 65e6;

[filtB,filtA] = butter(2,[0.5 1.5]*txFrequency/(samplingFrequency/2),'bandpass');

nUs4OEM = 2;

%% Initialize the system, sequence, and reconstruction
us	= Us4R('nUs4OEM',      nUs4OEM, ...
           'probeName',   'L7-4', ...
           'adapterType', 'atl/philips', ...
           'voltage',      40);

seqSTA = STASequence(	'txApertureCenter', (-15:3:15)*1e-3, ...
                        'txApertureSize',   32, ...
                        'txFocus',          -6*1e-3, ...
                        'txAngle',          0*pi/180, ...
                        'speedOfSound',     1540, ...
                        'txFrequency',      txFrequency, ...
                        'txNPeriods',       2, ...
                        'rxNSamples',       8*1024, ...
                        'nRepetitions',     1, ...
                        'txPri',            200*1e-6, ...
                        'tgcStart',         14, ...
                        'tgcSlope',         2e2);

seqPWI = PWISequence(	'txApertureCenter', 0*1e-3, ...
                        'txApertureSize',   128, ...
                        'txFocus',          inf*1e-3, ...
                        'txAngle',          [-10 0 10]*pi/180, ...
                        'speedOfSound',     1540, ...
                        'txFrequency',      txFrequency, ...
                        'txNPeriods',       2, ...
                        'rxNSamples',       4*1024, ...
                        'nRepetitions',     1, ...
                        'txPri',            200*1e-6, ...
                        'tgcStart',         14, ...
                        'tgcSlope',         2e2);

seqLIN = LINSequence(	'txCenterElement',	1:128, ...
                        'txApertureSize',   32, ...
                        'txFocus',          20*1e-3, ...
                        'txAngle',          0*pi/180, ...
                        'speedOfSound',     1540, ...
                        'txFrequency',      txFrequency, ...
                        'txNPeriods',       2, ...
                        'rxNSamples',       8*1024, ...
                        'nRepetitions',     1, ...
                        'txPri',            200*1e-6, ...
                        'tgcStart',         14, ...
                        'tgcSlope',         2e2);

% GPU/CPU reconstruction implemented in matlab.
rec = Reconstruction(   'filterEnable',     true, ...
                        'filterACoeff',     filtA, ...
                        'filterBCoeff',     filtB, ...
                        'iqEnable',         true, ...
                        'cicOrder',         2, ...
                        'decimation',       4, ...
                        'xGrid',            (-20:0.10:20)*1e-3, ...
                        'zGrid',            (  0:0.10:100)*1e-3);

us.upload(seqPWI,rec);
% us.upload(seqSTA,rec);
% us.upload(seqLIN,rec);

%% Run sequence and reconstruction
%[rf,img] = us.run;

%disp(size(rf));
%disp(size(img));

display = BModeDisplay((-20:0.10:20)*1e-3, (  0:0.10:100)*1e-3);
us.runLoop(@display.isOpen, @display.updateImg);


