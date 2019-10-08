

CC=gcc
CFLAGS += -Wall -Wno-switch -Wno-unused-variable

LIBS += -L./lib -lSDL2 -lSDL2main -lswscale -lavcodec -lavfilter -lavformat -lavutil -lswresample -lm -ldl -lpthread -lrt
INCLUDE += -I. -I./include/SDL2 -I./ffmpeg

player_path = player

player_src := $(player_path)/bruce_player.c


player_obj := $(subst .c,.o,$(player_src))

cmdutils_src := utils/cmdutils.c
cmdutils_obj := $(subst .c,.o,$(cmdutils_src))
#$(warning $(video_obj))

objs += $(player_obj) $(cmdutils_obj)
all: player_out

$(objs):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

player_out:$(player_obj) $(cmdutils_obj)
	$(CC) $(CFLAGS) -o $@ $(player_obj) $(cmdutils_obj) $(INCLUDE) $(LIBS)



clean:
	rm -rf player_out $(objs)

.PHONY: all clean
