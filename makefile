TARGET := linreg

CC = gcc
BUILD_DIR := ./build
SRC_DIRS := ./src
INC_DIR := ./inc


SRCS := $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)*/*.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := -I $(INC_DIR)

CFLAGS := $(INC_FLAGS) -MMD -MP
CFLAGS += -g -O2 -Wall -Werror

all: $(BUILD_DIR)/$(TARGET) save
# The final build step.
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

save:
	mkdir -p save/

-include $(DEPS)