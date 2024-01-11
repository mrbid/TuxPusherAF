/*
    James William Fletcher (github.com/mrbid)
        July 2022 - January 2024

    This version implements adaptive coin pushing speed so
    that the coins push slower when you use Gold due to weight
    and slower when you have less of them.

    Coin rotations are now implemented.

    I can build emscripten from GFLW or SDL but I chose to
    only build from SDL because it's better supported.

    Additions from github.com/Jm15itch
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef BUILD_GLFW
    #include "inc/gl.h"
    #define GLFW_INCLUDE_NONE
    #include "inc/glfw3.h"
    #define GL_DEBUG
#else
    #ifdef __EMSCRIPTEN__
        #include <emscripten.h>
        #include <emscripten/html5.h>
        #define GL_GLEXT_PROTOTYPES
        #define EGL_EGLEXT_PROTOTYPES
    #endif

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_opengles2.h>
#endif

#define MAX_MODELS 515
#include "esAux5.h"
#include "res.h"

#include "assets/scene.h"
#include "assets/coin.h"
#include "assets/coin_silver.h"
#include "assets/tux.h"
#include "assets/evil.h"
#include "assets/king.h"
#include "assets/ninja.h"
#include "assets/surf.h"
#include "assets/trip.h"
#include "assets/gameover.h"
#include "assets/rx.h"
#include "assets/sa.h"
#include "assets/ga.h"

#include "assets/friends/f0.h"
#include "assets/friends/f1.h"
#include "assets/friends/f2.h"
#include "assets/friends/f3.h"
#include "assets/friends/f4.h"
#include "assets/friends/f5.h"
#include "assets/friends/f6.h"
#include "assets/friends/f7.h"
#include "assets/friends/f8.h"
#include "assets/friends/f9.h"
#include "assets/friends/f10.h"
#include "assets/friends/f11.h"
#include "assets/friends/f12.h"
#include "assets/friends/f13.h"
#include "assets/friends/f14.h"
#include "assets/friends/f15.h"
#include "assets/friends/f16.h"
#include "assets/friends/f17.h"
#include "assets/friends/f18.h"
#include "assets/friends/f19.h"
#include "assets/friends/f20.h"
#include "assets/friends/f21.h"
#include "assets/friends/f22.h"
#include "assets/friends/f23.h"
#include "assets/friends/f24.h"
#include "assets/friends/f25.h"
#include "assets/friends/f26.h"
#include "assets/friends/f27.h"
#include "assets/friends/f28.h"
#include "assets/friends/f29.h"
#include "assets/friends/f30.h"
#include "assets/friends/f31.h"
#include "assets/friends/f32.h"
#include "assets/friends/f33.h"
#include "assets/friends/f34.h"
#include "assets/friends/f35.h"
#include "assets/friends/f36.h"
#include "assets/friends/f37.h"
#include "assets/friends/f38.h"
#include "assets/friends/f39.h"
#include "assets/friends/f40.h"
#include "assets/friends/f41.h"
#include "assets/friends/f42.h"
#include "assets/friends/f43.h"
#include "assets/friends/f44.h"
#include "assets/friends/f45.h"
#include "assets/friends/f46.h"
#include "assets/friends/f47.h"
#include "assets/friends/f48.h"
#include "assets/friends/f49.h"
#include "assets/friends/f50.h"
#include "assets/friends/f51.h"
#include "assets/friends/f52.h"
#include "assets/friends/f53.h"
#include "assets/friends/f54.h"
#include "assets/friends/f55.h"
#include "assets/friends/f56.h"
#include "assets/friends/f57.h"
#include "assets/friends/f58.h"
#include "assets/friends/f59.h"
#include "assets/friends/f60.h"
#include "assets/friends/f61.h"
#include "assets/friends/f62.h"
#include "assets/friends/f63.h"
#include "assets/friends/f64.h"
#include "assets/friends/f65.h"
#include "assets/friends/f66.h"
#include "assets/friends/f67.h"
#include "assets/friends/f68.h"
#include "assets/friends/f69.h"
#include "assets/friends/f70.h"
#include "assets/friends/f71.h"
#include "assets/friends/f72.h"
#include "assets/friends/f73.h"
#include "assets/friends/f74.h"
#include "assets/friends/f75.h"
#include "assets/friends/f76.h"
#include "assets/friends/f77.h"
#include "assets/friends/f78.h"
#include "assets/friends/f79.h"
#include "assets/friends/f80.h"
#include "assets/friends/f81.h"
#include "assets/friends/f82.h"
#include "assets/friends/f83.h"
#include "assets/friends/f84.h"
#include "assets/friends/f85.h"
#include "assets/friends/f86.h"
#include "assets/friends/f87.h"
#include "assets/friends/f88.h"
#include "assets/friends/f89.h"
#include "assets/friends/f90.h"
#include "assets/friends/f91.h"
#include "assets/friends/f92.h"
#include "assets/friends/f93.h"
#include "assets/friends/f94.h"
#include "assets/friends/f95.h"
#include "assets/friends/f96.h"
#include "assets/friends/f97.h"
#include "assets/friends/f98.h"
#include "assets/friends/f99.h"
#include "assets/friends/f100.h"
#include "assets/friends/f101.h"
#include "assets/friends/f102.h"
#include "assets/friends/f103.h"
#include "assets/friends/f104.h"
#include "assets/friends/f105.h"
#include "assets/friends/f106.h"
#include "assets/friends/f107.h"
#include "assets/friends/f108.h"
#include "assets/friends/f109.h"
#include "assets/friends/f110.h"
#include "assets/friends/f111.h"
#include "assets/friends/f112.h"
#include "assets/friends/f113.h"
#include "assets/friends/f114.h"
#include "assets/friends/f115.h"
#include "assets/friends/f116.h"
#include "assets/friends/f117.h"
#include "assets/friends/f118.h"
#include "assets/friends/f119.h"
#include "assets/friends/f120.h"
#include "assets/friends/f121.h"
#include "assets/friends/f122.h"
#include "assets/friends/f123.h"
#include "assets/friends/f124.h"
#include "assets/friends/f125.h"
#include "assets/friends/f126.h"
#include "assets/friends/f127.h"
#include "assets/friends/f128.h"
#include "assets/friends/f129.h"
#include "assets/friends/f130.h"
#include "assets/friends/f131.h"
#include "assets/friends/f132.h"
#include "assets/friends/f133.h"
#include "assets/friends/f134.h"
#include "assets/friends/f135.h"
#include "assets/friends/f136.h"
#include "assets/friends/f137.h"
#include "assets/friends/f138.h"
#include "assets/friends/f139.h"
#include "assets/friends/f140.h"
#include "assets/friends/f141.h"
#include "assets/friends/f142.h"
#include "assets/friends/f143.h"
#include "assets/friends/f144.h"
#include "assets/friends/f145.h"
#include "assets/friends/f146.h"
#include "assets/friends/f147.h"
#include "assets/friends/f148.h"
#include "assets/friends/f149.h"
#include "assets/friends/f150.h"
#include "assets/friends/f151.h"
#include "assets/friends/f152.h"
#include "assets/friends/f153.h"
#include "assets/friends/f154.h"
#include "assets/friends/f155.h"
#include "assets/friends/f156.h"
#include "assets/friends/f157.h"
#include "assets/friends/f158.h"
#include "assets/friends/f159.h"
#include "assets/friends/f160.h"
#include "assets/friends/f161.h"
#include "assets/friends/f162.h"
#include "assets/friends/f163.h"
#include "assets/friends/f164.h"
#include "assets/friends/f165.h"
#include "assets/friends/f166.h"
#include "assets/friends/f167.h"
#include "assets/friends/f168.h"
#include "assets/friends/f169.h"
#include "assets/friends/f170.h"
#include "assets/friends/f171.h"
#include "assets/friends/f172.h"
#include "assets/friends/f173.h"
#include "assets/friends/f174.h"
#include "assets/friends/f175.h"
#include "assets/friends/f176.h"
#include "assets/friends/f177.h"
#include "assets/friends/f178.h"
#include "assets/friends/f179.h"
#include "assets/friends/f180.h"
#include "assets/friends/f181.h"
#include "assets/friends/f182.h"
#include "assets/friends/f183.h"
#include "assets/friends/f184.h"
#include "assets/friends/f185.h"
#include "assets/friends/f186.h"
#include "assets/friends/f187.h"
#include "assets/friends/f188.h"
#include "assets/friends/f189.h"
#include "assets/friends/f190.h"
#include "assets/friends/f191.h"
#include "assets/friends/f192.h"
#include "assets/friends/f193.h"
#include "assets/friends/f194.h"
#include "assets/friends/f195.h"
#include "assets/friends/f196.h"
#include "assets/friends/f197.h"
#include "assets/friends/f198.h"
#include "assets/friends/f199.h"
#include "assets/friends/f200.h"
#include "assets/friends/f201.h"
#include "assets/friends/f202.h"
#include "assets/friends/f203.h"
#include "assets/friends/f204.h"
#include "assets/friends/f205.h"
#include "assets/friends/f206.h"
#include "assets/friends/f207.h"
#include "assets/friends/f208.h"
#include "assets/friends/f209.h"
#include "assets/friends/f210.h"
#include "assets/friends/f211.h"
#include "assets/friends/f212.h"
#include "assets/friends/f213.h"
#include "assets/friends/f214.h"
#include "assets/friends/f215.h"
#include "assets/friends/f216.h"
#include "assets/friends/f217.h"
#include "assets/friends/f218.h"
#include "assets/friends/f219.h"
#include "assets/friends/f220.h"
#include "assets/friends/f221.h"
#include "assets/friends/f222.h"
#include "assets/friends/f223.h"
#include "assets/friends/f224.h"
#include "assets/friends/f225.h"
#include "assets/friends/f226.h"
#include "assets/friends/f227.h"
#include "assets/friends/f228.h"
#include "assets/friends/f229.h"
#include "assets/friends/f230.h"
#include "assets/friends/f231.h"
#include "assets/friends/f232.h"
#include "assets/friends/f233.h"
#include "assets/friends/f234.h"
#include "assets/friends/f235.h"
#include "assets/friends/f236.h"
#include "assets/friends/f237.h"
#include "assets/friends/f238.h"
#include "assets/friends/f239.h"
#include "assets/friends/f240.h"
#include "assets/friends/f241.h"
#include "assets/friends/f242.h"
#include "assets/friends/f243.h"
#include "assets/friends/f244.h"
#include "assets/friends/f245.h"
#include "assets/friends/f246.h"
#include "assets/friends/f247.h"
#include "assets/friends/f248.h"
#include "assets/friends/f249.h"
#include "assets/friends/f250.h"
#include "assets/friends/f251.h"
#include "assets/friends/f252.h"
#include "assets/friends/f253.h"
#include "assets/friends/f254.h"
#include "assets/friends/f255.h"
#include "assets/friends/f256.h"
#include "assets/friends/f257.h"
#include "assets/friends/f258.h"
#include "assets/friends/f259.h"
#include "assets/friends/f260.h"
#include "assets/friends/f261.h"
#include "assets/friends/f262.h"
#include "assets/friends/f263.h"
#include "assets/friends/f264.h"
#include "assets/friends/f265.h"
#include "assets/friends/f266.h"
#include "assets/friends/f267.h"
#include "assets/friends/f268.h"
#include "assets/friends/f269.h"
#include "assets/friends/f270.h"
#include "assets/friends/f271.h"
#include "assets/friends/f272.h"
#include "assets/friends/f273.h"
#include "assets/friends/f274.h"
#include "assets/friends/f275.h"
#include "assets/friends/f276.h"
#include "assets/friends/f277.h"
#include "assets/friends/f278.h"
#include "assets/friends/f279.h"
#include "assets/friends/f280.h"
#include "assets/friends/f281.h"
#include "assets/friends/f282.h"
#include "assets/friends/f283.h"
#include "assets/friends/f284.h"
#include "assets/friends/f285.h"
#include "assets/friends/f286.h"
#include "assets/friends/f287.h"
#include "assets/friends/f288.h"
#include "assets/friends/f289.h"
#include "assets/friends/f290.h"
#include "assets/friends/f291.h"
#include "assets/friends/f292.h"
#include "assets/friends/f293.h"
#include "assets/friends/f294.h"
#include "assets/friends/f295.h"
#include "assets/friends/f296.h"
#include "assets/friends/f297.h"
#include "assets/friends/f298.h"
#include "assets/friends/f299.h"
#include "assets/friends/f300.h"
#include "assets/friends/f301.h"
#include "assets/friends/f302.h"
#include "assets/friends/f303.h"
#include "assets/friends/f304.h"
#include "assets/friends/f305.h"
#include "assets/friends/f306.h"
#include "assets/friends/f307.h"
#include "assets/friends/f308.h"
#include "assets/friends/f309.h"
#include "assets/friends/f310.h"
#include "assets/friends/f311.h"
#include "assets/friends/f312.h"
#include "assets/friends/f313.h"
#include "assets/friends/f314.h"
#include "assets/friends/f315.h"
#include "assets/friends/f316.h"
#include "assets/friends/f317.h"
#include "assets/friends/f318.h"
#include "assets/friends/f319.h"
#include "assets/friends/f320.h"
#include "assets/friends/f321.h"
#include "assets/friends/f322.h"
#include "assets/friends/f323.h"
#include "assets/friends/f324.h"
#include "assets/friends/f325.h"
#include "assets/friends/f326.h"
#include "assets/friends/f327.h"
#include "assets/friends/f328.h"
#include "assets/friends/f329.h"
#include "assets/friends/f330.h"
#include "assets/friends/f331.h"
#include "assets/friends/f332.h"
#include "assets/friends/f333.h"
#include "assets/friends/f334.h"
#include "assets/friends/f335.h"
#include "assets/friends/f336.h"
#include "assets/friends/f337.h"
#include "assets/friends/f338.h"
#include "assets/friends/f339.h"
#include "assets/friends/f340.h"
#include "assets/friends/f341.h"
#include "assets/friends/f342.h"
#include "assets/friends/f343.h"
#include "assets/friends/f344.h"
#include "assets/friends/f345.h"
#include "assets/friends/f346.h"
#include "assets/friends/f347.h"
#include "assets/friends/f348.h"
#include "assets/friends/f349.h"
#include "assets/friends/f350.h"
#include "assets/friends/f351.h"
#include "assets/friends/f352.h"
#include "assets/friends/f353.h"
#include "assets/friends/f354.h"
#include "assets/friends/f355.h"
#include "assets/friends/f356.h"
#include "assets/friends/f357.h"
#include "assets/friends/f358.h"
#include "assets/friends/f359.h"
#include "assets/friends/f360.h"
#include "assets/friends/f361.h"
#include "assets/friends/f362.h"
#include "assets/friends/f363.h"
#include "assets/friends/f364.h"
#include "assets/friends/f365.h"
#include "assets/friends/f366.h"
#include "assets/friends/f367.h"
#include "assets/friends/f368.h"
#include "assets/friends/f369.h"
#include "assets/friends/f370.h"
#include "assets/friends/f371.h"
#include "assets/friends/f372.h"
#include "assets/friends/f373.h"
#include "assets/friends/f374.h"
#include "assets/friends/f375.h"
#include "assets/friends/f376.h"
#include "assets/friends/f377.h"
#include "assets/friends/f378.h"
#include "assets/friends/f379.h"
#include "assets/friends/f380.h"
#include "assets/friends/f381.h"
#include "assets/friends/f382.h"
#include "assets/friends/f383.h"
#include "assets/friends/f384.h"
#include "assets/friends/f385.h"
#include "assets/friends/f386.h"
#include "assets/friends/f387.h"
#include "assets/friends/f388.h"
#include "assets/friends/f389.h"
#include "assets/friends/f390.h"
#include "assets/friends/f391.h"
#include "assets/friends/f392.h"
#include "assets/friends/f393.h"
#include "assets/friends/f394.h"
#include "assets/friends/f395.h"
#include "assets/friends/f396.h"
#include "assets/friends/f397.h"
#include "assets/friends/f398.h"
#include "assets/friends/f399.h"
#include "assets/friends/f400.h"
#include "assets/friends/f401.h"
#include "assets/friends/f402.h"
#include "assets/friends/f403.h"
#include "assets/friends/f404.h"
#include "assets/friends/f405.h"
#include "assets/friends/f406.h"
#include "assets/friends/f407.h"
#include "assets/friends/f408.h"
#include "assets/friends/f409.h"
#include "assets/friends/f410.h"
#include "assets/friends/f411.h"
#include "assets/friends/f412.h"
#include "assets/friends/f413.h"
#include "assets/friends/f414.h"
#include "assets/friends/f415.h"
#include "assets/friends/f416.h"
#include "assets/friends/f417.h"
#include "assets/friends/f418.h"
#include "assets/friends/f419.h"
#include "assets/friends/f420.h"
#include "assets/friends/f421.h"
#include "assets/friends/f422.h"
#include "assets/friends/f423.h"
#include "assets/friends/f424.h"
#include "assets/friends/f425.h"
#include "assets/friends/f426.h"
#include "assets/friends/f427.h"
#include "assets/friends/f428.h"
#include "assets/friends/f429.h"
#include "assets/friends/f430.h"
#include "assets/friends/f431.h"
#include "assets/friends/f432.h"
#include "assets/friends/f433.h"
#include "assets/friends/f434.h"
#include "assets/friends/f435.h"
#include "assets/friends/f436.h"
#include "assets/friends/f437.h"
#include "assets/friends/f438.h"
#include "assets/friends/f439.h"
#include "assets/friends/f440.h"
#include "assets/friends/f441.h"
#include "assets/friends/f442.h"
#include "assets/friends/f443.h"
#include "assets/friends/f444.h"
#include "assets/friends/f445.h"
#include "assets/friends/f446.h"
#include "assets/friends/f447.h"
#include "assets/friends/f448.h"
#include "assets/friends/f449.h"
#include "assets/friends/f450.h"
#include "assets/friends/f451.h"
#include "assets/friends/f452.h"
#include "assets/friends/f453.h"
#include "assets/friends/f454.h"
#include "assets/friends/f455.h"
#include "assets/friends/f456.h"
#include "assets/friends/f457.h"
#include "assets/friends/f458.h"
#include "assets/friends/f459.h"
#include "assets/friends/f460.h"
#include "assets/friends/f461.h"
#include "assets/friends/f462.h"
#include "assets/friends/f463.h"
#include "assets/friends/f464.h"
#include "assets/friends/f465.h"
#include "assets/friends/f466.h"
#include "assets/friends/f467.h"
#include "assets/friends/f468.h"
#include "assets/friends/f469.h"
#include "assets/friends/f470.h"
#include "assets/friends/f471.h"
#include "assets/friends/f472.h"
#include "assets/friends/f473.h"
#include "assets/friends/f474.h"
#include "assets/friends/f475.h"
#include "assets/friends/f476.h"
#include "assets/friends/f477.h"
#include "assets/friends/f478.h"
#include "assets/friends/f479.h"
#include "assets/friends/f480.h"
#include "assets/friends/f481.h"
#include "assets/friends/f482.h"
#include "assets/friends/f483.h"
#include "assets/friends/f484.h"
#include "assets/friends/f485.h"
#include "assets/friends/f486.h"
#include "assets/friends/f487.h"
#include "assets/friends/f488.h"
#include "assets/friends/f489.h"
#include "assets/friends/f490.h"
#include "assets/friends/f491.h"
#include "assets/friends/f492.h"
#include "assets/friends/f493.h"
#include "assets/friends/f494.h"
#include "assets/friends/f495.h"
#include "assets/friends/f496.h"
#include "assets/friends/f497.h"
#include "assets/friends/f498.h"
#include "assets/friends/f499.h"
#include "assets/friends/f500.h"
#include "assets/friends/f501.h"
#include "assets/friends/f502.h"
#include "assets/friends/f503.h"
#include "assets/friends/f504.h"
#include "assets/friends/f505.h"
#include "assets/friends/f506.h"
#include "assets/friends/f507.h"
#include "assets/friends/f508.h"
#include "assets/friends/f509.h"
#include "assets/friends/f510.h"
#include "assets/friends/f511.h"
#include "assets/friends/f512.h"
#include "assets/friends/f513.h"
#include "assets/friends/f514.h"

#define uint GLushort // it's a short don't forget that
#define sint GLshort  // and this.
#define f32 GLfloat
#define forceinline __attribute__((always_inline)) inline

//*************************************
// globals
//*************************************
char appTitle[] = "TuxPusher & Friends";
#ifdef BUILD_GLFW
    GLFWwindow* wnd;
#else
    SDL_Window* wnd;
    SDL_GLContext glc;
    SDL_Surface* s_icon = NULL;
    SDL_Cursor* cross_cursor;
    SDL_Cursor* beam_cursor;
#endif
uint cursor_state = 0;
uint winw = 1024, winh = 768;
f32 aspect, ww, wh, rww;
f32 t = 0.f;
f32 dt = 0;   // delta time
#ifndef __EMSCRIPTEN__
f32 fc = 0;   // frame count
f32 lfct = 0; // last frame count time
#endif
f32 touch_margin = 120.f;
f32 mx=0, my=0;
uint md=0;
f32 rst = 0.f;
uint ortho = 0;

// render state matrices
mat projection, view, model, modelview;

// render state inputs
vec lightpos = {0.f, 10.f, 13.f};
int csp = -1; // current shader program

// models
ESModel mdlPlane;
ESModel mdlGameover;
ESModel mdlScene;
ESModel mdlCoin;
ESModel mdlCoinSilver;
ESModel mdlTux;
ESModel mdlEvil;
ESModel mdlKing;
ESModel mdlSurf;
ESModel mdlNinja;
ESModel mdlTrip;
ESModel mdlRX;
ESModel mdlSA;
ESModel mdlGA;

// game vars
f32 gold_stack = 64.f;  // line 740+ defining these as float32 eliminates the need to cast in mSetPos3()
f32 silver_stack = 64.f;// function due to the use of a float32 also in the for(f32 i;) loop.
uint active_coin = 0;
uint inmotion = 0;
f32 gameover = 0.f;
uint isnewcoin = 0;
f32 PUSH_SPEED = 3.6f;
f32 MAX_PUSH_SPEED = 3.6f;

typedef struct
{
    f32 x, y, r, rs, a;
    signed short type;
} coin;
#define MAX_COINS 140
coin coins[MAX_COINS] = {0};

// Bit flag based method for storing trophie states, 
// 0b0000_0000 where the last bit denotes 1, second last denotes 2 etc like so:
// 0b0000_0001 = trophie 1
// 0b0000_0101 = trophie 1 and 3

char trophies_bits = 0; 
#define trophies_set(x) trophies_bits |= (0b1 << x)
#define trophies_clear() trophies_bits = 0
#define trophies_get(x) (trophies_bits >> x) & 0b1
#define trophies_all() trophies_bits
const uint max_friends = 6;

//*************************************
// game functions
//*************************************
void timestamp(char* ts)
{
    const time_t tt = time(0);
    strftime(ts, 16, "%H:%M:%S", localtime(&tt));
}
forceinline f32 f32Time()
{
#ifdef BUILD_GLFW
    return glfwGetTime();
#else
    return ((f32)SDL_GetTicks())*0.001f;
#endif
}
void setActiveCoin(const uint color)
{
    for(int i=max_friends; i < MAX_COINS; i++)
    {
        if(coins[i].type == -1)
        {
            coins[i].type = color;
            coins[i].a = 0.f;
            active_coin = i;
            return;
        }
    }
}
void takeStack()
{
    if(gameover != 0.f){return;}
    
    if(silver_stack != 0.f)
    {
        // play a silver coin
        isnewcoin = 1;
        setActiveCoin(0);
        inmotion = 1;
        PUSH_SPEED = (MAX_PUSH_SPEED*0.5f) + ((MAX_PUSH_SPEED*0.5f)*(silver_stack*0.015625f))+1.f; // and silver significantly lighter
    }
    else if(gold_stack != 0.f)
    {
        // play a gold coin
        isnewcoin = 2;
        setActiveCoin(1);
        inmotion = 1;
        PUSH_SPEED = ((MAX_PUSH_SPEED*(gold_stack*0.015625f))+1.f)*0.5f; // makes gold feel heavier
    }

    if(inmotion == 1)
    {
        if(mx < touch_margin)
        {
            coins[active_coin].x = -1.90433f;
            coins[active_coin].y = -4.54055f;
            return;
        }
        
        if(mx > ww-touch_margin)
        {
            coins[active_coin].x = 1.90433f;
            coins[active_coin].y = -4.54055f;
            return;
        }
        
        coins[active_coin].x = -1.90433f+(((mx-touch_margin)*rww)*3.80866f);
        coins[active_coin].y = -4.54055f;
    }
}
void injectFriend()
{
    if(inmotion != 0)
        return;
    
    int fcn = -1;
    for(int i=0; i < max_friends; i++)
    {
        if(coins[i].type == -1)
        {
            active_coin = i;
            fcn = i;
            coins[i].type = esRand(1, 520);
            if(coins[i].type > 6)
            {
                coins[i].a = esRandFloat(-PI, PI);
                coins[i].r = esModelArray[coins[i].type-7].radius;
                coins[i].rs = esRandFloat(0.7f, 2.2f);
                coins[i].r *= coins[i].rs;
            }
            else
            {
                coins[i].a = 0.f;
                coins[i].r = 0.34f;
                coins[i].rs = 0.f;
            }
            break;
        }
    }

    if(fcn != -1)
    {
        coins[active_coin].x = fRandFloat(-1.90433f, 1.90433f);
        coins[active_coin].y = -4.54055f;
        inmotion = 1;
    }
}
int insidePitch(const f32 x, const f32 y, const f32 r)
{
    // off bottom
    if(y < -4.03414f+r)
        return 0;
    
    // first left & right
    if(y < -2.22855f)
    {
        if(x < (-2.22482f - (0.77267f*(fabsf(y+4.03414f) * 0.553835588f))) + r)
            return 0;
        else if(x > (2.22482f + (0.77267f*(fabsf(y+4.03414f) * 0.553835588f))) - r)
            return 0;
    }
    else if(y < -0.292027f) // second left & right
    {
        if(x < (-2.99749f - (0.41114f*(fabsf(y+2.22855f) * 0.516389426f))) + r)
            return 0;
        else if(x > (2.99749f + (0.41114f*(fabsf(y+2.22855f) * 0.516389426f))) - r)
            return 0;
    }
    else if(y < 1.45439f) // third left & right
    {
        if(x < -3.40863f + r)
            return 0;
        else if(x > 3.40863f - r)
            return 0;
    }

    return 1;
}
int collision(int ci)
{
    for(int i=0; i < MAX_COINS; i++)
    {
        if(i == ci || coins[i].type == -1){continue;}
        const f32 xm = (coins[i].x - coins[ci].x);
        const f32 ym = (coins[i].y - coins[ci].y);
        const f32 radd = coins[i].r+coins[ci].r;
        if(xm*xm + ym*ym < radd*radd)
            return 1;
    }
    return 0;
}
uint stepCollisions()
{
    uint was_collision = 0;
    for(int i=0; i < MAX_COINS; i++)
    {
        if(coins[i].type == -1){continue;}
        for(int j=0; j < MAX_COINS; j++)
        {
            if(i == j || coins[j].type == -1 || j == active_coin){continue;}
            f32 xm = (coins[i].x - coins[j].x);
            xm += fRandFloat(-0.01f, 0.01f); // add some random offset to our unit vector, very subtle but works so well!
            const f32 ym = (coins[i].y - coins[j].y);
            f32 d = xm*xm + ym*ym;
            const f32 cr = coins[i].r+coins[j].r;
            if(d < cr*cr)
            {
                d = sqrtf(d);
                const f32 len = 1.f/d;
                const f32 uy = (ym * len);
                if(uy > 0.f){continue;} // best hack ever to massively simplify
                const f32 m = d-cr;
                coins[j].x += (xm * len) * m;
                coins[j].y += uy * m;
                coins[j].a += (coins[j].x-coins[i].x)*0.006f; // lol call it a stroke of genuis

                // first left & right
                if(coins[j].y < -2.22855f)
                {
                    const f32 fl = (-2.22482f - (0.77267f*(fabsf(coins[j].y+4.03414f) * 0.553835588f))) + coins[j].r;
                    if(coins[j].x < fl)
                    {
                        coins[j].x = fl;
                    }
                    else
                    {
                        const f32 fr = ( 2.22482f + (0.77267f*(fabsf(coins[j].y+4.03414f) * 0.553835588f))) - coins[j].r;
                        if(coins[j].x > fr)
                            coins[j].x = fr;
                    }
                }
                else if(coins[j].y < -0.292027f) // second left & right
                {
                    const f32 fl = (-2.99749f - (0.41114f*(fabsf(coins[j].y+2.22855f) * 0.516389426f))) + coins[j].r;
                    if(coins[j].x < fl)
                    {
                        coins[j].x = fl;
                    }
                    else
                    {
                        const f32 fr = (2.99749f + (0.41114f*(fabsf(coins[j].y+2.22855f) * 0.516389426f))) - coins[j].r;
                        if(coins[j].x > fr)
                            coins[j].x = fr;
                    }
                }
                else if(coins[j].y < 1.64f) // third left & right
                {
                    const f32 fl = -3.40863f + coins[j].r;
                    if(coins[j].x < fl)
                    {
                        coins[j].x = fl;
                    }
                    else
                    {
                        const f32 fr = 3.40863f - coins[j].r;
                        if(coins[j].x > fr)
                            coins[j].x = fr;
                    }
                }
                else if(coins[j].y < 2.58397f) // first house goal
                {
                    const f32 fl = (-3.40863f + (0.41113f*(fabsf(coins[j].y-1.45439f) * 0.885284796f)));
                    if(coins[j].x < fl)
                    {
                        coins[j].type = -1;
                    }
                    else
                    {
                        const f32 fr = (3.40863f - (0.41113f*(fabsf(coins[j].y-1.45439f) * 0.885284796f)));
                        if(coins[j].x > fr)
                            coins[j].type = -1;
                    }
                }
                else if(coins[j].y < 3.70642f) // second house goal
                {
                    const f32 fl = (-2.9975f + (1.34581f*(fabsf(coins[j].y-2.58397f) * 0.890908281f)));
                    if(coins[j].x < fl)
                    {
                        coins[j].type = -1;
                    }
                    else
                    {
                        const f32 fr = (2.9975f - (1.34581f*(fabsf(coins[j].y-2.58397f) * 0.890908281f)));
                        if(coins[j].x > fr)
                            coins[j].type = -1;
                    }
                }
                else if(coins[j].y < 4.10583f) // silver goal
                {
                    const f32 fl = (-1.65169f + (1.067374f*(fabsf(coins[j].y-3.70642f) * 2.503692947f)));
                    if(coins[j].x < fl)
                    {
                        if(j >= 0 && j <= max_friends)
                        {
                            if(coins[j].type > 0 && coins[j].type < 7)
                            {
                                if(trophies_get(coins[j].type-1) == 1) // already have? then reward coins!
                                {
                                    gold_stack += 6.f;
                                    silver_stack += 6.f;
                                }
                                else
                                {
                                    gold_stack += 12.f;
                                    trophies_set(coins[j].type-1);
                                }
                            }
                            else{silver_stack += esRandFloat(8.f, 16.f);}
                        }
                        else
                        {
                            if(coins[j].type == 0)
                                silver_stack += 1.f;
                            else if(coins[j].type == 1)
                                silver_stack += 2.f;
                        }

                        coins[j].type = -1;
                    }
                    else
                    {
                        const f32 fr = (1.65169f - (1.067374f*(fabsf(coins[j].y-3.70642f) * 2.503692947f)));
                        if(coins[j].x > fr)
                        {
                            if(j >= 0 && j <= max_friends)
                            {
                                if(coins[j].type > 0 && coins[j].type < 7)
                                {
                                    if(trophies_get(coins[j].type-1) == 1) // already have? then reward coins!
                                    {
                                        gold_stack += 6.f;
                                        silver_stack += 6.f;
                                    }
                                    else
                                    {
                                        gold_stack += 12.f;
                                        trophies_set(coins[j].type-1);
                                    }
                                }
                                else{silver_stack += esRandFloat(8.f, 16.f);}
                            }
                            else
                            {
                                if(coins[j].type == 0)
                                    silver_stack += 1.f;
                                else if(coins[j].type == 1)
                                    silver_stack += 2.f;
                            }

                            coins[j].type = -1;
                        }
                    }
                }
                else if(coins[j].y >= 4.31457f) // gold goal
                {
                    if(coins[j].x >= -0.584316f && coins[j].x <= 0.584316f)
                    {
                        if(j >= 0 && j <= max_friends)
                        {
                            if(coins[j].type > 0 && coins[j].type < 7)
                            {
                                if(trophies_get(coins[j].type-1) == 1) // already have? then reward coins!
                                {
                                    gold_stack += 6.f;
                                    silver_stack += 6.f;
                                }
                                else
                                {
                                    gold_stack += 12.f;
                                    trophies_set(coins[j].type-1);
                                }
                            }
                            else{silver_stack += esRandFloat(16.f, 32.f);}
                        }
                        else
                        {
                            if(coins[j].type == 0)
                                silver_stack += 1.f;
                            else if(coins[j].type == 1)
                                gold_stack += 2.f;
                        }

                        coins[j].type = -1;
                    }
                    else
                    {
                        if(j >= 0 && j <= max_friends)
                        {
                            if(coins[j].type > 0 && coins[j].type < 7)
                            {
                                if(trophies_get(coins[j].type-1) == 1) // already have? then reward coins!
                                {
                                    gold_stack += 6.f;
                                    silver_stack += 6.f;
                                }
                                else
                                {
                                    gold_stack += 12.f;
                                    trophies_set(coins[j].type-1);
                                }
                            }
                            else{silver_stack += esRandFloat(16.f, 32.f);}
                        }
                        else{silver_stack += 1.f;}

                        coins[j].type = -1;
                    }
                }
                
                was_collision++;
            }
        }
    }
    return was_collision;
}
void newGame()
{
    // seed randoms
    srand(time(0));
    srandf(time(0));

    // defaults
    gold_stack = 64.f;
    silver_stack = 64.f;
    active_coin = 0;
    inmotion = 0;
    gameover = 0.f;
    trophies_clear();
    for(int i=0; i < MAX_COINS; i++)
    {
        coins[i].type = -1;
        coins[i].r = 0.3f;
        coins[i].a = 0.f;
        coins[i].rs = 0.f;
    }

    // trophies
    for(int i=0; i < max_friends; i++)
    {
        coins[i].type = esRand(1, 520);
        coins[i].rs = 0.f;
        if(coins[i].type > 6)
        {
            coins[i].a = esRandFloat(-PI, PI);
            coins[i].r = esModelArray[coins[i].type-7].radius;
            coins[i].rs = esRandFloat(0.7f, 2.2f);
            coins[i].r *= coins[i].rs;
        }
        else
        {
            coins[i].a = 0.f;
            coins[i].r = 0.34f;
        }

        coins[i].x = fRandFloat(-3.40863f, 3.40863f);
        coins[i].y = fRandFloat(-4.03414f, 1.45439f-coins[i].r);
        while(insidePitch(coins[i].x, coins[i].y, coins[i].r) == 0 || collision(i) == 1)
        {
            coins[i].x = fRandFloat(-3.40863f, 3.40863f);
            coins[i].y = fRandFloat(-4.03414f, 1.45439f-coins[i].r);
        }
    }

    // coins
    const f32 lt = f32Time();
    for(int i=max_friends; i < MAX_COINS; i++)
    {
        coins[i].x = fRandFloat(-3.40863f, 3.40863f);
        coins[i].y = fRandFloat(-4.03414f, 1.45439f-coins[i].r);
        uint tl = 0;
        while(insidePitch(coins[i].x, coins[i].y, coins[i].r) == 0 || collision(i) == 1)
        {
            coins[i].x = fRandFloat(-3.40863f, 3.40863f);
            coins[i].y = fRandFloat(-4.03414f, 1.45439f-coins[i].r);
            if(f32Time()-lt > 0.033){tl=1;break;} // 33ms timeout
        }
        if(tl==1){break;}
        coins[i].type = esRand(0, 4); // makes gold rarer
        if(coins[i].type > 1){coins[i].type = 0;}
    }

    rst = f32Time(); // round start time
}

//*************************************
// render functions
//*************************************
forceinline void modelBind1(const ESModel* mdl)
{
    glBindBuffer(GL_ARRAY_BUFFER, mdl->vid);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mdl->iid);
}
forceinline void modelBind3(const ESModel* mdl)
{
    glBindBuffer(GL_ARRAY_BUFFER, mdl->cid);
    glVertexAttribPointer(color_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color_id);

    glBindBuffer(GL_ARRAY_BUFFER, mdl->vid);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);

    glBindBuffer(GL_ARRAY_BUFFER, mdl->nid);
    glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normal_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mdl->iid);
}
void doPerspective()
{
    ww = (f32)winw;
    wh = (f32)winh;

#ifdef __EMSCRIPTEN__
    const f32 mww = wh + (wh * 0.34f);
    if(ww > mww)
        ww = wh + (wh * 0.34f);
    else
        wh = ww - (ww * 0.2520f);
#endif

    winw = (uint)ww;
    winh = (uint)wh;

#ifdef __EMSCRIPTEN__
    emscripten_set_canvas_element_size("canvas", winw, winh);
#endif

    glViewport(0, 0, winw, winh);
    if(ortho == 1){touch_margin = ww*0.3076923192f;}
    else{touch_margin = ww*0.2058590651f;}
    rww = 1.0/(ww-touch_margin*2.0);
    mIdent(&projection);

    if(ortho == 1)
        mOrtho(&projection, -5.0f, 5.0f, -3.2f, 3.4f, 2.0f, 30.f);
    else
    {
#ifndef __EMSCRIPTEN__
        if(winw > winh)
            aspect = ww / wh;
        else
            aspect = wh / ww;
#else
        aspect = ww / wh;
#endif
        mPerspective(&projection, 30.0f, aspect, 2.0f, 30.f);
    }
}

//*************************************
// update & render
//*************************************
void main_loop()
{
//*************************************
// time delta for interpolation
//*************************************
    static f32 lt = 0;
    fc++;
    t = f32Time();
    dt = t-lt;
    lt = t;

//*************************************
// input handling
//*************************************
#ifdef BUILD_GLFW
    double tmx, tmy;
    glfwGetCursorPos(wnd, &tmx, &tmy);
    mx = (f32)tmx;
    my = (f32)tmy;
#else
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
#ifndef __EMSCRIPTEN__
        if(event.type == SDL_MOUSEMOTION)
        {
            mx = (f32)event.motion.x;
            my = (f32)event.motion.y;
        }
        else
#endif
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(inmotion == 0 && event.button.button == SDL_BUTTON_LEFT)
            {
                if(gameover > 0.f)
                {
                    if(f32Time() > gameover+3.0f)
                    {
                        newGame();
                        if(PUSH_SPEED < 32.f)
                        {
                            PUSH_SPEED += 1.f;
                            MAX_PUSH_SPEED = PUSH_SPEED;
                            char titlestr[256];
                            sprintf(titlestr, "TuxPusherAF [%.1f]", PUSH_SPEED);
                            SDL_SetWindowTitle(wnd, titlestr);
                        }
                    }
                    return;
                }
                takeStack();
                md = 1;
            }

            if(event.button.button == SDL_BUTTON_RIGHT)
            {
                static uint cs = 1;
                cs = 1 - cs;
                if(cs == 0)
                    SDL_ShowCursor(0);
                else
                    SDL_ShowCursor(1);
            }
        }
        else if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
                md = 0;
        }
        else if(event.type == SDL_KEYDOWN)
        {
#ifndef __EMSCRIPTEN__
            if(event.key.keysym.sym == SDLK_f)
            {
                if(t-lfct > 2.0)
                {
                    char strts[16];
                    timestamp(&strts[0]);
                    const f32 nfps = fc/(t-lfct);
                    printf("[%s] FPS: %g\n", strts, nfps);
                    lfct = t;
                    fc = 0;
                }
            }
            else
#endif
            if(event.key.keysym.sym == SDLK_c)
            {
                ortho = 1 - ortho;
                doPerspective();
            }
#ifdef __EMSCRIPTEN__
            else if(event.key.keysym.sym == SDLK_x)
            {
                emscripten_run_script("alert('James William Fletcher (github.com/mrbid)\\n\\nFor the full credits please check the developer console output or check the git readme on the GitHub linked above.');");
            }
#endif
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                winw = event.window.data1;
                winh = event.window.data2;
                doPerspective();
            }
        }
#ifndef __EMSCRIPTEN__
        else if(event.type == SDL_QUIT)
        {
            SDL_GL_DeleteContext(glc);
            SDL_FreeSurface(s_icon);
            SDL_FreeCursor(cross_cursor);
            SDL_FreeCursor(beam_cursor);
            SDL_DestroyWindow(wnd);
            SDL_Quit();
            exit(0);
        }
#endif
    }
#endif
    
//*************************************
// begin render
//*************************************
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//*************************************
// main render
//*************************************

    // cursor icon switching based on the mouse position. 
    // have a cross while over the playing field.
#ifndef BUILD_GLFW
    // cursor
    switch (cursor_state) 
    {
        case 0:
            if (mx <= ww-touch_margin+1.f && mx >= touch_margin-1.f)
                break;
            SDL_SetCursor(beam_cursor);
            cursor_state = 1;
            break;
        case 1:
            if (mx > touch_margin && mx < ww-touch_margin) 
                SDL_SetCursor(cross_cursor);
                cursor_state = 0;
            break;
    }
#endif
    
    // camera
    mIdent(&view);
    mSetPos3(&view, 0.f, 0.f, -13.f);
    if(ortho == 1)
        mRotY(&view, 50.f*DEG2RAD);
    else
        mRotY(&view, 62.f*DEG2RAD);

    // inject a new Friend if time has come
    injectFriend();
    
    // prep scene for rendering
    if(csp != 1)
    {
        shadeLambert3(&position_id, &projection_id, &modelview_id, &lightpos_id, &normal_id, &color_id, &ambient_id, &opacity_id);
        glUniformMatrix4fv(projection_id, 1, GL_FALSE, (f32*)&projection.m[0][0]);
        glUniform3f(lightpos_id, lightpos.x, lightpos.y, lightpos.z);
        glUniform1f(ambient_id, 0.148f);
        csp = 1;
    }
    glUniform1f(ambient_id, 0.148f);

    // render scene
    glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&view.m[0][0]);
    modelBind3(&mdlScene);
    glDrawElements(GL_TRIANGLES, scene_numind, GL_UNSIGNED_SHORT, 0);

    // detect gameover
    if(gold_stack < 0.f){gold_stack = 0.f;}
    if(silver_stack < 0.f){silver_stack = 0.f;}
    if(gameover > 0.f && (gold_stack != 0.f || silver_stack != 0.f))
    {
        gameover = 0.f;
    }
    else if(gold_stack == 0.f && silver_stack == 0.f)
    {
        if(gameover == 0.f)
            gameover = t+3.0f;
    }

    // coin
    glUniform1f(ambient_id, 0.148f);

    // targeting coin
    if(gold_stack > 0.f || silver_stack > 0.f)
    {
        if(coins[active_coin].type == 1)
            modelBind3(&mdlCoinSilver);
        else
            modelBind3(&mdlCoin);
        if(inmotion == 0)
        {
            if(silver_stack > 0.f)
                modelBind3(&mdlCoinSilver);
            else
                modelBind3(&mdlCoin);

            mIdent(&model);
            mScale(&model, 1.f, 1.f, 2.f);

            if(mx < touch_margin)
                mSetPos3(&model, -1.90433f, -4.54055f, 0);
            else if(mx > ww-touch_margin)
                mSetPos3(&model, 1.90433f, -4.54055f, 0);
            else
                mSetPos3(&model, -1.90433f+(((mx-touch_margin)*rww)*3.80866f), -4.54055f, 0);

            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
            glDrawElements(GL_TRIANGLES, coin_numind, GL_UNSIGNED_SHORT, 0);
        }
    }

    // do motion
    if(inmotion == 1)
    {
        if(coins[active_coin].y < -4.41414f+(coins[active_coin].r*2.f))
        {
            coins[active_coin].y += PUSH_SPEED * dt;
            for(int i=0; i < 6; i++) // six seems enough
                stepCollisions();
        }
        else
        {
            inmotion = 0;

            if(md == 1 && silver_stack > 0.f) // if left mouse is down, and have silvers, auto re-fire
            {
                if(gameover > 0.f)
                {
                    if(t > gameover+3.0f)
                    {
                        newGame();
                        if(PUSH_SPEED < 32.f)
                        {
                            PUSH_SPEED += 1.f;
                            MAX_PUSH_SPEED = PUSH_SPEED;
                            // should have set the window title here, oh well
                        }
                    }
                    return;
                }
                takeStack();
            }

            if(isnewcoin > 0)
            {
                if(isnewcoin == 1)
                    silver_stack -= 1.f;
                else
                    gold_stack -= 1.f;

                isnewcoin = 0;
            }
        }
    }

    // gold stack
    modelBind3(&mdlCoin);
    f32 gss = gold_stack;
    if(silver_stack == 0.f){gss -= 1.f;}
    if(gss < 0.f){gss = 0.f;}
    for(f32 i = 0.f; i < gss; i += 1.f)
    {
        mIdent(&model);
        if(ortho == 0)
            mSetPos3(&model, -2.62939f, -4.54055f, 0.033f*i);
        else
            mSetPos3(&model, -4.62939f, -4.54055f, 0.033f*i);
        mMul(&modelview, &model, &view);
        glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
        glDrawElements(GL_TRIANGLES, coin_numind, GL_UNSIGNED_SHORT, 0);
    }

    // silver stack
    modelBind3(&mdlCoinSilver);
    f32 sss = silver_stack-1.f;
    if(sss < 0.f){sss = 0.f;}
    for(f32 i = 0.f; i < sss; i += 1.f)
    {
        mIdent(&model);
        if(ortho == 0)
            mSetPos3(&model, 2.62939f, -4.54055f, 0.033f*i);
        else
            mSetPos3(&model, 4.62939f, -4.54055f, 0.033f*i);
        mMul(&modelview, &model, &view);
        glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
        glDrawElements(GL_TRIANGLES, coin_numind, GL_UNSIGNED_SHORT, 0);
    }

    // pitch coins
    for(int i=max_friends; i < MAX_COINS; i++)
    {
        if(coins[i].type == -1){continue;}
        
        if(coins[i].type == 0)
            modelBind3(&mdlCoinSilver);
        else
            modelBind3(&mdlCoin);

        ///
        uint halflit = 0;
        for(uint j = 0; j < max_friends; j++)
        {
            const float xm = (coins[i].x - coins[j].x);
            const float ym = (coins[i].y - coins[j].y);
            const float rm = (coins[i].r + coins[j].r)*2.5f;
            if(xm*xm + ym*ym < rm*rm)
            {
                halflit=1;
                break;
            }
        }
        if(halflit > 0)
            glUniform1f(ambient_id, 0.333f);
        else
            glUniform1f(ambient_id, 0.148f);
        ///

        mIdent(&model);
        //mScale(&model, 1.f, 1.f, 2.f);
        mSetPos3(&model, coins[i].x, coins[i].y, 0.f);
        mRotZ(&model, coins[i].a);
        mMul(&modelview, &model, &view);
        glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
        glDrawElements(GL_TRIANGLES, coin_numind, GL_UNSIGNED_SHORT, 0);
    }

    // tux is fancy
    shadeLambert3(&position_id, &projection_id, &modelview_id, &lightpos_id, &normal_id, &color_id, &ambient_id, &opacity_id);
    glUniformMatrix4fv(projection_id, 1, GL_FALSE, (f32*)&projection.m[0][0]);
    glUniform3f(lightpos_id, lightpos.x, lightpos.y, lightpos.z);
    glUniform1f(ambient_id, 0.148f);

    // trophies
    for(int i=0; i < max_friends; i++)
    {
        if(coins[i].type == -1){continue;}
        
        mIdent(&model);
        mSetPos3(&model, coins[i].x, coins[i].y, 0.f);
        if(coins[i].rs > 0.f){mScale1(&model, coins[i].rs);}
        mRotZ(&model, coins[i].a);
        mMul(&modelview, &model, &view);
        glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);

        if(coins[i].type > 6)
        {
            glUniform1f(ambient_id, 0.648f);
            esBindRender(coins[i].type-7);
        }
        else
        {
            // Draw the base Tux model, this will be our base to add apparel onto
            glUniform1f(ambient_id, 0.148f);
            modelBind3(&mdlTux);
            glDrawElements(GL_TRIANGLES, tux_numind, GL_UNSIGNED_SHORT, 0);

            // Tux Skin Selection.
            switch (coins[i].type) {
                case 2:
                    glUniform1f(ambient_id, 0.5f);
                    modelBind3(&mdlEvil);
                    glDrawElements(GL_TRIANGLES, evil_numind, GL_UNSIGNED_BYTE, 0);
                    break;
                case 3:
                    glUniform1f(ambient_id, 0.6f);
                    modelBind3(&mdlKing);
                    glDrawElements(GL_TRIANGLES, king_numind, GL_UNSIGNED_BYTE, 0);
                    break;
                case 4:
                    modelBind3(&mdlNinja);
                    glDrawElements(GL_TRIANGLES, ninja_numind, GL_UNSIGNED_BYTE, 0);
                    break;
                case 5:
                    glUniform1f(ambient_id, 0.4f);
                    modelBind3(&mdlSurf);
                    glDrawElements(GL_TRIANGLES, surf_numind, GL_UNSIGNED_SHORT, 0);
                    break;
                case 6:
                    glUniform1f(ambient_id, 0.5f);
                    modelBind3(&mdlTrip);
                    glDrawElements(GL_TRIANGLES, trip_numind, GL_UNSIGNED_SHORT, 0);
                    break;
            }
        }
    }

    //
    if(trophies_all())
    {
        if(trophies_get(0) == 1)
        {
            mIdent(&model);
            mSetPos3(&model, 3.92732f, 1.0346f, 0.f);
            mRotZ(&model, t*0.3f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);

            glUniform1f(ambient_id, 0.148f);
            modelBind3(&mdlTux);
            glDrawElements(GL_TRIANGLES, tux_numind, GL_UNSIGNED_SHORT, 0);
        }

        if(trophies_get(1) == 1)
        {
            mIdent(&model);
            mSetPos3(&model, 3.65552f, -1.30202f, 0.f);
            mRotZ(&model, t*0.3f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
            
            glUniform1f(ambient_id, 0.148f);
            modelBind3(&mdlTux);
            glDrawElements(GL_TRIANGLES, tux_numind, GL_UNSIGNED_SHORT, 0);

            glUniform1f(ambient_id, 0.5f);
            modelBind3(&mdlEvil);
            glDrawElements(GL_TRIANGLES, evil_numind, GL_UNSIGNED_BYTE, 0);
        }

        if(trophies_get(2) == 1)
        {
            mIdent(&model);
            mSetPos3(&model, 3.01911f, -3.23534f, 0.f);
            mRotZ(&model, t*0.3f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);

            glUniform1f(ambient_id, 0.148f);
            modelBind3(&mdlTux);
            glDrawElements(GL_TRIANGLES, tux_numind, GL_UNSIGNED_SHORT, 0);

            glUniform1f(ambient_id, 0.6f);
            modelBind3(&mdlKing);
            glDrawElements(GL_TRIANGLES, king_numind, GL_UNSIGNED_BYTE, 0);
        }

        if(trophies_get(3) == 1)
        {
            mIdent(&model);
            mSetPos3(&model, -3.92732f, 1.0346f, 0.f);
            mRotZ(&model, t*0.3f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);

            glUniform1f(ambient_id, 0.148f);
            modelBind3(&mdlTux);
            glDrawElements(GL_TRIANGLES, tux_numind, GL_UNSIGNED_SHORT, 0);

            modelBind3(&mdlNinja);
            glDrawElements(GL_TRIANGLES, ninja_numind, GL_UNSIGNED_BYTE, 0);
        }

        if(trophies_get(4) == 1)
        {
            mIdent(&model);
            mSetPos3(&model, -3.65552f, -1.30202f, 0.f);
            mRotZ(&model, t*0.3f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);

            glUniform1f(ambient_id, 0.148f);
            modelBind3(&mdlTux);
            glDrawElements(GL_TRIANGLES, tux_numind, GL_UNSIGNED_SHORT, 0);

            glUniform1f(ambient_id, 0.4f);
            modelBind3(&mdlSurf);
            glDrawElements(GL_TRIANGLES, surf_numind, GL_UNSIGNED_SHORT, 0);
        }

        if(trophies_get(5) == 1)
        {
            mIdent(&model);
            mSetPos3(&model, -3.01911f, -3.23534f, 0.f);
            mRotZ(&model, t*0.3f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);

            glUniform1f(ambient_id, 0.148f);
            modelBind3(&mdlTux);
            glDrawElements(GL_TRIANGLES, tux_numind, GL_UNSIGNED_SHORT, 0);

            glUniform1f(ambient_id, 0.5f);
            modelBind3(&mdlTrip);
            glDrawElements(GL_TRIANGLES, trip_numind, GL_UNSIGNED_SHORT, 0);
        }
    }

    // render scene props
    const f32 std = t-rst;
    if((gameover > 0.f && t > gameover) || std < 6.75f)
    {
        shadeFullbright(&position_id, &projection_id, &modelview_id, &color_id, &opacity_id);
        glUniformMatrix4fv(projection_id, 1, GL_FALSE, (f32*)&projection.m[0][0]);
        csp = 0;

        if(std < 6.75f)
        {
            if((std > 1.5f && std < 2.f) || (std > 2.5f && std < 3.f) || (std > 3.5f && std < 4.f))
            {
                glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&view.m[0][0]);
                glUniform3f(color_id, 0.89f, 0.f, 0.157f);
                modelBind1(&mdlRX);
                glDrawElements(GL_TRIANGLES, rx_numind, GL_UNSIGNED_BYTE, 0);
            }

            if((std > 4.5f && std < 4.75f) || (std > 5.f && std < 5.25f))
            {
                modelBind1(&mdlSA);

                mIdent(&model);
                mSetPos3(&model, -0.01f, 0.01f, 0.f);
                mMul(&modelview, &model, &view);
                glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
                glUniform3f(color_id, 0.f, 0.f, 0.f);
                glDrawElements(GL_TRIANGLES, sa_numind, GL_UNSIGNED_BYTE, 0);
                
                glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&view.m[0][0]);
                glUniform3f(color_id, 0.714f, 0.741f, 0.8f);
                glDrawElements(GL_TRIANGLES, sa_numind, GL_UNSIGNED_BYTE, 0);
            }

            if((std > 5.5f && std < 5.75f) || (std > 6.f && std < 6.75f))
            {
                f32 step = (std-6.25f)*2.f;
                if(step < 0.f){step = 0.f;}
                glUniform3f(color_id, 0.698f - (0.16859f * step), 0.667f + (0.14084f * step), 0.263f + (0.65857f * step));
                glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&view.m[0][0]);
                modelBind1(&mdlGA);
                glDrawElements(GL_TRIANGLES, ga_numind, GL_UNSIGNED_BYTE, 0);
            }
        }

        // render game over
        if(gameover > 0.f && t > gameover)
        {
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);

            modelBind1(&mdlPlane);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&view.m[0][0]);
            glUniform3f(color_id, 0.f, 0.f, 0.f);
            f32 opa = t-gameover;
            if(opa > 0.8f){opa = 0.8f;}
            glUniform1f(opacity_id, opa);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
            
            glUniform1f(opacity_id, 0.5f);
            modelBind1(&mdlGameover);

            mIdent(&model);
            mSetPos3(&model, -0.01f, 0.01f, 0.01f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
            glUniform3f(color_id, 0.f, 0.f, 0.f);
            glDrawElements(GL_TRIANGLES, gameover_numind, GL_UNSIGNED_SHORT, 0);

            mIdent(&model);
            mSetPos3(&model, 0.005f, -0.005f, -0.005f);
            mMul(&modelview, &model, &view);
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&modelview.m[0][0]);
            glUniform3f(color_id, 0.2f, 0.2f, 0.2f);
            glDrawElements(GL_TRIANGLES, gameover_numind, GL_UNSIGNED_SHORT, 0);

            const f32 ts = t*0.3f;
            glUniform3f(color_id, fabsf(cosf(ts)), fabsf(sinf(ts)), fabsf(cosf(ts)));
            glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*)&view.m[0][0]);
            glDrawElements(GL_TRIANGLES, gameover_numind, GL_UNSIGNED_SHORT, 0);
            
            glDisable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
            glUniform1f(opacity_id, 1.f);
        }
    }

//*************************************
// swap buffers / display render
//*************************************
#ifdef BUILD_GLFW
    glfwSwapBuffers(wnd);
#else
    SDL_GL_SwapWindow(wnd);
#endif
}

//*************************************
// GLFW Input Handelling
//*************************************
#ifdef BUILD_GLFW
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        if(inmotion == 0 && button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if(gameover > 0.f)
            {
                if(glfwGetTime() > gameover+3.0f)
                {
                    newGame();
                    if(PUSH_SPEED < 32.f)
                    {
                        PUSH_SPEED += 1.f;
                        MAX_PUSH_SPEED = PUSH_SPEED;
                        char titlestr[256];
                        sprintf(titlestr, "TuxPusherAF [%.1f]", PUSH_SPEED);
                        glfwSetWindowTitle(window, titlestr);
                    }
                }
                return;
            }
            takeStack();
            md = 1;
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            static uint cs = 1;
            cs = 1 - cs;
            if(cs == 0)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            else
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    else if(action == GLFW_RELEASE)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
            md = 0;
    }
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    winw = width;
    winh = height;

    glViewport(0, 0, winw, winh);
    ww = (double)winw;
    wh = (double)winh;
    if(ortho == 1){touch_margin = ww*0.3076923192f;}
    else{touch_margin = ww*0.2058590651f;}
    rww = 1.0/(ww-touch_margin*2.0);

    mIdent(&projection);

    if(ortho == 1)
        mOrtho(&projection, -5.0f, 5.0f, -3.2f, 3.4f, 0.01f, 320.f);
    else
    {
        if(winw > winh)
            aspect = ww / wh;
        else
            aspect = wh / ww;
        mPerspective(&projection, 30.0f, aspect, 0.1f, 320.f);
    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_F)
        {
            if(t-lfct > 2.0)
            {
                char strts[16];
                timestamp(&strts[0]);
                const double nfps = fc/(t-lfct);
                printf("[%s] FPS: %g\n", strts, nfps);
                lfct = t;
                fc = 0;
            }
        }
        else if(key == GLFW_KEY_C)
        {
            ortho = 1 - ortho;
            window_size_callback(window, winw, winh);
        }
    }
}
#endif

//*************************************
// Process Entry Point
//*************************************
#ifndef BUILD_GLFW
    #ifdef __EMSCRIPTEN__
    EM_BOOL emscripten_resize_event(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
    {
        winw = uiEvent->documentBodyClientWidth;
        winh = uiEvent->documentBodyClientHeight;
        doPerspective();
        return EM_FALSE;
    }
    EM_BOOL emscripten_mousemove_event(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
    {
        mx = (f32)mouseEvent->clientX;
        my = (f32)mouseEvent->clientY;
        return EM_FALSE;
    }

    EM_BOOL emscripten_touchmove_event(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData)
    {
        mx = (f32)touchEvent->touches[0].clientX;
        my = (f32)touchEvent->touches[0].clientY;
        return EM_FALSE;
    }

    EM_BOOL emscripten_touchend_event(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData)
    {
        mx = (f32)touchEvent->touches[0].clientX;
        my = (f32)touchEvent->touches[0].clientY;

        if(inmotion == 0)
        {
            if(gameover > 0.f)
            {
                if(f32Time() > gameover+3.0f)
                {
                    newGame();
                    if(PUSH_SPEED < 32.f)
                    {
                        PUSH_SPEED += 1.f;
                        MAX_PUSH_SPEED = PUSH_SPEED;
                        char titlestr[256];
                        sprintf(titlestr, "TuxPusherAF [%.1f]", PUSH_SPEED);
                        SDL_SetWindowTitle(wnd, titlestr);
                    }
                }
                return EM_FALSE;
            }
            takeStack();
            md = 1;
        }

        return EM_FALSE;
    }
    #else
    SDL_Surface* surfaceFromData(const Uint32* data, Uint32 w, Uint32 h)
    {
        SDL_Surface* s = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
        memcpy(s->pixels, data, s->pitch*h);
        return s;
    }
    #endif
void printAttrib(SDL_GLattr attr, char* name)
{
    int i;
    SDL_GL_GetAttribute(attr, &i);
    printf("%s: %i\n", name, i);
}
#endif
int main(int argc, char** argv)
{
    // allow custom msaa level
    int msaa = 16;
    if(argc >= 2){msaa = atoi(argv[1]);}

    // help
    printf("----\n");
    printf("TuxPusher & Friends (TuxPusher.com)\n");
    printf("In this case our \"friends\" are from LUMA GENIE (https://lumalabs.ai/genie)\n");
    printf("----\n");
    printf("James William Fletcher (github.com/mrbid)\n");
    printf("----\n");
#ifndef __EMSCRIPTEN__
    printf("Argv(2): msaa, speed\n");
    printf("e.g; ./uc 16 3.6\n");
    printf("----\n");
#endif
    printf("Left Click = Release coin (hold to auto-place silver coins)\n");
    printf("Right Click = Show/hide cursor\n");
    printf("C = Orthographic/Perspective\n");
#ifndef __EMSCRIPTEN__
    printf("F = FPS to console\n");
#endif
    printf("----\n");
    printf("Tux 3D model by Andy Cuccaro:\n");
    printf("https://andycuccaro.gumroad.com/\n");
    printf("----\n");
    printf("Fonts used in the End Game screen from top to bottom order:\n");
    printf("1. Fontasy Penguin by FontasyLand\n");
    printf("   https://www.fontspace.com/fontasy-penguin-font-f4848\n");
    printf("2. Plastic Love by Azkarizki\n");
    printf("   https://www.fontspace.com/plastic-love-font-f49676\n");
    printf("3. Allay Font by Abahrozi (https://twinletter.com/)\n");
    printf("   https://www.fontspace.com/allay-font-f66225\n");
    printf("----\n");
    printf("Rules:\n");
    printf("Getting a gold coin in a silver slot rewards you 2x silver coins.\n");
    printf("Getting a gold coin in a gold slot rewards you 2x gold coins.\n");
    printf("Getting a tux in a slot when you already have the tux gives you 6x gold coins and 6x silver coins.\n");
    printf("----\n");

#ifdef BUILD_GLFW
        // init glfw
        if(!glfwInit()){printf("glfwInit() failed.\n"); exit(EXIT_FAILURE);}
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_SAMPLES, msaa);
        wnd = glfwCreateWindow(winw, winh, appTitle, NULL, NULL);
        if(!wnd)
        {
            printf("glfwCreateWindow() failed.\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        const GLFWvidmode* desktop = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(wnd, (desktop->width/2)-(winw/2), (desktop->height/2)-(winh/2)); // center window on desktop
        glfwSetWindowSizeCallback(wnd, window_size_callback);
        glfwSetKeyCallback(wnd, key_callback);
        glfwSetMouseButtonCallback(wnd, mouse_button_callback);
        glfwMakeContextCurrent(wnd);
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(1); // 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync

        // set icon
        glfwSetWindowIcon(wnd, 1, &(GLFWimage){16, 16, (unsigned char*)icon_image});
#else
        // init sdl
        if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) < 0) // SDL_INIT_AUDIO
        {
            printf("ERROR: SDL_Init(): %s\n", SDL_GetError());
            return 1;
        }
    #ifdef __EMSCRIPTEN__
        double width, height;
        emscripten_get_element_css_size("body", &width, &height);
        winw = (uint)width, winh = (uint)height;
    #endif
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        wnd = SDL_CreateWindow(appTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winw, winh, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        while(wnd == NULL)
        {
            msaa--;
            if(msaa == 0)
            {
                printf("ERROR: SDL_CreateWindow(): %s\n", SDL_GetError());
                return 1;
            }
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa);
            wnd = SDL_CreateWindow(appTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winw, winh, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        }
        SDL_GL_SetSwapInterval(1); // 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync
        glc = SDL_GL_CreateContext(wnd);
        if(glc == NULL)
        {
            printf("ERROR: SDL_GL_CreateContext(): %s\n", SDL_GetError());
            return 1;
        }
        SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");

        // set cursors
        cross_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
        beam_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
        SDL_SetCursor(cross_cursor);

    #ifndef __EMSCRIPTEN__
        // set icon
        s_icon = surfaceFromData((Uint32*)icon_image, 16, 16);
        SDL_SetWindowIcon(wnd, s_icon);
    #endif
#endif

    // set game push speed
    PUSH_SPEED = 3.6f;
    if(argc >= 3)
    {
        PUSH_SPEED = atof(argv[2]);
        if(PUSH_SPEED > 32.f){PUSH_SPEED = 32.f;}
        char titlestr[256];
        sprintf(titlestr, "TuxPusherAF [%.1f]", PUSH_SPEED);
#ifdef BUILD_GLFW
        glfwSetWindowTitle(wnd, titlestr);
#else
        SDL_SetWindowTitle(wnd, titlestr);
#endif
    }

    // debug (cant do this on ES unless >= ES 3.2)
#if defined(GL_DEBUG) && !defined(__MINGW32__) // no need to debug the windows release
    esDebug(1);
#endif

#ifndef BUILD_GLFW
    // dump some info
    printAttrib(SDL_GL_DOUBLEBUFFER, "GL_DOUBLEBUFFER");
    printAttrib(SDL_GL_DEPTH_SIZE, "GL_DEPTH_SIZE");
    printAttrib(SDL_GL_RED_SIZE, "GL_RED_SIZE");
    printAttrib(SDL_GL_GREEN_SIZE, "GL_GREEN_SIZE");
    printAttrib(SDL_GL_BLUE_SIZE, "GL_BLUE_SIZE");
    printAttrib(SDL_GL_ALPHA_SIZE, "GL_ALPHA_SIZE");
    printAttrib(SDL_GL_BUFFER_SIZE, "GL_BUFFER_SIZE");
    printAttrib(SDL_GL_STENCIL_SIZE, "GL_STENCIL_SIZE");
    printAttrib(SDL_GL_ACCUM_RED_SIZE, "GL_ACCUM_RED_SIZE");
    printAttrib(SDL_GL_ACCUM_GREEN_SIZE, "GL_ACCUM_GREEN_SIZE");
    printAttrib(SDL_GL_ACCUM_BLUE_SIZE, "GL_ACCUM_BLUE_SIZE");
    printAttrib(SDL_GL_ACCUM_ALPHA_SIZE, "GL_ACCUM_ALPHA_SIZE");
    printAttrib(SDL_GL_STEREO, "GL_STEREO");
    printAttrib(SDL_GL_MULTISAMPLEBUFFERS, "GL_MULTISAMPLEBUFFERS");
    printAttrib(SDL_GL_MULTISAMPLESAMPLES, "GL_MULTISAMPLESAMPLES");
    printAttrib(SDL_GL_ACCELERATED_VISUAL, "GL_ACCELERATED_VISUAL");
    printAttrib(SDL_GL_RETAINED_BACKING, "GL_RETAINED_BACKING");
    printAttrib(SDL_GL_CONTEXT_MAJOR_VERSION, "GL_CONTEXT_MAJOR_VERSION");
    printAttrib(SDL_GL_CONTEXT_MINOR_VERSION, "GL_CONTEXT_MINOR_VERSION");
    printAttrib(SDL_GL_CONTEXT_FLAGS, "GL_CONTEXT_FLAGS");
    printAttrib(SDL_GL_CONTEXT_PROFILE_MASK, "GL_CONTEXT_PROFILE_MASK");
    printAttrib(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, "GL_SHARE_WITH_CURRENT_CONTEXT");
    printAttrib(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, "GL_FRAMEBUFFER_SRGB_CAPABLE");
    printAttrib(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, "GL_CONTEXT_RELEASE_BEHAVIOR");
    printAttrib(SDL_GL_CONTEXT_EGL, "GL_CONTEXT_EGL");

    printf("----\n");
    
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("Compiled against SDL version %u.%u.%u.\n", compiled.major, compiled.minor, compiled.patch);
    printf("Linked against SDL version %u.%u.%u.\n", linked.major, linked.minor, linked.patch);

    printf("----\n");
#else
    printf("%s\n", glfwGetVersionString());
    printf("----\n");
#endif

//*************************************
// bind vertex and index buffers
//*************************************

    // ***** PLANE *****
    const GLfloat plane_vert[] = {13,0,-13, -13,0,13, -13,0,-13, 13,0,13};
    const GLubyte plane_indi[] = {0,1,2,0,3,1};
    esBind(GL_ARRAY_BUFFER, &mdlPlane.vid, plane_vert, sizeof(plane_vert), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlPlane.iid, plane_indi, sizeof(plane_indi), GL_STATIC_DRAW);

    // ***** BIND SCENE *****
    esBind(GL_ARRAY_BUFFER, &mdlScene.cid, scene_colors, sizeof(scene_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlScene.vid, scene_vertices, sizeof(scene_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlScene.nid, scene_normals, sizeof(scene_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlScene.iid, scene_indices, sizeof(scene_indices), GL_STATIC_DRAW);

    // ***** BIND GAMEOVER *****
    esBind(GL_ARRAY_BUFFER, &mdlGameover.vid, gameover_vertices, sizeof(gameover_vertices), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlGameover.iid, gameover_indices, sizeof(gameover_indices), GL_STATIC_DRAW);

    // ***** BIND COIN *****
    esBind(GL_ARRAY_BUFFER, &mdlCoin.cid, coin_colors, sizeof(coin_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlCoin.vid, coin_vertices, sizeof(coin_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlCoin.nid, coin_normals, sizeof(coin_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlCoin.iid, coin_indices, sizeof(coin_indices), GL_STATIC_DRAW);

    // ***** BIND COIN SILVER *****
    esBind(GL_ARRAY_BUFFER, &mdlCoinSilver.cid, coin_silver_colors, sizeof(coin_silver_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlCoinSilver.vid, coin_silver_vertices, sizeof(coin_silver_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlCoinSilver.nid, coin_silver_normals, sizeof(coin_silver_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlCoinSilver.iid, coin_silver_indices, sizeof(coin_silver_indices), GL_STATIC_DRAW);

    // ***** BIND TUX *****
    esBind(GL_ARRAY_BUFFER, &mdlTux.cid, tux_colors, sizeof(tux_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlTux.vid, tux_vertices, sizeof(tux_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlTux.nid, tux_normals, sizeof(tux_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlTux.iid, tux_indices, sizeof(tux_indices), GL_STATIC_DRAW);

    // ***** BIND TUX - EVIL *****
    esBind(GL_ARRAY_BUFFER, &mdlEvil.cid, evil_colors, sizeof(evil_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlEvil.vid, evil_vertices, sizeof(evil_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlEvil.nid, evil_normals, sizeof(evil_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlEvil.iid, evil_indices, sizeof(evil_indices), GL_STATIC_DRAW);

    // ***** BIND TUX - KING *****
    esBind(GL_ARRAY_BUFFER, &mdlKing.cid, king_colors, sizeof(king_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlKing.vid, king_vertices, sizeof(king_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlKing.nid, king_normals, sizeof(king_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlKing.iid, king_indices, sizeof(king_indices), GL_STATIC_DRAW);

    // ***** BIND TUX - NINJA *****
    esBind(GL_ARRAY_BUFFER, &mdlNinja.cid, ninja_colors, sizeof(ninja_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlNinja.vid, ninja_vertices, sizeof(ninja_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlNinja.nid, ninja_normals, sizeof(ninja_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlNinja.iid, ninja_indices, sizeof(ninja_indices), GL_STATIC_DRAW);

    // ***** BIND TUX - SURF *****
    esBind(GL_ARRAY_BUFFER, &mdlSurf.cid, surf_colors, sizeof(surf_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlSurf.vid, surf_vertices, sizeof(surf_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlSurf.nid, surf_normals, sizeof(surf_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlSurf.iid, surf_indices, sizeof(surf_indices), GL_STATIC_DRAW);

    // ***** BIND TUX - TRIP *****
    esBind(GL_ARRAY_BUFFER, &mdlTrip.cid, trip_colors, sizeof(trip_colors), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlTrip.vid, trip_vertices, sizeof(trip_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlTrip.nid, trip_normals, sizeof(trip_normals), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlTrip.iid, trip_indices, sizeof(trip_indices), GL_STATIC_DRAW);

    // ***** BIND SCENE PROP - RED X *****
    esBind(GL_ARRAY_BUFFER, &mdlRX.vid, rx_vertices, sizeof(rx_vertices), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlRX.iid, rx_indices, sizeof(rx_indices), GL_STATIC_DRAW);

    // ***** BIND SCENE PROP - SILVER ARROW *****
    esBind(GL_ARRAY_BUFFER, &mdlSA.vid, sa_vertices, sizeof(sa_vertices), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlSA.iid, sa_indices, sizeof(sa_indices), GL_STATIC_DRAW);

    // ***** BIND SCENE PROP - GOLD ARROW *****
    esBind(GL_ARRAY_BUFFER, &mdlGA.vid, ga_vertices, sizeof(ga_vertices), GL_STATIC_DRAW);
    esBind(GL_ELEMENT_ARRAY_BUFFER, &mdlGA.iid, ga_indices, sizeof(ga_indices), GL_STATIC_DRAW);

    // lol and all the friends ...
    register_f0();register_f1();register_f2();register_f3();register_f4();register_f5();
    register_f6();register_f7();register_f8();register_f9();register_f10();register_f11();
    register_f12();register_f13();register_f14();register_f15();register_f16();register_f17();
    register_f18();register_f19();register_f20();register_f21();register_f22();register_f23();
    register_f24();register_f25();register_f26();register_f27();register_f28();register_f29();
    register_f30();register_f31();register_f32();register_f33();register_f34();register_f35();
    register_f36();register_f37();register_f38();register_f39();register_f40();register_f41();
    register_f42();register_f43();register_f44();register_f45();register_f46();register_f47();
    register_f48();register_f49();register_f50();register_f51();register_f52();register_f53();
    register_f54();register_f55();register_f56();register_f57();register_f58();register_f59();
    register_f60();register_f61();register_f62();register_f63();register_f64();register_f65();
    register_f66();register_f67();register_f68();register_f69();register_f70();register_f71();
    register_f72();register_f73();register_f74();register_f75();register_f76();register_f77();
    register_f78();register_f79();register_f80();register_f81();register_f82();register_f83();
    register_f84();register_f85();register_f86();register_f87();register_f88();register_f89();
    register_f90();register_f91();register_f92();register_f93();register_f94();register_f95();
    register_f96();register_f97();register_f98();register_f99();register_f100();register_f101();
    register_f102();register_f103();register_f104();register_f105();register_f106();register_f107();
    register_f108();register_f109();register_f110();register_f111();register_f112();register_f113();
    register_f114();register_f115();register_f116();register_f117();register_f118();register_f119();
    register_f120();register_f121();register_f122();register_f123();register_f124();register_f125();
    register_f126();register_f127();register_f128();register_f129();register_f130();register_f131();
    register_f132();register_f133();register_f134();register_f135();register_f136();register_f137();
    register_f138();register_f139();register_f140();register_f141();register_f142();register_f143();
    register_f144();register_f145();register_f146();register_f147();register_f148();register_f149();
    register_f150();register_f151();register_f152();register_f153();register_f154();register_f155();
    register_f156();register_f157();register_f158();register_f159();register_f160();register_f161();
    register_f162();register_f163();register_f164();register_f165();register_f166();register_f167();
    register_f168();register_f169();register_f170();register_f171();register_f172();register_f173();
    register_f174();register_f175();register_f176();register_f177();register_f178();register_f179();
    register_f180();register_f181();register_f182();register_f183();register_f184();register_f185();
    register_f186();register_f187();register_f188();register_f189();register_f190();register_f191();
    register_f192();register_f193();register_f194();register_f195();register_f196();register_f197();
    register_f198();register_f199();register_f200();register_f201();register_f202();register_f203();
    register_f204();register_f205();register_f206();register_f207();register_f208();register_f209();
    register_f210();register_f211();register_f212();register_f213();register_f214();register_f215();
    register_f216();register_f217();register_f218();register_f219();register_f220();register_f221();
    register_f222();register_f223();register_f224();register_f225();register_f226();register_f227();
    register_f228();register_f229();register_f230();register_f231();register_f232();register_f233();
    register_f234();register_f235();register_f236();register_f237();register_f238();register_f239();
    register_f240();register_f241();register_f242();register_f243();register_f244();register_f245();
    register_f246();register_f247();register_f248();register_f249();register_f250();register_f251();
    register_f252();register_f253();register_f254();register_f255();register_f256();register_f257();
    register_f258();register_f259();register_f260();register_f261();register_f262();register_f263();
    register_f264();register_f265();register_f266();register_f267();register_f268();register_f269();
    register_f270();register_f271();register_f272();register_f273();register_f274();register_f275();
    register_f276();register_f277();register_f278();register_f279();register_f280();register_f281();
    register_f282();register_f283();register_f284();register_f285();register_f286();register_f287();
    register_f288();register_f289();register_f290();register_f291();register_f292();register_f293();
    register_f294();register_f295();register_f296();register_f297();register_f298();register_f299();
    register_f300();register_f301();register_f302();register_f303();register_f304();register_f305();
    register_f306();register_f307();register_f308();register_f309();register_f310();register_f311();
    register_f312();register_f313();register_f314();register_f315();register_f316();register_f317();
    register_f318();register_f319();register_f320();register_f321();register_f322();register_f323();
    register_f324();register_f325();register_f326();register_f327();register_f328();register_f329();
    register_f330();register_f331();register_f332();register_f333();register_f334();register_f335();
    register_f336();register_f337();register_f338();register_f339();register_f340();register_f341();
    register_f342();register_f343();register_f344();register_f345();register_f346();register_f347();
    register_f348();register_f349();register_f350();register_f351();register_f352();register_f353();
    register_f354();register_f355();register_f356();register_f357();register_f358();register_f359();
    register_f360();register_f361();register_f362();register_f363();register_f364();register_f365();
    register_f366();register_f367();register_f368();register_f369();register_f370();register_f371();
    register_f372();register_f373();register_f374();register_f375();register_f376();register_f377();
    register_f378();register_f379();register_f380();register_f381();register_f382();register_f383();
    register_f384();register_f385();register_f386();register_f387();register_f388();register_f389();
    register_f390();register_f391();register_f392();register_f393();register_f394();register_f395();
    register_f396();register_f397();register_f398();register_f399();register_f400();register_f401();
    register_f402();register_f403();register_f404();register_f405();register_f406();register_f407();
    register_f408();register_f409();register_f410();register_f411();register_f412();register_f413();
    register_f414();register_f415();register_f416();register_f417();register_f418();register_f419();
    register_f420();register_f421();register_f422();register_f423();register_f424();register_f425();
    register_f426();register_f427();register_f428();register_f429();register_f430();register_f431();
    register_f432();register_f433();register_f434();register_f435();register_f436();register_f437();
    register_f438();register_f439();register_f440();register_f441();register_f442();register_f443();
    register_f444();register_f445();register_f446();register_f447();register_f448();register_f449();
    register_f450();register_f451();register_f452();register_f453();register_f454();register_f455();
    register_f456();register_f457();register_f458();register_f459();register_f460();register_f461();
    register_f462();register_f463();register_f464();register_f465();register_f466();register_f467();
    register_f468();register_f469();register_f470();register_f471();register_f472();register_f473();
    register_f474();register_f475();register_f476();register_f477();register_f478();register_f479();
    register_f480();register_f481();register_f482();register_f483();register_f484();register_f485();
    register_f486();register_f487();register_f488();register_f489();register_f490();register_f491();
    register_f492();register_f493();register_f494();register_f495();register_f496();register_f497();
    register_f498();register_f499();register_f500();register_f501();register_f502();register_f503();
    register_f504();register_f505();register_f506();register_f507();register_f508();register_f509();
    register_f510();register_f511();register_f512();register_f513();register_f514();

//*************************************
// compile & link shader program
//*************************************
    makeFullbright();
    makeLambert3();

//*************************************
// configure render options
//*************************************
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.52941f, 0.80784f, 0.92157f, 0.0f);

//*************************************
// execute update / render loop
//*************************************

    // projection
#ifdef BUILD_GLFW
    window_size_callback(wnd, winw, winh);
#else
    doPerspective();
#endif

    // new game
    newGame();
#ifndef __EMSCRIPTEN__
    lfct = t;
#endif

    // event loop
#ifdef BUILD_GLFW
    while(!glfwWindowShouldClose(wnd))
    {
        glfwPollEvents();
        main_loop();
    }
#else
    #ifdef __EMSCRIPTEN__
        emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, emscripten_resize_event);
        emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, emscripten_mousemove_event);
        emscripten_set_touchmove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, emscripten_touchmove_event);
        emscripten_set_touchend_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, emscripten_touchend_event);
        emscripten_set_main_loop(main_loop, 0, 1);
    #else
        while(1){main_loop();}
    #endif
#endif

    return 0;
}

