/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps               = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int borderpx         = 4;  /* border pixel of windows */
static const unsigned int gappih           = 10; /* horiz inner gap between windows */
static const unsigned int gappiv           = 10; /* vert inner gap between windows */
static const unsigned int gappoh           = 10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 10; /* vert outer gap between windows and screen edge */
static const float rootcolor[]             = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[]           = {0.16, 0.16, 0.21, 1.0};
static const float focuscolor[]            = {0.54, 0.56, 0.66, 1.0};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1, 0.1, 0.1, 1.0};

/* autostart */
static const char *const autostart[] = {
        /* "someblocks", NULL, */
        "chromium", NULL,
        "discord", NULL,
        "/home/r2d2/.wl-profile-post", NULL,
        NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "3", "4", "5", "6", "7", "8", "󰙯" };

static const Rule rules[] = {
        /* app_id     		title       tags mask     isfloating   monitor */
        { "Foot",      	        NULL,       1 << 1,       0,           -1 },
        { "Chromium",  	        NULL,       1 << 0,       0,           -1 },
        { "discord",        	NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL    -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER 
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
/*#define MODKEY WLR_MODIFIER_ALT*/
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                                      KEY,  view,       {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,                    KEY,  toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT,                   SKEY, tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, SKEY, toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define VOLCTRL(dir, step)   { .v = (const char*[]){ "pamixer", "--allow-boost", (dir == '+') ? "-i" : "-d", step, NULL } }
#define AUDIOCTRL(cmd) { .v = (const char*[]){ "/usr/bin/playerctl", cmd, NULL } }
#define BRGCTRL(amt)   { .v = (const char*[]){ "/usr/bin/brightnessctl", "set", amt, NULL } }

/* commands */
static const char *termcmd[]    = { "foot", NULL };
static const char *menucmd[]    = { "bemenu-run", NULL };
static const char *suspendcmd[] = { "systemctl", "suspend", NULL };
static const char *lockcmd[]    = { "waylock", NULL };
static const char *webcmd[]     = { "chromium", NULL };
static const char *snippet[]    = { "snippet", "0", NULL};
static const char *mutevol[]    = { "pamixer", "-t", NULL };
static const char *audioconf[]    = { "setsid", "-f", "foot", "-e" , "pulsemixer", NULL };

#include "shiftview.c"

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                            function        argument */
	
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                                0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                                    1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                            2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                                3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                               4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                           5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                             6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                              7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                             8),

    { MODKEY,                    XKB_KEY_q,                     killclient,     {0} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,                     spawn,          {.v = lockcmd} },
	
    { MODKEY,                    XKB_KEY_w,                     spawn,          {.v = webcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_W,                     spawn,          {.v = suspendcmd} },

    /* { MODKEY,                    XKB_KEY_e,                     togglefullscreen, {0} }, */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_E,                     quit,           {0} },

    /* { MODKEY,                 XKB_KEY_r,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_R,                     spawn,          {0} }, */
    /* { MODKEY,                 XKB_KEY_t,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_T,                     spawn,          {0} }, */

    { MODKEY,                    XKB_KEY_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_T,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_y,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Y,                     setlayout,      {0} },

    /* { MODKEY,                 XKB_KEY_u,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_U,                     spawn,          {0} }, */
    /* { MODKEY,                 XKB_KEY_i,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_I,                     spawn,          {0} }, */

    { MODKEY,                    XKB_KEY_o,                     incnmaster,     {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_O,                     incnmaster,     {.i = +1} },

    /* { MODKEY,                    XKB_KEY_p,                     spawn,          {.v = menucmd} }, */
	/* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_P,     	            spawn,          {.v = suspendcmd} }, */

	{ MODKEY,                 XKB_KEY_a,                     spawn,          {.v = audioconf} },
	/* { MODKEY,                 XKB_KEY_A,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_s,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_S,                     spawn,          {0} }, */

    { MODKEY,                    XKB_KEY_d,                     spawn,          {.v = menucmd} },
	/* { MODKEY,                    XKB_KEY_D,                     spawn,          {.v = discordcmd} }, */

    { MODKEY,                    XKB_KEY_f,                     togglefullscreen, {0} },
    /* { MODKEY,                    XKB_KEY_F,                     togglefullscreen, {0} }, */

    /* { MODKEY,                 XKB_KEY_g,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_G,                     spawn,          {0} }, */

    { MODKEY,                    XKB_KEY_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_H,                     shiftview,      { .i = -1 } },
    { MODKEY,                    XKB_KEY_j,                     focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,                     focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_L,                     shiftview,      { .i = 1 } },

	{ MODKEY,                    XKB_KEY_z,                     incgaps,        {.i = +1 } },
	/* { MODKEY,                 XKB_KEY_Z,                     spawn,          {0} }, */
	{ MODKEY,                    XKB_KEY_x,                     incgaps,        {.i = -1 } },
	/* { MODKEY,                 XKB_KEY_X,                     spawn,          {0} }, */
    /* { MODKEY,                 XKB_KEY_c,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_C,                     spawn,          {0} }, */
    /* { MODKEY,                 XKB_KEY_v,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_V,                     spawn,          {0} }, */
    /* { MODKEY,                 XKB_KEY_b,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_B,                     spawn,          {0} }, */
    /* { MODKEY,                 XKB_KEY_n,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_N,                     spawn,          {0} }, */
    /* { MODKEY,                 XKB_KEY_m,                     spawn,          {0} }, */
	/* { MODKEY,                 XKB_KEY_M,                     spawn,          {0} }, */

	{ MODKEY,                    XKB_KEY_Return,                spawn,          {.v = termcmd} },

	{ MODKEY,                    XKB_KEY_Left,                  shiftview,      { .i = -1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Left,                  tagmon,         { .i = -1 } },
	{ MODKEY,                    XKB_KEY_Right,                 shiftview,      { .i = 1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Right,                 tagmon,         { .i = 1 } },

    { MODKEY,                    XKB_KEY_Tab,                   view,           {0} },
	{ MODKEY,                    XKB_KEY_BackSpace,             togglefloating, {0} },
    { MODKEY,                    XKB_KEY_space,                 zoom,           {0} },
	{ MODKEY,                    XKB_KEY_backslash,             defaultgaps,    {0} },

	/* { MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_h,                     incgaps,        {.i = +1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_l,                     incgaps,        {.i = -1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,              XKB_KEY_H,      incogaps,      {.i = +1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,              XKB_KEY_L,      incogaps,      {.i = -1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_CTRL,               XKB_KEY_h,      incigaps,      {.i = +1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_CTRL,               XKB_KEY_l,      incigaps,      {.i = -1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_0,                     togglegaps,     {0} }, */
	/* { MODKEY,                    XKB_KEY_y,                     incihgaps,     {.i = +1 } }, */
	/* { MODKEY,                    XKB_KEY_o,                     incihgaps,     {.i = -1 } }, */
	/* { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_y,                     incivgaps,     {.i = +1 } }, */
	/* { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_o,                     incivgaps,     {.i = -1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_y,                     incohgaps,     {.i = +1 } }, */
	/* { MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_o,                     incohgaps,     {.i = -1 } }, */
	/* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Y,                     incovgaps,     {.i = +1 } }, */
	/* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_O,                     incovgaps,     {.i = -1 } }, */
    /* { MODKEY,                    XKB_KEY_Up,                    movekeyboard,   {.v = "0x -25y 0w 0h"} }, */
    /* { MODKEY,                    XKB_KEY_Down,                  movekeyboard,   {.v = "0x 25y 0w 0h"} }, */
    /* { MODKEY,                    XKB_KEY_Left,                  movekeyboard,   {.v = "-25x 0y 0w 0h"} }, */
    /* { MODKEY,                    XKB_KEY_Right,                 movekeyboard,   {.v = "25x 0y 0w 0h"} }, */
    /* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Up,                    movekeyboard,   {.v = "0x 0y 0w -25h"} }, */
    /* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Down,                  movekeyboard,   {.v = "0x 0y 0w 25h"} }, */
    /* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Left,                  movekeyboard,   {.v = "0x 0y -25w 0h"} }, */
    /* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Right,                 movekeyboard,   {.v = "0x 0y 25w 0h"} }, */
	{ MODKEY,                    XKB_KEY_0,                     view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,            tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,                 focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,                focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,                  tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,               tagmon,         {.i = WLR_DIRECTION_RIGHT} },

	/* MEDIA */
	{ 0,                         XKB_KEY_Print,                 spawn,          {.v = snippet } },
	{ 0,                         XKB_KEY_XF86AudioMute,         spawn,          {.v = mutevol } },
	{ 0,                         XKB_KEY_XF86AudioLowerVolume,  spawn,    VOLCTRL('-',"5") },
	{ 0,                         XKB_KEY_XF86AudioRaiseVolume,  spawn,    VOLCTRL('+',"5") },
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_XF86AudioLowerVolume,  spawn,    VOLCTRL('-',"1") },
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_XF86AudioRaiseVolume,  spawn,    VOLCTRL('+',"1") },
	/* { 0,                         XKB_KEY_F1,                    spawn,    AUDIOCTRL("previous") }, */
	/* { 0,                         XKB_KEY_F2,                    spawn,    AUDIOCTRL("next") }, */
	/* { 0,                         XKB_KEY_F1,                    spawn,    AUDIOCTRL("previous") }, */

    /* // { MODKEY,                 XK_Escape,                     spawn,    AUDIOCTRL("play-pause") }, */
	/* { MODKEY,                    XKB_KEY_Escape,                spawn,    SHCMD("~/scripts/media-toggle.sh") }, */
	/* /1* FN *1/ */
	/* { MODKEY,                    XKB_KEY_l,                     spawn,    SHCMD("xautolock -locknow") }, */
	{ 0,                         XKB_KEY_XF86MonBrightnessDown, spawn,    BRGCTRL("10%-") },
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_XF86MonBrightnessDown, spawn,    BRGCTRL("5%-") },
	{ 0,                         XKB_KEY_XF86MonBrightnessUp,   spawn,    BRGCTRL("+10%") },
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_XF86MonBrightnessUp,   spawn,    BRGCTRL("+5%") },
	/* { 0,                         XKB_KEY_XF86Calculator,        spawn,    SHCMD("$CALCULATOR") }, */

	/* { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_S,                spawn,    SHCMD("~/scripts/screenshot.sh") }, */

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
