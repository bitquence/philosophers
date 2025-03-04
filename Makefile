NAME = philo

BUILD_DIR := ./build
SRCS_DIR := ./src

CC := cc
VPATH := $(SRCS_DIR)
INCLUSION_DIRS := -Isrc
ifndef RELEASE_MODE
	DEBUGGER ?= gdb
	ADD_DEBUGGING_INFO := -g$(DEBUGGER)
else
	ENABLE_OPTIMIZATIONS := -O3
endif
CFLAGS += -Wall -Wextra -Werror -MMD -MP $(ENABLE_OPTIMIZATIONS) $(ADD_DEBUGGING_INFO) $(INCLUSION_DIRS)
#LDFLAGS :=
#LDLIBS :=

SRCS := $(NAME).c \
	t_error/err_representation.c \
	config/config.c config/parse_uint32.c \
	event/t_event_log.c event/event_log_clear.c \
	event/t_event_node.c event/event_new.c \
	time/instant_now.c time/duration_since.c \
	simulation/simulation_new.c simulation/assign_forks.c simulation/simulation_destroy.c \
	simulation/simulation_run/initialize_threads.c simulation/simulation_run/simulation_run.c \
	simulation/simulation_run/watch_simulation.c simulation/simulation_run/end_simulation.c \
	simulation/simulation_run/log.c simulation/simulation_run/init_variables.c \
	simulation/philosopher/philosophize.c simulation/philosopher/actions.c \
	simulation/philosopher/transition.c simulation/philosopher/simulation_state.c \
	simulation/philosopher/philosopher_sleep.c

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
