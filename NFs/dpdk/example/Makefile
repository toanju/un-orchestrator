ifeq ($(RTE_SDK),)
$(error "Please define RTE_SDK environment variable")
endif

include $(RTE_SDK)/mk/rte.vars.mk

# binary name
APP = example

# all source are stored in SRCS-y
SRCS-y := main.c init.c runtime.c 
#control_connection.c sockutils.c

CFLAGS += -O3
CFLAGS += $(WERROR_FLAGS)

#CFLAGS += -g

#Uncomment the next line to enable the usage of the semaphore in the NF
#CFLAGS += -DENABLE_SEMAPHORE

#Uncomment the next line to enable the log in the NF
#CFLAGS += -DENABLE_LOG

include $(RTE_SDK)/mk/rte.extapp.mk

