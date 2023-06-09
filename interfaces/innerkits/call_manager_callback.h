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

#ifndef CALL_MANAGER_CALLBACK_H
#define CALL_MANAGER_CALLBACK_H

#include <cstdio>

#include "call_manager_inner_type.h"

namespace OHOS {
namespace Telephony {
class CallManagerCallback {
public:
    CallManagerCallback() {}
    virtual ~CallManagerCallback() {}

    virtual int32_t OnCallDetailsChange(const CallAttributeInfo &info) = 0;
    virtual int32_t OnCallEventChange(const CallEventInfo &info) = 0;
    virtual int32_t OnCallDisconnectedCause(DisconnectedDetails cause) = 0;
    virtual int32_t OnReportAsyncResults(CallResultReportId reportId, AppExecFwk::PacMap &resultInfo) = 0;
    virtual int32_t OnOttCallRequest(OttCallRequestId requestId, AppExecFwk::PacMap &info) = 0;
};
} // namespace Telephony
} // namespace OHOS
#endif // CALL_MANAGER_CALLBACK_H
