# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\youkan\Documents\GitHub\camera03\Workspace06\Design01.cydsn\Design01.cyprj
# Date: Sat, 04 Mar 2017 07:49:58 GMT
#set_units -time ns
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {UART_TO_CAMERA_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 157 313} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {UART_TO_DEBUG_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {UART_TO_COMM_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_2}]]


# Component constraints for C:\Users\youkan\Documents\GitHub\camera03\Workspace06\Design01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\youkan\Documents\GitHub\camera03\Workspace06\Design01.cydsn\Design01.cyprj
# Date: Sat, 04 Mar 2017 07:49:47 GMT
