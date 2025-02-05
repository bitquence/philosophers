NAME = philo

BUILD_DIR := ./build
SRCS_DIR := ./src

CC := cc
VPATH := $(SRCS_DIR)
INCLUSION_DIRS := -Iinclude
ifndef RELEASE_MODE
	DEBUGGER ?= gdb
	ADD_DEBUGGING_INFO := -g$(DEBUGGER)
else
	ENABLE_OPTIMIZATIONS := -O3
endif
CFLAGS += -Wall -Wextra -Werror -MMD -MP $(ENABLE_OPTIMIZATIONS) $(ADD_DEBUGGING_INFO) $(INCLUSION_DIRS)
#LDFLAGS :=
#LDLIBS :=

SRCS := $(NAME).c
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

SRCS := $(addprefix $(SRCS_DIR)/,$(SRCS))
OBJS := $(addprefix $(BUILD_DIR)/,$(OBJS))
DEPS := $(addprefix $(BUILD_DIR)/,$(DEPS))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OUTPUT_OPTION) $^ $(LDLIBS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

.PHONY: update_lsp
update_lsp: fclean
	mkdir -p $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- make

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want
# those errors to show up.
-include $(DEPS)
