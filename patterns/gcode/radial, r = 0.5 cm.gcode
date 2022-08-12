; Setting units to millimetres
G21 
; Clearing offsets
G53 

; Auto homing
G91 
G0 Z10.000 F600 
G90 
G28 X0.000 Y0.000 Z0.000 

; Defining tool offset
M6 T12 O2 X120.000 Y30.000 Z56.000 

; Setting hotend temperature
M109 T12 S20 
; Setting bed temperature
M190 S0 

; Configuring flow
M221 T12 W0.490 Z0.200 S1.000 P1297 
; Configure priming
M721 T12 S0.000 E0.000 P0.000 I0 
; Configure priming
M722 T12 S0.000 E0.000 P0.000 I0 
; Selecting tool
T1 

; Invoking offsets
G0 X0.000 Y0.000 
G0 Z0.000 H2 

; Starting cleaning
G0 X0.000 Y0.000 F1800 
G1 X20.000 Y0.000 F600 E1 
G0 X20.000 Y0.490 F1800 
G1 X0.000 Y0.490 F600 E1 
G0 X0.000 Y0.980 F1800 
G1 X20.000 Y0.980 F600 E1 
G0 X20.000 Y1.470 F1800 
G1 X0.000 Y1.470 F600 E1 

; Starting printing
; Setting bed temperature
M190 S0 
; Setting hotend temperature
M109 S0 

; Auto homing
G91 
G0 Z10.000 F600 
G90 
G28 X0.000 Y0.000 Z0.000 

; Turning motors off
M18 
; Signaling finished print
M30 
