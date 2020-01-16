/* ec.h
 *
 * Copyright (C) 2006-2019 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* ec.h for openssl */

#ifndef WOLFSSL_EC_H_
#define WOLFSSL_EC_H_

#include <wolfssl/openssl/bn.h>
#include <wolfssl/wolfcrypt/ecc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Map OpenSSL NID value */
enum {
    POINT_CONVERSION_COMPRESSED = 2,
    POINT_CONVERSION_UNCOMPRESSED = 4,

#ifdef HAVE_ECC
    /* Use ecc_curve_type enum values for NID */
    NID_X9_62_prime192v1 = ECC_SECP192R1,
    NID_X9_62_prime256v1 = ECC_SECP256R1,
    NID_secp112r1 = ECC_SECP112R1,
    NID_secp112r2 = ECC_SECP112R2,
    NID_secp128r1 = ECC_SECP128R1,
    NID_secp128r2 = ECC_SECP128R2,
    NID_secp160r1 = ECC_SECP160R1,
    NID_secp160r2 = ECC_SECP160R2,
    NID_secp224r1 = ECC_SECP224R1,
    NID_secp384r1 = ECC_SECP384R1,
    NID_secp521r1 = ECC_SECP521R1,
    NID_secp160k1 = ECC_SECP160K1,
    NID_secp192k1 = ECC_SECP192K1,
    NID_secp224k1 = ECC_SECP224K1,
    NID_secp256k1 = ECC_SECP256K1,
    NID_brainpoolP160r1 = ECC_BRAINPOOLP160R1,
    NID_brainpoolP192r1 = ECC_BRAINPOOLP192R1,
    NID_brainpoolP224r1 = ECC_BRAINPOOLP224R1,
    NID_brainpoolP256r1 = ECC_BRAINPOOLP256R1,
    NID_brainpoolP320r1 = ECC_BRAINPOOLP320R1,
    NID_brainpoolP384r1 = ECC_BRAINPOOLP384R1,
    NID_brainpoolP512r1 = ECC_BRAINPOOLP512R1,
#endif

    OPENSSL_EC_NAMED_CURVE  = 0x001
};

#ifndef WOLFSSL_EC_TYPE_DEFINED /* guard on redeclaration */
typedef struct WOLFSSL_EC_KEY         WOLFSSL_EC_KEY;
typedef struct WOLFSSL_EC_POINT       WOLFSSL_EC_POINT;
typedef struct WOLFSSL_EC_GROUP       WOLFSSL_EC_GROUP;
#define WOLFSSL_EC_TYPE_DEFINED
#endif

typedef WOLFSSL_EC_KEY                EC_KEY;
typedef WOLFSSL_EC_GROUP              EC_GROUP;
typedef WOLFSSL_EC_POINT              EC_POINT;

struct WOLFSSL_EC_POINT {
    WOLFSSL_BIGNUM *X;
    WOLFSSL_BIGNUM *Y;
    WOLFSSL_BIGNUM *Z;

    void*          internal;     /* our ECC point */
    char           inSet;        /* internal set from external ? */
    char           exSet;        /* external set from internal ? */
};

struct WOLFSSL_EC_GROUP {
    int curve_idx; /* index of curve, used by WolfSSL as reference */
    int curve_nid; /* NID of curve, used by OpenSSL/OpenSSH as reference */
    int curve_oid; /* OID of curve, used by OpenSSL/OpenSSH as reference */
};

struct WOLFSSL_EC_KEY {
    WOLFSSL_EC_GROUP *group;
    WOLFSSL_EC_POINT *pub_key;
    WOLFSSL_BIGNUM *priv_key;

    void*          internal;     /* our ECC Key */
    char           inSet;        /* internal set from external ? */
    char           exSet;        /* external set from internal ? */
};

typedef struct WOLFSSL_EC_builtin_curve{
    int nid;
    const char *comment;
} WOLFSSL_EC_builtin_curve;

typedef WOLFSSL_EC_builtin_curve      EC_builtin_curve;

#define WOLFSSL_EC_KEY_LOAD_PRIVATE 1
#define WOLFSSL_EC_KEY_LOAD_PUBLIC  2

WOLFSSL_API
int wolfSSL_ECPoint_i2d(const WOLFSSL_EC_GROUP *curve,
                        const WOLFSSL_EC_POINT *p,
                        unsigned char *out, unsigned int *len);
WOLFSSL_API
int wolfSSL_ECPoint_d2i(unsigned char *in, unsigned int len,
                        const WOLFSSL_EC_GROUP *curve, WOLFSSL_EC_POINT *p);
WOLFSSL_API
int wolfSSL_EC_KEY_LoadDer(WOLFSSL_EC_KEY* key,
                           const unsigned char* der, int derSz);
WOLFSSL_API
int wolfSSL_EC_KEY_LoadDer_ex(WOLFSSL_EC_KEY* key,
                              const unsigned char* der, int derSz, int opt);
WOLFSSL_API
void wolfSSL_EC_KEY_free(WOLFSSL_EC_KEY *key);
WOLFSSL_API
WOLFSSL_EC_POINT *wolfSSL_EC_KEY_get0_public_key(const WOLFSSL_EC_KEY *key);
WOLFSSL_API
const WOLFSSL_EC_GROUP *wolfSSL_EC_KEY_get0_group(const WOLFSSL_EC_KEY *key);
WOLFSSL_API
int wolfSSL_EC_KEY_set_private_key(WOLFSSL_EC_KEY *key,
                                   const WOLFSSL_BIGNUM *priv_key);
WOLFSSL_API
WOLFSSL_BIGNUM *wolfSSL_EC_KEY_get0_private_key(const WOLFSSL_EC_KEY *key);
WOLFSSL_API
WOLFSSL_EC_KEY *wolfSSL_EC_KEY_new_by_curve_name(int nid);
WOLFSSL_API const char* wolfSSL_EC_curve_nid2nist(int nid);
WOLFSSL_API
WOLFSSL_EC_KEY *wolfSSL_EC_KEY_new(void);
WOLFSSL_API
int wolfSSL_EC_KEY_set_group(WOLFSSL_EC_KEY *key, WOLFSSL_EC_GROUP *group);
WOLFSSL_API
int wolfSSL_EC_KEY_generate_key(WOLFSSL_EC_KEY *key);
WOLFSSL_API
void wolfSSL_EC_KEY_set_asn1_flag(WOLFSSL_EC_KEY *key, int asn1_flag);
WOLFSSL_API
int wolfSSL_EC_KEY_set_public_key(WOLFSSL_EC_KEY *key,
                                  const WOLFSSL_EC_POINT *pub);
WOLFSSL_API
void wolfSSL_EC_GROUP_set_asn1_flag(WOLFSSL_EC_GROUP *group, int flag);
WOLFSSL_API
WOLFSSL_EC_GROUP *wolfSSL_EC_GROUP_new_by_curve_name(int nid);
WOLFSSL_API
int wolfSSL_EC_GROUP_cmp(const WOLFSSL_EC_GROUP *a, const WOLFSSL_EC_GROUP *b,
                         WOLFSSL_BN_CTX *ctx);
WOLFSSL_API
int wolfSSL_EC_GROUP_get_curve_name(const WOLFSSL_EC_GROUP *group);
WOLFSSL_API
int wolfSSL_EC_GROUP_get_degree(const WOLFSSL_EC_GROUP *group);
WOLFSSL_API
int wolfSSL_EC_GROUP_get_order(const WOLFSSL_EC_GROUP *group,
                               WOLFSSL_BIGNUM *order, WOLFSSL_BN_CTX *ctx);
WOLFSSL_API
int wolfSSL_EC_GROUP_order_bits(const WOLFSSL_EC_GROUP *group);
WOLFSSL_API
void wolfSSL_EC_GROUP_free(WOLFSSL_EC_GROUP *group);
WOLFSSL_API
WOLFSSL_EC_POINT *wolfSSL_EC_POINT_new(const WOLFSSL_EC_GROUP *group);
WOLFSSL_API
int wolfSSL_EC_POINT_get_affine_coordinates_GFp(const WOLFSSL_EC_GROUP *group,
                                                const WOLFSSL_EC_POINT *p,
                                                WOLFSSL_BIGNUM *x,
                                                WOLFSSL_BIGNUM *y,
                                                WOLFSSL_BN_CTX *ctx);
WOLFSSL_API
int wolfSSL_EC_POINT_mul(const WOLFSSL_EC_GROUP *group, WOLFSSL_EC_POINT *r,
                         const WOLFSSL_BIGNUM *n,
                         const WOLFSSL_EC_POINT *q, const WOLFSSL_BIGNUM *m,
                         WOLFSSL_BN_CTX *ctx);
WOLFSSL_API
void wolfSSL_EC_POINT_clear_free(WOLFSSL_EC_POINT *point);
WOLFSSL_API
int wolfSSL_EC_POINT_cmp(const WOLFSSL_EC_GROUP *group,
                         const WOLFSSL_EC_POINT *a, const WOLFSSL_EC_POINT *b,
                         WOLFSSL_BN_CTX *ctx);
WOLFSSL_API
void wolfSSL_EC_POINT_free(WOLFSSL_EC_POINT *point);
WOLFSSL_API
int wolfSSL_EC_POINT_is_at_infinity(const WOLFSSL_EC_GROUP *group,
                                    const WOLFSSL_EC_POINT *a);

WOLFSSL_API
size_t wolfSSL_EC_get_builtin_curves(WOLFSSL_EC_builtin_curve *r, size_t nitems);

#ifndef HAVE_SELFTEST
WOLFSSL_API
char* wolfSSL_EC_POINT_point2hex(const WOLFSSL_EC_GROUP* group,
                                 const WOLFSSL_EC_POINT* point, int form,
                                 WOLFSSL_BN_CTX* ctx);
#endif

#ifndef HAVE_ECC
#define OPENSSL_NO_EC
#endif

#define EC_KEY_new                      wolfSSL_EC_KEY_new
#define EC_KEY_free                     wolfSSL_EC_KEY_free
#define EC_KEY_get0_public_key          wolfSSL_EC_KEY_get0_public_key
#define EC_KEY_get0_group               wolfSSL_EC_KEY_get0_group
#define EC_KEY_set_private_key          wolfSSL_EC_KEY_set_private_key
#define EC_KEY_get0_private_key         wolfSSL_EC_KEY_get0_private_key
#define EC_KEY_new_by_curve_name        wolfSSL_EC_KEY_new_by_curve_name
#define EC_KEY_set_group                wolfSSL_EC_KEY_set_group
#define EC_KEY_generate_key             wolfSSL_EC_KEY_generate_key
#define EC_KEY_set_asn1_flag            wolfSSL_EC_KEY_set_asn1_flag
#define EC_KEY_set_public_key           wolfSSL_EC_KEY_set_public_key

#define EC_GROUP_free                   wolfSSL_EC_GROUP_free
#define EC_GROUP_set_asn1_flag          wolfSSL_EC_GROUP_set_asn1_flag
#define EC_GROUP_new_by_curve_name      wolfSSL_EC_GROUP_new_by_curve_name
#define EC_GROUP_cmp                    wolfSSL_EC_GROUP_cmp
#define EC_GROUP_get_curve_name         wolfSSL_EC_GROUP_get_curve_name
#define EC_GROUP_get_degree             wolfSSL_EC_GROUP_get_degree
#define EC_GROUP_get_order              wolfSSL_EC_GROUP_get_order
#define EC_GROUP_order_bits             wolfSSL_EC_GROUP_order_bits

#define EC_POINT_new                    wolfSSL_EC_POINT_new
#define EC_POINT_free                   wolfSSL_EC_POINT_free
#define EC_POINT_get_affine_coordinates_GFp \
                                     wolfSSL_EC_POINT_get_affine_coordinates_GFp
#define EC_POINT_mul                    wolfSSL_EC_POINT_mul
#define EC_POINT_clear_free             wolfSSL_EC_POINT_clear_free
#define EC_POINT_cmp                    wolfSSL_EC_POINT_cmp
#define EC_POINT_is_at_infinity         wolfSSL_EC_POINT_is_at_infinity

#ifndef HAVE_SELFTEST
    #define EC_POINT_point2hex          wolfSSL_EC_POINT_point2hex
#endif

#define EC_POINT_dump                   wolfSSL_EC_POINT_dump
#define EC_get_builtin_curves           wolfSSL_EC_get_builtin_curves

#define EC_curve_nid2nist               wolfSSL_EC_curve_nid2nist

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* header */
