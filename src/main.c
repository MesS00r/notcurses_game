#include <locale.h>
#include <signal.h>
#include <notcurses/notcurses.h>
#include <gamelib/world.h>

#define TIMEOUT_MS 50

int main(void) {
    setlocale(LC_ALL, "");

    struct notcurses_options opts = {
        .flags = NCOPTION_NO_QUIT_SIGHANDLERS 
    };
    World *world = world_init(&opts);
    if (!world) {
        fprintf(stderr, "World is not initialized");
        return EXIT_FAILURE;
    }

    world_set_timeout(world, TIMEOUT_MS);
    struct ncplane *stdplane = world_get_stdplane(world);

    signal(SIGINT, SIG_IGN);

    DebugOptions d_opts = {
        .cols = 15,
        .rows = 7,
        .name = "debug",

        .bg_rgb = 0xffffff,
        .fg_rgb = 0x000000
    };
    DebugPlane *debug_p = debug_plane_init(&d_opts, stdplane);
    if (!debug_p) {
        fprintf(stderr, "Debug plane is not initialized");
        return EXIT_FAILURE;
    }
    world_set_debug_plane(world, debug_p);

    uint32_t key;
    uint32_t rows, cols;

    const char *hello;
    uint32_t x, y;

    while(true) {
        ncplane_erase(stdplane);

        key = world_getch(world);
        
        world_debug_plane_prerender(world);

        if (key == 'q' || key == NCKEY_SIGNAL) break;
        if ((key == 'c' || key == 'C') && world_what_mod(world, NCKEY_MOD_CTRL)) break;

        world_read_term_size(world, &rows, &cols);

        hello = "hello world!!!";
        x = (cols - (uint32_t)strlen(hello)) / 2;
        y = rows / 2;
        ncplane_putstr_yx(stdplane, y, x, hello);
        
        world_render(world);
    }

    world_destroy(world);
    return EXIT_SUCCESS;
}

// #include <locale.h>
// #include <signal.h>
// #include <notcurses/notcurses.h>

// #define TIMEOUT_MS 50

// int main(void) {
//     setlocale(LC_ALL, "");

//     struct notcurses_options opt = {
//         .flags = NCOPTION_NO_QUIT_SIGHANDLERS 
//     };
//     struct notcurses *nc = notcurses_init(&opt, NULL);
//     if (!nc) return EXIT_FAILURE;
    
//     signal(SIGINT, SIG_IGN);

//     struct ncplane *stdscr = notcurses_stdplane(nc);
//     struct ncinput ni = {};
//     struct timespec timeout = {
//         .tv_sec = 0,
//         .tv_nsec = TIMEOUT_MS * 1000000
//     };

//     uint64_t channels = 0;
//     ncchannels_set_bg_rgb(&channels, 0xff5f00);
//     ncchannels_set_fg_rgb(&channels, 0xffffff);
//     ncplane_set_base(stdscr, ".", 0, channels);
//     ncplane_set_styles(stdscr, NCSTYLE_BOLD);

//     uint32_t key;
//     uint32_t rows, cols;

//     const char *hello;
//     uint32_t x, y;

//     uint32_t last_key = 0;
//     bool last_ctrl = false;

//     while(true) {
//         key = notcurses_get(nc, &timeout, &ni);

//         if (key == 'q' || key == NCKEY_SIGNAL) break;
//         if ((key == 'c' || key == 'C') && ni.ctrl) break;

//         if (key > 0) {
//             last_key = key;
//             last_ctrl = ni.modifiers & NCKEY_MOD_CTRL;
//         }

//         ncplane_erase(stdscr);
//         notcurses_term_dim_yx(nc, &rows, &cols);

//         if (last_key != 0) {
//             ncplane_printf_yx(stdscr, 0, 0, "Key ID: %u ", last_key);
//             ncplane_printf_yx(stdscr, 1, 0, "Ctrl: %s ", last_ctrl ? "YES" : "NO");
//         }

//         hello = "hello world!!!";
//         x = (uint32_t)(cols - strlen(hello))/2;
//         y = rows/2;
//         ncplane_putstr_yx(stdscr, y, x, hello);
    
//         notcurses_render(nc);
//     }

//     notcurses_stop(nc);
//     return EXIT_SUCCESS;
// }