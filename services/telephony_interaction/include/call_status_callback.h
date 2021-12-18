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

#ifndef CALL_STATUS_CALLBACK_H
#define CALL_STATUS_CALLBACK_H

#include "ipc_types.h"

#include "call_status_manager.h"
#include "call_status_callback_stub.h"

namespace OHOS {
namespace Telephony {
class CallStatusCallback : public CallStatusCallbackStub {
public:
    explicit CallStatusCallback();
    ~CallStatusCallback();

    int32_t UpdateCallReportInfo(const CallReportInfo &info) override;
    int32_t UpdateCallsReportInfo(const CallsReportInfo &info) override;
    int32_t UpdateDisconnectedCause(const DisconnectedDetails &cause) override;
    int32_t UpdateEventResultInfo(const CellularCallEventInfo &info) override;
    int32_t UpdateGetWaitingResult(const CallWaitResponse &response) override;
    int32_t UpdateSetWaitingResult(int32_t result) override;
    int32_t UpdateGetRestrictionResult(const CallRestrictionResponse &result) override;
    int32_t UpdateSetRestrictionResult(int32_t result) override;
    int32_t UpdateGetTransferResult(const CallTransferResponse &response) override;
    int32_t UpdateSetTransferResult(int32_t result) override;
    int32_t UpdateGetCallClipResult(const ClipResponse &clipResponse) override;
    int32_t UpdateGetCallClirResult(const ClirResponse &clirResponse) override;
    int32_t UpdateSetCallClirResult(int32_t result) override;
};
} // namespace Telephony
} // namespace OHOS

#endif
