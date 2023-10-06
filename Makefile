############# CC FLAGS ###############################
NAME = challenge.out
CC = g++
CPPFLAGS = -g -std=c++11
DEFS = -DFIPS

############# ENVIRONMENT ###############################
OPENSSL_PREFIX ?= /usr/local/ssl
OPENSSL_LIBDIR ?= $(OPENSSL_PREFIX)/lib
OPENSSL_INCLUDEDIR ?= $(OPENSSL_PREFIX)/include
LIBCRYPTOSEC_PREFIX ?= /usr/local
LIBCRYPTOSEC ?= $(LIBCRYPTOSEC_PREFIX)/lib64/libcryptosec.so
LIBCRYPTOSEC_INCLUDEDIR ?= $(LIBCRYPTOSEC_PREFIX)/include/libcryptosec/
LIBP11_PREFIX ?= /opt/libp11/
LIBP11_INCLUDEDIR ?= $(LIBP11_PREFIX)/include/

############ DEPENDENCIES ############################
LIBS = $(LIBCRYPTOSEC) -L$(OPENSSL_LIBDIR) -Wl,-rpath,$(OPENSSL_LIBDIR) -lcrypto -pthread
INCLUDES = -I$(OPENSSL_INCLUDEDIR) -I$(LIBCRYPTOSEC_INCLUDEDIR) -I$(LIBP11_INCLUDEDIR)

########### OBJECTS ##################################
SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = challenge.out

########### AUX TARGETS ##############################
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(DEFS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) $(DEFS) -o $(NAME) $(OBJS) $(LIBS)
	@echo 'Build complete!'

########### TARGETS ##################################

all: $(TARGET)

TMP_DIR = tmp

clean:
	rm -f $(OBJ_DIR)/*.o $(TMP_DIR)/*.txt $(TARGET)

