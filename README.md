# bruce_player
参考FFmpeg自研播放器，依赖ffmpeg静态库（demux、decoder）、sdl2.0.9静态库（render、window）、libz静态库。旨在深入学习ffmpeg播放器架构和工作原理。

# 运行平台
Ubuntu 16.04

# 使用方法
1、在项目根目录执行 make 命令，将生成 player_out 可执行文件，也就是播放器。
2、运行 ./player_out url（视频源路径，网络或者本地路径）

# ffmpeg依赖库
libavfilter.a
libavformat.a
libavcodec.a
libswresample.a
libswscale.a
libavutil.a

# sdl2.0.9依赖库
libSDL2.a
libSDL2main.a

# libz依赖库
libz.a
