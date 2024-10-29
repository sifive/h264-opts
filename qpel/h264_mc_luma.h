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

#ifndef QPEL_H264_MC_LUMA_H
#define QPEL_H264_MC_LUMA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#if HAVE_INTRINSICS_RVV
typedef unsigned char pixel;

void put_h264_qpel16_mc00_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc01_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc02_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc03_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc10_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc11_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc12_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc13_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc20_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc21_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc22_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc23_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc30_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc31_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc32_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel16_mc33_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);

void avg_h264_qpel16_mc00_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc01_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc02_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc03_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc10_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc11_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc12_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc13_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc20_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc21_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc22_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc23_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc30_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc31_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc32_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel16_mc33_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);

void put_h264_qpel8_mc00_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc01_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc02_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc03_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc10_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc11_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc12_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc13_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc20_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc21_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc22_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc23_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc30_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc31_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc32_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void put_h264_qpel8_mc33_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);

void avg_h264_qpel8_mc00_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc01_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc02_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc03_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc10_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc11_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc12_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc13_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc20_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc21_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc22_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc23_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc30_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc31_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc32_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
void avg_h264_qpel8_mc33_8_rvv(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride);
#endif
#endif