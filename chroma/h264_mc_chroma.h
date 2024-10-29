/*
 * Copyright (c) 2023 SiFive, Inc.

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 *  http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CHROMA_H264_MC_CHROMA_H
#define CHROMA_H264_MC_CHROMA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#if HAVE_INTRINSICS_RVV
typedef unsigned char pixel;

void h264_put_chroma_mc8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride, int h, int x, int y);
void h264_avg_chroma_mc8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride, int h, int x, int y);
void h264_put_chroma_mc4_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride, int h, int x, int y);
void h264_avg_chroma_mc4_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride, int h, int x, int y);
void h264_put_chroma_mc2_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride, int h, int x, int y);
void h264_avg_chroma_mc2_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride, int h, int x, int y);
#endif
#endif