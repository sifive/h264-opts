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

#ifndef INLOOP_H264_INLOOP_H
#define INLOOP_H264_INLOOP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#if HAVE_INTRINSICS_RVV
typedef unsigned char pixel;

void h264_v_loop_filter_luma_8_rvv(uint8_t *pix, ptrdiff_t stride, int alpha, int beta, int8_t *tc0);
void h264_h_loop_filter_luma_8_rvv(uint8_t *pix, ptrdiff_t stride, int alpha, int beta, int8_t *tc0);

void h264_v_loop_filter_chroma_8_rvv(uint8_t *pix, ptrdiff_t stride, int alpha, int beta, int8_t *tc0);
void h264_h_loop_filter_chroma_8_rvv(uint8_t *pix, ptrdiff_t stride, int alpha, int beta, int8_t *tc0);

void h264_v_loop_filter_luma_intra_8_rvv(uint8_t *p_pix, ptrdiff_t stride, int alpha, int beta);
void h264_h_loop_filter_luma_intra_8_rvv(uint8_t *p_pix, ptrdiff_t stride, int alpha, int beta);

void h264_v_loop_filter_chroma_intra_8_rvv(uint8_t *p_pix, ptrdiff_t stride, int alpha, int beta);
void h264_h_loop_filter_chroma_intra_8_rvv(uint8_t *p_pix, ptrdiff_t stride, int alpha, int beta);

void h264_h_loop_filter_chroma_mbaff_intra_8_rvv(uint8_t *p_pix, ptrdiff_t stride, int alpha, int beta);
#endif
#endif