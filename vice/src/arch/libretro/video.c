#include "vice.h"
#include "interrupt.h"
#include "cmdline.h"
#include "video.h"
#include "videoarch.h"
#include "palette.h"
#include "viewport.h"
#include "keyboard.h"
#include "lib.h"
#include "log.h"
#include "ui.h"
#include "vsync.h"
#include "raster.h"
#include "sound.h"
#include "machine.h"
#include "resources.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libretro-core.h"

struct video_canvas_s *RCANVAS;

int machine_ui_done = 0;

static const cmdline_option_t cmdline_options[] = {
     { NULL }
};

int video_init_cmdline_options(void)
{
   return cmdline_register_options(cmdline_options);
}

int video_arch_cmdline_options_init(void)
{
   return cmdline_register_options(cmdline_options);
}

void video_canvas_resize(struct video_canvas_s *canvas,  char resizecv)
{
}

static video_canvas_t *retro_canvas_create(video_canvas_t *canvas, unsigned int *width, unsigned int *height)
{
   return canvas;
}

video_canvas_t *video_canvas_create(video_canvas_t *canvas, 
      unsigned int *width, unsigned int *height, int mapped)
{
   canvas->videoconfig->rendermode = VIDEO_RENDER_RGB_1X1;
   canvas->depth = 8*pix_bytes;
   video_canvas_set_palette(canvas, canvas->palette);
   return canvas;
}

void video_canvas_destroy(struct video_canvas_s *canvas)
{
}

static int video_frame_buffer_alloc(video_canvas_t *canvas, 
      BYTE **draw_buffer, 
      unsigned int fb_width, 
      unsigned int fb_height, 
      unsigned int *fb_pitch);
static void video_frame_buffer_free(video_canvas_t *canvas, 
      BYTE *draw_buffer);
static void video_frame_buffer_clear(video_canvas_t *canvas, 
      BYTE *draw_buffer, 
      BYTE value, 
      unsigned int fb_width, 
      unsigned int fb_height, 
      unsigned int fb_pitch);

void video_arch_canvas_init(struct video_canvas_s *canvas)
{
}

static int video_frame_buffer_alloc(video_canvas_t *canvas, 
      BYTE **draw_buffer, 
      unsigned int fb_width, 
      unsigned int fb_height, 
      unsigned int *fb_pitch)
{
   return 0;
}

static void video_frame_buffer_free(video_canvas_t *canvas, BYTE *draw_buffer)
{
}

static void video_frame_buffer_clear(video_canvas_t *canvas, 
      BYTE *draw_buffer, 
      BYTE value, 
      unsigned int fb_width, 
      unsigned int fb_height, 
      unsigned int fb_pitch)
{
   memset(draw_buffer, value, fb_pitch * fb_height);
}

char video_canvas_can_resize(video_canvas_t *canvas)
{
   return 1;
}

int video_canvas_set_palette(struct video_canvas_s *canvas,
      struct palette_s *palette)
{
   unsigned int col;
   int i;

   if (palette == NULL) {
      return 0; /* no palette, nothing to do */
   }

   canvas->palette = palette;

   for (i = 0; i < palette->num_entries; i++) {
      if (pix_bytes == 2)
         col = RGB565(palette->entries[i].red, palette->entries[i].green, palette->entries[i].blue);
      else
         col = palette->entries[i].red<<16 | palette->entries[i].green<<8 | palette->entries[i].blue;

      video_render_setphysicalcolor(canvas->videoconfig, i, col, canvas->depth);
   }
   for (i = 0; i < 256; i++) {
      if (pix_bytes == 2)
         video_render_setrawrgb(i, RGB565(i, 0, 0), RGB565(0, i, 0), RGB565(0, 0, i));
      else
         video_render_setrawrgb(i, i, i, i);
   }
   video_render_initraw(canvas->videoconfig);

   return 0;
}

void video_canvas_refresh(struct video_canvas_s *canvas,
      unsigned int xs, unsigned int ys,
      unsigned int xi, unsigned int yi,
      unsigned int w, unsigned int h)
{ 
#ifdef RETRO_DEBUG
   printf("XS:%d YS:%d XI:%d YI:%d W:%d H:%d\n",xs,ys,xi,yi,w,h);
#endif
   RCANVAS=canvas;
}

int video_init()
{
   return 0;
}

void video_shutdown()
{
}

int video_arch_resources_init()
{
   return 0;
}

void video_arch_resources_shutdown()
{
}

void fullscreen_capability(struct cap_fullscreen_s *cap_fullscreen)
{
}
