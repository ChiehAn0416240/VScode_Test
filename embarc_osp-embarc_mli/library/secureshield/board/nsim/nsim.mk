ifneq ($(VALID_CUR_CORE), arcem)
ifneq ($(VALID_CUR_CORE), arcsem)
$(error $(VALID_BOARD)-$(VALID_BD_VER)-$(VALID_CUR_CORE) is not supported in secureshield!)
else
LIB_SECURESHIELD_VERSION = 2
endif
else
LIB_SECURESHIELD_VERSION = 1
endif

LIB_SECURESHIELD_BOARD_NSIM_DIR = $(LIB_SECURESHIELD_DIR)/board/nsim

LIB_SECURESHIELD_ASMSRCDIR += $(LIB_SECURESHIELD_BOARD_NSIM_DIR)
LIB_SECURESHIELD_CSRCDIR += $(LIB_SECURESHIELD_BOARD_NSIM_DIR)
LIB_SECURESHIELD_INCDIR += $(LIB_SECURESHIELD_BOARD_NSIM_DIR)


SECURESHIELD_BOARD_CONFIG_FILE = $(LIB_SECURESHIELD_DIR)/board/nsim/secureshield_board_config.h