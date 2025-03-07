#include "entity.h"
#include "sound.h"
#include "functions.h"
#include "common.h"
#include "message.h"
#include "save.h"
#include "structures.h"

void PlayerItemPacciCane_Action1(Entity*);
void PlayerItemPacciCane_Init(Entity* this);

void PlayerItemPacciCane(Entity* this) {
    static void (*const PlayerItemPacciCane_Actions[])(Entity*) = {
        PlayerItemPacciCane_Init,
        PlayerItemPacciCane_Action1,
    };
    PlayerItemPacciCane_Actions[this->action](this);
}

void PlayerItemPacciCane_Init(Entity* this) {
    this->action = 1;
    this->frameIndex = -1;
    LoadSwapGFX(this, 1, 3);
    SoundReq(SFX_10E);
    PlayerItemPacciCane_Action1(this);
}

void PlayerItemPacciCane_Action1(Entity* this) {
    u32 playerFrame;
    u32 frameIndex;
    u32 flipX;
    if (((gPlayerEntity.frame & ANIM_DONE) != 0) || (this != gPlayerState.item)) {
        if (this == gPlayerState.item) {
            gPlayerState.item = NULL;
        }
        DeleteEntity(this);
    } else {
        playerFrame = gPlayerEntity.frame & 0xf;
        if (playerFrame != 0xf) {
            frameIndex = gPlayerEntity.frameIndex;
            playerFrame += 0x91;
            if (frameIndex - playerFrame != this->frameIndex) {
                this->frameIndex = frameIndex + 0x6f;
                sub_080042D0(this, this->frameIndex, this->spriteIndex);
            }
            sub_08078E84(this, &gPlayerEntity);
        } else {
            this->frameIndex = -1;
        }
    }

    if ((gPlayerEntity.animationState & 2)) {
        flipX = gPlayerEntity.spriteSettings.flipX ^ 1;
    } else {
        flipX = gPlayerEntity.spriteSettings.flipX;
    }
    this->spriteSettings.flipX = flipX;
}

// TODO This name sounds like this does not belong in this file
void ClearMenuSavestate(void) {
    MemClear(&gPauseMenuOptions, sizeof(gPauseMenuOptions));
}
