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

#ifndef WEIGHTED_H264_WEIGHTED_SUM_H
#define WEIGHTED_H264_WEIGHTED_SUM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#if HAVE_INTRINSICS_RVV
typedef unsigned char pixel;

void weight_h264_pixels_16_8_rvv(uint8_t *p_block, ptrdiff_t stride,
                                 int height, int log2_den, int weight, int offset);
void weight_h264_pixels_8_8_rvv(uint8_t *p_block, ptrdiff_t stride,
                                 int height, int log2_den, int weight, int offset);
void weight_h264_pixels_4_8_rvv(uint8_t *p_block, ptrdiff_t stride,
                                 int height, int log2_den, int weight, int offset);

void biweight_h264_pixels_16_8_rvv(uint8_t *p_dst, uint8_t *p_src, ptrdiff_t stride,
                                   int height, int log2_den, int weightd, int weights, int offset);
void biweight_h264_pixels_8_8_rvv(uint8_t *p_dst, uint8_t *p_src, ptrdiff_t stride,
                                  int height, int log2_den, int weightd, int weights, int offset);
void biweight_h264_pixels_4_8_rvv(uint8_t *p_dst, uint8_t *p_src, ptrdiff_t stride,
                                  int height, int log2_den, int weightd, int weights, int offset);
#endif
#endif