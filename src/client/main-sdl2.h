/* File: main-sdl2.h */
/* Purpose: SDL2 frontend header file for mangband */
/* Original SDL2 written by "kts of kettek (kettek1@kettek.net)". */

#include <SDL.h>

/* forward declarations */
typedef struct FontData FontData;
typedef struct PictData PictData;
typedef struct TermData TermData;
/* defines/constants */
#define TERM_MAIN 0
#define TERM_MIRROR 1
#define TERM_RECALL 2
#define TERM_CHOICE 3
#define TERM_CHAT 4
#define TERM_MAX 8

// MMM BEGIN: our "special" SDL2 menu system, take note it can be removed fairly easily!
static int menu_mode, menu_term;
static int menu_x, menu_y;
#define MENU_HIDE 0
#define MENU_SHOW 1
static errr renderMenu(TermData *td);
static errr handleMenu(int i, int x, int y);
// MMM END

/* main hooks */
extern errr init_sdl2(void);
extern void quit_sdl2(cptr s);

/* hook declarations */
static errr xtraTermHook(int n, int v);
static errr cursTermHook(int x, int y);
static errr wipeTermHook(int x, int y, int n);
static errr textTermHook(int x, int y, int n, byte attr, cptr s);
static errr pictTermHook(int x, int y, int n, const byte *ap, const char *ch, const byte *tap, const char *tcp);
static void initTermHook(term *t);
static void nukeTermHook(term *t);
/* declarations */
struct FontData {
  cptr filename;       // The filename of this font
  SDL_Surface *surface; // surface of all glyphs
  Uint8 w, h;           // dimensions of character
  int scalable;         // if we can scale this font
};
struct PictData {
  cptr filename;       // The filename of this pict
  SDL_Surface *surface; // surface of sprites
  Uint8 w, h;           // dimensions of each sprite
};
#define TERM_LOCK_CELLS  (1 << 0)  // Do not allow the terminal's rows/cols to be resized
#define TERM_LOCK_RATIO  (1 << 1)  // Force resizes to maintain original ratio of width/height
#define TERM_LOCK_SIZE   (1 << 2)  // Do not allow the window to be resized
#define TERM_DO_SCALE    (1 << 3)  // Scale the renderer
#define TERM_DO_STRETCH  (1 << 4)  //
#define TERM_IS_ONLINE   (1 << 5)  // Term is online
#define TERM_IS_VIRTUAL  (1 << 6)  // Term is virtual and uses term[TERM_MAIN]'s window/renderer
#define TERM_IS_HIDDEN   (1 << 7)  // Whether or not the term should be shown or not
#define TERM_FONT_SMOOTH (1 << 8)  // whether to use font smoothing
// font/pict display modes
#define TERM_CELL_FONT 0      // Cell sizings are based on font sizes
#define TERM_CELL_PICT 1      // Cell sizings are based on pict sizes
#define TERM_CELL_CUST 2      // Cell sizings use orig_w&orig_h, derived from INI file
#define TERM_PICT_STRETCH 0   // Pict rendering stretches to fit the cell
#define TERM_PICT_SCALE 1     // Pict rendering scales to fit the cell
#define TERM_PICT_STATIC 2    // Pict rendering uses the static size
#define TERM_CHAR_SCALE 0     // Text rendering scales to fit the cell
#define TERM_CHAR_STATIC 1    // Text rendering uses the static size
#define TERM_CHAR_STRETCH 2   // Text rendering stretch to fit the cell
struct TermData {
  SDL_Window *window;           // The term's actual window
  SDL_Renderer *renderer;       // The renderer for above window
  SDL_Texture *framebuffer;     // Our framebuffer
  SDL_Texture *alt_framebuffer; // Bad, but if using virtual terminals, TERM_MAIN must have 2 framebuffers, one for the vterm and one for the main render

  unsigned int config;        // configuration bit field, see TERM_*
  Uint8 cell_mode;            // See TERM_CELL_*
  Uint8 pict_mode;            // See TERM_PICT_*
  Uint8 char_mode;            // See TERM_CHAR_*

  SDL_Rect ren_rect;          // The term's x/y positions and w/h dimensions for rendering
  SDL_Rect win_rect;          // Store window size (UNUSED!!!)
  int x, y;                   // The term's x/y position
  int width, height;          // The term's width and height
  int fb_w, fb_h;             // Framebuffer w/h
  SDL_Rect dng_rect;          // Dungeon rect (ALT MODE)
  int alt_fb_w, alt_fb_h;     // Alt.Framebuffer w/h (ALT MODE)
  u16b dng_cols, dng_rows;    // Dungeon size (ALT MODE)

  int zoom;                   // Amount of zooming / 100

  SDL_Rect menu_rect;
  SDL_Rect grip_rect;
  SDL_Rect resize_rect;       // Resize rect
  int need_render;            // If this term needs re-render (GUI)
  int win_need_render;        // If this window needs re-render (and all VIRTUAL terms)
  int need_redraw;            // Framebuffer was lost, need to ask Term_draw() to do it all over
  int need_cutout;            // Need to perform special dungeon cutout (ALT MODE)

  Uint32 window_id;           // SDL window id acquired from SDL_GetWindowID(window)

  size_t id;                  // id corresponding to TERM_* defines

  term t;                     // The actual "z-term" object

  char title[128];            // The title of the z-term

  Uint8 rows, cols;           // The term's rows and columns count
  Uint8 cell_w, cell_h;       // The term's cell width and height, in pixels,
  Uint8 orig_w, orig_h;       // The term's original cell width and height, in pixels,
  // depending on user settings, this is set to font or pict size
  // I would really prefer not to have these two file names needed, but I want loading/etc. logic to be handled separately from configuration loading
  char font_file[128];        // Filename of the font
  int font_size;              // Size of the font
  char pict_file[128];        // Filename of the pict
  char mask_file[128];        // Filename of the pict

  FontData *font_data;        // The term's font data
  PictData *pict_data;        // The term's pict data
  SDL_Texture *font_texture;  // The term's font texture, in memory
  SDL_Texture *pict_texture;  // The term's pict texture
};
/* functions */
static errr initTermData(TermData *td, cptr name, int id, cptr font);
static errr applyTermConf(TermData *td);
static errr setTermCells(TermData *td, int w, int h);
static errr setTermTitle(TermData *td);
static errr refreshTerm(TermData *td);
static void refreshTermAlt(TermData *td);
static errr resizeTerm(TermData *td, int rows, int cols);
static errr loadConfig(void);
static errr saveConfig(void);
static errr loadFont(TermData *td, cptr filename, int fontsize, int smoothing);
static errr unloadFont(TermData *td);
static errr attachFont(FontData *fd, TermData *td);
static errr detachFont(TermData *td);
static errr loadPict(TermData *td, cptr filename);
static errr unloadPict(TermData *td);
static errr attachPict(PictData *pd, TermData *td);
static errr detachPict(TermData *td);
static errr fileToFont(FontData *fd, cptr filename, int fontsize, int smoothing);
static errr cleanFontData(FontData *fd);

static errr imgToPict(PictData *pd, cptr filename, cptr maskname);
static errr cleanPictData(PictData *pd);

/* GUI */
static void renderTerm(TermData *td);
static errr renderGui(TermData *td);
static errr sysText(TermData *td, int x, int y, int n, byte attr, cptr s);
static void termStack(int i);
static void termConstrain(int i);

/* ALT.DUNGEON */
static void wipeTermCell_UI(int x, int y, int cutout);
static errr textTermHook_ALT(int x, int y, int n, byte attr, cptr s);
static errr pictTermHook_ALT(int x, int y, int n, const byte *ap, const char *cp, const byte *tap, const char *tcp);
