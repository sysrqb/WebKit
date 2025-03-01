// GENERATED FILE - DO NOT EDIT.
// Generated by gen_vk_internal_shaders.py.
//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// shaders/gen/ImageCopy.frag.00000015.inc:
//   Pre-generated shader for the ANGLE Vulkan back-end.

#pragma once
constexpr uint8_t kImageCopy_frag_00000015[] = {
    0x1f,0x8b,0x08,0x00,0x00,0x00,0x00,0x00,0x02,0xff,0x85,0x96,0xcb,0x6f,0x55,0x55,
    0x14,0xc6,0xf7,0x3e,0xb7,0xed,0xbd,0x05,0x4b,0x5b,0xb4,0x2f,0xd4,0xb6,0x58,0x4c,
    0xd5,0xb6,0x58,0xd2,0x56,0x30,0xa2,0x51,0x42,0xa0,0x02,0x95,0xc2,0x75,0xd6,0x81,
    0x31,0x71,0xe2,0x40,0x18,0xe8,0x88,0x81,0x31,0x46,0x34,0xe9,0x8c,0x7f,0x81,0x87,
    0x68,0x4c,0x45,0x8d,0xa8,0x20,0x8f,0x21,0xf8,0x20,0x9a,0xaa,0x8d,0xa6,0x6a,0x63,
    0x47,0x6a,0x63,0x84,0xd8,0xda,0x8a,0xa5,0x71,0xad,0xb3,0x7f,0xcb,0xae,0x54,0xa3,
    0x24,0x3b,0xe7,0xec,0x6f,0xbd,0xbe,0x6f,0xad,0x75,0x4f,0x29,0x64,0x1d,0xc5,0x10,
    0x62,0x58,0x15,0x4a,0xe1,0xf1,0x18,0xf2,0x7f,0xf5,0x21,0x0b,0xfa,0xba,0x3a,0x54,
    0xe5,0xcf,0x9d,0x7b,0xca,0x7b,0x36,0x3e,0xfb,0xdc,0x53,0x1b,0xfb,0x07,0x7a,0xd5,
    0xbe,0x26,0x14,0x72,0x3f,0xb5,0xd5,0x86,0x62,0xa8,0x90,0xa7,0x9e,0x67,0x9e,0x7c,
    0xfa,0x80,0xe2,0x27,0xe4,0x5c,0x94,0x53,0x27,0x7e,0x8a,0x4b,0x81,0x30,0x18,0x2a,
    0x43,0x63,0x4a,0x1f,0x3a,0x78,0x1a,0x16,0xc1,0x4a,0x0e,0xcb,0xc0,0xea,0x1c,0x56,
    0x00,0xbb,0xc5,0x61,0x15,0x60,0xcd,0x0e,0xab,0x04,0xbb,0xcd,0x61,0x55,0x60,0xed,
    0x0e,0x2b,0x82,0x6d,0x70,0x58,0x09,0xec,0x2e,0x87,0x55,0x83,0x75,0x3b,0x6c,0x15,
    0x58,0xaf,0xc3,0x56,0x83,0xf5,0x3b,0xec,0x26,0xb0,0x2d,0x0e,0xab,0x01,0xdb,0xea,
    0xb0,0x35,0x60,0x0f,0x6b,0xbf,0x45,0xa9,0xf5,0x60,0xa7,0x28,0x3c,0x41,0xee,0x5a,
    0xee,0xa7,0xe4,0x79,0x07,0x3d,0xb4,0xfb,0x7a,0x77,0xd7,0xde,0xb7,0x72,0xbf,0x59,
    0xb2,0x64,0xb9,0xbd,0x90,0xf7,0x4f,0xdf,0x1b,0xc4,0xa7,0x8a,0x5e,0x68,0xef,0x9b,
    0xe4,0x5e,0xa4,0x47,0x19,0xf7,0x1a,0xee,0x15,0xf8,0x37,0xe0,0x1f,0xf2,0xdc,0xf5,
    0x7f,0xf7,0xcf,0xe2,0xec,0x34,0xfc,0xcf,0x31,0x9f,0x76,0xc9,0xd9,0x44,0x6f,0x35,
    0xd7,0x03,0xdc,0x9b,0xc1,0xba,0xe0,0xd8,0x02,0x47,0xf5,0x5f,0x87,0xad,0xe8,0xec,
    0xad,0xcc,0x5b,0xed,0x6d,0xd8,0x1b,0xf2,0x1d,0xc9,0xf2,0x1e,0x75,0xc1,0xdd,0x76,
    0xce,0xe2,0xba,0xe1,0x62,0xf7,0xcd,0xcc,0xc0,0xee,0xdb,0xa8,0xa3,0xbd,0xd8,0x8d,
    0x6f,0xc1,0xd9,0xcb,0xec,0x8a,0xdd,0x47,0x56,0xe4,0x3f,0xb8,0x42,0xc7,0x21,0x76,
    0xc6,0xee,0x87,0xd9,0x03,0xe5,0xfd,0x32,0xbe,0x9e,0xcf,0x28,0xb3,0xb0,0xfb,0x11,
    0x66,0xd1,0x28,0x2c,0x8e,0x32,0x0b,0xe5,0x76,0x4c,0x9e,0x47,0xb1,0x69,0xae,0xe3,
    0xf4,0xeb,0x18,0x3d,0x3d,0xce,0xef,0xd1,0xe6,0xfc,0x2a,0xfe,0x59,0xde,0xdb,0xea,
    0x30,0x46,0x5d,0x7e,0xfa,0xff,0x78,0x6a,0xce,0x37,0x79,0x1f,0x23,0xa7,0xde,0x4f,
    0xad,0xd0,0x7b,0x9a,0xfe,0xa8,0xff,0x05,0xde,0x6b,0xf0,0xbf,0xc0,0xf7,0x40,0xb1,
    0xfb,0x64,0x5a,0x19,0x7c,0x03,0xd8,0x82,0x20,0x3a,0xc3,0x07,0xd1,0x73,0x12,0xce,
    0x7b,0x65,0x02,0xca,0xf7,0x35,0xb0,0x93,0x8e,0xdb,0x01,0x76,0xf6,0x75,0xec,0x8f,
    0x48,0x06,0xdd,0x8f,0x4b,0xec,0x50,0x0b,0xf9,0xd4,0xe7,0x32,0xf8,0x8b,0xe2,0xa3,
    0xf7,0x8f,0x88,0xbb,0x4c,0x9c,0xee,0xcd,0xc7,0xc4,0xb5,0x12,0xa7,0x3b,0xf3,0x09,
    0xf8,0x1b,0xe2,0xa3,0xbb,0xf4,0x29,0x98,0xee,0xd2,0xbc,0x30,0x1f,0x87,0xcf,0x75,
    0xf1,0x57,0xdb,0x15,0x39,0xe3,0xe8,0xd1,0xf7,0x7d,0x12,0xa7,0xbd,0xf9,0x8c,0x9a,
    0xfa,0xef,0x79,0xfa,0xf5,0x39,0xf8,0x7e,0xb9,0x29,0xa7,0xfb,0x63,0xc2,0xcc,0xef,
    0x0f,0xc9,0x61,0xb9,0xf4,0x39,0x27,0x5e,0xea,0xf7,0x68,0x4c,0x3e,0x95,0xc4,0x5c,
    0x71,0x1a,0xbe,0x40,0x43,0xb7,0xd3,0xf0,0x25,0xb8,0x69,0xf8,0x0a,0xcc,0x34,0x4c,
    0x3a,0x0d,0x6a,0x9b,0x90,0x33,0x49,0xdd,0x09,0xa7,0xe1,0x6b,0x6a,0x47,0xa7,0xe1,
    0x1b,0x70,0xd3,0xb0,0x35,0x26,0xcc,0xfc,0x54,0x83,0xe5,0x9a,0x74,0x1a,0x76,0xc5,
    0xe4,0x33,0x4e,0xcc,0x84,0xd3,0xf0,0x2d,0x1a,0x36,0x3b,0x0d,0xdf,0x81,0x9b,0x86,
    0xef,0xc1,0x4c,0xc3,0xb4,0xd3,0xa0,0xb6,0x29,0x39,0xd3,0xd4,0x9d,0x62,0x8f,0xb4,
    0xee,0x0f,0xd4,0xde,0x15,0x97,0xf7,0x5b,0x39,0x9a,0xef,0xb4,0xe3,0xb8,0x1b,0xbf,
    0x49,0xe2,0xa6,0xe0,0xa3,0xbf,0x81,0xb7,0xd8,0x7f,0xdb,0xb9,0xb7,0xe1,0x3c,0xe2,
    0x76,0xee,0x1d,0xf0,0x17,0xd8,0xb9,0x77,0xc1,0x34,0xaf,0xc6,0xe9,0x6f,0xfe,0x3d,
    0xe2,0x4e,0x13,0xa7,0x3d,0x7d,0x1f,0xdc,0xfa,0xfe,0x01,0xb1,0xc1,0x61,0x67,0xc0,
    0x54,0xc3,0xb0,0x20,0xfa,0x7d,0x3a,0x8b,0xef,0x19,0x72,0x58,0x8d,0x0f,0xa9,0x31,
    0xea,0x6a,0x9c,0x03,0x7f,0x42,0x98,0xe9,0x6f,0xf4,0x3c,0x9a,0xce,0xf2,0x5d,0x38,
    0xe7,0xe6,0xf1,0x23,0xf1,0xdb,0xdc,0x3c,0x7e,0x02,0xb7,0x79,0xfc,0x0c,0x66,0xf3,
    0x28,0xc5,0xe5,0x79,0xa8,0x6d,0x46,0xce,0x2c,0x3d,0x9e,0x71,0x3a,0x7e,0xa1,0x76,
    0x21,0x9f,0x51,0x29,0xd7,0xf1,0x2b,0xd8,0x79,0xf7,0x5b,0xcf,0x9c,0xce,0xab,0xc4,
    0xd9,0x79,0x49,0x72,0x29,0x7e,0x8d,0xd8,0xab,0x79,0xae,0xea,0x5c,0xd7,0x6f,0xe4,
    0xb9,0xc6,0xf7,0xa6,0xd2,0x7d,0xc7,0x75,0xee,0xca,0x53,0x39,0xcd,0x3a,0xbd,0x73,
    0xe8,0x2d,0x3b,0xbd,0xbf,0x83,0x9b,0xde,0x79,0x30,0xd3,0xbb,0xe8,0xf6,0x6f,0x3e,
    0xd7,0x19,0x72,0x4c,0x73,0x2f,0x38,0xbd,0xd7,0x9d,0xde,0x31,0x72,0xfd,0x09,0x3e,
    0x02,0x27,0x8b,0x5b,0x64,0x17,0xd5,0xe7,0x06,0x35,0x67,0xf1,0x5f,0xa0,0x6e,0xd1,
    0xf5,0x59,0x7d,0x96,0xf4,0x6f,0x16,0x9a,0x96,0x5c,0x5d,0x6d,0xe2,0xca,0x3e,0x67,
    0xf1,0xbf,0xfb,0x5c,0x88,0x80,0x9c,0x57,0xe8,0x73,0x45,0x4c,0xb1,0x6a,0xb7,0x3e,
    0x57,0x91,0x4b,0x6d,0xff,0xd6,0x67,0xe3,0xa4,0xcf,0x39,0x76,0xee,0x31,0x62,0x16,
    0x89,0x5f,0x5a,0x31,0x93,0x92,0xf3,0x1d,0x8a,0x69,0x96,0x33,0xc4,0x15,0xe3,0xf2,
    0xbc,0x6a,0x63,0x9a,0xd7,0x41,0x37,0xaf,0xba,0x98,0x70,0x9b,0x57,0x7d,0x4c,0x98,
    0xcd,0x6b,0xc0,0xf5,0x4d,0x6d,0x6b,0xe5,0x34,0x51,0x77,0xad,0xd3,0xd5,0x18,0x53,
    0xed,0x21,0x74,0x15,0xe9,0x91,0xe9,0x1a,0x20,0xa6,0xc9,0xf1,0x69,0x86,0xcf,0x21,
    0xc7,0xa7,0x25,0x26,0xdc,0xf8,0xac,0x8b,0x09,0x33,0x3e,0xfd,0x8e,0x8f,0xda,0x6e,
    0x95,0xd3,0x46,0x6e,0x7d,0xb7,0x39,0xde,0x0e,0x97,0x02,0xdf,0x5c,0xe5,0xb8,0x2d,
    0x2e,0xe3,0xf6,0x3d,0xeb,0x27,0xb6,0xcd,0x7d,0x6b,0xda,0xe1,0x75,0xd8,0x7d,0x07,
    0xd6,0xc7,0x84,0x5f,0x22,0x7f,0x47,0x4c,0xd8,0xa8,0xdb,0xf5,0x0d,0x31,0xe1,0x23,
    0x70,0xed,0x74,0x5c,0xd5,0x76,0xa7,0x9c,0x4e,0xea,0xe9,0xbb,0xf1,0xda,0x4e,0xcc,
    0x90,0xfb,0x5b,0x60,0x7e,0x9d,0x6e,0xb6,0x7b,0xe1,0xae,0x5c,0xb7,0x93,0xcf,0xf8,
    0xdc,0x0d,0x9f,0x23,0x8e,0xcf,0x3d,0x31,0xe1,0xc6,0xa7,0xc7,0xf1,0x51,0x5b,0x97,
    0x9c,0x1e,0xea,0x74,0x39,0x3e,0x3b,0x88,0xd1,0x7a,0x19,0x7c,0xcc,0xaf,0xc7,0xf1,
    0x19,0x8e,0xc9,0x47,0x39,0xee,0x20,0x9f,0xf1,0xb9,0x17,0x3e,0x65,0xc7,0xa7,0x37,
    0x26,0xdc,0xf8,0xf4,0x39,0x3e,0x6a,0xdb,0x24,0xa7,0x8f,0x3a,0x9b,0x1c,0x9f,0xc1,
    0x98,0xfe,0x8f,0x32,0x1c,0x97,0xf7,0xc9,0xfc,0xfa,0x1c,0x9f,0x72,0x4c,0x3e,0xca,
    0x71,0x90,0x7c,0x7e,0xc6,0xfd,0xce,0x77,0x7f,0x4c,0xfb,0xa0,0x3b,0x53,0xa6,0xae,
    0xdf,0xd3,0x01,0xe7,0xbb,0x2f,0xa6,0xfd,0xd6,0x7d,0xd7,0x38,0xcd,0xf3,0x90,0x30,
    0xb9,0x88,0xed,0x86,0x4c,0x6d,0x8b,0x9c,0xbf,0x00,0x5e,0xb4,0x44,0xba,0x20,0x0e,
    0x00,0x00
};

// Generated from:
//
// #version 450 core
//
// #extension GL_GOOGLE_include_directive : require
// #extension GL_EXT_samplerless_texture_functions : require
//
// layout(set = 0, binding = 0)uniform itexture2DArray src;
// layout(location = 0)out ivec4 dst;
//
// #line 1 "shaders/src/ImageCopy.inc"
//
// layout(push_constant)uniform PushConstants {
//
//     ivec2 srcOffset;
//     ivec2 dstOffset;
//     int srcMip;
//     int srcLayer;
//     int srcSampleCount;
//
//     bool flipX;
//     bool flipY;
//
//     bool premultiplyAlpha;
//     bool unmultiplyAlpha;
//
//     bool dstHasLuminance;
//     bool dstIsAlpha;
//
//     bool srcIsSRGB;
//     bool dstIsSRGB;
//
//     int dstDefaultChannelsMask;
//     bool rotateXY;
// } params;
//
// ivec2 transformImageCoords(ivec2 glFragCoords)
// {
//     ivec2 imageCoordsOut = glFragCoords - params . dstOffset;
//
//     if(params . flipX)
//     {
//         imageCoordsOut . x = - imageCoordsOut . x;
//     }
//     if(params . flipY)
//     {
//         imageCoordsOut . y = - imageCoordsOut . y;
//     }
//     if(params . rotateXY)
//     {
//         imageCoordsOut . xy = imageCoordsOut . yx;
//     }
//
//     return imageCoordsOut;
// }
//
//       ivec4 transformSrcValue(ivec4 srcValue)
// {
//
//     if(params . premultiplyAlpha)
//     {
//         srcValue . rgb *= srcValue . a;
//     }
//     else if(params . unmultiplyAlpha && srcValue . a > 0)
//     {
//         srcValue . rgb /= srcValue . a;
//     }
//
//           ivec4 dstValue = ivec4(srcValue);
//
//     if(params . dstHasLuminance)
//     {
//         dstValue . rg = dstValue . ra;
//     }
//     else if(params . dstIsAlpha)
//     {
//         dstValue . r = dstValue . a;
//     }
//     else
//     {
//         int defaultChannelsMask = params . dstDefaultChannelsMask;
//         if((defaultChannelsMask & 2)!= 0)
//         {
//             dstValue . g = 0;
//         }
//         if((defaultChannelsMask & 4)!= 0)
//         {
//             dstValue . b = 0;
//         }
//         if((defaultChannelsMask & 8)!= 0)
//         {
//             dstValue . a = 1;
//         }
//     }
//
//     return dstValue;
// }
// #line 56 "shaders/src/ImageCopy.frag"
//
// void main()
// {
//     ivec2 srcSubImageCoords = transformImageCoords(ivec2(gl_FragCoord . xy));
//
//           ivec4 srcValue = texelFetch(src, ivec3(params . srcOffset + srcSubImageCoords, params . srcLayer), params . srcMip);
//
//     dst = transformSrcValue(srcValue);
// }
