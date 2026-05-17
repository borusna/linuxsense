# linuxsense
rgb for phn16s-71 and similar devices, on arch-based distros

## build
```bash 
g++ $(pkg-config --cflags gtk4) -o oslinuxsense main.cpp config.cpp $(pkg-config --libs gtk4) -linih
```
