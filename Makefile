SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

HEAD_SERVER = server.h
HEAD_CLIENT = client.h

SRCS_SERVER = server.c server_utils.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

SRCS_CLIENT = client.c client_utils.c
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT)

$(OBJS_SERVER): %.o: %.c $(HEAD_SERVER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_CLIENT): %.o: %.c $(HEAD_CLIENT)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
