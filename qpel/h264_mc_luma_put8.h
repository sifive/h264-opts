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

#ifndef QPEL_H264_MC_LUMA_PUT8_H
#define QPEL_H264_MC_LUMA_PUT8_H
#include <riscv_vector.h>
#include "h264_lowpass.h"
#include "h264_utility.h"

__attribute__((always_inline)) static void put_copy_block8(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        vuint8m1_t row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        vuint8m1_t row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row6 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row7 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        __riscv_vse8_v_u8m1(p_dst_iter, row0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, row1, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, row2, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, row3, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, row4, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, row5, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, row6, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, row7, vl);
        p_dst_iter += stride;

        p_src_iter = p_src_begin + vl;
        p_dst_iter = p_dst_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_h_lowpass(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t dst_stride, ptrdiff_t src_stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;

    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        for (int j = 0; j < 8; j += 2)
        {
            vuint16m2_t dst0_u, dst1_u;
            h_lowpass_u16m2(&dst0_u, &dst1_u, &p_src_iter, src_stride, vl);

            __riscv_vse8_v_u8m1(p_dst_iter, __riscv_vnclipu_wx_u8m1(dst0_u, 5, __RISCV_FRM_RNE, vl), vl);
            p_dst_iter += dst_stride;
            __riscv_vse8_v_u8m1(p_dst_iter, __riscv_vnclipu_wx_u8m1(dst1_u, 5, __RISCV_FRM_RNE, vl), vl);
            p_dst_iter += dst_stride;
        }

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_hv_lowpass(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8mf2(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        p_src_iter -= (stride << 1);

        vint16m1_t h_row0, h_row1, h_row2, h_row3, h_row4, h_row5, h_row6, h_row7;
        vint16m1_t h_row8, h_row9, h_row10, h_row11, h_row12, h_row13;

        h_lowpass_i16m1(&h_row0, &h_row1, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row2, &h_row3, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row4, &h_row5, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row6, &h_row7, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row8, &h_row9, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row10, &h_row11, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row12, &h_row13, &p_src_iter, stride, vl);

        vuint32m2_t dst0, dst1;
        v_lowpass_u32m2(&dst0, &dst1, &h_row0, &h_row1, &h_row2, &h_row3, &h_row4, &h_row5, &h_row6, stride, vl);

        vuint8mf2_t dst0_u8, dst1_u8;
        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);

        __riscv_vse8_v_u8mf2(p_dst_iter, dst0_u8, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8mf2(p_dst_iter, dst1_u8, vl);
        p_dst_iter += stride;

        v_lowpass_u32m2(&dst0, &dst1, &h_row2, &h_row3, &h_row4, &h_row5, &h_row6, &h_row7, &h_row8, stride, vl);

        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);
        __riscv_vse8_v_u8mf2(p_dst_iter, dst0_u8, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8mf2(p_dst_iter, dst1_u8, vl);
        p_dst_iter += stride;

        v_lowpass_u32m2(&dst0, &dst1, &h_row4, &h_row5, &h_row6, &h_row7, &h_row8, &h_row9, &h_row10, stride, vl);

        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);
        __riscv_vse8_v_u8mf2(p_dst_iter, dst0_u8, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8mf2(p_dst_iter, dst1_u8, vl);
        p_dst_iter += stride;

        v_lowpass_u32m2(&dst0, &dst1, &h_row6, &h_row7, &h_row8, &h_row9, &h_row10, &h_row11, &h_row12, stride, vl);

        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);
        __riscv_vse8_v_u8mf2(p_dst_iter, dst0_u8, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8mf2(p_dst_iter, dst1_u8, vl);

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_hv_lowpass_l2(uint8_t *p_dst, const uint8_t *p_src, uint8_t *p_l2_src, ptrdiff_t stride, ptrdiff_t l2_stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8mf2(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        p_src_iter -= (stride << 1);

        vint16m1_t h_row0, h_row1, h_row2, h_row3, h_row4, h_row5, h_row6, h_row7;
        vint16m1_t h_row8, h_row9, h_row10, h_row11, h_row12, h_row13;

        h_lowpass_i16m1(&h_row0, &h_row1, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row2, &h_row3, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row4, &h_row5, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row6, &h_row7, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row8, &h_row9, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row10, &h_row11, &p_src_iter, stride, vl);
        h_lowpass_i16m1(&h_row12, &h_row13, &p_src_iter, stride, vl);

        vuint32m2_t dst0, dst1;
        vuint8mf2_t dst0_u8, dst1_u8;

        v_lowpass_u32m2(&dst0, &dst1, &h_row0, &h_row1, &h_row2, &h_row3, &h_row4, &h_row5, &h_row6, stride, vl);
        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);
        put_average_l2(&p_dst_iter, &p_l2_src, stride, l2_stride, dst0_u8, dst1_u8, vl);

        v_lowpass_u32m2(&dst0, &dst1, &h_row2, &h_row3, &h_row4, &h_row5, &h_row6, &h_row7, &h_row8, stride, vl);
        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);
        put_average_l2(&p_dst_iter, &p_l2_src, stride, l2_stride, dst0_u8, dst1_u8, vl);

        v_lowpass_u32m2(&dst0, &dst1, &h_row4, &h_row5, &h_row6, &h_row7, &h_row8, &h_row9, &h_row10, stride, vl);
        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);
        put_average_l2(&p_dst_iter, &p_l2_src, stride, l2_stride, dst0_u8, dst1_u8, vl);

        v_lowpass_u32m2(&dst0, &dst1, &h_row6, &h_row7, &h_row8, &h_row9, &h_row10, &h_row11, &h_row12, stride, vl);
        u32_to_u8(&dst0_u8, &dst1_u8, dst0, dst1, vl);
        put_average_l2(&p_dst_iter, &p_l2_src, stride, l2_stride, dst0_u8, dst1_u8, vl);

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_v_lowpass(uint8_t *p_dst, const uint8_t *p_src, ptrdiff_t dst_stride, ptrdiff_t src_stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        p_src_iter -= (src_stride * 2);

        vuint8m1_t row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        vuint8m1_t row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        vuint8m1_t row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        vuint8m1_t row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        vuint8m1_t row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        vuint8m1_t row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        vuint8m1_t row6 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;

        vuint8m1_t dst0, dst1;
        v_lowpass_u8m1(&dst0, &dst1, row0, row1, row2, row3, row4, row5, row6, vl);
        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += dst_stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += dst_stride;

        // 3rd, 4th dst
        row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;

        v_lowpass_u8m1(&dst0, &dst1, row2, row3, row4, row5, row6, row0, row1, vl);
        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += dst_stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += dst_stride;

        // 5th, 6th dst
        row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;

        v_lowpass_u8m1(&dst0, &dst1, row4, row5, row6, row0, row1, row2, row3, vl);
        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += dst_stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += dst_stride;

        // 7th, 8th dst
        row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;
        row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += src_stride;

        v_lowpass_u8m1(&dst0, &dst1, row6, row0, row1, row2, row3, row4, row5, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += dst_stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_v_lowpass_l2(uint8_t *p_dst, const uint8_t *p_src, const uint8_t *p_l2_src, int stride, int l2_stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        p_src_iter -= (stride * 2);

        vuint8m1_t row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row6 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        vuint8m1_t l2_row0 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;
        vuint8m1_t l2_row1 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;

        vuint8m1_t dst0, dst1;
        v_lowpass_u8m1(&dst0, &dst1, row0, row1, row2, row3, row4, row5, row6, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, l2_row0, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, l2_row1, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 3rd, 4th dst
        row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        l2_row0 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;
        l2_row1 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;

        v_lowpass_u8m1(&dst0, &dst1, row2, row3, row4, row5, row6, row0, row1, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, l2_row0, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, l2_row1, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 5th, 6th dst
        row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        l2_row0 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;
        l2_row1 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;

        v_lowpass_u8m1(&dst0, &dst1, row4, row5, row6, row0, row1, row2, row3, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, l2_row0, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, l2_row1, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 7th, 8th dst
        row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        l2_row0 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;
        l2_row1 = __riscv_vle8_v_u8m1(p_l2_src, vl);
        p_l2_src += l2_stride;

        v_lowpass_u8m1(&dst0, &dst1, row6, row0, row1, row2, row3, row4, row5, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, l2_row0, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, l2_row1, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_v_lowpass_l2src(uint8_t *p_dst, const uint8_t *p_src, int stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        p_src_iter -= (stride * 2);

        vuint8m1_t row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row6 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        vuint8m1_t dst0, dst1;
        v_lowpass_u8m1(&dst0, &dst1, row0, row1, row2, row3, row4, row5, row6, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row2, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row3, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 3rd, 4th dst
        row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        v_lowpass_u8m1(&dst0, &dst1, row2, row3, row4, row5, row6, row0, row1, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row4, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row5, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 5th, 6th dst
        row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        v_lowpass_u8m1(&dst0, &dst1, row4, row5, row6, row0, row1, row2, row3, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row6, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row0, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 7th, 8th dst
        row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        v_lowpass_u8m1(&dst0, &dst1, row6, row0, row1, row2, row3, row4, row5, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row1, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row2, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_h_lowpass_l2src(uint8_t *p_dst, const uint8_t *p_src, int stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        for (int j = 0; j < 8; j += 2)
        {
            vuint8m1_t dst0, dst1;
            h_lowpass_u8m1_l2src(&dst0, &dst1, &p_src_iter, stride, vl);

            __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
            p_dst_iter += stride;
            __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
            p_dst_iter += stride;
        }

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_h_lowpass_l2src_shift(uint8_t *p_dst, const uint8_t *p_src, int stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        for (int j = 0; j < 8; j += 2)
        {
            vuint8m1_t dst0, dst1;
            h_lowpass_u8m1_l2src_shift(&dst0, &dst1, &p_src_iter, stride, vl);

            __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
            p_dst_iter += stride;
            __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
            p_dst_iter += stride;
        }

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}

__attribute__((always_inline)) static void put_h264_qpel8_v_lowpass_l2src_shift(uint8_t *p_dst, const uint8_t *p_src, int stride)
{
    const uint8_t *p_src_iter = p_src;
    uint8_t *p_dst_iter = p_dst;
    int len = 8;

    while (len > 0)
    {
        int vl = __riscv_vsetvl_e8m1(len);
        const uint8_t *p_src_begin = p_src_iter;
        uint8_t *p_dst_begin = p_dst_iter;

        p_src_iter -= (stride * 2);

        vuint8m1_t row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        vuint8m1_t row6 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        vuint8m1_t dst0, dst1;
        v_lowpass_u8m1(&dst0, &dst1, row0, row1, row2, row3, row4, row5, row6, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row3, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row4, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 3rd, 4th dst
        row0 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row1 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        v_lowpass_u8m1(&dst0, &dst1, row2, row3, row4, row5, row6, row0, row1, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row5, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row6, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 5th, 6th dst
        row2 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row3 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        v_lowpass_u8m1(&dst0, &dst1, row4, row5, row6, row0, row1, row2, row3, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row0, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row1, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        // 7th, 8th dst
        row4 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;
        row5 = __riscv_vle8_v_u8m1(p_src_iter, vl);
        p_src_iter += stride;

        v_lowpass_u8m1(&dst0, &dst1, row6, row0, row1, row2, row3, row4, row5, vl);
        dst0 = __riscv_vaaddu_vv_u8m1(dst0, row2, __RISCV_FRM_RNE, vl);
        dst1 = __riscv_vaaddu_vv_u8m1(dst1, row3, __RISCV_FRM_RNE, vl);

        __riscv_vse8_v_u8m1(p_dst_iter, dst0, vl);
        p_dst_iter += stride;
        __riscv_vse8_v_u8m1(p_dst_iter, dst1, vl);
        p_dst_iter += stride;

        p_dst_iter = p_dst_begin + vl;
        p_src_iter = p_src_begin + vl;
        len -= vl;
    }
}
#endif