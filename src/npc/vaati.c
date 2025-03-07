#include "global.h"
#include "entity.h"
#include "script.h"
#include "sound.h"
#include "functions.h"

extern void sub_08095CB0(Entity*);
extern void CreateRepeatedSoundManager(Entity*);
extern void DeleteRepeatedSoundManager(Entity*);
extern void CreateVaatiApparateManager(Entity*, u32);

void VaatiAction0(Entity*);
void VaatiAction1(Entity*);
void sub_08066B74(Entity*, ScriptExecutionContext*);

void (*const vaatiActions[])(Entity*) = { VaatiAction0, VaatiAction1 };

void Vaati(Entity* this) {
    vaatiActions[this->action](this);
    this->palette.b.b0 = this->palette.b.b4 + (this->frameSpriteSettings & 1);
}

void VaatiAction0(Entity* this) {
    this->action = 1;
    this->subAction = 0;
    this->spriteSettings.draw = 1;
    this->field_0x68.HALF.LO = 0;
    this->field_0x68.HALF.HI = 0;
    SetDefaultPriority(this, PRIO_MESSAGE);
    sub_0807DD64(this);
    VaatiAction1(this);
}

void VaatiAction1(Entity* this) {
    ScriptExecutionContext* tmp;
    sub_0807DD94(this, sub_08066B74);
    if ((*(s8*)&this->field_0x68.HALF.HI != 0) && ((gRoomTransition.frameCount & 3) == 0)) {
        sub_08095CB0(this);
    }

    if ((this->frame & ~0x80) != 0) {
        switch (this->frame & ~0x80u) {
            case 1:
                EnqueueSFX(SFX_21C);
                break;
            case 2:
                EnqueueSFX(SFX_21E);
                break;
            case 3:
                tmp = (*(ScriptExecutionContext**)&this->cutsceneBeh);
                tmp->intVariable = 4;
                CreateRepeatedSoundManager(this);
                break;
            case 4:
                tmp = (*(ScriptExecutionContext**)&this->cutsceneBeh);
                tmp->intVariable = 4;
                DeleteRepeatedSoundManager(this);
                EnqueueSFX(SFX_21D);
                break;
        }
        this->frame &= ~0x80;
    }
}

void sub_08066B74(Entity* this, ScriptExecutionContext* context) {
    u8 animationState;
    u32 currentAction;
    u32 actions;

    actions = context->postScriptActions & 0xfff00000;
    context->postScriptActions = context->postScriptActions & 0xfffff;
    if (actions != 0) {
        do {
            currentAction = (~actions + 1) & actions;
            actions = actions ^ currentAction;
            animationState = this->animationState >> 1;

            switch (currentAction) {
                case 1 << 20:
                    this->field_0x80.HWORD = animationState + 0x10;
                    break;
                case 1 << 21:
                    this->field_0x80.HWORD = animationState + 0x14;
                    break;
                case 1 << 22:
                    this->field_0x80.HWORD = animationState + 0x18;
                    break;
                case 1 << 23:
                    this->field_0x80.HWORD = animationState + 0x1c;
                    break;
                case 1 << 24:
                    this->field_0x80.HWORD = animationState + 0x20;
                    break;
                case 1 << 25:
                    this->field_0x80.HWORD = animationState + 0x24;
                    break;
                case 1 << 26:
                    this->field_0x80.HWORD = animationState + 0x28;
                    break;
                case 1 << 27:
                    this->field_0x80.HWORD = animationState + 0x2c;
                    break;
                case 1 << 28:
                    this->field_0x80.HWORD = animationState + 0x30;
                    break;
                case 1 << 29:
                    this->field_0x68.HALF.LO = 1;
                    break;
                case 1 << 30:
                    this->field_0x68.HALF.LO = 0xff;
                    break;
                case 1 << 31:
                    this->field_0x68.HALF.HI ^= 1;
                    break;
            }
        } while (actions != 0);
    }
    HandlePostScriptActions(this, *(ScriptExecutionContext**)&this->cutsceneBeh);
}

void Vaati_Apparate(Entity* this) {
    CreateVaatiApparateManager(this, 0);
    SoundReq(SFX_APPARATE);
}

void Vaati_Evaporate(Entity* this) {
    CreateVaatiApparateManager(this, 1);
    SoundReq(SFX_EVAPORATE);
}
