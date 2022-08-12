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
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X1.339 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X1.339 Y13.820 F600 E1 
G1 X1.111 Y13.591 F600 E1 
G1 X0.882 Y13.363 F600 E1 
G1 X0.653 Y13.134 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X0.653 Y12.383 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X0.653 Y12.383 F600 E1 
G1 X0.882 Y12.611 F600 E1 
G1 X1.111 Y12.840 F600 E1 
G1 X1.339 Y13.069 F600 E1 
G1 X1.568 Y13.297 F600 E1 
G1 X1.797 Y13.526 F600 E1 
G1 X2.025 Y13.755 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X2.744 Y13.722 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X2.744 Y13.722 F600 E1 
G1 X2.515 Y13.493 F600 E1 
G1 X2.254 Y13.232 F600 E1 
G1 X2.025 Y13.003 F600 E1 
G1 X1.797 Y12.775 F600 E1 
G1 X1.568 Y12.546 F600 E1 
G1 X1.339 Y12.317 F600 E1 
G1 X1.111 Y12.089 F600 E1 
G1 X0.882 Y11.860 F600 E1 
G1 X0.653 Y11.631 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X0.653 Y10.880 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X0.653 Y10.880 F600 E1 
G1 X0.882 Y11.109 F600 E1 
G1 X1.111 Y11.337 F600 E1 
G1 X1.339 Y11.566 F600 E1 
G1 X1.568 Y11.795 F600 E1 
G1 X1.797 Y12.023 F600 E1 
G1 X2.025 Y12.252 F600 E1 
G1 X2.254 Y12.481 F600 E1 
G1 X2.515 Y12.742 F600 E1 
G1 X2.744 Y12.971 F600 E1 
G1 X2.973 Y13.199 F600 E1 
G1 X3.201 Y13.428 F600 E1 
G1 X3.430 Y13.657 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X4.345 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X4.345 Y13.820 F600 E1 
G1 X4.116 Y13.591 F600 E1 
G1 X3.887 Y13.363 F600 E1 
G1 X3.659 Y13.134 F600 E1 
G1 X3.430 Y12.905 F600 E1 
G1 X3.201 Y12.677 F600 E1 
G1 X2.973 Y12.448 F600 E1 
G1 X2.744 Y12.219 F600 E1 
G1 X2.483 Y11.958 F600 E1 
G1 X2.254 Y11.729 F600 E1 
G1 X2.025 Y11.501 F600 E1 
G1 X1.797 Y11.272 F600 E1 
G1 X1.568 Y11.043 F600 E1 
G1 X1.339 Y10.815 F600 E1 
G1 X1.111 Y10.586 F600 E1 
G1 X0.882 Y10.357 F600 E1 
G1 X0.653 Y10.129 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X0.719 Y9.443 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X0.719 Y9.443 F600 E1 
G1 X0.947 Y9.671 F600 E1 
G1 X1.176 Y9.900 F600 E1 
G1 X1.405 Y10.129 F600 E1 
G1 X1.633 Y10.357 F600 E1 
G1 X1.862 Y10.586 F600 E1 
G1 X2.091 Y10.815 F600 E1 
G1 X2.319 Y11.043 F600 E1 
G1 X2.548 Y11.272 F600 E1 
G1 X2.777 Y11.501 F600 E1 
G1 X3.005 Y11.729 F600 E1 
G1 X3.234 Y11.958 F600 E1 
G1 X3.495 Y12.219 F600 E1 
G1 X3.724 Y12.448 F600 E1 
G1 X3.953 Y12.677 F600 E1 
G1 X4.181 Y12.905 F600 E1 
G1 X4.410 Y13.134 F600 E1 
G1 X4.639 Y13.363 F600 E1 
G1 X4.867 Y13.591 F600 E1 
G1 X5.096 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X5.847 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X5.847 Y13.820 F600 E1 
G1 X5.619 Y13.591 F600 E1 
G1 X5.390 Y13.363 F600 E1 
G1 X5.161 Y13.134 F600 E1 
G1 X4.933 Y12.905 F600 E1 
G1 X4.704 Y12.677 F600 E1 
G1 X4.475 Y12.448 F600 E1 
G1 X4.247 Y12.219 F600 E1 
G1 X3.985 Y11.958 F600 E1 
G1 X3.757 Y11.729 F600 E1 
G1 X3.528 Y11.501 F600 E1 
G1 X3.299 Y11.272 F600 E1 
G1 X3.071 Y11.043 F600 E1 
G1 X2.842 Y10.815 F600 E1 
G1 X2.613 Y10.586 F600 E1 
G1 X2.385 Y10.357 F600 E1 
G1 X2.156 Y10.129 F600 E1 
G1 X1.927 Y9.900 F600 E1 
G1 X1.699 Y9.671 F600 E1 
G1 X1.470 Y9.443 F600 E1 
G1 X1.241 Y9.214 F600 E1 
G1 X1.013 Y8.985 F600 E1 
G1 X0.751 Y8.724 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X0.653 Y7.875 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X0.653 Y7.875 F600 E1 
G1 X0.817 Y8.038 F600 E1 
G1 X1.045 Y8.267 F600 E1 
G1 X1.274 Y8.495 F600 E1 
G1 X1.503 Y8.724 F600 E1 
G1 X1.764 Y8.985 F600 E1 
G1 X1.993 Y9.214 F600 E1 
G1 X2.221 Y9.443 F600 E1 
G1 X2.450 Y9.671 F600 E1 
G1 X2.679 Y9.900 F600 E1 
G1 X2.907 Y10.129 F600 E1 
G1 X3.136 Y10.357 F600 E1 
G1 X3.365 Y10.586 F600 E1 
G1 X3.593 Y10.815 F600 E1 
G1 X3.822 Y11.043 F600 E1 
G1 X4.051 Y11.272 F600 E1 
G1 X4.279 Y11.501 F600 E1 
G1 X4.508 Y11.729 F600 E1 
G1 X4.737 Y11.958 F600 E1 
G1 X4.998 Y12.219 F600 E1 
G1 X5.227 Y12.448 F600 E1 
G1 X5.455 Y12.677 F600 E1 
G1 X5.684 Y12.905 F600 E1 
G1 X5.913 Y13.134 F600 E1 
G1 X6.141 Y13.363 F600 E1 
G1 X6.370 Y13.591 F600 E1 
G1 X6.599 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X7.350 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X7.350 Y13.820 F600 E1 
G1 X7.121 Y13.591 F600 E1 
G1 X6.893 Y13.363 F600 E1 
G1 X6.664 Y13.134 F600 E1 
G1 X6.435 Y12.905 F600 E1 
G1 X6.207 Y12.677 F600 E1 
G1 X5.978 Y12.448 F600 E1 
G1 X5.749 Y12.219 F600 E1 
G1 X5.488 Y11.958 F600 E1 
G1 X5.259 Y11.729 F600 E1 
G1 X5.031 Y11.501 F600 E1 
G1 X4.802 Y11.272 F600 E1 
G1 X4.573 Y11.043 F600 E1 
G1 X4.345 Y10.815 F600 E1 
G1 X4.116 Y10.586 F600 E1 
G1 X3.887 Y10.357 F600 E1 
G1 X3.659 Y10.129 F600 E1 
G1 X3.430 Y9.900 F600 E1 
G1 X3.201 Y9.671 F600 E1 
G1 X2.973 Y9.443 F600 E1 
G1 X2.744 Y9.214 F600 E1 
G1 X2.515 Y8.985 F600 E1 
G1 X2.254 Y8.724 F600 E1 
G1 X2.025 Y8.495 F600 E1 
G1 X1.797 Y8.267 F600 E1 
G1 X1.568 Y8.038 F600 E1 
G1 X1.339 Y7.809 F600 E1 
G1 X1.111 Y7.581 F600 E1 
G1 X0.882 Y7.352 F600 E1 
G1 X0.653 Y7.123 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X0.719 Y6.437 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X0.719 Y6.437 F600 E1 
G1 X0.947 Y6.666 F600 E1 
G1 X1.176 Y6.895 F600 E1 
G1 X1.405 Y7.123 F600 E1 
G1 X1.633 Y7.352 F600 E1 
G1 X1.862 Y7.581 F600 E1 
G1 X2.091 Y7.809 F600 E1 
G1 X2.319 Y8.038 F600 E1 
G1 X2.548 Y8.267 F600 E1 
G1 X2.777 Y8.495 F600 E1 
G1 X3.005 Y8.724 F600 E1 
G1 X3.267 Y8.985 F600 E1 
G1 X3.495 Y9.214 F600 E1 
G1 X3.724 Y9.443 F600 E1 
G1 X3.953 Y9.671 F600 E1 
G1 X4.181 Y9.900 F600 E1 
G1 X4.410 Y10.129 F600 E1 
G1 X4.639 Y10.357 F600 E1 
G1 X4.867 Y10.586 F600 E1 
G1 X5.096 Y10.815 F600 E1 
G1 X5.325 Y11.043 F600 E1 
G1 X5.553 Y11.272 F600 E1 
G1 X5.782 Y11.501 F600 E1 
G1 X6.011 Y11.729 F600 E1 
G1 X6.239 Y11.958 F600 E1 
G1 X6.501 Y12.219 F600 E1 
G1 X6.729 Y12.448 F600 E1 
G1 X6.958 Y12.677 F600 E1 
G1 X7.187 Y12.905 F600 E1 
G1 X7.415 Y13.134 F600 E1 
G1 X7.644 Y13.363 F600 E1 
G1 X7.873 Y13.591 F600 E1 
G1 X8.101 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X8.853 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X8.853 Y13.820 F600 E1 
G1 X8.624 Y13.591 F600 E1 
G1 X8.395 Y13.363 F600 E1 
G1 X8.167 Y13.134 F600 E1 
G1 X7.938 Y12.905 F600 E1 
G1 X7.709 Y12.677 F600 E1 
G1 X7.481 Y12.448 F600 E1 
G1 X7.252 Y12.219 F600 E1 
G1 X6.991 Y11.958 F600 E1 
G1 X6.762 Y11.729 F600 E1 
G1 X6.533 Y11.501 F600 E1 
G1 X6.305 Y11.272 F600 E1 
G1 X6.076 Y11.043 F600 E1 
G1 X5.847 Y10.815 F600 E1 
G1 X5.619 Y10.586 F600 E1 
G1 X5.390 Y10.357 F600 E1 
G1 X5.161 Y10.129 F600 E1 
G1 X4.933 Y9.900 F600 E1 
G1 X4.704 Y9.671 F600 E1 
G1 X4.475 Y9.443 F600 E1 
G1 X4.247 Y9.214 F600 E1 
G1 X4.018 Y8.985 F600 E1 
G1 X3.757 Y8.724 F600 E1 
G1 X3.528 Y8.495 F600 E1 
G1 X3.299 Y8.267 F600 E1 
G1 X3.071 Y8.038 F600 E1 
G1 X2.842 Y7.809 F600 E1 
G1 X2.613 Y7.581 F600 E1 
G1 X2.385 Y7.352 F600 E1 
G1 X2.156 Y7.123 F600 E1 
G1 X1.927 Y6.895 F600 E1 
G1 X1.699 Y6.666 F600 E1 
G1 X1.470 Y6.437 F600 E1 
G1 X1.241 Y6.209 F600 E1 
G1 X1.013 Y5.980 F600 E1 
G1 X0.784 Y5.751 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X1.535 Y5.751 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X1.535 Y5.751 F600 E1 
G1 X1.764 Y5.980 F600 E1 
G1 X1.993 Y6.209 F600 E1 
G1 X2.221 Y6.437 F600 E1 
G1 X2.450 Y6.666 F600 E1 
G1 X2.679 Y6.895 F600 E1 
G1 X2.907 Y7.123 F600 E1 
G1 X3.136 Y7.352 F600 E1 
G1 X3.365 Y7.581 F600 E1 
G1 X3.593 Y7.809 F600 E1 
G1 X3.822 Y8.038 F600 E1 
G1 X4.051 Y8.267 F600 E1 
G1 X4.279 Y8.495 F600 E1 
G1 X4.508 Y8.724 F600 E1 
G1 X4.769 Y8.985 F600 E1 
G1 X4.998 Y9.214 F600 E1 
G1 X5.227 Y9.443 F600 E1 
G1 X5.455 Y9.671 F600 E1 
G1 X5.684 Y9.900 F600 E1 
G1 X5.913 Y10.129 F600 E1 
G1 X6.141 Y10.357 F600 E1 
G1 X6.370 Y10.586 F600 E1 
G1 X6.599 Y10.815 F600 E1 
G1 X6.827 Y11.043 F600 E1 
G1 X7.056 Y11.272 F600 E1 
G1 X7.285 Y11.501 F600 E1 
G1 X7.513 Y11.729 F600 E1 
G1 X7.742 Y11.958 F600 E1 
G1 X8.003 Y12.219 F600 E1 
G1 X8.232 Y12.448 F600 E1 
G1 X8.461 Y12.677 F600 E1 
G1 X8.689 Y12.905 F600 E1 
G1 X8.918 Y13.134 F600 E1 
G1 X9.147 Y13.363 F600 E1 
G1 X9.375 Y13.591 F600 E1 
G1 X9.604 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X10.355 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X10.355 Y13.820 F600 E1 
G1 X10.127 Y13.591 F600 E1 
G1 X9.898 Y13.363 F600 E1 
G1 X9.669 Y13.134 F600 E1 
G1 X9.441 Y12.905 F600 E1 
G1 X9.212 Y12.677 F600 E1 
G1 X8.983 Y12.448 F600 E1 
G1 X8.755 Y12.219 F600 E1 
G1 X8.493 Y11.958 F600 E1 
G1 X8.265 Y11.729 F600 E1 
G1 X8.036 Y11.501 F600 E1 
G1 X7.807 Y11.272 F600 E1 
G1 X7.579 Y11.043 F600 E1 
G1 X7.350 Y10.815 F600 E1 
G1 X7.121 Y10.586 F600 E1 
G1 X6.893 Y10.357 F600 E1 
G1 X6.664 Y10.129 F600 E1 
G1 X6.435 Y9.900 F600 E1 
G1 X6.207 Y9.671 F600 E1 
G1 X5.978 Y9.443 F600 E1 
G1 X5.749 Y9.214 F600 E1 
G1 X5.521 Y8.985 F600 E1 
G1 X5.259 Y8.724 F600 E1 
G1 X5.031 Y8.495 F600 E1 
G1 X4.802 Y8.267 F600 E1 
G1 X4.573 Y8.038 F600 E1 
G1 X4.345 Y7.809 F600 E1 
G1 X4.116 Y7.581 F600 E1 
G1 X3.887 Y7.352 F600 E1 
G1 X3.659 Y7.123 F600 E1 
G1 X3.430 Y6.895 F600 E1 
G1 X3.201 Y6.666 F600 E1 
G1 X2.973 Y6.437 F600 E1 
G1 X2.744 Y6.209 F600 E1 
G1 X2.515 Y5.980 F600 E1 
G1 X2.287 Y5.751 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X3.038 Y5.751 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X3.038 Y5.751 F600 E1 
G1 X3.267 Y5.980 F600 E1 
G1 X3.495 Y6.209 F600 E1 
G1 X3.724 Y6.437 F600 E1 
G1 X3.953 Y6.666 F600 E1 
G1 X4.181 Y6.895 F600 E1 
G1 X4.410 Y7.123 F600 E1 
G1 X4.639 Y7.352 F600 E1 
G1 X4.867 Y7.581 F600 E1 
G1 X5.096 Y7.809 F600 E1 
G1 X5.325 Y8.038 F600 E1 
G1 X5.553 Y8.267 F600 E1 
G1 X5.782 Y8.495 F600 E1 
G1 X6.011 Y8.724 F600 E1 
G1 X6.272 Y8.985 F600 E1 
G1 X6.501 Y9.214 F600 E1 
G1 X6.729 Y9.443 F600 E1 
G1 X6.958 Y9.671 F600 E1 
G1 X7.187 Y9.900 F600 E1 
G1 X7.415 Y10.129 F600 E1 
G1 X7.644 Y10.357 F600 E1 
G1 X7.873 Y10.586 F600 E1 
G1 X8.101 Y10.815 F600 E1 
G1 X8.330 Y11.043 F600 E1 
G1 X8.559 Y11.272 F600 E1 
G1 X8.787 Y11.501 F600 E1 
G1 X9.016 Y11.729 F600 E1 
G1 X9.245 Y11.958 F600 E1 
G1 X9.506 Y12.219 F600 E1 
G1 X9.735 Y12.448 F600 E1 
G1 X9.963 Y12.677 F600 E1 
G1 X10.192 Y12.905 F600 E1 
G1 X10.421 Y13.134 F600 E1 
G1 X10.649 Y13.363 F600 E1 
G1 X10.878 Y13.591 F600 E1 
G1 X11.107 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X11.858 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X11.858 Y13.820 F600 E1 
G1 X11.629 Y13.591 F600 E1 
G1 X11.401 Y13.363 F600 E1 
G1 X11.172 Y13.134 F600 E1 
G1 X10.943 Y12.905 F600 E1 
G1 X10.715 Y12.677 F600 E1 
G1 X10.486 Y12.448 F600 E1 
G1 X10.257 Y12.219 F600 E1 
G1 X9.996 Y11.958 F600 E1 
G1 X9.767 Y11.729 F600 E1 
G1 X9.539 Y11.501 F600 E1 
G1 X9.310 Y11.272 F600 E1 
G1 X9.081 Y11.043 F600 E1 
G1 X8.853 Y10.815 F600 E1 
G1 X8.624 Y10.586 F600 E1 
G1 X8.395 Y10.357 F600 E1 
G1 X8.167 Y10.129 F600 E1 
G1 X7.938 Y9.900 F600 E1 
G1 X7.709 Y9.671 F600 E1 
G1 X7.481 Y9.443 F600 E1 
G1 X7.252 Y9.214 F600 E1 
G1 X7.023 Y8.985 F600 E1 
G1 X6.762 Y8.724 F600 E1 
G1 X6.533 Y8.495 F600 E1 
G1 X6.305 Y8.267 F600 E1 
G1 X6.076 Y8.038 F600 E1 
G1 X5.847 Y7.809 F600 E1 
G1 X5.619 Y7.581 F600 E1 
G1 X5.390 Y7.352 F600 E1 
G1 X5.161 Y7.123 F600 E1 
G1 X4.933 Y6.895 F600 E1 
G1 X4.704 Y6.666 F600 E1 
G1 X4.475 Y6.437 F600 E1 
G1 X4.247 Y6.209 F600 E1 
G1 X4.018 Y5.980 F600 E1 
G1 X3.789 Y5.751 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X4.541 Y5.751 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X4.541 Y5.751 F600 E1 
G1 X4.769 Y5.980 F600 E1 
G1 X4.998 Y6.209 F600 E1 
G1 X5.227 Y6.437 F600 E1 
G1 X5.455 Y6.666 F600 E1 
G1 X5.684 Y6.895 F600 E1 
G1 X5.913 Y7.123 F600 E1 
G1 X6.141 Y7.352 F600 E1 
G1 X6.370 Y7.581 F600 E1 
G1 X6.599 Y7.809 F600 E1 
G1 X6.827 Y8.038 F600 E1 
G1 X7.056 Y8.267 F600 E1 
G1 X7.285 Y8.495 F600 E1 
G1 X7.513 Y8.724 F600 E1 
G1 X7.775 Y8.985 F600 E1 
G1 X8.003 Y9.214 F600 E1 
G1 X8.232 Y9.443 F600 E1 
G1 X8.461 Y9.671 F600 E1 
G1 X8.689 Y9.900 F600 E1 
G1 X8.918 Y10.129 F600 E1 
G1 X9.147 Y10.357 F600 E1 
G1 X9.375 Y10.586 F600 E1 
G1 X9.604 Y10.815 F600 E1 
G1 X9.833 Y11.043 F600 E1 
G1 X10.061 Y11.272 F600 E1 
G1 X10.290 Y11.501 F600 E1 
G1 X10.519 Y11.729 F600 E1 
G1 X10.747 Y11.958 F600 E1 
G1 X11.009 Y12.219 F600 E1 
G1 X11.237 Y12.448 F600 E1 
G1 X11.466 Y12.677 F600 E1 
G1 X11.695 Y12.905 F600 E1 
G1 X11.923 Y13.134 F600 E1 
G1 X12.152 Y13.363 F600 E1 
G1 X12.381 Y13.591 F600 E1 
G1 X12.609 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X13.361 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X13.361 Y13.820 F600 E1 
G1 X13.132 Y13.591 F600 E1 
G1 X12.903 Y13.363 F600 E1 
G1 X12.675 Y13.134 F600 E1 
G1 X12.446 Y12.905 F600 E1 
G1 X12.217 Y12.677 F600 E1 
G1 X11.989 Y12.448 F600 E1 
G1 X11.760 Y12.219 F600 E1 
G1 X11.499 Y11.958 F600 E1 
G1 X11.270 Y11.729 F600 E1 
G1 X11.041 Y11.501 F600 E1 
G1 X10.813 Y11.272 F600 E1 
G1 X10.584 Y11.043 F600 E1 
G1 X10.355 Y10.815 F600 E1 
G1 X10.127 Y10.586 F600 E1 
G1 X9.898 Y10.357 F600 E1 
G1 X9.669 Y10.129 F600 E1 
G1 X9.441 Y9.900 F600 E1 
G1 X9.212 Y9.671 F600 E1 
G1 X8.983 Y9.443 F600 E1 
G1 X8.755 Y9.214 F600 E1 
G1 X8.526 Y8.985 F600 E1 
G1 X8.265 Y8.724 F600 E1 
G1 X8.036 Y8.495 F600 E1 
G1 X7.807 Y8.267 F600 E1 
G1 X7.579 Y8.038 F600 E1 
G1 X7.350 Y7.809 F600 E1 
G1 X7.121 Y7.581 F600 E1 
G1 X6.893 Y7.352 F600 E1 
G1 X6.664 Y7.123 F600 E1 
G1 X6.435 Y6.895 F600 E1 
G1 X6.207 Y6.666 F600 E1 
G1 X5.978 Y6.437 F600 E1 
G1 X5.749 Y6.209 F600 E1 
G1 X5.521 Y5.980 F600 E1 
G1 X5.292 Y5.751 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X6.043 Y5.751 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X6.043 Y5.751 F600 E1 
G1 X6.272 Y5.980 F600 E1 
G1 X6.501 Y6.209 F600 E1 
G1 X6.729 Y6.437 F600 E1 
G1 X6.958 Y6.666 F600 E1 
G1 X7.187 Y6.895 F600 E1 
G1 X7.415 Y7.123 F600 E1 
G1 X7.644 Y7.352 F600 E1 
G1 X7.873 Y7.581 F600 E1 
G1 X8.101 Y7.809 F600 E1 
G1 X8.330 Y8.038 F600 E1 
G1 X8.559 Y8.267 F600 E1 
G1 X8.787 Y8.495 F600 E1 
G1 X9.016 Y8.724 F600 E1 
G1 X9.277 Y8.985 F600 E1 
G1 X9.506 Y9.214 F600 E1 
G1 X9.735 Y9.443 F600 E1 
G1 X9.963 Y9.671 F600 E1 
G1 X10.192 Y9.900 F600 E1 
G1 X10.421 Y10.129 F600 E1 
G1 X10.649 Y10.357 F600 E1 
G1 X10.878 Y10.586 F600 E1 
G1 X11.107 Y10.815 F600 E1 
G1 X11.335 Y11.043 F600 E1 
G1 X11.564 Y11.272 F600 E1 
G1 X11.793 Y11.501 F600 E1 
G1 X12.021 Y11.729 F600 E1 
G1 X12.250 Y11.958 F600 E1 
G1 X12.511 Y12.219 F600 E1 
G1 X12.740 Y12.448 F600 E1 
G1 X12.969 Y12.677 F600 E1 
G1 X13.197 Y12.905 F600 E1 
G1 X13.426 Y13.134 F600 E1 
G1 X13.655 Y13.363 F600 E1 
G1 X13.883 Y13.591 F600 E1 
G1 X14.112 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X14.863 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X14.863 Y13.820 F600 E1 
G1 X14.635 Y13.591 F600 E1 
G1 X14.406 Y13.363 F600 E1 
G1 X14.177 Y13.134 F600 E1 
G1 X13.949 Y12.905 F600 E1 
G1 X13.720 Y12.677 F600 E1 
G1 X13.491 Y12.448 F600 E1 
G1 X13.263 Y12.219 F600 E1 
G1 X13.001 Y11.958 F600 E1 
G1 X12.773 Y11.729 F600 E1 
G1 X12.544 Y11.501 F600 E1 
G1 X12.315 Y11.272 F600 E1 
G1 X12.087 Y11.043 F600 E1 
G1 X11.858 Y10.815 F600 E1 
G1 X11.629 Y10.586 F600 E1 
G1 X11.401 Y10.357 F600 E1 
G1 X11.172 Y10.129 F600 E1 
G1 X10.943 Y9.900 F600 E1 
G1 X10.715 Y9.671 F600 E1 
G1 X10.486 Y9.443 F600 E1 
G1 X10.257 Y9.214 F600 E1 
G1 X10.029 Y8.985 F600 E1 
G1 X9.767 Y8.724 F600 E1 
G1 X9.539 Y8.495 F600 E1 
G1 X9.310 Y8.267 F600 E1 
G1 X9.081 Y8.038 F600 E1 
G1 X8.853 Y7.809 F600 E1 
G1 X8.624 Y7.581 F600 E1 
G1 X8.395 Y7.352 F600 E1 
G1 X8.167 Y7.123 F600 E1 
G1 X7.938 Y6.895 F600 E1 
G1 X7.709 Y6.666 F600 E1 
G1 X7.481 Y6.437 F600 E1 
G1 X7.252 Y6.209 F600 E1 
G1 X7.023 Y5.980 F600 E1 
G1 X6.795 Y5.751 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X7.546 Y5.751 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X7.546 Y5.751 F600 E1 
G1 X7.775 Y5.980 F600 E1 
G1 X8.003 Y6.209 F600 E1 
G1 X8.232 Y6.437 F600 E1 
G1 X8.461 Y6.666 F600 E1 
G1 X8.689 Y6.895 F600 E1 
G1 X8.918 Y7.123 F600 E1 
G1 X9.147 Y7.352 F600 E1 
G1 X9.375 Y7.581 F600 E1 
G1 X9.604 Y7.809 F600 E1 
G1 X9.833 Y8.038 F600 E1 
G1 X10.061 Y8.267 F600 E1 
G1 X10.290 Y8.495 F600 E1 
G1 X10.519 Y8.724 F600 E1 
G1 X10.780 Y8.985 F600 E1 
G1 X11.009 Y9.214 F600 E1 
G1 X11.237 Y9.443 F600 E1 
G1 X11.466 Y9.671 F600 E1 
G1 X11.695 Y9.900 F600 E1 
G1 X11.923 Y10.129 F600 E1 
G1 X12.152 Y10.357 F600 E1 
G1 X12.381 Y10.586 F600 E1 
G1 X12.609 Y10.815 F600 E1 
G1 X12.838 Y11.043 F600 E1 
G1 X13.067 Y11.272 F600 E1 
G1 X13.295 Y11.501 F600 E1 
G1 X13.524 Y11.729 F600 E1 
G1 X13.753 Y11.958 F600 E1 
G1 X14.014 Y12.219 F600 E1 
G1 X14.243 Y12.448 F600 E1 
G1 X14.471 Y12.677 F600 E1 
G1 X14.700 Y12.905 F600 E1 
G1 X14.929 Y13.134 F600 E1 
G1 X15.157 Y13.363 F600 E1 
G1 X15.386 Y13.591 F600 E1 
G1 X15.615 Y13.820 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X16.366 Y13.820 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X16.366 Y13.820 F600 E1 
G1 X16.137 Y13.591 F600 E1 
G1 X15.909 Y13.363 F600 E1 
G1 X15.680 Y13.134 F600 E1 
G1 X15.451 Y12.905 F600 E1 
G1 X15.223 Y12.677 F600 E1 
G1 X14.994 Y12.448 F600 E1 
G1 X14.765 Y12.219 F600 E1 
G1 X14.504 Y11.958 F600 E1 
G1 X14.275 Y11.729 F600 E1 
G1 X14.047 Y11.501 F600 E1 
G1 X13.818 Y11.272 F600 E1 
G1 X13.589 Y11.043 F600 E1 
G1 X13.361 Y10.815 F600 E1 
G1 X13.132 Y10.586 F600 E1 
G1 X12.903 Y10.357 F600 E1 
G1 X12.675 Y10.129 F600 E1 
G1 X12.446 Y9.900 F600 E1 
G1 X12.217 Y9.671 F600 E1 
G1 X11.989 Y9.443 F600 E1 
G1 X11.760 Y9.214 F600 E1 
G1 X11.531 Y8.985 F600 E1 
G1 X11.270 Y8.724 F600 E1 
G1 X11.041 Y8.495 F600 E1 
G1 X10.813 Y8.267 F600 E1 
G1 X10.584 Y8.038 F600 E1 
G1 X10.355 Y7.809 F600 E1 
G1 X10.127 Y7.581 F600 E1 
G1 X9.898 Y7.352 F600 E1 
G1 X9.669 Y7.123 F600 E1 
G1 X9.441 Y6.895 F600 E1 
G1 X9.212 Y6.666 F600 E1 
G1 X8.983 Y6.437 F600 E1 
G1 X8.755 Y6.209 F600 E1 
G1 X8.526 Y5.980 F600 E1 
G1 X8.297 Y5.751 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X8.951 Y5.653 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X8.951 Y5.653 F600 E1 
G1 X9.147 Y5.849 F600 E1 
G1 X9.375 Y6.078 F600 E1 
G1 X9.604 Y6.307 F600 E1 
G1 X9.833 Y6.535 F600 E1 
G1 X10.061 Y6.764 F600 E1 
G1 X10.290 Y6.993 F600 E1 
G1 X10.519 Y7.221 F600 E1 
G1 X10.747 Y7.450 F600 E1 
G1 X10.976 Y7.679 F600 E1 
G1 X11.205 Y7.907 F600 E1 
G1 X11.433 Y8.136 F600 E1 
G1 X11.662 Y8.365 F600 E1 
G1 X11.891 Y8.593 F600 E1 
G1 X12.152 Y8.855 F600 E1 
G1 X12.381 Y9.083 F600 E1 
G1 X12.609 Y9.312 F600 E1 
G1 X12.838 Y9.541 F600 E1 
G1 X13.067 Y9.769 F600 E1 
G1 X13.295 Y9.998 F600 E1 
G1 X13.524 Y10.227 F600 E1 
G1 X13.753 Y10.455 F600 E1 
G1 X13.981 Y10.684 F600 E1 
G1 X14.210 Y10.913 F600 E1 
G1 X14.439 Y11.141 F600 E1 
G1 X14.667 Y11.370 F600 E1 
G1 X14.896 Y11.599 F600 E1 
G1 X15.125 Y11.827 F600 E1 
G1 X15.386 Y12.089 F600 E1 
G1 X15.615 Y12.317 F600 E1 
G1 X15.843 Y12.546 F600 E1 
G1 X16.072 Y12.775 F600 E1 
G1 X16.301 Y13.003 F600 E1 
G1 X16.529 Y13.232 F600 E1 
G1 X16.758 Y13.461 F600 E1 
G1 X16.987 Y13.689 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X16.987 Y12.938 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X16.987 Y12.938 F600 E1 
G1 X16.758 Y12.709 F600 E1 
G1 X16.529 Y12.481 F600 E1 
G1 X16.301 Y12.252 F600 E1 
G1 X16.072 Y12.023 F600 E1 
G1 X15.843 Y11.795 F600 E1 
G1 X15.615 Y11.566 F600 E1 
G1 X15.386 Y11.337 F600 E1 
G1 X15.125 Y11.076 F600 E1 
G1 X14.896 Y10.847 F600 E1 
G1 X14.667 Y10.619 F600 E1 
G1 X14.439 Y10.390 F600 E1 
G1 X14.210 Y10.161 F600 E1 
G1 X13.981 Y9.933 F600 E1 
G1 X13.753 Y9.704 F600 E1 
G1 X13.524 Y9.475 F600 E1 
G1 X13.295 Y9.247 F600 E1 
G1 X13.067 Y9.018 F600 E1 
G1 X12.838 Y8.789 F600 E1 
G1 X12.609 Y8.561 F600 E1 
G1 X12.381 Y8.332 F600 E1 
G1 X12.152 Y8.103 F600 E1 
G1 X11.891 Y7.842 F600 E1 
G1 X11.662 Y7.613 F600 E1 
G1 X11.433 Y7.385 F600 E1 
G1 X11.205 Y7.156 F600 E1 
G1 X10.976 Y6.927 F600 E1 
G1 X10.747 Y6.699 F600 E1 
G1 X10.519 Y6.470 F600 E1 
G1 X10.290 Y6.241 F600 E1 
G1 X10.061 Y6.013 F600 E1 
G1 X9.833 Y5.784 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X10.519 Y5.719 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X10.519 Y5.719 F600 E1 
G1 X10.747 Y5.947 F600 E1 
G1 X10.976 Y6.176 F600 E1 
G1 X11.205 Y6.405 F600 E1 
G1 X11.433 Y6.633 F600 E1 
G1 X11.662 Y6.862 F600 E1 
G1 X11.891 Y7.091 F600 E1 
G1 X12.152 Y7.352 F600 E1 
G1 X12.381 Y7.581 F600 E1 
G1 X12.609 Y7.809 F600 E1 
G1 X12.838 Y8.038 F600 E1 
G1 X13.067 Y8.267 F600 E1 
G1 X13.295 Y8.495 F600 E1 
G1 X13.524 Y8.724 F600 E1 
G1 X13.753 Y8.953 F600 E1 
G1 X13.981 Y9.181 F600 E1 
G1 X14.210 Y9.410 F600 E1 
G1 X14.439 Y9.639 F600 E1 
G1 X14.667 Y9.867 F600 E1 
G1 X14.896 Y10.096 F600 E1 
G1 X15.125 Y10.325 F600 E1 
G1 X15.386 Y10.586 F600 E1 
G1 X15.615 Y10.815 F600 E1 
G1 X15.843 Y11.043 F600 E1 
G1 X16.072 Y11.272 F600 E1 
G1 X16.301 Y11.501 F600 E1 
G1 X16.529 Y11.729 F600 E1 
G1 X16.758 Y11.958 F600 E1 
G1 X16.987 Y12.187 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X16.987 Y11.435 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X16.987 Y11.435 F600 E1 
G1 X16.758 Y11.207 F600 E1 
G1 X16.529 Y10.978 F600 E1 
G1 X16.301 Y10.749 F600 E1 
G1 X16.072 Y10.521 F600 E1 
G1 X15.843 Y10.292 F600 E1 
G1 X15.615 Y10.063 F600 E1 
G1 X15.386 Y9.835 F600 E1 
G1 X15.125 Y9.573 F600 E1 
G1 X14.896 Y9.345 F600 E1 
G1 X14.667 Y9.116 F600 E1 
G1 X14.439 Y8.887 F600 E1 
G1 X14.210 Y8.659 F600 E1 
G1 X13.981 Y8.430 F600 E1 
G1 X13.753 Y8.201 F600 E1 
G1 X13.524 Y7.973 F600 E1 
G1 X13.295 Y7.744 F600 E1 
G1 X13.067 Y7.515 F600 E1 
G1 X12.838 Y7.287 F600 E1 
G1 X12.609 Y7.058 F600 E1 
G1 X12.381 Y6.829 F600 E1 
G1 X12.152 Y6.601 F600 E1 
G1 X11.891 Y6.339 F600 E1 
G1 X11.662 Y6.111 F600 E1 
G1 X11.433 Y5.882 F600 E1 
G1 X11.205 Y5.653 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X11.956 Y5.653 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X11.956 Y5.653 F600 E1 
G1 X12.152 Y5.849 F600 E1 
G1 X12.381 Y6.078 F600 E1 
G1 X12.609 Y6.307 F600 E1 
G1 X12.838 Y6.535 F600 E1 
G1 X13.067 Y6.764 F600 E1 
G1 X13.295 Y6.993 F600 E1 
G1 X13.524 Y7.221 F600 E1 
G1 X13.753 Y7.450 F600 E1 
G1 X13.981 Y7.679 F600 E1 
G1 X14.210 Y7.907 F600 E1 
G1 X14.439 Y8.136 F600 E1 
G1 X14.667 Y8.365 F600 E1 
G1 X14.896 Y8.593 F600 E1 
G1 X15.125 Y8.822 F600 E1 
G1 X15.386 Y9.083 F600 E1 
G1 X15.615 Y9.312 F600 E1 
G1 X15.843 Y9.541 F600 E1 
G1 X16.072 Y9.769 F600 E1 
G1 X16.301 Y9.998 F600 E1 
G1 X16.529 Y10.227 F600 E1 
G1 X16.758 Y10.455 F600 E1 
G1 X16.987 Y10.684 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X16.987 Y9.933 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X16.987 Y9.933 F600 E1 
G1 X16.758 Y9.704 F600 E1 
G1 X16.529 Y9.475 F600 E1 
G1 X16.301 Y9.247 F600 E1 
G1 X16.072 Y9.018 F600 E1 
G1 X15.843 Y8.789 F600 E1 
G1 X15.615 Y8.561 F600 E1 
G1 X15.386 Y8.332 F600 E1 
G1 X15.125 Y8.071 F600 E1 
G1 X14.896 Y7.842 F600 E1 
G1 X14.667 Y7.613 F600 E1 
G1 X14.439 Y7.385 F600 E1 
G1 X14.210 Y7.156 F600 E1 
G1 X13.981 Y6.927 F600 E1 
G1 X13.753 Y6.699 F600 E1 
G1 X13.524 Y6.470 F600 E1 
G1 X13.295 Y6.241 F600 E1 
G1 X13.067 Y6.013 F600 E1 
G1 X12.838 Y5.784 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X13.524 Y5.719 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X13.524 Y5.719 F600 E1 
G1 X13.753 Y5.947 F600 E1 
G1 X13.981 Y6.176 F600 E1 
G1 X14.210 Y6.405 F600 E1 
G1 X14.439 Y6.633 F600 E1 
G1 X14.667 Y6.862 F600 E1 
G1 X14.896 Y7.091 F600 E1 
G1 X15.125 Y7.319 F600 E1 
G1 X15.386 Y7.581 F600 E1 
G1 X15.615 Y7.809 F600 E1 
G1 X15.843 Y8.038 F600 E1 
G1 X16.072 Y8.267 F600 E1 
G1 X16.301 Y8.495 F600 E1 
G1 X16.529 Y8.724 F600 E1 
G1 X16.758 Y8.953 F600 E1 
G1 X16.987 Y9.181 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X16.987 Y8.430 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X16.987 Y8.430 F600 E1 
G1 X16.758 Y8.201 F600 E1 
G1 X16.529 Y7.973 F600 E1 
G1 X16.301 Y7.744 F600 E1 
G1 X16.072 Y7.515 F600 E1 
G1 X15.843 Y7.287 F600 E1 
G1 X15.615 Y7.058 F600 E1 
G1 X15.386 Y6.829 F600 E1 
G1 X15.125 Y6.568 F600 E1 
G1 X14.896 Y6.339 F600 E1 
G1 X14.667 Y6.111 F600 E1 
G1 X14.439 Y5.882 F600 E1 
G1 X14.210 Y5.653 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X14.961 Y5.653 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X14.961 Y5.653 F600 E1 
G1 X15.125 Y5.817 F600 E1 
G1 X15.386 Y6.078 F600 E1 
G1 X15.615 Y6.307 F600 E1 
G1 X15.843 Y6.535 F600 E1 
G1 X16.072 Y6.764 F600 E1 
G1 X16.301 Y6.993 F600 E1 
G1 X16.529 Y7.221 F600 E1 
G1 X16.758 Y7.450 F600 E1 
G1 X16.987 Y7.679 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X16.987 Y6.927 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X16.987 Y6.927 F600 E1 
G1 X16.758 Y6.699 F600 E1 
G1 X16.529 Y6.470 F600 E1 
G1 X16.301 Y6.241 F600 E1 
G1 X16.072 Y6.013 F600 E1 
G1 X15.843 Y5.784 F600 E1 
; Moving up.
G0 Z1.000 F600.000
; Moving to new starting point.
G0 X16.529 Y5.719 F1800 
; Moving down.
G0 Z0.000 F600.000
; Starting new path.
G1 X16.529 Y5.719 F600 E1 
G1 X16.758 Y5.947 F600 E1 
G1 X16.987 Y6.176 F600 E1 
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
