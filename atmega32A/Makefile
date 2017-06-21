.PHONY 	  	        :clean

src_dirs  		:= src
header_dirs		:= include
build_dir		:= build
bin_dir			:= bin
hex_dir			:= bin_hex
map_dir			:= map
disasm_dir 		:= disasm
eeprom_dir		:= eeprom

TARG_NAME		:= heating
EEPROM_NAME		:= eeprom

ELF_TARG     		:= $(addsuffix .elf, $(TARG_NAME))
HEX_TARG		:= $(addsuffix .hex, $(TARG_NAME))
DISASM			:= $(addsuffix .s, $(TARG_NAME))

ELF_TARG		:= $(addprefix $(bin_dir)/, $(ELF_TARG))
HEX_TARG		:= $(addprefix $(hex_dir)/, $(HEX_TARG))
DISASM			:= $(addprefix $(disasm_dir)/,$(DISASM)) 
EEPROM_R_HEX		:= $(eeprom_dir)/$(EEPROM_NAME).hex
EEPROM_W_HEX		:= $(eeprom_dir)/$(EEPROM_NAME).hex

DEVICE     		:= atmega32a
CLOCK      		:= 8000000
NAME      		:= m32
PROGRAMMER 		:= -c usbasp -P usb
H_FUSE      		:= -U hfuse:w:0xd9:m 
L_FUSE			:= -U lfuse:w:0xc4:m
EEPROM_READ		:= -U eeprom:r:$(EEPROM_R_HEX):i
EEPROM_WRITE		:= -U eeprom:w:$(EEPROM_W_HEX):i

AVRDUDE 		:= avrdude $(PROGRAMMER) -p $(NAME)

CC    			:= avr-gcc 

CC_FLAGS		:=-std=gnu99 
CC_FLAGS		+= -Wall
CC_FLAGS		+= -O1
CC_FLAGS		+= -mmcu=$(DEVICE)
CC_FLAGS		+= -DF_CPU=$(CLOCK) 
CC_FLAGS		+= -funsigned-char 
CC_FLAGS		+= -ffunction-sections  
CC_FLAGS		+= -funsigned-bitfields
CC_FLAGS		+= -fdata-sections
CC_FLAGS		+= -fpack-struct
CC_FLAGS		+= -fshort-enums

LINK_FLAGS		:= -mmcu=$(DEVICE)


search_wildcards 	:= $(addsuffix /*.c, $(src_dirs))

all: $(HEX_TARG)

$(ELF_TARG): $(addprefix $(build_dir)/, $(notdir $(patsubst %.c, %.o, $(wildcard $(search_wildcards)))))
	@mkdir -p $(@D)
	@mkdir -p $(map_dir)
	$(CC) -Wl,-Map=$(map_dir)/$(TARG_NAME).map -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections $(LINK_FLAGS) $^ -o $@

$(HEX_TARG): $(ELF_TARG)
	@mkdir -p $(@D)
	rm -f $(HEX_TARG)
	avr-objcopy -j .text -j .data -O ihex $< $@
	avr-size --format=avr --mcu=$(DEVICE) $<

VPATH			:= $(src_dirs)

$(build_dir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -MD $(addprefix -I, $(header_dirs)) $< -o $@
	
include $(wildcard $(build_dirs)/*.d)

#Other targets

flash: all
	$(AVRDUDE) $(L_FUSE) -U flash:w:$(HEX_TARG):i

fuse:
	$(AVRDUDE) $(L_FUSE) $(H_FUSE)

read_eeprom:
	@mkdir -p $(eeprom_dir)
	$(AVRDUDE) $(EEPROM_READ)

write_eeprom: $(EEPROM_W_HEX)
	@mkdir -p $(eeprom_dir)
	$(AVRDUDE) $(EEPROM_WRITE)

$(EEPROM_W_HEX): $(eeprom_dir)/$(EEPROM_NAME).txt
	avr-objcopy -I binary $< -O ihex $@
	


disasm: $(ELF_TARG)
	@mkdir -p $(disasm_dir)
	avr-objdump -d $< > $(DISASM)



clean:
	rm -rf $(build_dir)
	rm -rf $(bin_dir)
	rm -rf $(map_dir)
	rm -rf $(hex_dir)
	rm -rf $(disasm_dir)
	rm -rf $(EEPROM_W_HEX)