# List of all the board related files.
BOARDSRC = ../boards/RT-STM32H743I-NUCLEO144/board.c

# Required include directories
BOARDINC = ../boards/RT-STM32H743I-NUCLEO144

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
