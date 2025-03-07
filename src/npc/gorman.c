#include "functions.h"
#include "npc.h"

void sub_080697A4(Entity* this);
void sub_08069838(Entity* this);
void sub_08069888(Entity* this);

const SpriteLoadData gUnk_08111C3C[] = {
    { 193, 64, 4 },
    { 5313, 64, 4 },
    { 0, 0, 0 },
};
void sub_080697C4(Entity*);
void sub_080697EC(Entity*);
void (*const gUnk_08111C48[])(Entity*) = {
    sub_080697C4,
    sub_080697EC,
};
const u16 gUnk_08111C50[] = {
    TEXT_INDEX(TEXT_GORMAN_ORACLES, 0x1), TEXT_INDEX(TEXT_GORMAN_ORACLES, 0x2), TEXT_INDEX(TEXT_GORMAN_ORACLES, 0xc),
    TEXT_INDEX(TEXT_GORMAN_ORACLES, 0xd), TEXT_INDEX(TEXT_GORMAN_ORACLES, 0xe), TEXT_INDEX(TEXT_GORMAN_ORACLES, 0x15),
};
const Coords gUnk_08111C5C[] = {
    { .HALF = { 0x68, 0x1c8 } }, { .HALF = { 0x28, 0x1c8 } }, { .HALF = { 0x68, 0x188 } },
    { .HALF = { 0x68, 0x1c8 } }, { .HALF = { 0x28, 0x188 } }, { .HALF = { 0x68, 0x188 } }
};
const u8 gUnk_08111C74[] = {
    0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 0,
};
const Coords gUnk_08111C84[] = {
    { .HALF = { 0x178, 0x108 } },
    { .HALF = { 0x138, 0x108 } },
};
const u8 gUnk_08111C8C[] = {
    0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 0,
};
const u8 gUnk_08111C9C[] = {
    0, 1, 0, 1, 2, 3, 2, 3, 4, 5, 4, 5,
};
const u8 gUnk_08111CA8[] = {
    1, 2, 0, 0, 3, 4, 1, 2, 5, 5, 3, 4,
};
const u8 gUnk_08111CB4[] = {
    0,
    1,
    0,
    1,
};
const u8 gUnk_08111CB8[] = {
    1,
    1,
    0,
    0,
};

void Gorman(Entity* this) {
    if ((this->flags & ENT_SCRIPTED) != 0) {
        sub_08069838(this);
    } else {
        sub_080697A4(this);
    }
}

void sub_080697A4(Entity* this) {
    gUnk_08111C48[this->action](this);
    sub_0806ED78(this);
}

void sub_080697C4(Entity* this) {
    if (LoadExtraSpriteData(this, gUnk_08111C3C)) {
        this->action = 1;
        InitializeAnimation(this, 2);
        AddInteractableWhenBigObject(this);
    }
}

void sub_080697EC(Entity* this) {
    s32 tmp;

    tmp = GetAnimationStateInRectRadius(this, 0x20, 0x20);
    if (tmp >= 0) {
        if (this->subtimer == 0) {
            this->subtimer = 16;
            if (this->animIndex != tmp) {
                InitializeAnimation(this, tmp);
            }
        } else {
            this->subtimer--;
        }
    }
    if (this->interactType != 0) {
        this->interactType = 0;
        sub_08069888(this);
    }
}

void sub_08069838(Entity* this) {
    if (this->action == 0) {
        if (!LoadExtraSpriteData(this, gUnk_08111C3C)) {
            return;
        }
        this->action++;
        this->field_0x68.HALF.LO = 0;
        this->field_0x68.HALF.HI = 0;
        sub_0807DD64(this);
    }
    sub_0807DD94(this, NULL);
    if (this->interactType != 0) {
        this->interactType = 0;
        sub_08069888(this);
    }
}

void sub_08069888(Entity* this) {
    s32 index;
    if (CheckGlobalFlag(GOMAN_RENTED_HOUSE) == 0) {
        index = 0;
        SetGlobalFlag(GOMAN_RENTED_HOUSE);
    } else if (((CheckGlobalFlag(RENTED_HOUSE_DIN) == 0) && (CheckGlobalFlag(RENTED_HOUSE_NAYRU) == 0)) &&
               (CheckGlobalFlag(RENTED_HOUSE_FARORE) == 0)) {
        index = 1;
    } else if (CheckGlobalFlag(TATEKAKE_HOUSE) == 0) {
        index = 2;
    } else if (CheckGlobalFlag(GOMAN_NEW_HOUSE) == 0) {
        index = 3;
        SetGlobalFlag(GOMAN_NEW_HOUSE);
    } else if ((CheckGlobalFlag(NEW_HOUSE_DIN) == 0) && (CheckGlobalFlag(NEW_HOUSE_NAYRU) == 0)) {
        index = CheckGlobalFlag(NEW_HOUSE_FARORE) ? 5 : 4;
    } else {
        index = 5;
    }
    MessageNoOverlap(gUnk_08111C50[index], this);
}

void sub_0806991C(Entity* this, ScriptExecutionContext* context) {
    u32 tmp;
    const Coords* ptr;
    this->field_0x68.HALF.LO = (Random() & 0x1f) + 0x3c;
    ptr = &gUnk_08111C5C[*(s8*)&this->field_0x68.HALF.HI];
    context->x.HALF.HI = gRoomControls.origin_x + ptr->HALF.x;
    context->y.HALF.HI = gRoomControls.origin_y + ptr->HALF.y;
    context->unk_19 = 8;
    context->postScriptActions |= 2;
    context->condition = 0;
    tmp = sub_080045DA(context->x.HALF.HI - this->x.HALF.HI, context->y.HALF.HI - this->y.HALF.HI);
    this->direction = tmp;
    this->animationState = (this->animationState & 0x80) | gUnk_08111C74[(tmp << 0x18) >> 0x1c];
    gActiveScriptInfo.flags |= 1;
}

void sub_080699AC(Entity* this, ScriptExecutionContext* context) {
    u32 tmp;
    const Coords* ptr;
    this->field_0x68.HALF.LO = (Random() & 0x1f) + 0x3c;
    ptr = &gUnk_08111C84[*(s8*)&this->field_0x68.HALF.HI];
    context->x.HALF.HI = gRoomControls.origin_x + ptr->HALF.x;
    context->y.HALF.HI = gRoomControls.origin_y + ptr->HALF.y;
    context->unk_19 = 8;
    context->postScriptActions |= 2;
    context->condition = 0;
    tmp = sub_080045DA(context->x.HALF.HI - this->x.HALF.HI, context->y.HALF.HI - this->y.HALF.HI);
    this->direction = tmp;
    this->animationState = (this->animationState & 0x80) | gUnk_08111C8C[(tmp << 0x18) >> 0x1c];
    gActiveScriptInfo.flags |= 1;
}

void sub_08069A3C(Entity* this) {
    this->field_0x68.HALF.HI = gUnk_08111C9C[(Random() & 1) + (s8)this->field_0x68.HALF.HI * 2];
}

void sub_08069A60(Entity* this) {
    this->field_0x68.HALF.HI = gUnk_08111CA8[(Random() & 1) + (s8)this->field_0x68.HALF.HI * 2];
}

void sub_08069A84(Entity* this) {
    this->field_0x68.HALF.HI = gUnk_08111CB4[(Random() & 1) + (s8)this->field_0x68.HALF.HI * 2];
}

void sub_08069AA8(Entity* this) {
    this->field_0x68.HALF.HI = gUnk_08111CB8[(Random() & 1) + (s8)this->field_0x68.HALF.HI * 2];
}

void sub_08069ACC(Entity* this, ScriptExecutionContext* context) {
    if (--this->field_0x68.HALF.LO * 0x1000000 < 1) {
        context->condition = 1;
    } else {
        context->condition = 0;
    }
}

void Gorman_Head(Entity* this) {
    SetExtraSpriteFrame(this, 0, (this->frame & 7) + 0xf);
    SetExtraSpriteFrame(this, 1, this->frameIndex);
    SetSpriteSubEntryOffsetData1(this, 1, 0);
    sub_0807000C(this);
}
