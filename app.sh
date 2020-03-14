make
clang *.c ush.h ./libmx/inc/libmx.h ./libmx/libmx.a
make uninstall
rm -rf ush.h.gch libmx/inc/libmx.h.gch
mv ./a.out ./ush
