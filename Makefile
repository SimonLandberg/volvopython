  CC = gcc

  INCLUDES= -Lmw -lmw -Ios -Imw

  TARGET= main

  all: $(TARGET)

  $(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c $(INCLUDES) flags.c can1.c

  clean:
	$(RM) $(TARGET)
	$(all)