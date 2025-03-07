#include "sound.h"
#include "entity.h"
#include "script.h"
#include "functions.h"
#include "flags.h"
#include "effects.h"
#include "npc.h"

static const Hitbox gUnk_08110E94;

typedef struct {
    s8 x;
    s8 y;
} PACKED PosOffset;

void sub_080673C0(Entity*);
void sub_080673F4(Entity*);
void sub_08067410(Entity*);
void sub_0806752C(Entity*);
void sub_08067418(Entity*);
void sub_08067514(Entity*);

void CastorWildsStatue(Entity* this) {
    static void (*const actionFuncs[])(Entity*) = {
        sub_080673C0,
        sub_080673F4,
        sub_08067410,
        sub_0806752C,
    };
    static void (*const scriptedActionFuncs[])(Entity*) = {
        sub_08067418,
        sub_08067514,
    };
    if ((this->flags & ENT_SCRIPTED) != 0) {
        scriptedActionFuncs[this->action](this);
    } else {
        actionFuncs[this->action](this);
        sub_0806ED78(this);
    }
}

void sub_080673C0(Entity* this) {
    if (gRoomTransition.entity_update_type != 0) {
        this->action = 3;
    } else {
        this->action = 1;
    }
    this->frameIndex = this->type & 1;
    if ((this->type & 1) == 0) {
        this->hitbox = (Hitbox*)&gUnk_08110E94;
    }
}

void sub_080673F4(Entity* this) {
    if (this->interactType != 0) {
        this->action = 2;
        this->interactType = 0;
    }
}

void sub_08067410(Entity* this) {
    this->action = 1;
}

void sub_08067418(Entity* this) {
    this->action = 1;
    this->field_0x74.HWORD = COORD_TO_TILE(this);
    if (this->type == 0) {
        this->hitbox = (Hitbox*)&gUnk_08110E94;
        SetTile(0x4022, this->field_0x74.HWORD - 1, this->collisionLayer);
        SetTile(0x4022, this->field_0x74.HWORD, this->collisionLayer);
        SetTile(0x4022, this->field_0x74.HWORD + 0x3f, this->collisionLayer);
        SetTile(0x4022, this->field_0x74.HWORD + 0x40, this->collisionLayer);
    } else {
        this->collisionLayer = 3;
        this->spriteOrientation.flipY = 1;
        this->spriteRendering.b3 = 1;
        this->spritePriority.b0 = 2;
        if (CheckLocalFlag(HIKYOU_00_SEKIZOU) == 0) {
            SetTile(0x4022, 0xe81, 1);
            SetTile(0x4022, 0xe82, 1);
            SetTile(0x4022, 0xe83, 1);
            SetTile(0x4022, 0xec3, 1);
        }
    }
    sub_0807DD50(this);
}

void sub_08067514(Entity* this) {
    sub_0807DD94(this, NULL);
    if (this->type == 0) {
        sub_0806ED78(this);
    }
}

void sub_0806752C(Entity* this) {
    sub_0806FD3C(this);
}

void sub_08067534(Entity* this) {
    static const s8 gUnk_08110E64[] = { -8, 8, 0, 0 };
    Entity* entity;
    s32 i;
    for (i = 0; i < 2; ++i) {
        entity = CreateFx(this, FX_DEATH, 0);
        if (entity != NULL) {
            entity->x.HALF.HI += gUnk_08110E64[i];
            entity->y.HALF.HI += 0x1c;
        }
    }
    EnqueueSFX(SFX_14C);
    InitScreenShake(40, 4);
}

void sub_0806757C(Entity* this) {
    static const u32 gUnk_08110E68[] = { 0xc8, 0xc9, 0xca, 0xc8 };
    if (this->subAction != 0) {
        if (this->subAction >= 3) {
            RestorePrevTileEntity(0xe81, 1);
            RestorePrevTileEntity(0xe82, 1);
            RestorePrevTileEntity(0xe83, 1);
            RestorePrevTileEntity(0xec3, 1);
        } else {
            LoadFixedGFX(this, gUnk_08110E68[this->subAction]);
        }
    }
}

void sub_080675D4(Entity* this) {
    static const PosOffset gUnk_08110E78[] = { { 0x0, 0x0 },    { 0x0, -0x10 }, { 0x0, 0x10 },
                                               { -0x10, 0x0 },  { 0x10, 0x0 },  { -0x10, -0x10 },
                                               { -0x10, 0x10 }, { 0x10, 0x10 }, { 0x10, -0x10 } };
    static const PosOffset gUnk_08110E8A[] = {
        { -0xc, -0xc }, { 0xc, -0xc }, { -0xc, 0xc }, { 0xc, 0xc }, { 0x0, 0x0 }
    };
    const PosOffset* gUnk = gUnk_08110E78;
    u32 subAction = (this->subAction << 2) - 0xc;
    s32 i;

    for (i = 0; i < 9; i++, gUnk++) {
        Entity* ent = CreateFx(this, FX_DEATH, 0);
        if (ent != NULL) {
            ent->x.HALF.HI += gUnk->x;
            ent->y.HALF.HI += gUnk->y;
            ent->z.HALF.HI = subAction;
            ent->collisionLayer = this->collisionLayer;
            ent->spriteOrientation.flipY = this->spriteOrientation.flipY;
            ent->spriteRendering.b3 = this->spriteRendering.b3;
            SortEntityAbove(this, ent);
        }
    };
    gUnk = gUnk_08110E8A;
    for (i = 0; i < 4; i++, gUnk++) {
        Entity* ent = CreateFx(this, FX_ROCK, 0);
        if (ent != NULL) {
            ent->x.HALF.HI = gUnk->x + ent->x.HALF.HI;
            ent->y.HALF.HI = gUnk->y + ent->y.HALF.HI;
            ent->z.HALF.HI = subAction;
            ent->collisionLayer = this->collisionLayer;
            ent->spriteOrientation.flipY = this->spriteOrientation.flipY;
            ent->spriteRendering.b3 = this->spriteRendering.b3;
            SortEntityAbove(this, ent);
        }
    };
    if (this->subAction > 2) {
        this->spriteSettings.draw = 0;
    }
}

static const Hitbox gUnk_08110E94 = { 0, 3, { 5, 3, 3, 5 }, 12, 20 };

void sub_080676D8(Entity* this) {
    this->subAction++;
}

void sub_080676E0(Entity* this, ScriptExecutionContext* context) {
    switch (context->unk_18) {
        case 0: {
            context->unk_18 = 1;
            context->unk_19 = 0x20;
            break;
        }
        case 1: {
            this->z.HALF.HI = (context->unk_19 >> 1) - 0x10;
            if (--context->unk_19 == 0) {
                context->unk_18 = 2;
                context->unk_19 = 0x24;
            }

            break;
        }
        case 2: {
            if (--context->unk_19 == 0) {
                context->unk_18 = 3;
            }
            break;
        }
        default: {
            if (GravityUpdate(this, Q_8_8(24.0)) == 0) {
                return;
            }
            break;
        }
    }

    gActiveScriptInfo.commandSize = 0;
}

void CastorWildsStatue_Fusion(Entity* this) {
    if (this->action == 0) {
        this->action++;
        this->spriteSettings.draw = 1;
        this->y.HALF.HI -= 0x18;
        InitializeAnimation(this, 1);
        ChangeObjPalette(this, 0x17b);
    } else {
        GetNextFrame(this);
    }
}
