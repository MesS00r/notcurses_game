#include <locale.h>
#include <signal.h>
#include <notcurses/notcurses.h>

#define TIMEOUT_MS 50

int main(void) {
    setlocale(LC_ALL, "");

    struct notcurses_options opt = {
        .flags = NCOPTION_NO_QUIT_SIGHANDLERS 
    };
    struct notcurses *nc = notcurses_init(&opt, NULL);
    if (!nc) return EXIT_FAILURE;
    
    signal(SIGINT, SIG_IGN);

    struct ncplane *stdscr = notcurses_stdplane(nc);
    struct ncinput ni = {};
    struct timespec timeout = {
        .tv_sec = 0,
        .tv_nsec = TIMEOUT_MS * 1000000
    };

    uint64_t channels = 0;
    ncchannels_set_bg_rgb(&channels, 0xff5f00);
    ncchannels_set_fg_rgb(&channels, 0xffffff);
    ncplane_set_base(stdscr, ".", 0, channels);
    ncplane_set_styles(stdscr, NCSTYLE_BOLD);

    uint32_t key;
    uint32_t rows, cols;

    const char *hello;
    uint32_t x, y;

    while(true) {
        ncplane_erase(stdscr);

        key = notcurses_get(nc, &timeout, &ni);

        if (key == 'q' || key == NCKEY_SIGNAL) break;
        if ((key == 'c' || key == 'C') && ni.ctrl) break;

        notcurses_term_dim_yx(nc, &rows, &cols);

        if (key != (uint32_t)-1) {
            ncplane_printf_yx(stdscr, 0, 0, "Key ID: %u ", key);
            ncplane_printf_yx(stdscr, 1, 0, "Ctrl: %s ", ni.ctrl ? "YES" : "NO");
        }

        hello = "hello world!!!";
        x = (cols - (uint32_t)strlen(hello)) / 2;
        y = rows / 2;
        ncplane_printf_yx(stdscr, y, x, "%s", hello);
        
        notcurses_render(nc);
    }

    notcurses_stop(nc);
    return EXIT_SUCCESS;
}