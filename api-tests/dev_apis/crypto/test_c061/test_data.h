/** @file
 * Copyright (c) 2019-2025, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "val_crypto.h"

typedef struct {
    char                    test_desc[75];
    psa_key_type_t          key_type;
    uint8_t                 key_data[32];
    uint32_t                key_length;
    psa_key_usage_t         usage;
    psa_algorithm_t         key_alg;
    psa_algorithm_t         alg;
    uint8_t                 plaintext[120];
    uint8_t                 additional_data[32];
    uint8_t                 nonce[32];
    size_t                  nonce_size;
    size_t                  ad_length;
    size_t                  plaintext_length;
    size_t                  input_length;
    size_t                  output_size;
    uint8_t                 expected_output[120];
    size_t                  expected_length;
    size_t                  tag_size;
    uint8_t                 expected_tag[64];
    size_t                  expected_tag_length;
    psa_status_t            expected_status;
} test_data;
#if ((defined(ARCH_TEST_CCM) || defined(ARCH_TEST_GCM)) && defined(ARCH_TEST_AES_128))
static const test_data check1[] = {
#ifdef ARCH_TEST_CCM
#ifdef ARCH_TEST_AES_128
{"Test psa_aead_finish - AES-CCM\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43},
 AES_16B_KEY_SIZE, PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CCM, PSA_ALG_CCM,
{0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a, 0x7c, 0x0a, 0x61, 0xc9, 0xf8,
 0x25, 0xa4, 0x86, 0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 24, 24, BUFFER_SIZE,
{0x26, 0xc5, 0x69, 0x61, 0xc0, 0x35, 0xa7, 0xe4, 0x52, 0xcc, 0xe6, 0x1b, 0xc6,
 0xee, 0x22, 0x0d, 0x77, 0xb3, 0xf9, 0x4d, 0x18, 0xfd, 0x10, 0xb6},
 24, SIZE_32B,
{0xd8, 0x0e, 0x8b, 0xf8, 0x0f, 0x4a, 0x46, 0xca, 0xb0, 0x6d, 0x43, 0x13, 0xf0,
 0xdb, 0x9b, 0xe9}, 16,
 PSA_SUCCESS
},

{"Test psa_aead_finish - AES-CCM 24 bytes Tag length = 4\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43}, AES_16B_KEY_SIZE, PSA_KEY_USAGE_ENCRYPT,
 PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 4),
 PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 4),
{0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a, 0x7c, 0x0a, 0x61, 0xc9, 0xf8,
 0x25, 0xa4, 0x86, 0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 24, 24, BUFFER_SIZE,
{0x26, 0xc5, 0x69, 0x61, 0xc0, 0x35, 0xa7, 0xe4, 0x52, 0xcc, 0xe6, 0x1b, 0xc6,
 0xee, 0x22, 0x0d, 0x77, 0xb3, 0xf9, 0x4d, 0x18, 0xfd, 0x10, 0xb6},
 24, SIZE_32B, {0x64, 0x3b, 0x4f, 0x39}, 4,
 PSA_SUCCESS
},

{"Test psa_aead_finish - Small buffer size\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43},
 AES_16B_KEY_SIZE, PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CCM, PSA_ALG_CCM,
{0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a, 0x7c, 0x0a, 0x61, 0xc9, 0xf8,
 0x25, 0xa4, 0x86, 0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 24, 24, BUFFER_SIZE, {0}, 0, 10, {0}, 0,
 PSA_ERROR_BUFFER_TOO_SMALL
},

{"Test psa_aead_finish - Input length is less than plaintext length\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43},
 AES_16B_KEY_SIZE, PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CCM, PSA_ALG_CCM,
{0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a, 0x7c, 0x0a, 0x61, 0xc9, 0xf8,
 0x25, 0xa4, 0x86, 0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 24, 30, BUFFER_SIZE, {0}, 0, SIZE_32B, {0}, 0,
 PSA_ERROR_INVALID_ARGUMENT
},
#endif
#endif

#ifdef ARCH_TEST_GCM
#ifdef ARCH_TEST_AES_128
{"Test psa_aead_finish - GCM - 16B AES - 12B Nonce & 12B additional data\n", PSA_KEY_TYPE_AES,
{0x3d, 0xe0, 0x98, 0x74, 0xb3, 0x88, 0xe6, 0x49, 0x19, 0x88, 0xd0, 0xc3, 0x60,
 0x7e, 0xae, 0x1f}, AES_16B_KEY_SIZE, PSA_KEY_USAGE_ENCRYPT, PSA_ALG_GCM, PSA_ALG_GCM,
{0x45, 0x00, 0x00, 0x1c, 0x42, 0xa2, 0x00, 0x00, 0x80, 0x01, 0x44, 0x1f, 0x40,
 0x67, 0x93, 0xb6, 0xe0, 0x00, 0x00, 0x02, 0x0a, 0x00, 0xf5, 0xff, 0x01, 0x02,
 0x02, 0x01},
{0x42, 0xf6, 0x7e, 0x3f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
{0x57, 0x69, 0x0e, 0x43, 0x4e, 0x28, 0x00, 0x00, 0xa2, 0xfc, 0xa1, 0xa3},
 12, 12, 28, 28, BUFFER_SIZE,
{0xFB, 0xA2, 0xCA, 0x84, 0x5E, 0x5D, 0xF9, 0xF0, 0xF2, 0x2C, 0x3E, 0x6E, 0x86,
 0xDD, 0x83, 0x1E, 0x1F, 0xC6, 0x57, 0x92, 0xCD, 0x1A, 0xF9, 0x13, 0x0E, 0x13,
 0x79, 0xED}, 28, SIZE_32B,
{0x36, 0x9F, 0x07, 0x1F, 0x35, 0xE0, 0x34, 0xBE, 0x95, 0xF1, 0x12, 0xE4, 0xE7,
 0xD0, 0x5D, 0x35}, 16,
 PSA_SUCCESS
},
#endif
#endif

#ifdef ARCH_TEST_CHACHA20
{"Test psa_aead_finish - CHACHA20_POLY1305 - 12B Nonce and 12B add data\n",
PSA_KEY_TYPE_CHACHA20, {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b,
0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b,
0x9c, 0x9d, 0x9e, 0x9f}, 32, PSA_KEY_USAGE_ENCRYPT,
PSA_ALG_CHACHA20_POLY1305, PSA_ALG_CHACHA20_POLY1305,
{0x4c, 0x61, 0x64, 0x69, 0x65, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x47, 0x65, 0x6e, 0x74, 0x6c,
0x65, 0x6d, 0x65, 0x6e, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6c, 0x61, 0x73,
0x73, 0x20, 0x6f, 0x66, 0x20, 0x27, 0x39, 0x39, 0x3a, 0x20, 0x49, 0x66, 0x20, 0x49, 0x20, 0x63,
0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6f, 0x66, 0x66, 0x65, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x6f,
0x6e, 0x6c, 0x79, 0x20, 0x6f, 0x6e, 0x65, 0x20, 0x74, 0x69, 0x70, 0x20, 0x66, 0x6f, 0x72, 0x20,
0x74, 0x68, 0x65, 0x20, 0x66, 0x75, 0x74, 0x75, 0x72, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x73,
0x63, 0x72, 0x65, 0x65, 0x6e, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x62, 0x65, 0x20, 0x69,
0x74, 0x2e},
{0x50, 0x51, 0x52, 0x53, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7},
{0x07, 0x00, 0x00, 0x00, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47}, 12, 12, 114, 114,
BUFFER_SIZE, {0xd3, 0x1a, 0x8d, 0x34, 0x64, 0x8e, 0x60, 0xdb, 0x7b, 0x86, 0xaf, 0xbc, 0x53,
0xef, 0x7e, 0xc2, 0xa4, 0xad, 0xed, 0x51, 0x29, 0x6e, 0x08, 0xfe, 0xa9, 0xe2, 0xb5, 0xa7, 0x36,
0xee, 0x62, 0xd6, 0x3d, 0xbe, 0xa4, 0x5e, 0x8c, 0xa9, 0x67, 0x12, 0x82, 0xfa, 0xfb, 0x69, 0xda,
0x92, 0x72, 0x8b, 0x1a, 0x71, 0xde, 0x0a, 0x9e, 0x06, 0x0b, 0x29, 0x05, 0xd6, 0xa5, 0xb6, 0x7e,
0xcd, 0x3b, 0x36, 0x92, 0xdd, 0xbd, 0x7f, 0x2d, 0x77, 0x8b, 0x8c, 0x98, 0x03, 0xae, 0xe3, 0x28,
0x09, 0x1b, 0x58, 0xfa, 0xb3, 0x24, 0xe4, 0xfa, 0xd6, 0x75, 0x94, 0x55, 0x85, 0x80, 0x8b, 0x48,
0x31, 0xd7, 0xbc, 0x3f, 0xf4, 0xde, 0xf0, 0x8e, 0x4b, 0x7a, 0x9d, 0xe5, 0x76, 0xd2, 0x65, 0x86,
0xce, 0xc6, 0x4b, 0x61, 0x16},
114, PSA_AEAD_TAG_LENGTH(PSA_KEY_TYPE_CHACHA20, 256, PSA_ALG_CHACHA20_POLY1305),
{0x1a, 0xe1, 0x0b, 0x59, 0x4f, 0x09, 0xe2, 0x6a, 0x7e, 0x90, 0x2e, 0xcb, 0xd0, 0x60, 0x06, 0x91},
16, PSA_SUCCESS},
#endif

#ifdef ARCH_TEST_XCHACHA20
{"Test psa_aead_finish - XCHACHA20_POLY1305 - 24B Nonce and 12B add data\n",
PSA_KEY_TYPE_XCHACHA20, {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b,
0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b,
0x9c, 0x9d, 0x9e, 0x9f}, 32, PSA_KEY_USAGE_ENCRYPT,
PSA_ALG_XCHACHA20_POLY1305, PSA_ALG_XCHACHA20_POLY1305,
{0x4c, 0x61, 0x64, 0x69, 0x65, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x47, 0x65, 0x6e, 0x74, 0x6c,
0x65, 0x6d, 0x65, 0x6e, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6c, 0x61, 0x73,
0x73, 0x20, 0x6f, 0x66, 0x20, 0x27, 0x39, 0x39, 0x3a, 0x20, 0x49, 0x66, 0x20, 0x49, 0x20, 0x63,
0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6f, 0x66, 0x66, 0x65, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x6f,
0x6e, 0x6c, 0x79, 0x20, 0x6f, 0x6e, 0x65, 0x20, 0x74, 0x69, 0x70, 0x20, 0x66, 0x6f, 0x72, 0x20,
0x74, 0x68, 0x65, 0x20, 0x66, 0x75, 0x74, 0x75, 0x72, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x73,
0x63, 0x72, 0x65, 0x65, 0x6e, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x62, 0x65, 0x20, 0x69,
0x74, 0x2e},
{0x50, 0x51, 0x52, 0x53, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7},
{0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57}, 24, 12, 114, 114, BUFFER_SIZE,
{0xbd, 0x6d, 0x17, 0x9d, 0x3e, 0x83, 0xd4, 0x3b, 0x95, 0x76, 0x57, 0x94, 0x93, 0xc0, 0xe9, 0x39,
0x57, 0x2a, 0x17, 0x00, 0x25, 0x2b, 0xfa, 0xcc, 0xbe, 0xd2, 0x90, 0x2c, 0x21, 0x39, 0x6c, 0xbb,
0x73, 0x1c, 0x7f, 0x1b, 0x0b, 0x4a, 0xa6, 0x44, 0x0b, 0xf3, 0xa8, 0x2f, 0x4e, 0xda, 0x7e, 0x39,
0xae, 0x64, 0xc6, 0x70, 0x8c, 0x54, 0xc2, 0x16, 0xcb, 0x96, 0xb7, 0x2e, 0x12, 0x13, 0xb4, 0x52,
0x2f, 0x8c, 0x9b, 0xa4, 0x0d, 0xb5, 0xd9, 0x45, 0xb1, 0x1b, 0x69, 0xb9, 0x82, 0xc1, 0xbb, 0x9e,
0x3f, 0x3f, 0xac, 0x2b, 0xc3, 0x69, 0x48, 0x8f, 0x76, 0xb2, 0x38, 0x35, 0x65, 0xd3, 0xff, 0xf9,
0x21, 0xf9, 0x66, 0x4c, 0x97, 0x63, 0x7d, 0xa9, 0x76, 0x88, 0x12, 0xf6, 0x15, 0xc6, 0x8b, 0x13,
0xb5, 0x2e}, 114, PSA_AEAD_TAG_LENGTH(PSA_KEY_TYPE_XCHACHA20, 256, PSA_ALG_XCHACHA20_POLY1305),
{0xc0, 0x87, 0x59, 0x24, 0xc1, 0xc7, 0x98, 0x79, 0x47, 0xde, 0xaf, 0xd8, 0x78, 0x0a, 0xcf, 0x49},
16, PSA_SUCCESS},
#endif
};
#endif
