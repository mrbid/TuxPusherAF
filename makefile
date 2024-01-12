CC ?= cc
INCLUDE_HEADERS = -I inc
LINK_DEPS = -lSDL2 -lGLESv2 -lEGL
CFLAGS ?= -Ofast
LDFLAGS = -lm
PRJ_NAME = tuxpusheraf

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

.PHONY: all
all: release

plygame:
	mkdir -p release
	$(CC) $(CFLAGS) main.c $(INCLUDE_HEADERS) $(LINK_DEPS) $(LDFLAGS) -o release/$(PRJ_NAME)
	strip --strip-unneeded release/$(PRJ_NAME)
	upx --lzma --best release/$(PRJ_NAME)

test: plygame
	./release/$(PRJ_NAME)

debify:
	mkdir -p deb/usr/games
	cp release/$(PRJ_NAME) deb/usr/games/$(PRJ_NAME)
	dpkg-deb --build deb release/$(PRJ_NAME).deb

appimage:
	mkdir -p $(PRJ_NAME).AppDir/usr/bin
	gcc main.c -I inc -lSDL2 -lGLESv2 -lEGL -Ofast -lm -o $(PRJ_NAME).AppDir/usr/bin/$(PRJ_NAME)
	strip --strip-unneeded $(PRJ_NAME).AppDir/usr/bin/$(PRJ_NAME)
	upx --lzma --best $(PRJ_NAME).AppDir/usr/bin/$(PRJ_NAME)
	./appimagetool-x86_64.AppImage $(PRJ_NAME).AppDir release/$(PRJ_NAME)-x86_64.AppImage

webgl:
	mkdir -p web
	emcc main.c $(INCLUDE_HEADERS) -O3 --closure 1 -s FILESYSTEM=0 -s USE_SDL=2 -s TOTAL_MEMORY=512MB -s ENVIRONMENT=web -o web/game.html --shell-file t.html
	emrun --browser chrome web/index.html

webrun:
	emrun --browser chrome web/index.html

glfw:
	mkdir -p release
	cc -DBUILD_GLFW main.c glad_gl.c -I inc -Ofast -lglfw -lm -o release/$(PRJ_NAME)_glfw
	strip --strip-unneeded release/$(PRJ_NAME)_glfw
	upx --lzma --best release/$(PRJ_NAME)_glfw

release: plygame glfw debify appimage
	i686-w64-mingw32-gcc -DBUILD_GLFW main.c glad_gl.c -Ofast -I inc -Llib -lglfw3dll -lm -o release/$(PRJ_NAME).exe
	cp lib/glfw3.dll release/glfw3.dll
	strip --strip-unneeded release/glfw3.dll
	upx --lzma --best release/glfw3.dll
	zip release/$(PRJ_NAME)_win.zip release/glfw3.dll release/$(PRJ_NAME).exe
	rm -f release/glfw3.dll release/$(PRJ_NAME).exe

install:
	install -Dm 0755 release/$(PRJ_NAME) -t $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(PRJ_NAME)

clean:
	rm -f release/$(PRJ_NAME)
	rm -f release/$(PRJ_NAME)_glfw
	rm -f release/$(PRJ_NAME).deb
	rm -f release/$(PRJ_NAME)-x86_64.AppImage
	rm -f release/glfw3.dll
	rm -f release/$(PRJ_NAME).exe
	rm -f release/$(PRJ_NAME)_win.zip
	rm -f web/game.html
	rm -f web/game.wasm
	rm -f web/game.js
	rm -f $(PRJ_NAME).AppDir/usr/bin/$(PRJ_NAME)
	rm -f deb/usr/games/$(PRJ_NAME)
	
