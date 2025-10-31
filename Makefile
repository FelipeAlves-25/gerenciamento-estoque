OUT = build/out
MAIN_FILE = src/main.c
FUNC_FILE = src/func.c
OBJ_FUNC_FILE = bin/func.o
OBJ_MAIN_FILE = bin/main.o

all: $(OUT)

$(OBJ_MAIN_FILE) $(OBJ_FUNC_FILE): $(MAIN_FILE) $(FUNC_FILE)
	gcc -c $(FUNC_FILE) -o $(OBJ_FUNC_FILE)
	gcc -c $(MAIN_FILE) -o $(OBJ_MAIN_FILE)

$(OUT): $(OBJ_FUNC_FILE) $(OBJ_MAIN_FILE)
	gcc $(OBJ_FUNC_FILE) $(OBJ_MAIN_FILE) -o $(OUT)

exec: $(OUT)
	./$(OUT)