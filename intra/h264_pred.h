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

#ifndef INTRA_H264_PRED_H
#define INTRA_H264_PRED_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#if HAVE_INTRINSICS_RVV
typedef unsigned char pixel;

void pred8x8_vert_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_hor_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_plane_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_128_dc_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_top_dc_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_left_dc_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_dc_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_l0t_dc_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_0lt_dc_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_l00_dc_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred8x8_0l0_dc_rvv(uint8_t *p_src, ptrdiff_t stride);

void pred16x16_dc_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred16x16_top_dc_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred16x16_left_dc_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred16x16_128_dc_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred16x16_vert_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred16x16_hor_8_rvv(uint8_t *p_src, ptrdiff_t stride);
void pred16x16_plane_8_rvv(uint8_t *p_src, ptrdiff_t stride);
#endif
#endif