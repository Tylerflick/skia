/*
 * Copyright 2016 Xamarin Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

// EXPERIMENTAL EXPERIMENTAL EXPERIMENTAL EXPERIMENTAL
// DO NOT USE -- FOR INTERNAL TESTING ONLY

#ifndef sk_bitmap_DEFINED
#define sk_bitmap_DEFINED

#include "sk_types.h"

SK_C_PLUS_PLUS_BEGIN_GUARD

SK_API void sk_bitmap_destructor(sk_bitmap_t* cbitmap);
SK_API sk_bitmap_t* sk_bitmap_new();
SK_API void sk_bitmap_get_info(sk_bitmap_t* cbitmap, sk_imageinfo_t* info);
SK_API void* sk_bitmap_get_pixels(sk_bitmap_t* cbitmap, size_t* length);
SK_API size_t sk_bitmap_get_row_bytes(sk_bitmap_t* cbitmap);
SK_API size_t sk_bitmap_get_byte_count(sk_bitmap_t* cbitmap);
SK_API void sk_bitmap_reset(sk_bitmap_t* cbitmap);
SK_API bool sk_bitmap_is_null(sk_bitmap_t* cbitmap);
SK_API bool sk_bitmap_is_immutable(sk_bitmap_t* cbitmap);
SK_API void sk_bitmap_set_immutable(sk_bitmap_t* cbitmap);
SK_API bool sk_bitmap_is_volatile(sk_bitmap_t* cbitmap);
SK_API void sk_bitmap_set_volatile(sk_bitmap_t* cbitmap, bool value);
SK_API void sk_bitmap_erase(sk_bitmap_t* cbitmap, sk_color_t color);
SK_API void sk_bitmap_erase_rect(sk_bitmap_t* cbitmap, sk_color_t color, sk_irect_t* rect);
SK_API sk_color_t sk_bitmap_get_pixel_color(sk_bitmap_t* cbitmap, int x, int y);
SK_API sk_color_t sk_bitmap_get_index8_color(sk_bitmap_t* cbitmap, int x, int y);
SK_API void sk_bitmap_set_pixel_color(sk_bitmap_t* cbitmap, int x, int y, sk_color_t color);
SK_API bool sk_bitmap_ready_to_draw(sk_bitmap_t* cbitmap);
SK_API bool sk_bitmap_copy_pixels_to(sk_bitmap_t* cbitmap, void* const dst, size_t dstSize, size_t dstRowBytes, bool preserveDstPad);
SK_API bool sk_bitmap_copy(sk_bitmap_t* cbitmap, sk_bitmap_t* dst, sk_colortype_t ct);
SK_API bool sk_bitmap_can_copy_to(sk_bitmap_t* cbitmap, sk_colortype_t ct);
SK_API void sk_bitmap_lock_pixels(sk_bitmap_t* cbitmap);
SK_API void sk_bitmap_unlock_pixels(sk_bitmap_t* cbitmap);
SK_API void sk_bitmap_get_pixel_colors(sk_bitmap_t* cbitmap, sk_color_t* colors);
SK_API void sk_bitmap_set_pixel_colors(sk_bitmap_t* cbitmap, const sk_color_t* colors);
SK_API bool sk_bitmap_install_pixels(sk_bitmap_t* cbitmap, const sk_imageinfo_t* cinfo, void* pixels, size_t rowBytes, sk_colortable_t* ctable, const sk_bitmap_release_proc releaseProc, void* context);
SK_API bool sk_bitmap_try_alloc_pixels(sk_bitmap_t* cbitmap, const sk_imageinfo_t* requestedInfo, size_t rowBytes);
SK_API bool sk_bitmap_try_alloc_pixels_with_color_table(sk_bitmap_t* cbitmap, const sk_imageinfo_t* requestedInfo, sk_pixelref_factory_t* factory, sk_colortable_t* ctable);
SK_API sk_colortable_t* sk_bitmap_get_colortable(sk_bitmap_t* cbitmap);
SK_API void sk_bitmap_set_pixels(sk_bitmap_t* cbitmap, void* pixels, sk_colortable_t* ctable);


SK_C_PLUS_PLUS_END_GUARD

#endif
