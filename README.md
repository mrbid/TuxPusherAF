# TuxPusher & Friends
An improved and extended version over [the original.](https://github.com/mrbid/TuxPusher)

Featuring 515 assets generated by various members of the [LUMA GENIE](https://lumalabs.ai/genie) Discord server.

[![Screenshot of the Tux Pusher game](https://dashboard.snapcraft.io/site_media/appmedia/2024/01/Screenshot_2024-01-11_05-38-10.png)](https://www.youtube.com/watch?v=39AIfMu2cYA "Tux Pusher Game Video")

### Improvements
- Coins now rotate
- Holding left mouse will auto-place silver coins
- 515 new "interim" prizes until you get all 6 Tux!

### Controls
_Just move around your mouse and click to release a coin._
- Left Click = Release coin. _(hold to auto-place silver coins)_
- Right Click = Show/Hide cursor.
- C = Orthographic/Perspective.
- F = FPS to console.

### Play Options
- **Snapcraft:** https://snapcraft.io/tuxpusheraf
- **Flathub:** https://flathub.org/en-GB/apps/com.tuxpusher.TuxPusherAF
- **Windows:** https://github.com/mrbid/TuxPusherAF/releases/download/1.0/TuxPusherAF_windows.zip
- **Other Builds:** https://github.com/mrbid/TuxPusherAF/releases/

---
### Build Instructions
---
## Simple *(generates all builds)*
```
sudo ./getdeps.sh
make
```
## Manual Linux SDL
```
sudo apt install libsdl2-2.0-0 libsdl2-dev
cc main.c -I inc -lSDL2 -lGLESv2 -lEGL -Ofast -lm -o tuxpusher
```
## Manual Linux GLFW
```
sudo apt install libglfw3 libglfw3-dev
cc -DBUILD_GLFW main.c glad_gl.c -I inc -Ofast -lglfw -lm -o tuxpusher
```

---

### Typography
- [Fontasy Penguin by FontasyLand](https://www.fontspace.com/fontasy-penguin-font-f4848)
- [Plastic Love by Azkarizki](https://www.fontspace.com/plastic-love-font-f49676)
- [Allay Font by Abahrozi](https://www.fontspace.com/allay-font-f66225) ([twinletter.com](https://twinletter.com))

## License
This software TuxPusher is released under the [GPL-2.0-only](https://spdx.org/licenses/GPL-2.0-only.html) license. Being released under 'GPL-2.0-only' means that any subsequent versions of the GPL-2.0 license are NOT applicable to the source code or assets in this GitHub repository. This GPL-2.0-only licensing includes source code and all assets apart from the Tux 3D asset ([tux.h](assets/tux.h)) created by [Andy Cuccaro](https://sketchfab.com/andycuccaro) which is licenced under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).
