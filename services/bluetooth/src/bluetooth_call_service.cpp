/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bluetooth_call_service.h"

#include "call_manager_errors.h"
#include "telephony_log_wrapper.h"

#include "bluetooth_call_manager.h"

namespace OHOS {
namespace Telephony {
BluetoothCallService::BluetoothCallService()
    : callControlManagerPtr_(DelayedSingleton<CallControlManager>::GetInstance()),
    sendDtmfState_(false), sendDtmfCallId_(ERR_ID)
{}

BluetoothCallService::~BluetoothCallService()
{}

int32_t BluetoothCallService::AnswerCall()
{
    int32_t callId = ERR_ID;
    int32_t ret = AnswerCallPolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("AnswerCallPolicy failed!");
        return ret;
    }
    sptr<CallBase> call = GetOneCallObject(callId);
    if (call == nullptr) {
        TELEPHONY_LOGE("the call object is nullptr, callId:%{public}d", callId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    VideoStateType videoState = call->GetVideoStateType();
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->AnswerCall(callId, static_cast<int32_t>(videoState));
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::RejectCall()
{
    int32_t callId = ERR_ID;
    bool rejectWithMessage = false;
    std::u16string textMessage = Str8ToStr16("");
    int32_t ret = RejectCallPolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("RejectCallPolicy failed!");
        return ret;
    }
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->RejectCall(callId, rejectWithMessage, textMessage);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::HangUpCall()
{
    int32_t callId = ERR_ID;
    int32_t ret = HangUpPolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("HangUpPolicy failed!");
        return ret;
    }
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->HangUpCall(callId);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::GetCallState()
{
    int32_t numActive = GetCallNum(TelCallState::CALL_STATUS_ACTIVE);
    int32_t numHeld = GetCallNum(TelCallState::CALL_STATUS_HOLDING);
    int32_t callState = static_cast<int32_t>(TelCallState::CALL_STATUS_IDLE);
    std::string number = "";
    if (numHeld > 0) {
        callState = static_cast<int32_t>(TelCallState::CALL_STATUS_HOLDING);
        number = GetCallNumber(TelCallState::CALL_STATUS_HOLDING);
    }
    if (numActive > 0) {
        callState = static_cast<int32_t>(TelCallState::CALL_STATUS_ACTIVE);
        number = GetCallNumber(TelCallState::CALL_STATUS_ACTIVE);
    }
    return DelayedSingleton<BluetoothCallManager>::GetInstance()->
        SendBtCallState(numActive, numHeld, callState, number);
}

int32_t BluetoothCallService::HoldCall()
{
    int32_t callId = ERR_ID;
    int32_t ret = HoldCallPolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("HoldCallPolicy failed!");
        return ret;
    }
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->HoldCall(callId);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::UnHoldCall()
{
    int32_t callId = ERR_ID;
    int32_t ret = UnHoldCallPolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("UnHoldCallPolicy failed!");
        return ret;
    }
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->UnHoldCall(callId);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::SwitchCall()
{
    int32_t callId = ERR_ID;
    int32_t ret = SwitchCallPolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("SwitchCallPolicy failed!");
        return ret;
    }
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->SwitchCall(callId);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::StartDtmf(char str)
{
    int32_t callId = ERR_ID;
    int32_t ret = StartDtmfPolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("StartDtmfPolicy failed!");
        return ret;
    }
    if (callControlManagerPtr_ != nullptr) {
        {
            std::lock_guard<std::mutex> guard(lock_);
            sendDtmfState_ = true;
            sendDtmfCallId_ = callId;
        }
        return callControlManagerPtr_->StartDtmf(callId, str);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::StopDtmf()
{
    int32_t callId = ERR_ID;
    if (callControlManagerPtr_ != nullptr) {
        {
            std::lock_guard<std::mutex> guard(lock_);
            callId = sendDtmfCallId_;
            sendDtmfState_ = false;
            sendDtmfCallId_ = ERR_ID;
        }
        return callControlManagerPtr_->StopDtmf(callId);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::CombineConference()
{
    int32_t callId = ERR_ID;
    int32_t ret = CombineConferencePolicy(callId);
    if (ret != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("CombineConferencePolicy failed!");
        return ret;
    }
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->CombineConference(callId);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t BluetoothCallService::SeparateConference()
{
    int32_t callId = ERR_ID;
    if (callControlManagerPtr_ != nullptr) {
        return callControlManagerPtr_->SeparateConference(callId);
    } else {
        TELEPHONY_LOGE("callControlManagerPtr_ is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

std::vector<CallAttributeInfo> BluetoothCallService::GetCurrentCallList(int32_t slotId)
{
    return GetCallInfoList(slotId);
}
} // namespace Telephony
} // namespace OHOS
