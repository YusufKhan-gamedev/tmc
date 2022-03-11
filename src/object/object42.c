/**
 * @file object42.c
 * @ingroup Objects
 *
 * @brief Object42 object
 */

#define NENT_DEPRECATED
#include "global.h"
#include "object.h"
#include "functions.h"

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unk_68[4];
    /*0x6c*/ u16 unk_6c;
} Object42Entity;

void sub_0808DDB4(Object42Entity*);
void sub_0808DDE0(Object42Entity*);
void sub_0808DDE8(Object42Entity*);

void Object42(Object42Entity* this) {
    static void (*const gUnk_081217A8[])(Object42Entity*) = {
        sub_0808DDB4,
        sub_0808DDE0,
    };
    static void (*const gUnk_081217B0[])(Object42Entity*) = {
        sub_0808DDB4,
        sub_0808DDE8,
    };
    if (super->type != 0) {
        gUnk_081217B0[super->action](this);
    } else {
        gUnk_081217A8[super->action](this);
    }
}

void sub_0808DDB4(Object42Entity* this) {
    super->action = 1;
    if (super->type != 0) {
        super->actionDelay = 0x78;
        this->unk_6c = 0xf0;
        InitializeAnimation(super, 0);
        sub_0808DDE8(this);
    }
}

void sub_0808DDE0(Object42Entity* this) {
    DeleteThisEntity();
}

void sub_0808DDE8(Object42Entity* this) {
    static const s8 gUnk_081217B8[] = { 0, -6, 0, 6 };
    Entity* player;
    this->unk_6c--;
    if (sub_0807953C()) {
        super->field_0xf++;
    }
    if (((0x1e < super->field_0xf) || ((gPlayerState.flags & 0x1810) != 0)) || (this->unk_6c == 0)) {
        gPlayerState.flags &= 0xfffffbff;
        DeleteThisEntity();
    }
    player = &gPlayerEntity;
    super->x.HALF.HI = (s8)gUnk_081217B8[gPlayerEntity.animationState >> 1] + player->x.HALF.HI;
    super->y.HALF.HI = gPlayerEntity.y.HALF.HI + -6;
    super->z = gPlayerEntity.z;
    super->collisionLayer = gPlayerEntity.collisionLayer;
    super->spriteRendering.b3 = gPlayerEntity.spriteRendering.b3;
    super->spriteOrientation.flipY = gPlayerEntity.spriteOrientation.flipY;
    if ((gPlayerState.flags & 0x400) != 0) {
        GetNextFrame(super);
    } else {
        DeleteThisEntity();
    }
    if (gPlayerEntity.animationState >> 1 == 2) {
        sub_0806FEBC(&gPlayerEntity, 3, super);
        super->y.HALF.HI -= 5;
    } else {
        sub_0806FEBC(&gPlayerEntity, 0, super);
    }
}
