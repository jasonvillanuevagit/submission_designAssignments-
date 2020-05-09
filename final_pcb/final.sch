EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "2020-05-08"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 8950 1450 1    60   ~ 0
Vin
Text Label 9350 1450 1    60   ~ 0
IOREF
Text Label 8900 2500 0    60   ~ 0
A0
Text Label 8900 2600 0    60   ~ 0
A1
Text Label 8900 2700 0    60   ~ 0
A2
Text Label 8900 2800 0    60   ~ 0
A3
Text Label 8900 2900 0    60   ~ 0
A4(SDA)
Text Label 8900 3000 0    60   ~ 0
A5(SCL)
Text Label 10550 3000 0    60   ~ 0
0(Rx)
Text Label 10550 2800 0    60   ~ 0
2
Text Label 10550 2900 0    60   ~ 0
1(Tx)
Text Label 10550 2700 0    60   ~ 0
3(**)
Text Label 10550 2600 0    60   ~ 0
4
Text Label 10550 2500 0    60   ~ 0
5(**)
Text Label 10550 2400 0    60   ~ 0
6(**)
Text Label 10550 2300 0    60   ~ 0
7
Text Label 10550 2100 0    60   ~ 0
8
Text Label 10550 2000 0    60   ~ 0
9(**)
Text Label 10550 1900 0    60   ~ 0
10(**/SS)
Text Label 10550 1800 0    60   ~ 0
11(**/MOSI)
Text Label 10550 1700 0    60   ~ 0
12(MISO)
Text Label 10550 1600 0    60   ~ 0
13(SCK)
Text Label 10550 1400 0    60   ~ 0
AREF
NoConn ~ 9400 1600
Text Label 10550 1300 0    60   ~ 0
A4(SDA)
Text Label 10550 1200 0    60   ~ 0
A5(SCL)
Text Notes 10850 1000 0    60   ~ 0
Holes
Text Notes 8550 750  0    60   ~ 0
Shield for Arduino that uses\nthe same pin disposition\nlike "Uno" board Rev 3.
$Comp
L Connector_Generic:Conn_01x08 P1
U 1 1 56D70129
P 9600 1900
F 0 "P1" H 9600 2350 50  0000 C CNN
F 1 "Power" V 9700 1900 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 9750 1900 20  0000 C CNN
F 3 "" H 9600 1900 50  0000 C CNN
	1    9600 1900
	1    0    0    -1  
$EndComp
Text Label 8650 1800 0    60   ~ 0
Reset
$Comp
L power:+3.3V #PWR01
U 1 1 56D70538
P 9150 1450
F 0 "#PWR01" H 9150 1300 50  0001 C CNN
F 1 "+3.3V" V 9150 1700 50  0000 C CNN
F 2 "" H 9150 1450 50  0000 C CNN
F 3 "" H 9150 1450 50  0000 C CNN
	1    9150 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 56D707BB
P 9050 1350
F 0 "#PWR02" H 9050 1200 50  0001 C CNN
F 1 "+5V" V 9050 1550 50  0000 C CNN
F 2 "" H 9050 1350 50  0000 C CNN
F 3 "" H 9050 1350 50  0000 C CNN
	1    9050 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 56D70CC2
P 9300 3150
F 0 "#PWR03" H 9300 2900 50  0001 C CNN
F 1 "GND" H 9300 3000 50  0000 C CNN
F 2 "" H 9300 3150 50  0000 C CNN
F 3 "" H 9300 3150 50  0000 C CNN
	1    9300 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 56D70CFF
P 10300 3150
F 0 "#PWR04" H 10300 2900 50  0001 C CNN
F 1 "GND" H 10300 3000 50  0000 C CNN
F 2 "" H 10300 3150 50  0000 C CNN
F 3 "" H 10300 3150 50  0000 C CNN
	1    10300 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 P2
U 1 1 56D70DD8
P 9600 2700
F 0 "P2" H 9600 2300 50  0000 C CNN
F 1 "Analog" V 9700 2700 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x06" V 9750 2750 20  0000 C CNN
F 3 "" H 9600 2700 50  0000 C CNN
	1    9600 2700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P5
U 1 1 56D71177
P 10800 650
F 0 "P5" V 10900 650 50  0000 C CNN
F 1 "CONN_01X01" V 10900 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10721 724 20  0000 C CNN
F 3 "" H 10800 650 50  0000 C CNN
	1    10800 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P6
U 1 1 56D71274
P 10900 650
F 0 "P6" V 11000 650 50  0000 C CNN
F 1 "CONN_01X01" V 11000 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10900 650 20  0001 C CNN
F 3 "" H 10900 650 50  0000 C CNN
	1    10900 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P7
U 1 1 56D712A8
P 11000 650
F 0 "P7" V 11100 650 50  0000 C CNN
F 1 "CONN_01X01" V 11100 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" V 11000 650 20  0001 C CNN
F 3 "" H 11000 650 50  0000 C CNN
	1    11000 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P8
U 1 1 56D712DB
P 11100 650
F 0 "P8" V 11200 650 50  0000 C CNN
F 1 "CONN_01X01" V 11200 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 11024 572 20  0000 C CNN
F 3 "" H 11100 650 50  0000 C CNN
	1    11100 650 
	0    -1   -1   0   
$EndComp
NoConn ~ 10800 850 
NoConn ~ 10900 850 
NoConn ~ 11000 850 
NoConn ~ 11100 850 
$Comp
L Connector_Generic:Conn_01x08 P4
U 1 1 56D7164F
P 10000 2600
F 0 "P4" H 10000 2100 50  0000 C CNN
F 1 "Digital" V 10100 2600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 10150 2550 20  0000 C CNN
F 3 "" H 10000 2600 50  0000 C CNN
	1    10000 2600
	-1   0    0    -1  
$EndComp
Wire Notes Line
	8525 825  9925 825 
Wire Notes Line
	9925 825  9925 475 
Wire Wire Line
	9350 1450 9350 1700
Wire Wire Line
	9350 1700 9400 1700
Wire Wire Line
	9400 1900 9150 1900
Wire Wire Line
	9400 2000 9050 2000
Wire Wire Line
	9400 2300 8950 2300
Wire Wire Line
	9400 2100 9300 2100
Wire Wire Line
	9400 2200 9300 2200
Connection ~ 9300 2200
Wire Wire Line
	8950 2300 8950 1450
Wire Wire Line
	9050 2000 9050 1350
Wire Wire Line
	9150 1900 9150 1450
Wire Wire Line
	9400 2500 8900 2500
Wire Wire Line
	9400 2600 8900 2600
Wire Wire Line
	9400 2700 8900 2700
Wire Wire Line
	9400 2800 8900 2800
Wire Wire Line
	9400 2900 8900 2900
Wire Wire Line
	9400 3000 8900 3000
$Comp
L Connector_Generic:Conn_01x10 P3
U 1 1 56D721E0
P 10000 1600
F 0 "P3" H 10000 2150 50  0000 C CNN
F 1 "Digital" V 10100 1600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x10" V 10150 1600 20  0000 C CNN
F 3 "" H 10000 1600 50  0000 C CNN
	1    10000 1600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10200 2100 10550 2100
Wire Wire Line
	10200 2000 10550 2000
Wire Wire Line
	10200 1900 10550 1900
Wire Wire Line
	10200 1800 10550 1800
Wire Wire Line
	10200 1700 10550 1700
Wire Wire Line
	10200 1600 10550 1600
Wire Wire Line
	10200 1400 10550 1400
Wire Wire Line
	10200 1300 10550 1300
Wire Wire Line
	10200 1200 10550 1200
Wire Wire Line
	10200 3000 10550 3000
Wire Wire Line
	10200 2900 10550 2900
Wire Wire Line
	10200 2800 10550 2800
Wire Wire Line
	10200 2700 10550 2700
Wire Wire Line
	10200 2600 10550 2600
Wire Wire Line
	10200 2500 10550 2500
Wire Wire Line
	10200 2400 10550 2400
Wire Wire Line
	10200 2300 10550 2300
Wire Wire Line
	10200 1500 10300 1500
Wire Wire Line
	10300 1500 10300 3150
Wire Wire Line
	9300 2100 9300 2200
Wire Wire Line
	9300 2200 9300 3150
Wire Notes Line
	8500 500  8500 3450
Wire Notes Line
	8500 3450 11200 3450
Wire Wire Line
	9400 1800 8650 1800
Text Notes 9700 1600 0    60   ~ 0
1
Wire Notes Line
	11200 1000 10700 1000
Wire Notes Line
	10700 1000 10700 500 
$Comp
L final-rescue:LTST-C193TBKT-5A-dk_LED-Indication-Discrete-final-rescue D1
U 1 1 5EB0ACFA
P 1350 850
F 0 "D1" H 1300 1081 60  0000 C CNN
F 1 "LTST-C193TBKT-5A" H 1300 1081 60  0001 C CNN
F 2 "LTST-C193TGKT-5A:0603" H 1550 1050 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTST-C193TBKT-5A.pdf" H 1550 1150 60  0001 L CNN
F 4 "160-1827-1-ND" H 1550 1250 60  0001 L CNN "Digi-Key_PN"
F 5 "LTST-C193TBKT-5A" H 1550 1350 60  0001 L CNN "MPN"
F 6 "Optoelectronics" H 1550 1450 60  0001 L CNN "Category"
F 7 "LED Indication - Discrete" H 1550 1550 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTST-C193TBKT-5A.pdf" H 1550 1650 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/lite-on-inc/LTST-C193TBKT-5A/160-1827-1-ND/2355044" H 1550 1750 60  0001 L CNN "DK_Detail_Page"
F 10 "LED BLUE CLEAR CHIP SMD" H 1550 1850 60  0001 L CNN "Description"
F 11 "Lite-On Inc." H 1550 1950 60  0001 L CNN "Manufacturer"
F 12 "Active" H 1550 2050 60  0001 L CNN "Status"
	1    1350 850 
	1    0    0    -1  
$EndComp
Text Label 9050 1500 0    50   ~ 0
+5V
Text Label 550  1050 0    50   ~ 0
+5V
$Comp
L Device:R R2
U 1 1 5EB42605
P 900 1050
F 0 "R2" V 1107 1050 50  0000 C CNN
F 1 "200" V 1016 1050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 830 1050 50  0001 C CNN
F 3 "~" H 900 1050 50  0001 C CNN
	1    900  1050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	550  1050 750  1050
Wire Wire Line
	1450 850  1850 850 
Text Label 1850 850  0    60   ~ 0
6(**)
Text Label 1850 1250 0    60   ~ 0
5(**)
$Comp
L Switch:SW_Push SW1
U 1 1 5EB54A30
P 1600 1850
F 0 "SW1" H 1600 2043 50  0000 C CNN
F 1 "SW_Push" H 1600 2044 50  0001 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 1600 2050 50  0001 C CNN
F 3 "~" H 1600 2050 50  0001 C CNN
	1    1600 1850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5EB557FA
P 1600 2200
F 0 "SW2" H 1600 2393 50  0000 C CNN
F 1 "SW_Push" H 1600 2394 50  0001 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 1600 2400 50  0001 C CNN
F 3 "~" H 1600 2400 50  0001 C CNN
	1    1600 2200
	1    0    0    -1  
$EndComp
$Comp
L final-rescue:LTST-C193TBKT-5A-dk_LED-Indication-Discrete-final-rescue D2
U 1 1 5EB6547C
P 1350 1250
F 0 "D2" H 1300 1481 60  0000 C CNN
F 1 "LTST-C193TBKT-5A" H 1300 1481 60  0001 C CNN
F 2 "LTST-C193TGKT-5A:0603" H 1550 1450 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTST-C193TBKT-5A.pdf" H 1550 1550 60  0001 L CNN
F 4 "160-1827-1-ND" H 1550 1650 60  0001 L CNN "Digi-Key_PN"
F 5 "LTST-C193TBKT-5A" H 1550 1750 60  0001 L CNN "MPN"
F 6 "Optoelectronics" H 1550 1850 60  0001 L CNN "Category"
F 7 "LED Indication - Discrete" H 1550 1950 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTST-C193TBKT-5A.pdf" H 1550 2050 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/lite-on-inc/LTST-C193TBKT-5A/160-1827-1-ND/2355044" H 1550 2150 60  0001 L CNN "DK_Detail_Page"
F 10 "LED BLUE CLEAR CHIP SMD" H 1550 2250 60  0001 L CNN "Description"
F 11 "Lite-On Inc." H 1550 2350 60  0001 L CNN "Manufacturer"
F 12 "Active" H 1550 2450 60  0001 L CNN "Status"
	1    1350 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1250 1850 1250
Text Label 550  2050 0    50   ~ 0
+5V
Wire Wire Line
	1800 1850 1950 1850
Wire Wire Line
	1950 1850 1950 2000
Wire Wire Line
	1950 2200 1800 2200
Wire Wire Line
	1950 2000 2050 2000
Connection ~ 1950 2000
Wire Wire Line
	1950 2000 1950 2200
Text GLabel 2050 2000 2    50   Input ~ 0
GND
Wire Wire Line
	1300 1850 1300 1650
Wire Wire Line
	1300 1850 1400 1850
Wire Wire Line
	1300 2200 1300 2400
Wire Wire Line
	1300 2200 1400 2200
Text Label 1300 2400 0    60   ~ 0
2
Text Label 1300 1500 0    60   ~ 0
3(**)
Wire Wire Line
	1200 1850 1300 1850
Connection ~ 1300 1850
Wire Wire Line
	900  2050 900  1850
Wire Wire Line
	550  2050 900  2050
Wire Wire Line
	900  2050 900  2200
Connection ~ 900  2050
Wire Wire Line
	1200 2200 1300 2200
Connection ~ 1300 2200
$Comp
L final-rescue:3362P-1-103LF-2020-05-04_22-01-12-final-rescue 10k1
U 1 1 5EB97CA8
P 900 3150
F 0 "10k1" H 1300 3019 60  0000 C CNN
F 1 "3362P-1-103LF" H 1300 2913 60  0000 C CNN
F 2 "footprints:3362P-1-103LF" H 1325 2715 60  0001 C CNN
F 3 "" H 900 3150 60  0000 C CNN
	1    900  3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  3150 600  3150
Text Label 600  3150 0    50   ~ 0
+5V
Text GLabel 1800 3150 2    50   Input ~ 0
GND
Wire Wire Line
	1700 3150 1800 3150
Text Label 1300 2650 0    60   ~ 0
A0
$Comp
L Connector:Conn_01x03_Female J4
U 1 1 5EBA2383
P 600 3850
F 0 "J4" H 492 3617 50  0000 C CNN
F 1 "Conn_01x03_Female" H 628 3785 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 600 3850 50  0001 C CNN
F 3 "~" H 600 3850 50  0001 C CNN
	1    600  3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	800  3950 900  3950
Text Label 900  3950 0    50   ~ 0
+5V
Wire Wire Line
	800  3750 900  3750
Text GLabel 900  3750 2    50   Input ~ 0
GND
Wire Wire Line
	800  3850 900  3850
Text Label 900  3850 0    60   ~ 0
A1
$Comp
L Device:R R5
U 1 1 5EBB8D2E
P 1600 4050
F 0 "R5" V 1807 4050 50  0000 C CNN
F 1 "5k" V 1716 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1530 4050 50  0001 C CNN
F 3 "~" H 1600 4050 50  0001 C CNN
	1    1600 4050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 5EBBA83C
P 1800 4050
F 0 "R6" V 2007 4050 50  0000 C CNN
F 1 "5k" V 1916 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1730 4050 50  0001 C CNN
F 3 "~" H 1800 4050 50  0001 C CNN
	1    1800 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3850 1800 3900
Wire Wire Line
	1600 4200 1600 4350
Wire Wire Line
	1800 4200 1800 4350
Text Label 1600 4350 3    60   ~ 0
A5(SCL)
Text Label 1800 4350 3    60   ~ 0
A4(SDA)
Text Label 1700 3700 0    50   ~ 0
+5V
Wire Wire Line
	1700 3700 1700 3850
Wire Wire Line
	1600 3900 1600 3850
Wire Wire Line
	1600 3850 1700 3850
Connection ~ 1700 3850
Wire Wire Line
	1700 3850 1800 3850
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 5EC442A6
P 600 6200
F 0 "J1" H 492 5867 50  0000 C CNN
F 1 "Conn_01x04_Female" H 628 6085 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 600 6200 50  0001 C CNN
F 3 "~" H 600 6200 50  0001 C CNN
	1    600  6200
	-1   0    0    1   
$EndComp
Text Label 1000 6000 0    50   ~ 0
+5V
Wire Wire Line
	800  6000 1000 6000
Wire Wire Line
	800  6100 1000 6100
Wire Wire Line
	800  6200 1000 6200
Wire Wire Line
	800  6300 1000 6300
Text GLabel 1000 6100 2    50   Input ~ 0
GND
Text Label 1000 6300 0    60   ~ 0
A4(SDA)
Text Label 1000 6200 0    60   ~ 0
A5(SCL)
$Comp
L Connector:Conn_01x03_Female J5
U 1 1 5EC58053
P 1550 6150
F 0 "J5" H 1442 5917 50  0000 C CNN
F 1 "Conn_01x03_Female" H 1578 6085 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 1550 6150 50  0001 C CNN
F 3 "~" H 1550 6150 50  0001 C CNN
	1    1550 6150
	-1   0    0    1   
$EndComp
Wire Wire Line
	1750 6250 1850 6250
Text Label 1850 6250 0    50   ~ 0
+5V
Wire Wire Line
	1750 6050 1850 6050
Text GLabel 1850 6050 2    50   Input ~ 0
GND
Wire Wire Line
	1750 6150 1850 6150
Text Label 1850 6150 0    60   ~ 0
A4(SDA)
$Comp
L RF_Module:RFM95W-915S2 U1
U 1 1 5EC5E3FF
P 5900 4000
F 0 "U1" H 5900 4681 50  0000 C CNN
F 1 "RFM95W-915S2" H 5900 4590 50  0000 C CNN
F 2 "RFM95W-915S2:XCVR_RFM95W-915S2" H 2600 5650 50  0001 C CNN
F 3 "https://www.hoperf.com/data/upload/portal/20181127/5bfcbea20e9ef.pdf" H 2600 5650 50  0001 C CNN
	1    5900 4000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 5EC53D0D
P 600 4350
F 0 "J2" H 492 4017 50  0000 C CNN
F 1 "Conn_01x04_Female" H 628 4235 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 600 4350 50  0001 C CNN
F 3 "~" H 600 4350 50  0001 C CNN
	1    600  4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	800  4150 1050 4150
Wire Wire Line
	800  4250 1050 4250
Wire Wire Line
	800  4350 1050 4350
Wire Wire Line
	800  4450 1050 4450
Text GLabel 1050 4150 2    50   Input ~ 0
E0
Text GLabel 1050 4250 2    50   Input ~ 0
E1
Text GLabel 1050 4350 2    50   Input ~ 0
E2
Text GLabel 1050 4450 2    50   Input ~ 0
E3
Text Label 1500 5600 0    60   ~ 0
10(**/SS)
Text Label 1500 5500 0    60   ~ 0
11(**/MOSI)
Wire Wire Line
	1300 5600 1500 5600
Wire Wire Line
	1300 5500 1500 5500
Wire Wire Line
	1300 5400 1500 5400
Text Label 1500 5400 0    60   ~ 0
12(MISO)
Text Label 1500 5300 0    60   ~ 0
13(SCK)
Wire Wire Line
	1300 5300 1500 5300
Text GLabel 1500 5200 2    50   Input ~ 0
GND
Wire Wire Line
	1300 5200 1500 5200
Text Label 1500 5100 0    50   ~ 0
+5V
Wire Wire Line
	1300 5100 1500 5100
$Comp
L Connector:Conn_01x06_Female J3
U 1 1 5EC1E40C
P 1100 5400
F 0 "J3" H 992 4967 50  0000 C CNN
F 1 "Conn_01x06_Female" H 992 4966 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 1100 5400 50  0001 C CNN
F 3 "~" H 1100 5400 50  0001 C CNN
	1    1100 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	5400 3800 5150 3800
Wire Wire Line
	5400 3700 5150 3700
Wire Wire Line
	5400 3900 5150 3900
Wire Wire Line
	5400 4000 5150 4000
Wire Wire Line
	5800 4600 5900 4600
Connection ~ 5900 4600
Wire Wire Line
	5900 4600 6000 4600
Text GLabel 5900 4700 3    50   Input ~ 0
GND
$Comp
L Device:Antenna AE1
U 1 1 5ECAECC3
P 6700 3700
F 0 "AE1" V 6654 3830 50  0000 L CNN
F 1 "Antenna" V 6745 3830 50  0000 L CNN
F 2 "RF_Antenna:Texas_SWRA117D_2.4GHz_Left" H 6700 3700 50  0001 C CNN
F 3 "~" H 6700 3700 50  0001 C CNN
	1    6700 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 3700 6500 3700
Wire Wire Line
	5400 4200 5150 4200
Wire Wire Line
	5150 4200 5150 4650
Wire Wire Line
	5150 4650 5900 4650
Wire Wire Line
	5900 4600 5900 4650
Wire Wire Line
	5900 4650 5900 4700
Connection ~ 5900 4650
$Comp
L Connector:Conn_01x06_Female J9
U 1 1 5ECBBA62
P 6800 4100
F 0 "J9" H 6828 4030 50  0000 L CNN
F 1 "Conn_01x06_Female" H 6692 3666 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 6800 4100 50  0001 C CNN
F 3 "~" H 6800 4100 50  0001 C CNN
	1    6800 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3900 6600 3900
Wire Wire Line
	6400 4000 6600 4000
Wire Wire Line
	6400 4100 6600 4100
Wire Wire Line
	6400 4200 6600 4200
Wire Wire Line
	6400 4300 6600 4300
Wire Wire Line
	6400 4400 6600 4400
Text Label 5150 3800 2    60   ~ 0
11(**/MOSI)
Text Label 5150 3900 2    60   ~ 0
12(MISO)
Text Label 5150 4000 2    60   ~ 0
10(**/SS)
Text Label 5150 3700 2    60   ~ 0
13(SCK)
Text Label 9150 1550 0    50   ~ 0
+3.3V
Text Label 5900 3200 1    50   ~ 0
+3.3V
Wire Wire Line
	5900 3200 5900 3500
$Comp
L Connector:Screw_Terminal_01x02 J8
U 1 1 5ECF5593
P 6250 5450
F 0 "J8" H 6168 5125 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 6168 5216 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 6250 5450 50  0001 C CNN
F 3 "~" H 6250 5450 50  0001 C CNN
	1    6250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 5450 5850 5450
Wire Wire Line
	5850 5550 6050 5550
$Comp
L Connector:Conn_01x02_Female J7
U 1 1 5ED9D251
P 5650 5550
F 0 "J7" H 5542 5317 50  0000 C CNN
F 1 "Conn_01x02_Female" H 5542 5316 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 5650 5550 50  0001 C CNN
F 3 "~" H 5650 5550 50  0001 C CNN
	1    5650 5550
	-1   0    0    1   
$EndComp
Wire Wire Line
	6000 2450 5800 2450
Wire Wire Line
	6000 2550 5800 2550
Text Label 5800 2450 2    60   ~ 0
A2
Text Label 5800 2550 2    60   ~ 0
A3
$Comp
L Connector:Conn_01x03_Female J6
U 1 1 5EDB3C96
P 6200 2550
F 0 "J6" H 6228 2530 50  0000 L CNN
F 1 "Conn_01x03_Female" H 6228 2485 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 6200 2550 50  0001 C CNN
F 3 "~" H 6200 2550 50  0001 C CNN
	1    6200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2650 5800 2650
Text Label 5800 2650 2    60   ~ 0
9(**)
$Comp
L Device:C C1
U 1 1 5EDC5EC1
P 1550 2750
F 0 "C1" V 1298 2750 50  0000 C CNN
F 1 "100nF" V 1389 2750 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_4x3" H 1588 2600 50  0001 C CNN
F 3 "~" H 1550 2750 50  0001 C CNN
	1    1550 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 2750 1300 2750
Wire Wire Line
	1300 2650 1300 2750
Wire Wire Line
	1300 2750 1300 2850
Connection ~ 1300 2750
Wire Wire Line
	1700 2750 1800 2750
Text GLabel 1800 2750 2    50   Input ~ 0
GND
Wire Notes Line
	800  5800 800  4800
Text Notes 1350 4950 0    50   ~ 0
SPI 
Text Notes 700  2650 0    50   ~ 0
10k POT
Wire Wire Line
	1050 1050 1050 850 
Wire Wire Line
	1050 850  1150 850 
Wire Wire Line
	1050 1050 1050 1250
Wire Wire Line
	1050 1250 1150 1250
Connection ~ 1050 1050
Wire Notes Line
	2350 2450 2350 1350
Text Notes 650  1550 0    50   ~ 0
Buttons
Wire Notes Line
	2150 1350 2150 500 
Wire Notes Line
	2150 500  500  500 
Text Notes 700  700  0    50   ~ 0
LEDs
Wire Notes Line
	500  5800 500  6350
Wire Notes Line
	1400 6350 1400 5800
Text Notes 900  5900 0    50   ~ 0
MPU6050
Wire Notes Line
	1300 4550 500  4550
Text Notes 800  4100 0    50   ~ 0
Port E
Wire Notes Line
	1150 3500 1150 4000
Text Notes 800  3600 0    50   ~ 0
LM35
Wire Notes Line
	2250 6350 2250 5800
Text Notes 1800 5900 0    50   ~ 0
DS18S20
Text Notes 1400 3650 0    50   ~ 0
Pull-up
Wire Notes Line
	4400 5100 4400 2750
Wire Notes Line
	7500 2750 7500 5100
Text Notes 5000 3300 0    50   ~ 0
RFM95-98
Wire Notes Line
	6450 5750 5500 5750
Wire Notes Line
	5500 5750 5500 5100
Wire Notes Line
	6450 5100 6450 5750
Text Notes 6100 5250 2    50   ~ 0
Clamps
Wire Notes Line
	6350 2750 6350 2250
Wire Notes Line
	6350 2250 5550 2250
Wire Notes Line
	5550 2250 5550 2750
Text Notes 6100 2350 2    50   ~ 0
 DRV8833
$Comp
L Device:R R4
U 1 1 5EB8C84F
P 1050 2200
F 0 "R4" V 1257 2200 50  0000 C CNN
F 1 "1k" V 1166 2200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 980 2200 50  0001 C CNN
F 3 "~" H 1050 2200 50  0001 C CNN
	1    1050 2200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5EB6C351
P 1050 1850
F 0 "R3" V 1257 1850 50  0000 C CNN
F 1 "1k" V 1166 1850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 980 1850 50  0001 C CNN
F 3 "~" H 1050 1850 50  0001 C CNN
	1    1050 1850
	0    -1   -1   0   
$EndComp
Wire Notes Line
	500  1350 2350 1350
Wire Notes Line
	500  2450 2350 2450
Wire Notes Line
	500  3500 2100 3500
Wire Notes Line
	2100 2450 2100 5800
Wire Notes Line
	800  4800 2100 4800
Wire Notes Line
	1300 3500 1300 4800
Wire Notes Line
	500  500  500  4550
Wire Notes Line
	500  4000 1300 4000
Wire Notes Line
	500  6350 2250 6350
Wire Notes Line
	500  5800 2250 5800
Wire Notes Line
	4400 5100 7500 5100
Wire Notes Line
	4400 2750 7500 2750
$EndSCHEMATC
