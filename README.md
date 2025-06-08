# Near-Field EMI Detector

## ✨Project Overview

This project aims to design and develop a near-field electromagnetic interference (EMI) detector capable 
of measuring electric and magnetic fields separately. The detector will use a microcontroller and two 
sensor probes one for detecting electric fields (E-fields) and one for detecting magnetic fields (H-fields). 
By measuring these fields individually, the detector will provide precise data on EMI sources, which is 
valuable for troubleshooting and optimizing electronic circuits.

## 🎯Objectives

1. To design and build a cost-effective near-field EMI detector capable of detecting both electric and 
magnetic fields. 
2. To develop a microcontroller-based system to read, process, and display field strength 
measurements in real-time. 
3. To enhance the device with features such as data logging,  or visual indicators for EMI levels.

## 🛠️Technical Approach 

### 1. System Design: 
- A microcontroller (Arduino/ESP32) will serve as the central processing unit to handle data 
acquisition and user interface. 
- Two probes will be developed: 
E-field Probe: A metal plate or antenna with an operational amplifier for high
impedance measurement of electric fields. 
H-field Probe: A loop antenna or Hall Effect sensor to detect magnetic fields. 
- Both sensors will connect to the microcontroller’s analog inputs for signal processing. 
### 2. Signal Processing: 
- Operational amplifiers will be used to boost the signal strength from both probes. 
- Signal conditioning, including filtering and threshold detection, will be applied in 
software. 
### 3. Software Development: 
- The microcontroller will read sensor data, apply signal filtering, and output field strength 
measurements. 
- Threshold levels will be set to indicate varying EMI levels. 
- Data will be displayed on an OLED/LCD screen or sent to a mobile device for real-time 
monitoring. 
### 4. Testing and Calibration: 
- Testing near known EMI sources (e.g., power supplies, transformers) to verify the 
accuracy and range of the detector. 
- Calibration of sensor sensitivity to ensure reliable differentiation between electric and 
magnetic field strengths. 
