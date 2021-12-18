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

#include "hang_up_sms.h"

#include "call_manager_errors.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
HangUpSms::HangUpSms() : msgManager_(std::make_unique<ShortMessageManager>()) {}

void HangUpSms::IncomingCallHungUp(sptr<CallBase> &callObjectPtr, bool isSendSms, std::string content)
{
    if (callObjectPtr == nullptr || !isSendSms || content.empty() || callObjectPtr->GetAccountNumber().empty()) {
        TELEPHONY_LOGE("incoming data is nullptr!");
        return;
    }
    std::string number = callObjectPtr->GetAccountNumber();
    SendMessage(callObjectPtr->GetSlotId(), ConvertToUtf16(number), ConvertToUtf16(content));
    TELEPHONY_LOGI("send rejectCall message");
}

void HangUpSms::SendMessage(int32_t slotId, const std::u16string &desAddr, const std::u16string &text)
{
    if (msgManager_ == nullptr) {
        TELEPHONY_LOGE("short message manager nullptr");
        return;
    }
    msgManager_->SendMessage(slotId, desAddr, ConvertToUtf16(""), text, nullptr, nullptr);
}

std::u16string HangUpSms::ConvertToUtf16(const std::string &str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    return converter.from_bytes(str);
}

void HangUpSms::NewCallCreated(sptr<CallBase> &callObjectPtr) {}

void HangUpSms::CallDestroyed(sptr<CallBase> &callObjectPtr) {}

void HangUpSms::IncomingCallActivated(sptr<CallBase> &callObjectPtr) {}

void HangUpSms::CallStateUpdated(sptr<CallBase> &callObjectPtr, TelCallState priorState, TelCallState nextState) {}
} // namespace Telephony
} // namespace OHOS