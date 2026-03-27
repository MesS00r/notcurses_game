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
        .cols = 10,
        .rows = 2,
        .name = "debug",

        .bg_rgb = 0xffffff,
        .fg_rgb = 0x000000
    };
    DebugPlane *debug_p = debug_plane_init(&d_opts, stdplane);
    if (!debug_p) {
        fprintf(stderr, "Debug plane is not initialized");
        return EXIT_FAILURE;
    }
    world_set_debug_plane(world, debug_plane_get_plane(debug_p));

    uint32_t key;
    uint32_t rows, cols;

    const char *hello;
    uint32_t x, y;

    while(true) {
        ncplane_erase(stdplane);

        key = world_getch(world);
        
        world_debug_plane_prerender(world, key, world_what_mod(world, NCKEY_MOD_CTRL));

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