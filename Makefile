

CC=gcc
CFLAGS += -Wall

LIBS += -L./lib -lSDL2 -lSDL2main -lswscale -lavcodec -lavfilter -lavformat -lavutil -lswresample -lm -ldl -lpthread -lrt
INCLUDE += -I./include/SDL2 \
	-I./include/ffmpeg/libavcodec -I./include/ffmpeg/libavfilter -I./include/ffmpeg/libavformat -I./include/ffmpeg/libavutil \
	-I./include/ffmpeg/libswresample -I./include/ffmpeg/libswscale

player_path = player

player_src := $(player_path)/bruce_player.c


player_obj := $(subst .c,.o,$(player_src))

#$(warning $(video_obj))

objs += $(player_obj)

all: player_out

$(objs):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

player_out:$(player_obj)
	$(CC) $(CFLAGS) -o $@ $(player_obj) $(INCLUDE) $(LIBS)



clean:
	rm -rf player_out $(objs)

.PHONY: all clean
