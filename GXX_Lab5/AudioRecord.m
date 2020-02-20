% % Record your voice for 5 seconds.
% recObj = audiorecorder;
% disp('Start speaking.')
% recordblocking(recObj, 2 );
% disp('End of Recording.');
% 
% % Play back the recording.
% play(recObj);
% 
% % Store data in double-precision array.
% myRecording = getaudiodata(recObj);
% figure; plot(myRecording); % Plot the original waveform.
% 
% % cut the area you want and convert it into integers
% % crop from pointer to pointer+1000
% MyAudioArray = uint8((myRecording(:)+1)*128/2); 
% csvwrite('AudioArray.csv',MyAudioArray');
% % Plot the modified waveform.
% figure;plot(MyAudioArray);

MyNewTransmit = MyAudioArray;
% Setup the serial port connection in matlab
delete (instrfind);
mcu = serial('COM4','BAUD',115200); %configuration of UART port
mcu.OutputBufferSize=40001;  %8000-bits data size
fopen(mcu); %open mcu port
fwrite(mcu,'x','uint8','async');
pause(5);
fwrite(mcu, MyNewTransmit,'uint8','async');
% Set a delay for it to complete the transimission than close the port
pause(5);
fclose(mcu);
delete(mcu);